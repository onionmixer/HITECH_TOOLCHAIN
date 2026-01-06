# Hi-Tech C Z80 Cross Compiler Toolchain for MSX

Native Linux toolchain for Hi-Tech C v3.09 Z80 cross compiler with MSX library support.

## Overview

This toolchain provides a complete Hi-Tech C v3.09 development environment that runs natively on Linux without requiring DOSBox or CP/M emulation. It includes:

- Native Linux binaries for all compiler tools
- Standard C libraries (gen, stdio, float)
- MSX-specific libraries (BIOS, DOS, VDP, PSG, etc.)
- CRT startup files for MSX ROM and DOS programs

## Directory Structure

```
HITECH_TOOLCHAIN/
├── bin/                           # Executable tools
│   ├── cpp_new3                   # C Preprocessor
│   ├── p1x3                       # C Parser (generates IR)
│   ├── cgen3                      # Code Generator (IR to ASM)
│   ├── optim3                     # Peephole Optimizer
│   ├── zasx3                      # Z80 Assembler
│   ├── linq3                      # Linker
│   ├── libr3                      # Library Manager
│   ├── objtohex                   # Object to HEX converter
│   └── cref3                      # Cross Reference Generator
├── include/
│   ├── hitechc/                   # Standard C headers
│   │   ├── stdio.h, stdlib.h, string.h, ...
│   └── msx/                       # MSX-specific headers
│       ├── bios.h, vdp.h, psg.h, msxdos.h, ...
├── lib/
│   ├── hitechc/                   # Standard C libraries
│   │   ├── zlibc.lib              # General library (80 modules)
│   │   ├── zlibio.lib             # Standard I/O library (42 modules)
│   │   └── zlibf.lib              # Floating point library (40 modules)
│   └── msx/                       # MSX libraries
│       ├── zlibmsx.lib            # MSX BIOS/DOS library (59 modules)
│       ├── zcrtmsx.obj            # CRT for MSX-DOS programs
│       ├── zcrtrom.obj            # CRT for 16KB ROM
│       ├── zcrtrom32.obj          # CRT for 32KB ROM
│       └── megarom.obj            # CRT for MegaROM
├── source/
│   ├── hitechc/                   # Compiler source (p1x3)
│   ├── hitechc_library/           # Library source
│   │   ├── gen/                   # General functions
│   │   ├── stdio/                 # Standard I/O
│   │   └── float/                 # Floating point math
│   └── msx/                       # MSX library source
│       ├── bios/                  # BIOS wrappers
│       ├── crt/                   # Startup code
│       ├── dos/                   # MSX-DOS functions
│       ├── psg/                   # Sound chip (PSG)
│       ├── slot/                  # Slot management
│       └── vdp/                   # Video Display Processor
├── extra/                         # Alternative platforms
│   ├── dosbox/                    # DOSBox (MS-DOS emulation)
│   │   ├── HOWTOUSE_hitechc_dosbox.md
│   │   └── bin/                   # DOS binaries (.EXE)
│   └── zxcc/                      # ZXCC (CP/M emulation)
│       ├── HOWTOUSE_hitechc_cpm.md
│       └── bin/                   # CP/M binaries (.COM)
├── script_old/                    # Legacy build scripts (reference)
│   ├── 01_make_hitechc_compiler.sh
│   ├── 02_make_hitechc_library.sh
│   └── 03_make_msx_library.sh
└── Makefile                       # Main build system
```

## Building

The toolchain uses a single Makefile with proper dependency management.

### Build Commands

```bash
# Build everything (compiler, libraries, MSX libraries)
make all

# Build only the compiler (p1x3)
make compiler

# Build Hi-Tech C libraries (depends on compiler)
make hitechc-libs

# Build MSX libraries (depends on hitechc-libs)
make msx-libs

# Clean all build artifacts
make clean
```

### Parallel Build Support

The Makefile supports parallel builds for faster compilation:

```bash
make -j4 all
```

### Build Dependencies

```
compiler → hitechc-libs → msx-libs
```

1. **compiler**: Builds p1x3 C parser from source using GCC
2. **hitechc-libs**: Builds zlibc.lib, zlibio.lib, zlibf.lib (requires compiler)
3. **msx-libs**: Builds zlibmsx.lib and CRT startup files (requires hitechc-libs)

## Compilation Pipeline

```
source.c
    │
    ▼ cpp_new3 (preprocessor)
source.i
    │
    ▼ p1x3 (C parser)
source.p1 (intermediate representation)
    │
    ▼ cgen3 (code generator)
source.as (Z80 assembly)
    │
    ▼ optim3 (optimizer)
source.asm (optimized assembly)
    │
    ▼ zasx3 (assembler)
source.obj (relocatable object)
    │
    ▼ linq3 (linker)
program.com / program.bin
```

## Usage Example

### Compiling a simple MSX program

