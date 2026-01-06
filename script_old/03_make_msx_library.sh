#!/bin/bash
#
# 03_make_msx_library.sh
# Build MSX-specific libraries and CRT startup files
#

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

echo "========================================"
echo "Building MSX Libraries"
echo "========================================"

BIN_DIR="bin"
SRC_DIR="source/msx"
LIB_DIR="lib/msx"
BUILD_DIR="build/msx"

# Check tools exist
if [ ! -x "$BIN_DIR/zasx3" ]; then
    echo "Error: zasx3 not found in $BIN_DIR"
    exit 1
fi

if [ ! -x "$BIN_DIR/libr3" ]; then
    echo "Error: libr3 not found in $BIN_DIR"
    exit 1
fi

# Create build directory
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

compile_asm() {
    local src="$1"
    local base="$2"

    cp "$src" "$BUILD_DIR/${base}.asm"

    cd "$BUILD_DIR"
    "../../$BIN_DIR/zasx3" "${base}.asm" 2>/dev/null
    cd "$SCRIPT_DIR"

    [ -f "$BUILD_DIR/${base}.obj" ]
}

#############################################
# MSX Library (zlibmsx.lib)
#############################################
echo ""
echo "--- Building MSX Library (zlibmsx.lib) ---"

SUCCESS=0
FAIL=0

for dir in bios dos psg slot vdp; do
    for f in "$SRC_DIR/$dir"/*.as; do
        [ -f "$f" ] || continue
        base=$(basename "$f" .as)
        if compile_asm "$f" "$base"; then
            SUCCESS=$((SUCCESS + 1))
        else
            echo "FAIL: $dir/$base.as"
            FAIL=$((FAIL + 1))
        fi
    done
done

echo "MSX Library: Success=$SUCCESS, Failed=$FAIL"

if [ $SUCCESS -gt 0 ]; then
    cd "$BUILD_DIR"
    "../../$BIN_DIR/libr3" r zlibmsx.lib *.obj 2>/dev/null
    cp zlibmsx.lib "../../$LIB_DIR/"
    cd "$SCRIPT_DIR"
    ls -la "$LIB_DIR/zlibmsx.lib"
fi

#############################################
# CRT Startup Files
#############################################
echo ""
echo "--- Building CRT Startup Files ---"

# Clean build directory for CRT
rm -f "$BUILD_DIR"/*.obj "$BUILD_DIR"/*.asm

SUCCESS=0
FAIL=0

for f in "$SRC_DIR/crt"/*.as; do
    [ -f "$f" ] || continue
    base=$(basename "$f" .as)
    if compile_asm "$f" "$base"; then
        SUCCESS=$((SUCCESS + 1))
        cp "$BUILD_DIR/${base}.obj" "$LIB_DIR/"
        ls -la "$LIB_DIR/${base}.obj"
    else
        echo "FAIL: $base.as"
        FAIL=$((FAIL + 1))
    fi
done

echo "CRT Files: Success=$SUCCESS, Failed=$FAIL"

#############################################
# Cleanup and Summary
#############################################
echo ""
echo "========================================"
echo "Cleaning up..."
rm -rf "build"

echo ""
echo "========================================"
echo "MSX Build Summary"
echo "========================================"
echo ""
echo "Library:"
ls -la "$LIB_DIR"/*.lib 2>/dev/null || echo "No library built"
echo ""
echo "CRT Files:"
ls -la "$LIB_DIR"/*.obj 2>/dev/null || echo "No CRT files built"
