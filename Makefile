# ============================================
# Hi-Tech C Toolchain Makefile
# ============================================
# Build order (dependencies):
#   01: compiler     - Build p1x3 compiler
#   02: hitechc-libs - Build Hi-Tech C libraries (depends on compiler)
#   03: msx-libs     - Build MSX libraries (depends on hitechc-libs)
#
# Note: This Makefile supports parallel builds (make -j).
#       MSX library and CRT files use separate build directories
#       (build/msx and build/crt) to prevent conflicts.
# ============================================

.SUFFIXES:

# ============================================
# Directory Configuration
# ============================================
BIN_DIR     := bin
BUILD_DIR   := build
SRC_DIR     := source
INC_HITECHC := include/hitechc
LIB_HITECHC := lib/hitechc
LIB_MSX     := lib/msx

# ============================================
# Tools
# ============================================
GCC    := gcc
P1X3   := $(BIN_DIR)/p1x3
CPP    := $(BIN_DIR)/cpp_new3
CGEN   := $(BIN_DIR)/cgen3
OPTIM  := $(BIN_DIR)/optim3
ZASM   := $(BIN_DIR)/zasx3
LIBR   := $(BIN_DIR)/libr3

# ============================================
# Source Files
# ============================================

# 01: p1x3 compiler sources
P1X3_SRCS := $(wildcard $(SRC_DIR)/hitechc/*.c)

# 02: Hi-Tech C library sources
GEN_C_SRCS   := $(wildcard $(SRC_DIR)/hitechc_library/gen/*.c)
GEN_AS_SRCS  := $(wildcard $(SRC_DIR)/hitechc_library/gen/*.as)
STDIO_C_SRCS := $(wildcard $(SRC_DIR)/hitechc_library/stdio/*.c)
FLOAT_C_SRCS := $(wildcard $(SRC_DIR)/hitechc_library/float/*.c)
FLOAT_AS_SRCS := $(wildcard $(SRC_DIR)/hitechc_library/float/*.as)

# 03: MSX library sources
MSX_BIOS_SRCS := $(wildcard $(SRC_DIR)/msx/bios/*.as)
MSX_DOS_SRCS  := $(wildcard $(SRC_DIR)/msx/dos/*.as)
MSX_PSG_SRCS  := $(wildcard $(SRC_DIR)/msx/psg/*.as)
MSX_SLOT_SRCS := $(wildcard $(SRC_DIR)/msx/slot/*.as)
MSX_VDP_SRCS  := $(wildcard $(SRC_DIR)/msx/vdp/*.as)
CRT_SRCS      := $(wildcard $(SRC_DIR)/msx/crt/*.as)

# ============================================
# Object Files
# ============================================

# Gen library objects
GEN_C_OBJS  := $(patsubst $(SRC_DIR)/hitechc_library/gen/%.c,$(BUILD_DIR)/gen/%.obj,$(GEN_C_SRCS))
GEN_AS_OBJS := $(patsubst $(SRC_DIR)/hitechc_library/gen/%.as,$(BUILD_DIR)/gen/%.obj,$(GEN_AS_SRCS))
GEN_OBJS    := $(GEN_C_OBJS) $(GEN_AS_OBJS)

# Stdio library objects
STDIO_OBJS := $(patsubst $(SRC_DIR)/hitechc_library/stdio/%.c,$(BUILD_DIR)/stdio/%.obj,$(STDIO_C_SRCS))

# Float library objects
FLOAT_C_OBJS  := $(patsubst $(SRC_DIR)/hitechc_library/float/%.c,$(BUILD_DIR)/float/%.obj,$(FLOAT_C_SRCS))
FLOAT_AS_OBJS := $(patsubst $(SRC_DIR)/hitechc_library/float/%.as,$(BUILD_DIR)/float/%.obj,$(FLOAT_AS_SRCS))
FLOAT_OBJS    := $(FLOAT_C_OBJS) $(FLOAT_AS_OBJS)

# MSX library objects
MSX_OBJS := $(patsubst $(SRC_DIR)/msx/bios/%.as,$(BUILD_DIR)/msx/%.obj,$(MSX_BIOS_SRCS)) \
            $(patsubst $(SRC_DIR)/msx/dos/%.as,$(BUILD_DIR)/msx/%.obj,$(MSX_DOS_SRCS)) \
            $(patsubst $(SRC_DIR)/msx/psg/%.as,$(BUILD_DIR)/msx/%.obj,$(MSX_PSG_SRCS)) \
            $(patsubst $(SRC_DIR)/msx/slot/%.as,$(BUILD_DIR)/msx/%.obj,$(MSX_SLOT_SRCS)) \
            $(patsubst $(SRC_DIR)/msx/vdp/%.as,$(BUILD_DIR)/msx/%.obj,$(MSX_VDP_SRCS))

# CRT objects (individual files, not archived)
CRT_OBJS := $(patsubst $(SRC_DIR)/msx/crt/%.as,$(LIB_MSX)/%.obj,$(CRT_SRCS))

# ============================================
# Phony Targets
# ============================================
.PHONY: all clean compiler hitechc-libs msx-libs

# ============================================
# Main Targets (with dependencies)
# ============================================

# Default target: build everything
all: msx-libs

# 01: Build p1x3 compiler (no dependencies)
compiler: $(P1X3)

# 02: Build Hi-Tech C libraries (depends on compiler)
hitechc-libs: compiler \
              $(LIB_HITECHC)/zlibc.lib \
              $(LIB_HITECHC)/zlibio.lib \
              $(LIB_HITECHC)/zlibf.lib

# 03: Build MSX libraries (depends on hitechc-libs)
msx-libs: hitechc-libs \
          $(LIB_MSX)/zlibmsx.lib \
          $(CRT_OBJS)

# ============================================
# Build Directory Setup
# ============================================
# Note: For parallel build safety, directories are created inline using
#       mkdir -p in each rule. Header files are copied using flock to
#       prevent race conditions when multiple jobs run simultaneously.

# Macro to safely copy headers (uses flock for synchronization)
# Usage: $(call ENSURE_HEADERS)
define ENSURE_HEADERS
@mkdir -p $(BUILD_DIR)/inc && \
 flock $(BUILD_DIR)/inc -c '\
   if [ ! -f $(BUILD_DIR)/inc/.copied ]; then \
     cp $(INC_HITECHC)/*.h $(BUILD_DIR)/inc/; \
     touch $(BUILD_DIR)/inc/.copied; \
   fi'
endef

# ============================================
# 01: p1x3 Compiler Build Rule
# ============================================

$(BIN_DIR):
	@mkdir -p $@

$(P1X3): $(P1X3_SRCS) | $(BIN_DIR)
	@echo "========================================"
	@echo "Building Hi-Tech C Compiler (p1x3)"
	@echo "========================================"
	$(GCC) -o $@ $^ -O2 -w
	@echo "Success: p1x3 built"

# ============================================
# 02: Hi-Tech C Library Build Rules
# ============================================

# Gen library (zlibc.lib)
$(LIB_HITECHC)/zlibc.lib: $(GEN_OBJS) | $(LIB_HITECHC)
	@echo "--- Creating zlibc.lib ---"
	@cd $(BUILD_DIR)/gen && ../../$(LIBR) r zlibc.lib *.obj 2>/dev/null
	@cp $(BUILD_DIR)/gen/zlibc.lib $@
	@echo "Success: zlibc.lib created"

# Stdio library (zlibio.lib)
$(LIB_HITECHC)/zlibio.lib: $(STDIO_OBJS) | $(LIB_HITECHC)
	@echo "--- Creating zlibio.lib ---"
	@cd $(BUILD_DIR)/stdio && ../../$(LIBR) r zlibio.lib *.obj 2>/dev/null
	@cp $(BUILD_DIR)/stdio/zlibio.lib $@
	@echo "Success: zlibio.lib created"

# Float library (zlibf.lib)
$(LIB_HITECHC)/zlibf.lib: $(FLOAT_OBJS) | $(LIB_HITECHC)
	@echo "--- Creating zlibf.lib ---"
	@cd $(BUILD_DIR)/float && ../../$(LIBR) r zlibf.lib *.obj 2>/dev/null
	@cp $(BUILD_DIR)/float/zlibf.lib $@
	@echo "Success: zlibf.lib created"

$(LIB_HITECHC):
	@mkdir -p $@

# ============================================
# 03: MSX Library Build Rules
# ============================================

# MSX library (zlibmsx.lib)
$(LIB_MSX)/zlibmsx.lib: $(MSX_OBJS) | $(LIB_MSX)
	@echo "--- Creating zlibmsx.lib ---"
	@cd $(BUILD_DIR)/msx && ../../$(LIBR) r zlibmsx.lib *.obj 2>/dev/null
	@cp $(BUILD_DIR)/msx/zlibmsx.lib $@
	@echo "Success: zlibmsx.lib created"

$(LIB_MSX):
	@mkdir -p $@

# ============================================
# C Compilation Rules (cpp -> p1x3 -> cgen3 -> optim3 -> zasx3)
# ============================================

# Gen C files
$(BUILD_DIR)/gen/%.obj: $(SRC_DIR)/hitechc_library/gen/%.c $(P1X3)
	$(call ENSURE_HEADERS)
	@mkdir -p $(BUILD_DIR)/gen
	@echo "Compiling: $<"
	@cp $< $(BUILD_DIR)/gen/$*.c
	@cd $(BUILD_DIR)/gen && \
	 ../../$(CPP) -I../inc -I. $*.c $*.i 2>/dev/null && \
	 ../../$(P1X3) $*.i > $*.p1 2>/dev/null && \
	 ../../$(CGEN) $*.p1 $*.as 2>/dev/null && \
	 ../../$(OPTIM) $*.as $*.asm 2>/dev/null && \
	 ../../$(ZASM) $*.asm 2>/dev/null
	@rm -f $(BUILD_DIR)/gen/$*.c $(BUILD_DIR)/gen/$*.i $(BUILD_DIR)/gen/$*.p1 \
	       $(BUILD_DIR)/gen/$*.as $(BUILD_DIR)/gen/$*.asm

# Stdio C files
$(BUILD_DIR)/stdio/%.obj: $(SRC_DIR)/hitechc_library/stdio/%.c $(P1X3)
	$(call ENSURE_HEADERS)
	@mkdir -p $(BUILD_DIR)/stdio
	@echo "Compiling: $<"
	@cp $< $(BUILD_DIR)/stdio/$*.c
	@cd $(BUILD_DIR)/stdio && \
	 ../../$(CPP) -I../inc -I. $*.c $*.i 2>/dev/null && \
	 ../../$(P1X3) $*.i > $*.p1 2>/dev/null && \
	 ../../$(CGEN) $*.p1 $*.as 2>/dev/null && \
	 ../../$(OPTIM) $*.as $*.asm 2>/dev/null && \
	 ../../$(ZASM) $*.asm 2>/dev/null
	@rm -f $(BUILD_DIR)/stdio/$*.c $(BUILD_DIR)/stdio/$*.i $(BUILD_DIR)/stdio/$*.p1 \
	       $(BUILD_DIR)/stdio/$*.as $(BUILD_DIR)/stdio/$*.asm

# Float C files
$(BUILD_DIR)/float/%.obj: $(SRC_DIR)/hitechc_library/float/%.c $(P1X3)
	$(call ENSURE_HEADERS)
	@mkdir -p $(BUILD_DIR)/float
	@echo "Compiling: $<"
	@cp $< $(BUILD_DIR)/float/$*.c
	@cd $(BUILD_DIR)/float && \
	 ../../$(CPP) -I../inc -I. $*.c $*.i 2>/dev/null && \
	 ../../$(P1X3) $*.i > $*.p1 2>/dev/null && \
	 ../../$(CGEN) $*.p1 $*.as 2>/dev/null && \
	 ../../$(OPTIM) $*.as $*.asm 2>/dev/null && \
	 ../../$(ZASM) $*.asm 2>/dev/null
	@rm -f $(BUILD_DIR)/float/$*.c $(BUILD_DIR)/float/$*.i $(BUILD_DIR)/float/$*.p1 \
	       $(BUILD_DIR)/float/$*.as $(BUILD_DIR)/float/$*.asm

# ============================================
# ASM Compilation Rules (zasx3)
# ============================================

# Gen ASM files
$(BUILD_DIR)/gen/%.obj: $(SRC_DIR)/hitechc_library/gen/%.as
	@mkdir -p $(BUILD_DIR)/gen
	@echo "Assembling: $<"
	@cp $< $(BUILD_DIR)/gen/$*.asm
	@cd $(BUILD_DIR)/gen && ../../$(ZASM) $*.asm 2>/dev/null
	@rm -f $(BUILD_DIR)/gen/$*.asm

# Float ASM files
$(BUILD_DIR)/float/%.obj: $(SRC_DIR)/hitechc_library/float/%.as
	@mkdir -p $(BUILD_DIR)/float
	@echo "Assembling: $<"
	@cp $< $(BUILD_DIR)/float/$*.asm
	@cd $(BUILD_DIR)/float && ../../$(ZASM) $*.asm 2>/dev/null
	@rm -f $(BUILD_DIR)/float/$*.asm

# MSX BIOS ASM files
$(BUILD_DIR)/msx/%.obj: $(SRC_DIR)/msx/bios/%.as
	@mkdir -p $(BUILD_DIR)/msx
	@echo "Assembling: $<"
	@cp $< $(BUILD_DIR)/msx/$*.asm
	@cd $(BUILD_DIR)/msx && ../../$(ZASM) $*.asm 2>/dev/null
	@rm -f $(BUILD_DIR)/msx/$*.asm

# MSX DOS ASM files
$(BUILD_DIR)/msx/%.obj: $(SRC_DIR)/msx/dos/%.as
	@mkdir -p $(BUILD_DIR)/msx
	@echo "Assembling: $<"
	@cp $< $(BUILD_DIR)/msx/$*.asm
	@cd $(BUILD_DIR)/msx && ../../$(ZASM) $*.asm 2>/dev/null
	@rm -f $(BUILD_DIR)/msx/$*.asm

# MSX PSG ASM files
$(BUILD_DIR)/msx/%.obj: $(SRC_DIR)/msx/psg/%.as
	@mkdir -p $(BUILD_DIR)/msx
	@echo "Assembling: $<"
	@cp $< $(BUILD_DIR)/msx/$*.asm
	@cd $(BUILD_DIR)/msx && ../../$(ZASM) $*.asm 2>/dev/null
	@rm -f $(BUILD_DIR)/msx/$*.asm

# MSX SLOT ASM files
$(BUILD_DIR)/msx/%.obj: $(SRC_DIR)/msx/slot/%.as
	@mkdir -p $(BUILD_DIR)/msx
	@echo "Assembling: $<"
	@cp $< $(BUILD_DIR)/msx/$*.asm
	@cd $(BUILD_DIR)/msx && ../../$(ZASM) $*.asm 2>/dev/null
	@rm -f $(BUILD_DIR)/msx/$*.asm

# MSX VDP ASM files
$(BUILD_DIR)/msx/%.obj: $(SRC_DIR)/msx/vdp/%.as
	@mkdir -p $(BUILD_DIR)/msx
	@echo "Assembling: $<"
	@cp $< $(BUILD_DIR)/msx/$*.asm
	@cd $(BUILD_DIR)/msx && ../../$(ZASM) $*.asm 2>/dev/null
	@rm -f $(BUILD_DIR)/msx/$*.asm

# CRT ASM files (built in separate directory to support parallel builds)
# Using build/crt instead of build/msx prevents CRT objects from being
# accidentally included in zlibmsx.lib when using 'make -j'
$(LIB_MSX)/%.obj: $(SRC_DIR)/msx/crt/%.as
	@mkdir -p $(BUILD_DIR)/crt $(LIB_MSX)
	@echo "Assembling CRT: $<"
	@cp $< $(BUILD_DIR)/crt/$*.asm
	@cd $(BUILD_DIR)/crt && ../../$(ZASM) $*.asm 2>/dev/null
	@cp $(BUILD_DIR)/crt/$*.obj $@
	@rm -f $(BUILD_DIR)/crt/$*.asm $(BUILD_DIR)/crt/$*.obj

# ============================================
# Clean
# ============================================

clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR)
	rm -f $(P1X3)
	rm -f $(LIB_HITECHC)/zlibc.lib $(LIB_HITECHC)/zlibio.lib $(LIB_HITECHC)/zlibf.lib
	rm -f $(LIB_MSX)/zlibmsx.lib $(LIB_MSX)/*.obj
	@echo "Clean complete."

