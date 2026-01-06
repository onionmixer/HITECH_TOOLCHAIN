# Hi-Tech C Z80 Compiler with ZXCC (CP/M Emulator)

This guide explains how to use the Hi-Tech C v3.09 CP/M binaries via ZXCC on Linux.

## Contents

```
bin/
├── C309.COM        # Compiler driver (patched version)
├── C309-20.COM     # Updated compiler driver
├── C-ORIG.COM      # Original compiler driver
├── CPP.COM         # C Preprocessor
├── P1.COM          # C Parser
├── CGEN.COM        # Code Generator
├── OPTIM.COM       # Peephole Optimizer
├── ZAS.COM         # Z80 Assembler
├── LINQ.COM        # Linker (renamed from LINK to avoid conflicts)
├── LIBR.COM        # Library Manager
├── OBJTOHEX.COM    # Object to HEX converter
├── CREF.COM        # Cross Reference
├── DEBUG.COM       # Debugger
├── DEHUFF.COM      # Huffman decompressor
├── SYMTOAS.COM     # Symbol to assembly converter
├── $EXEC.COM       # Execution helper
├── CRTCPM.OBJ      # CP/M Runtime startup
├── DRTCPM.OBJ      # Default runtime
├── NRTCPM.OBJ      # No-runtime startup
├── RRTCPM.OBJ      # ROM runtime
├── LIBC.LIB        # Standard C library (patched)
├── LIBCORIG.LIB    # Original C library
├── LIBF.LIB        # Floating-point library (patched)
├── LIBFORIG.LIB    # Original floating-point library
└── LIBOVR.LIB      # Overlay library
```

## Prerequisites

### Install ZXCC

ZXCC is a CP/M 2.2 emulator that runs CP/M programs on Unix-like systems.

#### Build from Source

```bash
# Clone repository
git clone https://github.com/lipro-cpm4l/zxcc.git
cd zxcc

# Build and install
./configure --prefix=/usr/local
make
sudo make install
```

#### Package Manager (if available)

```bash
# Some distributions may have zxcc in their repos
sudo apt install zxcc      # Debian/Ubuntu (if available)
```

## ZXCC Configuration

### 1. Create CP/M Directory Structure

```bash
# Create ZXCC directories
sudo mkdir -p /usr/local/lib/cpm/bin80
sudo mkdir -p /usr/local/lib/cpm/lib80

# Or use user directory
mkdir -p ~/.cpm/bin80
mkdir -p ~/.cpm/lib80
```

### 2. Copy Hi-Tech C Files

```bash
ZXCC_BIN=/usr/local/lib/cpm/bin80    # or ~/.cpm/bin80
ZXCC_LIB=/usr/local/lib/cpm/lib80    # or ~/.cpm/lib80

# Copy executables
cp bin/*.COM "$ZXCC_BIN/"

# Copy libraries and runtime objects
cp bin/*.LIB "$ZXCC_LIB/"
cp bin/*.OBJ "$ZXCC_LIB/"
```

### 3. Set Environment Variables

Add to `~/.bashrc` or `~/.profile`:

```bash
# ZXCC Configuration
export ZCCCFG=/usr/local/lib/cpm
# Or for user installation:
# export ZCCCFG=$HOME/.cpm

# CP/M search paths
export CPMDIR80=$ZCCCFG/bin80
export CPMLIBDIR80=$ZCCCFG/lib80

# Add to PATH for convenience
alias zxc='zxcc c309'
alias zxcpp='zxcc cpp'
alias zxp1='zxcc p1'
alias zxcgen='zxcc cgen'
alias zxoptim='zxcc optim'
alias zxas='zxcc zas'
alias zxlink='zxcc linq'
alias zxlibr='zxcc libr'
```

Reload configuration:

```bash
source ~/.bashrc
```

## Basic Usage

### Compile a Simple Program

```bash
# Using compiler driver
zxcc c309 hello.c -o hello.com

# Verbose mode
zxcc c309 -v hello.c
```

### Manual Compilation Pipeline

