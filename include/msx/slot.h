/*
 * slot.h - MSX Slot Management Functions
 *
 * MSX uses a slot system for memory expansion:
 * - 4 primary slots (0-3)
 * - Each primary slot can be expanded into 4 secondary slots
 * - Memory is divided into 4 pages of 16KB each
 *
 * Slot byte format: E0SSPP
 *   E  = Expansion flag (bit 7): 1 if using secondary slot
 *   SS = Secondary slot (bits 5-4): 0-3
 *   PP = Primary slot (bits 1-0): 0-3
 *
 * Compatible with HI-TECH Z80 C Compiler.
 * This file does NOT modify any original HI-TECH C source files.
 */

#ifndef _MSX_SLOT_H
#define _MSX_SLOT_H

/* ============================================
 * Slot Constants
 * ============================================ */

/* Primary slots */
#define SLOT_0          0x00
#define SLOT_1          0x01
#define SLOT_2          0x02
#define SLOT_3          0x03

/* Expanded slot flag */
#define SLOT_EXPANDED   0x80

/* Page addresses */
#define PAGE_0          0x0000  /* 0x0000-0x3FFF (BIOS ROM) */
#define PAGE_1          0x4000  /* 0x4000-0x7FFF (Cartridge) */
#define PAGE_2          0x8000  /* 0x8000-0xBFFF (Cartridge/RAM) */
#define PAGE_3          0xC000  /* 0xC000-0xFFFF (Main RAM) */

/* Page size */
#define PAGE_SIZE       0x4000  /* 16KB per page */

/* ============================================
 * I/O Ports and Registers
 * ============================================ */

/* Primary slot select (I/O port) */
#define SLOT_SELECT_PORT    0xA8

/* Secondary slot register (memory mapped) */
#define SLOT_SECONDARY_REG  0xFFFF

/* ============================================
 * System Variables (Work Area)
 * ============================================ */

#define EXPTBL      0xFCC1  /* Slot expansion table (4 bytes) */
#define SLTTBL      0xFCC5  /* Current slot selections (4 bytes) */
#define SLTATR      0xFCC9  /* Slot attributes (64 bytes) */
#define SLTWRK      0xFD09  /* Slot work area (128 bytes) */

/* ============================================
 * Slot Macros
 * ============================================ */

/* Create slot byte from primary and secondary */
#define MAKE_SLOT(primary, secondary) \
    (SLOT_EXPANDED | (((secondary) & 0x03) << 4) | ((primary) & 0x03))

/* Create non-expanded slot byte */
#define MAKE_SLOT_PRIMARY(primary) \
    ((primary) & 0x03)

/* Extract primary slot from slot byte */
#define GET_PRIMARY_SLOT(slot) \
    ((slot) & 0x03)

/* Extract secondary slot from slot byte */
#define GET_SECONDARY_SLOT(slot) \
    (((slot) >> 4) & 0x03)

/* Check if slot is expanded */
#define IS_EXPANDED_SLOT(slot) \
    ((slot) & SLOT_EXPANDED)

/* Get page number from address */
#define ADDR_TO_PAGE(addr) \
    (((unsigned)(addr)) >> 14)

/* Get slot bits for specific page */
#define SLOT_FOR_PAGE(slot, page) \
    (((slot) & 0x03) << ((page) * 2))

/* ============================================
 * Slot Function Declarations
 * ============================================ */

/*
 * Read byte from specified slot
 * slot: slot number (use MAKE_SLOT or MAKE_SLOT_PRIMARY macros)
 * addr: memory address to read
 * Returns: byte read from slot
 *
 * Note: Uses BIOS RDSLT (0x000C)
 */
unsigned char slot_read(unsigned char slot, unsigned addr);

/*
 * Write byte to specified slot
 * slot: slot number
 * addr: memory address to write
 * value: byte value to write
 *
 * Note: Uses BIOS WRSLT (0x0014)
 */
void slot_write(unsigned char slot, unsigned addr, unsigned char value);

/*
 * Call routine in specified slot
 * slot: slot number
 * addr: address of routine to call
 *
 * Note: Uses BIOS CALSLT (0x001C)
 * Warning: Called routine should preserve IX register
 */
void slot_call(unsigned char slot, unsigned addr);

/*
 * Interslot call (alias for slot_call)
 */
void interslot_call(unsigned char slot, unsigned addr);

/*
 * Get slot number of currently executing code
 * Returns: slot number (including expansion info if applicable)
 *
 * Useful for ROM cartridges to determine their own slot
 */
int rom_get_slot(void);

/*
 * Check if primary slot is expanded
 * slot: primary slot number (0-3)
 * Returns: 1 if expanded, 0 if not
 */
int rom_is_expanded(int slot);

/*
 * Search all slots for ROM with specified signature
 * signature: pointer to 2-byte signature (typically "AB" for MSX ROM)
 * Returns: slot number if found, 0xFF if not found
 *
 * Searches all primary and secondary slots for ROM cartridge
 */
unsigned char slot_search(unsigned char *signature);

/* ============================================
 * BIOS Entry Points for Slot Operations
 * ============================================ */

#define BIOS_RDSLT      0x000C  /* Read from slot */
#define BIOS_WRSLT      0x0014  /* Write to slot */
#define BIOS_CALSLT     0x001C  /* Interslot call */
#define BIOS_ENASLT     0x0024  /* Enable slot */
#define BIOS_CALLF      0x0030  /* Interslot call (far) */

/* ============================================
 * Advanced Slot Operations (via BIOS)
 * ============================================ */

/*
 * Enable slot in specified page
 * Uses BIOS ENASLT - changes slot mapping
 *
 * These are declared in bios.h:
 *   void enaslt(int slot, unsigned addr);
 *   int rdslt(int slot, unsigned addr);
 *   void wrslt(int slot, unsigned addr, int data);
 *   void calslt(int slot, unsigned addr);
 */

/* ============================================
 * Slot Usage Examples
 * ============================================ */

/*
 * Example 1: Read from primary slot 1
 *   unsigned char data = slot_read(SLOT_1, 0x4000);
 *
 * Example 2: Read from expanded slot 2-1
 *   unsigned char data = slot_read(MAKE_SLOT(2, 1), 0x4000);
 *
 * Example 3: Get current ROM's slot
 *   int my_slot = rom_get_slot();
 *
 * Example 4: Search for ROM cartridge
 *   unsigned char sig[2] = {'A', 'B'};
 *   unsigned char rom_slot = slot_search(sig);
 *   if (rom_slot != 0xFF) {
 *       // Found ROM in slot rom_slot
 *   }
 *
 * Example 5: Call routine in another slot
 *   slot_call(MAKE_SLOT(1, 0), 0x4010);
 */

#endif /* _MSX_SLOT_H */
