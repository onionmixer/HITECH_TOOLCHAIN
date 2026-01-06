# Hi-Tech C Z80 Compiler with DOSBox

This guide explains how to use the original Hi-Tech C v3.09 DOS binaries via DOSBox on Linux.

## Contents

```
bin/
├── ZC.EXE          # Compiler driver (front-end)
├── CPP.EXE         # C Preprocessor
├── P1.EXE          # C Parser
├── CGEN.EXE        # Code Generator
├── OPTIM.EXE       # Peephole Optimizer
├── ZAS.EXE         # Z80 Assembler
├── LINK.EXE        # Linker
├── LIBR.EXE        # Library Manager
├── OBJTOHEX.EXE    # Object to HEX converter
├── CREF.EXE        # Cross Reference
├── DEHUFF.EXE      # Huffman decompressor
├── DUMP.COM        # Object file dumper
├── ZCRT.OBJ        # C Runtime startup
├── ZCRTCPM.OBJ     # CP/M Runtime startup
├── ZCRTI.OBJ       # Interrupt-safe runtime
├── ZRRTCPM.OBJ     # ROM runtime
├── ZLIBC.LIB       # Standard C library
└── ZLIBF.LIB       # Floating-point library
```

## Prerequisites

### Install DOSBox

```bash
# Ubuntu/Debian
sudo apt install dosbox

# Arch Linux
sudo pacman -S dosbox

# Fedora
sudo dnf install dosbox
```

## DOSBox Configuration

### 1. Create Configuration File

```bash
mkdir -p ~/.dosbox
cp /etc/dosbox/dosbox.conf ~/.dosbox/dosbox-hitech.conf
```

### 2. Edit Configuration

Edit `~/.dosbox/dosbox-hitech.conf`:

```ini
[sdl]
fullscreen=false
output=surface

[cpu]
cycles=max

[autoexec]
# Mount Hi-Tech C directory
mount c /path/to/HITECH_TOOLCHAIN/extra/dosbox/bin
# Mount working directory
mount d /path/to/your/project
# Set PATH
set PATH=C:\
# Change to working directory
d:
```

## Linux Framebuffer Mode (Headless)

For servers or headless systems without X11:

### Environment Variables

```bash
# Use framebuffer output
export SDL_VIDEODRIVER=fbcon

# Or use dummy video (no display)
export SDL_VIDEODRIVER=dummy
export SDL_AUDIODRIVER=dummy

# Run DOSBox
dosbox -conf ~/.dosbox/dosbox-hitech.conf
```

### Batch Mode Execution

Create a batch file for automated compilation:

```bash
# Create DOS batch file
cat > /tmp/compile.bat << 'EOF'
C:
ZC -c %1
exit
EOF
```

Run DOSBox in batch mode:

```bash
dosbox -conf ~/.dosbox/dosbox-hitech.conf -c "mount c /path/to/bin" \
       -c "mount d /tmp" -c "d:" -c "c:\zc -c test.c" -c "exit"
```

## Compilation Examples

### Inside DOSBox

```dos
C:\>ZC -v hello.c -o hello.com
```

### Compilation Pipeline (Manual)

```dos
C:\>CPP hello.c hello.i
C:\>P1 hello.i hello.p1
C:\>CGEN hello.p1 hello.as
C:\>OPTIM hello.as hello.asm
C:\>ZAS hello.asm
C:\>LINK -C100H -Phello.com ZCRT.OBJ hello.obj ZLIBC.LIB
```

## Wrapper Script for Linux

Create a wrapper script `htc-dos.sh`:

```bash
#!/bin/bash
# Hi-Tech C DOSBox wrapper script

HITECH_DIR="$(dirname "$0")/bin"
WORK_DIR="$(pwd)"

# Prepare DOS-compatible paths
mkdir -p /tmp/htc-work
cp "$@" /tmp/htc-work/ 2>/dev/null

# Create batch file
BATCH="/tmp/htc-work/compile.bat"
echo "C:" > "$BATCH"
echo "ZC $*" >> "$BATCH"
echo "exit" >> "$BATCH"

# Run DOSBox
export SDL_VIDEODRIVER=dummy
export SDL_AUDIODRIVER=dummy

dosbox -conf /dev/null \
    -c "mount c $HITECH_DIR" \
    -c "mount d /tmp/htc-work" \
    -c "d:" \
    -c "call compile.bat" \
    -c "exit" 2>/dev/null

# Copy results back
cp /tmp/htc-work/*.obj "$WORK_DIR/" 2>/dev/null
cp /tmp/htc-work/*.com "$WORK_DIR/" 2>/dev/null
```

## DOSBox Performance Tips

### Increase CPU Cycles

In `dosbox.conf`:

```ini
[cpu]
cycles=max
# or fixed value
cycles=50000
```

### Reduce Screen Updates

```ini
[render]
frameskip=10
```

### Disable Sound

```ini
[mixer]
nosound=true

[speaker]
pcspeaker=false

[sblaster]
sbtype=none
```

## Troubleshooting

### "Not enough memory"

Increase DOSBox memory:

```ini
[dosbox]
memsize=64
```

### Path Too Long

DOS has 8.3 filename limits. Use short paths:

```bash
# Bad
/home/username/very/long/path/to/source/file.c

# Good
mount d /tmp
copy file to /tmp
```

### Slow Compilation

Use `cycles=max` or higher fixed cycles value.

## Reference

- DOSBox Documentation: https://www.dosbox.com/wiki/
- Hi-Tech C Manual: See `manuals/` directory
- Original Distribution: https://github.com/agn453/HI-TECH-Z80-C-Cross-Compiler
