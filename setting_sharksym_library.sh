#!/bin/bash
# setting_sharksym_library.sh
# Sharksym MSX Library Setup Script
#
# Downloads and installs the sharksym MSX-DOS/MSX-DOS2 libraries
# from https://github.com/sharksym/CPMEMU_HI-TECH_C
#
# Usage: ./setting_sharksym_library.sh

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_URL="https://github.com/sharksym/CPMEMU_HI-TECH_C"

echo "========================================="
echo "Sharksym MSX Library Setup"
echo "========================================="

# 1. Create directories
echo "[1/4] Creating directories..."
mkdir -p "$SCRIPT_DIR/lib/sharksym"
mkdir -p "$SCRIPT_DIR/doc/sharksym"
mkdir -p "$SCRIPT_DIR/examples/sharksym"

# 2. Git clone to temporary directory
echo "[2/4] Cloning repository..."
TEMP_DIR=$(mktemp -d)
trap "rm -rf $TEMP_DIR" EXIT

git clone --depth 1 "$REPO_URL" "$TEMP_DIR/repo"

# 3. Copy files
echo "[3/4] Copying files..."

# 3.1 Library files (lib/sharksym/)
echo "  - Library files (.LIB, .O, .H, BL*.C)"
cp "$TEMP_DIR/repo"/*.LIB "$SCRIPT_DIR/lib/sharksym/" 2>/dev/null || true
cp "$TEMP_DIR/repo"/*.O "$SCRIPT_DIR/lib/sharksym/" 2>/dev/null || true
cp "$TEMP_DIR/repo"/*.H "$SCRIPT_DIR/lib/sharksym/" 2>/dev/null || true
cp "$TEMP_DIR/repo"/BL*.C "$SCRIPT_DIR/lib/sharksym/" 2>/dev/null || true

# 3.2 Examples (examples/sharksym/)
echo "  - Example projects"
if [ -d "$TEMP_DIR/repo/EXAMPLE" ]; then
    cp -r "$TEMP_DIR/repo/EXAMPLE"/* "$SCRIPT_DIR/examples/sharksym/"
fi

# 3.3 Documentation (doc/sharksym/)
echo "  - Documentation"
if [ -d "$TEMP_DIR/repo/Z80V309" ]; then
    cp -r "$TEMP_DIR/repo/Z80V309"/* "$SCRIPT_DIR/doc/sharksym/"
fi
cp "$TEMP_DIR/repo/README.md" "$SCRIPT_DIR/doc/sharksym/README_sharksym.md" 2>/dev/null || true

# 4. Cleanup (handled by trap)
echo "[4/4] Cleaning up temporary files..."

echo ""
echo "========================================="
echo "Installation complete!"
echo "========================================="
echo ""
echo "Installed locations:"
echo "  - Libraries: $SCRIPT_DIR/lib/sharksym/"
echo "  - Examples:  $SCRIPT_DIR/examples/sharksym/"
echo "  - Documents: $SCRIPT_DIR/doc/sharksym/"
echo ""
echo "Library files:"
ls -la "$SCRIPT_DIR/lib/sharksym/"*.LIB 2>/dev/null | head -10 || echo "  (none)"
echo ""