```bash
# 1. Preprocess
zxcc cpp hello.c hello.i

# 2. Parse
zxcc p1 hello.i hello.p1

# 3. Generate code
zxcc cgen hello.p1 hello.as

# 4. Optimize
zxcc optim hello.as hello.asm

# 5. Assemble
zxcc zas hello.asm

# 6. Link
zxcc linq -C100H -Phello.com crtcpm.obj hello.obj libc.lib
```

## Wrapper Script

Create `htc-cpm.sh` for easier compilation:

```bash
#!/bin/bash
# Hi-Tech C CP/M wrapper script

# Check ZXCC configuration
if [ -z "$ZCCCFG" ]; then
    export ZCCCFG=/usr/local/lib/cpm
fi

# Compiler driver
compile() {
    local src="$1"
    local out="${2:-${src%.c}.com}"

    zxcc c309 "$src" -o "$out"
}

# Manual pipeline for debugging
compile_verbose() {
    local src="$1"
    local base="${src%.c}"

    echo "=== Preprocessing ==="
    zxcc cpp "$src" "${base}.i" || return 1

    echo "=== Parsing ==="
    zxcc p1 "${base}.i" "${base}.p1" || return 1

    echo "=== Code Generation ==="
    zxcc cgen "${base}.p1" "${base}.as" || return 1

    echo "=== Optimization ==="
    zxcc optim "${base}.as" "${base}.asm" || return 1

    echo "=== Assembly ==="
    zxcc zas "${base}.asm" || return 1

    echo "=== Linking ==="
    zxcc linq -C100H -P"${base}.com" crtcpm.obj "${base}.obj" libc.lib || return 1

    echo "=== Done: ${base}.com ==="
}

# Main
case "$1" in
    -v|--verbose)
        shift
        compile_verbose "$@"
        ;;
    *)
        compile "$@"
        ;;
esac
```

## File Path Handling

ZXCC automatically converts Unix paths to CP/M format:

```bash
# Unix path
zxcc c309 /home/user/project/hello.c

# Converted internally to CP/M path
# Files are accessed via ZXCC's file mapping
```

### Working Directory

ZXCC uses the current directory as the default CP/M drive:

```bash
cd /path/to/project
zxcc c309 hello.c        # hello.c in current directory
```

## Library Path Configuration

To use custom libraries, set the library path:

```bash
# In environment
export CPMLIBDIR80=/path/to/libs

# Or specify directly in link command
zxcc linq -L/path/to/libs crtcpm.obj hello.obj libc.lib
```

## Cross-Compilation for MSX

For MSX development, use MSX-specific libraries:

```bash
# Link with MSX libraries
zxcc linq -C100H -Phello.com \
    zcrtmsx.obj \
    hello.obj \
    zlibmsx.lib \
    libc.lib
```

## Troubleshooting

### "Command not found: zxcc"

Ensure ZXCC is installed and in PATH:

```bash
which zxcc
# If not found, add to PATH:
export PATH=$PATH:/usr/local/bin
```

### "Cannot find C309.COM"

Set the CP/M binary path:

```bash
export CPMDIR80=/path/to/bin80
# Or check ZCCCFG
export ZCCCFG=/path/to/cpm
```

### "Cannot find LIBC.LIB"

Set the library path:

```bash
export CPMLIBDIR80=/path/to/lib80
```

### File Not Found Errors

- Use absolute paths or ensure files are in current directory
- Check file permissions
- Verify ZXCC path mapping

### Memory Errors

CP/M programs have limited memory (64KB). For large programs:
- Split into multiple source files
- Use overlay support (LIBOVR.LIB)

## Differences from DOS Version

| Feature | DOS (.EXE) | CP/M (.COM) |
|---------|-----------|-------------|
| Linker name | LINK.EXE | LINQ.COM |
| Max memory | Extended | 64KB TPA |
| Path format | DOS paths | CP/M drive:filename |
| Libraries | ZLIBC.LIB | LIBC.LIB |

## References

- ZXCC Project: https://github.com/lipro-cpm4l/zxcc
- Hi-Tech C CP/M Distribution: https://github.com/agn453/HI-TECH-Z80-C
- CP/M Documentation: http://www.cpm.z80.de/