```bash
TOOLCHAIN=/path/to/HITECH_TOOLCHAIN

# Preprocess
$TOOLCHAIN/bin/cpp_new3 -I$TOOLCHAIN/include/hitechc -I$TOOLCHAIN/include/msx hello.c hello.i

# Parse
$TOOLCHAIN/bin/p1x3 hello.i > hello.p1

# Generate code
$TOOLCHAIN/bin/cgen3 hello.p1 hello.as

# Optimize
$TOOLCHAIN/bin/optim3 hello.as hello.asm

# Assemble
$TOOLCHAIN/bin/zasx3 hello.asm

# Link (MSX-DOS program)
$TOOLCHAIN/bin/linq3 -Z -C100H -Phello.com \
    $TOOLCHAIN/lib/msx/zcrtmsx.obj \
    hello.obj \
    $TOOLCHAIN/lib/msx/zlibmsx.lib \
    $TOOLCHAIN/lib/hitechc/zlibc.lib \
    $TOOLCHAIN/lib/hitechc/zlibio.lib
```

## Alternative Platforms (extra/)

The `extra/` directory contains original Hi-Tech C binaries for alternative execution environments:

### DOSBox (extra/dosbox/)

MS-DOS version of Hi-Tech C that runs under DOSBox emulation.

- **Binaries**: Original `.EXE` files for MS-DOS
- **Documentation**: See `extra/dosbox/HOWTOUSE_hitechc_dosbox.md`
- **Use case**: When you need to use the original DOS tools or verify compatibility

### ZXCC (extra/zxcc/)

CP/M version of Hi-Tech C that runs under ZXCC (CP/M emulator for Unix).

- **Binaries**: Original `.COM` files for CP/M
- **Documentation**: See `extra/zxcc/HOWTOUSE_hitechc_cpm.md`
- **Use case**: Running original CP/M tools, testing CP/M compatibility, or using patched CP/M binaries

These alternative platforms are provided for compatibility and reference. For normal development, use the native Linux binaries in `bin/`.

## Requirements

- Linux x86-64
- GCC (for building p1x3 from source)
- make

## References & Credits

This toolchain is based on the following open source projects:

### Hi-Tech C Compiler Source (DOS Version)
- **Repository**: https://github.com/agn453/HI-TECH-Z80-C-Cross-Compiler
- **Description**: Original Hi-Tech Z80 C v3.09 compiler binaries and library source
- **License**: Free for any use (see repository for details)

### Hi-Tech C Compiler (CP/M Version - Patched)
- **Repository**: https://github.com/agn453/HI-TECH-Z80-C
- **Description**: Patched CP/M version of Hi-Tech C with bug fixes and enhancements
- **Contents**:
  - CP/M binaries (.COM files) in `dist/` directory
  - Patched libraries (LIBC.LIB, LIBF.LIB)
  - Multiple CRT variants (CRTCPM.OBJ, DRTCPM.OBJ, etc.)
  - LINQ.COM (linker renamed to avoid conflicts)
  - C309.COM (patched compiler driver)
- **License**: Free for any use (see repository for details)
- **Note**: Used for `extra/zxcc/bin/` CP/M binaries

### MSX Library Extensions
- **Repository**: https://github.com/msx-solis/HI-TECH-Z80-C-Cross-Compiler-msx
- **Description**: MSX-specific libraries, headers, and CRT startup files
- **License**: See repository for details

### Decompiled Compiler Tools
The native Linux tools were built from decompiled/restored source code:

- **dp1 (p1x3)**: https://github.com/nikitinprior/dp1
  - C Parser - restored from original P1.COM
- **dcpp**: https://github.com/nikitinprior/dcpp
  - C Preprocessor
- **doptim**: https://github.com/nikitinprior/doptim
  - Peephole Optimizer
- **dzas**: https://github.com/nikitinprior/dzas
  - Z80 Assembler
- **dlibr**: https://github.com/nikitinprior/dlibr
  - Library Manager
- **dlink**: https://github.com/nikitinprior/dlink
  - Linker
- **dcgen**: https://github.com/nikitinprior/dcgenv2
  - Code Generator

### Original Copyright Notice

```
The HI-TECH Z80 C cross compiler V3.09 is provided free of charge for any use,
private or commercial, strictly as-is. No warranty or product support
is offered or implied including merchantability, fitness for a particular
purpose, or non-infringement. In no event will HI-TECH Software or its
corporate affiliates be liable for any direct or indirect damages.

You may use this software for whatever you like, providing you acknowledge
that the copyright to this software remains with HI-TECH Software and its
corporate affiliates.

All copyrights to the algorithms used, binary code, trademarks, etc.
belong to the legal owner - Microchip Technology Inc. and its subsidiaries.
```

## Known Limitations

- The p1x3 parser has a 50-byte buffer for file paths in `# line` directives
  - Workaround: Use short paths or copy source files to a temporary directory
- Some CP/M-specific features may not work on Linux

## Version History

- **2025-01-06**: Makefile build system
  - Replaced shell scripts with unified Makefile
  - Added parallel build support (make -j)
  - Proper dependency management between build stages
  - Legacy scripts preserved in `script_old/`

- **2025-01-06**: Initial release
  - Native Linux toolchain
  - Complete library build from source
  - MSX support with BIOS/DOS/VDP/PSG libraries

## License

This project is licensed under the **GNU General Public License v3.0** (GPL-3.0).

See the [LICENSE](LICENSE) file for details.

Note: This toolchain incorporates code from multiple upstream projects. The original Hi-Tech C compiler is provided free of charge by Microchip Technology Inc. Please refer to the "Original Copyright Notice" section and individual project repositories for their specific licensing terms.
