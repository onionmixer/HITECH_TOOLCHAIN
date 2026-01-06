#!/bin/bash
#
# 02_make_hitechc_library.sh
# Build Hi-Tech C standard libraries (gen, stdio, float)
#

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

echo "========================================"
echo "Building Hi-Tech C Libraries"
echo "========================================"

BIN_DIR="bin"
SRC_DIR="source/hitechc_library"
INC_DIR="include/hitechc"
LIB_DIR="lib/hitechc"
BUILD_DIR="build"

# Check tools exist
for tool in cpp_new3 p1x3 cgen3 optim3 zasx3 libr3; do
    if [ ! -x "$BIN_DIR/$tool" ]; then
        echo "Error: $tool not found in $BIN_DIR"
        exit 1
    fi
done

# Create build directory
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR/inc"
mkdir -p "$BUILD_DIR/gen"
mkdir -p "$BUILD_DIR/stdio"
mkdir -p "$BUILD_DIR/float"

# Copy headers to build directory (short path)
cp "$INC_DIR"/*.h "$BUILD_DIR/inc/"

compile_c() {
    local src="$1"
    local base="$2"
    local build_subdir="$3"

    # Copy source to build directory
    cp "$src" "$BUILD_DIR/$build_subdir/${base}.c"

    cd "$BUILD_DIR/$build_subdir"

    # Pipeline: cpp -> p1x3 -> cgen3 -> optim3 -> zasx3
    "../../$BIN_DIR/cpp_new3" -I../inc -I. "${base}.c" "${base}.i" 2>/dev/null && \
    "../../$BIN_DIR/p1x3" "${base}.i" > "${base}.p1" 2>/dev/null && \
    "../../$BIN_DIR/cgen3" "${base}.p1" "${base}.as" 2>/dev/null && \
    "../../$BIN_DIR/optim3" "${base}.as" "${base}.asm" 2>/dev/null && \
    "../../$BIN_DIR/zasx3" "${base}.asm" 2>/dev/null

    cd "$SCRIPT_DIR"

    [ -f "$BUILD_DIR/$build_subdir/${base}.obj" ]
}

compile_asm() {
    local src="$1"
    local base="$2"
    local build_subdir="$3"

    cp "$src" "$BUILD_DIR/$build_subdir/${base}.asm"

    cd "$BUILD_DIR/$build_subdir"
    "../../$BIN_DIR/zasx3" "${base}.asm" 2>/dev/null
    cd "$SCRIPT_DIR"

    [ -f "$BUILD_DIR/$build_subdir/${base}.obj" ]
}

#############################################
# Gen Library (zlibc.lib)
#############################################
echo ""
echo "--- Building Gen Library (zlibc.lib) ---"

SUCCESS=0
FAIL=0

# C files
for f in "$SRC_DIR/gen"/*.c; do
    [ -f "$f" ] || continue
    base=$(basename "$f" .c)
    if compile_c "$f" "$base" "gen"; then
        SUCCESS=$((SUCCESS + 1))
    else
        echo "FAIL: $base.c"
        FAIL=$((FAIL + 1))
    fi
done

# ASM files
for f in "$SRC_DIR/gen"/*.as; do
    [ -f "$f" ] || continue
    base=$(basename "$f" .as)
    if compile_asm "$f" "$base" "gen"; then
        SUCCESS=$((SUCCESS + 1))
    else
        echo "FAIL: $base.as"
        FAIL=$((FAIL + 1))
    fi
done

echo "Gen: Success=$SUCCESS, Failed=$FAIL"

if [ $SUCCESS -gt 0 ]; then
    cd "$BUILD_DIR/gen"
    "../../$BIN_DIR/libr3" r zlibc.lib *.obj 2>/dev/null
    cp zlibc.lib "../../$LIB_DIR/"
    cd "$SCRIPT_DIR"
    ls -la "$LIB_DIR/zlibc.lib"
fi

#############################################
# Stdio Library (zlibio.lib)
#############################################
echo ""
echo "--- Building Stdio Library (zlibio.lib) ---"

SUCCESS=0
FAIL=0

for f in "$SRC_DIR/stdio"/*.c; do
    [ -f "$f" ] || continue
    base=$(basename "$f" .c)
    if compile_c "$f" "$base" "stdio"; then
        SUCCESS=$((SUCCESS + 1))
    else
        echo "FAIL: $base.c"
        FAIL=$((FAIL + 1))
    fi
done

echo "Stdio: Success=$SUCCESS, Failed=$FAIL"

if [ $SUCCESS -gt 0 ]; then
    cd "$BUILD_DIR/stdio"
    "../../$BIN_DIR/libr3" r zlibio.lib *.obj 2>/dev/null
    cp zlibio.lib "../../$LIB_DIR/"
    cd "$SCRIPT_DIR"
    ls -la "$LIB_DIR/zlibio.lib"
fi

#############################################
# Float Library (zlibf.lib)
#############################################
echo ""
echo "--- Building Float Library (zlibf.lib) ---"

SUCCESS=0
FAIL=0

# C files
for f in "$SRC_DIR/float"/*.c; do
    [ -f "$f" ] || continue
    base=$(basename "$f" .c)
    if compile_c "$f" "$base" "float"; then
        SUCCESS=$((SUCCESS + 1))
    else
        echo "FAIL: $base.c"
        FAIL=$((FAIL + 1))
    fi
done

# ASM files
for f in "$SRC_DIR/float"/*.as; do
    [ -f "$f" ] || continue
    base=$(basename "$f" .as)
    if compile_asm "$f" "$base" "float"; then
        SUCCESS=$((SUCCESS + 1))
    else
        echo "FAIL: $base.as"
        FAIL=$((FAIL + 1))
    fi
done

echo "Float: Success=$SUCCESS, Failed=$FAIL"

if [ $SUCCESS -gt 0 ]; then
    cd "$BUILD_DIR/float"
    "../../$BIN_DIR/libr3" r zlibf.lib *.obj 2>/dev/null
    cp zlibf.lib "../../$LIB_DIR/"
    cd "$SCRIPT_DIR"
    ls -la "$LIB_DIR/zlibf.lib"
fi

#############################################
# Cleanup and Summary
#############################################
echo ""
echo "========================================"
echo "Cleaning up..."
rm -rf "$BUILD_DIR"

echo ""
echo "========================================"
echo "Library Build Summary"
echo "========================================"
echo ""
ls -la "$LIB_DIR"/*.lib 2>/dev/null || echo "No libraries built"
