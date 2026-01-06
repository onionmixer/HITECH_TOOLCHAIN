/*
 * rom.h - MSX ROM Cartridge Definitions
 *
 * Support for MSX ROM cartridge development including:
 * - 16KB ROM (page 1: 0x4000-0x7FFF)
 * - 32KB ROM (page 1-2: 0x4000-0xBFFF)
 * - MegaROM mappers (ASCII8, ASCII16, Konami, etc.)
 *
 * Compatible with HI-TECH Z80 C Compiler.
 */

#ifndef _MSX_ROM_H
#define _MSX_ROM_H

/* ============================================
 * ROM Header Constants
 * ============================================ */

/* ROM signature bytes */
#define ROM_SIG1        0x41    /* 'A' */
#define ROM_SIG2        0x42    /* 'B' */

/* ROM types */
#define ROM_TYPE_16K    0       /* 16KB ROM at 0x4000 */
#define ROM_TYPE_32K    1       /* 32KB ROM at 0x4000 */
#define ROM_TYPE_48K    2       /* 48KB ROM (rare) */
#define ROM_TYPE_MEGA   3       /* MegaROM with mapper */

/* ============================================
 * Memory Map for ROM Cartridges
 * ============================================ */

/* Page addresses (each page is 16KB) */
#define PAGE0_ADDR      0x0000  /* Page 0: BIOS ROM */
#define PAGE1_ADDR      0x4000  /* Page 1: Cartridge ROM */
#define PAGE2_ADDR      0x8000  /* Page 2: Cartridge ROM or RAM */
#define PAGE3_ADDR      0xC000  /* Page 3: Main RAM */

/* Common ROM start address */
#define ROM_START       0x4000  /* Standard ROM start */
#define ROM_INIT        0x4002  /* Initialization routine */
#define ROM_STATEMENT   0x4004  /* BASIC statement handler */
#define ROM_DEVICE      0x4006  /* Device handler */
#define ROM_TEXT        0x4008  /* BASIC text pointer */
#define ROM_RESERVED    0x400A  /* Reserved (6 bytes) */

/* ============================================
 * MegaROM Mapper Types
 * ============================================ */

#define MAPPER_NONE     0       /* No mapper (plain ROM) */
#define MAPPER_KONAMI   1       /* Konami without SCC */
#define MAPPER_KONAMI_SCC 2     /* Konami with SCC */
#define MAPPER_ASCII8   3       /* ASCII 8KB mapper */
#define MAPPER_ASCII16  4       /* ASCII 16KB mapper */
#define MAPPER_GAMEMASTER2 5    /* Game Master 2 */
#define MAPPER_FMPAC    6       /* FM-PAC */

/* ============================================
 * Konami Mapper (without SCC)
 * Bank registers at: 0x6000, 0x8000, 0xA000
 * ============================================ */

#define KONAMI_BANK0    0x4000  /* Bank 0: fixed to page 0 */
#define KONAMI_BANK1    0x6000  /* Bank 1: switchable */
#define KONAMI_BANK2    0x8000  /* Bank 2: switchable */
#define KONAMI_BANK3    0xA000  /* Bank 3: switchable */

#define KONAMI_REG1     0x6000  /* Bank 1 register */
#define KONAMI_REG2     0x8000  /* Bank 2 register */
#define KONAMI_REG3     0xA000  /* Bank 3 register */

/* ============================================
 * Konami SCC Mapper
 * Bank registers at: 0x5000, 0x7000, 0x9000, 0xB000
 * ============================================ */

#define KONAMI_SCC_REG0 0x5000  /* Bank 0 register */
#define KONAMI_SCC_REG1 0x7000  /* Bank 1 register */
#define KONAMI_SCC_REG2 0x9000  /* Bank 2 register */
#define KONAMI_SCC_REG3 0xB000  /* Bank 3 register */
#define KONAMI_SCC_ADDR 0x9800  /* SCC registers (when bank=0x3F) */

/* ============================================
 * ASCII 8KB Mapper
 * Bank registers at: 0x6000, 0x6800, 0x7000, 0x7800
 * ============================================ */

#define ASCII8_BANK0    0x4000  /* Bank 0: 0x4000-0x5FFF */
#define ASCII8_BANK1    0x6000  /* Bank 1: 0x6000-0x7FFF */
#define ASCII8_BANK2    0x8000  /* Bank 2: 0x8000-0x9FFF */
#define ASCII8_BANK3    0xA000  /* Bank 3: 0xA000-0xBFFF */

#define ASCII8_REG0     0x6000  /* Bank 0 register */
#define ASCII8_REG1     0x6800  /* Bank 1 register */
#define ASCII8_REG2     0x7000  /* Bank 2 register */
#define ASCII8_REG3     0x7800  /* Bank 3 register */

/* ============================================
 * ASCII 16KB Mapper
 * Bank registers at: 0x6000, 0x7000
 * ============================================ */

#define ASCII16_BANK0   0x4000  /* Bank 0: 0x4000-0x7FFF */
#define ASCII16_BANK1   0x8000  /* Bank 1: 0x8000-0xBFFF */

#define ASCII16_REG0    0x6000  /* Bank 0 register */
#define ASCII16_REG1    0x7000  /* Bank 1 register */

/* ============================================
 * Slot Management
 * ============================================ */

/* Primary slot select register */
#define SLOT_SELECT     0xA8    /* I/O port for primary slot select */

/* Secondary slot register (memory mapped) */
#define SLOT_SECONDARY  0xFFFF  /* Secondary slot register */

/* Slot helper macros */
#define SLOT_PAGE(slot, page)   (((slot) & 3) << ((page) * 2))
#define SLOT_EXPANDED(slot)     ((slot) & 0x80)

/* ============================================
 * ROM Function Declarations
 * ============================================ */

/* Slot functions */
unsigned char slot_read(unsigned char slot, unsigned addr);
void slot_write(unsigned char slot, unsigned addr, unsigned char value);
void slot_call(unsigned char slot, unsigned addr);
unsigned char slot_search(unsigned char *signature);

/* MegaROM bank switching */
void rom_set_bank_konami(int bank, int page);
void rom_set_bank_ascii8(int bank, int page);
void rom_set_bank_ascii16(int bank, int page);

/* Interslot call (BIOS) */
void interslot_call(unsigned char slot, unsigned addr);
unsigned char interslot_read(unsigned char slot, unsigned addr);
void interslot_write(unsigned char slot, unsigned addr, unsigned char value);

/* ROM detection */
int rom_get_slot(void);         /* Get current ROM slot */
int rom_is_expanded(int slot);  /* Check if slot is expanded */

#endif /* _MSX_ROM_H */
