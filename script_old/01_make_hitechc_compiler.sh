#!/bin/bash
#
# 01_make_hitechc_compiler.sh
# Build Hi-Tech C p1x3 compiler (C parser) from source
#

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

echo "========================================"
echo "Building Hi-Tech C Compiler (p1x3)"
echo "========================================"

SRC_DIR="source/hitechc"
BIN_DIR="bin"

# Check source files exist
if [ ! -f "$SRC_DIR/main.c" ]; then
    echo "Error: Source files not found in $SRC_DIR"
    exit 1
fi

# Build p1x3
echo "Compiling p1x3..."
gcc -o "$BIN_DIR/p1x3" \
    "$SRC_DIR/cclass.c" \
    "$SRC_DIR/emit.c" \
    "$SRC_DIR/expr.c" \
    "$SRC_DIR/lex.c" \
    "$SRC_DIR/main.c" \
    "$SRC_DIR/memchk.c" \
    "$SRC_DIR/op.c" \
    "$SRC_DIR/program.c" \
    "$SRC_DIR/stmt.c" \
    "$SRC_DIR/sym.c" \
    "$SRC_DIR/type.c" \
    -O2 -w

if [ -f "$BIN_DIR/p1x3" ]; then
    echo "Success: p1x3 built"
    ls -la "$BIN_DIR/p1x3"
else
    echo "Error: Build failed"
    exit 1
fi

echo ""
echo "========================================"
echo "Build complete!"
echo "========================================"
