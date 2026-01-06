/*
 * system.h - MSX System Variables and Work Area
 *
 * MSX BIOS uses a work area in RAM (0xF380-0xFFFF) to store
 * system state, screen settings, and hardware configurations.
 *
 * This header provides access to these system variables for
 * advanced programming and direct hardware access.
 *
 * Compatible with HI-TECH Z80 C Compiler.
 * This file does NOT modify any original HI-TECH C source files.
 */

#ifndef _MSX_SYSTEM_H
#define _MSX_SYSTEM_H

/* ============================================
 * Memory Access Macros
 * ============================================ */

/* Read byte from memory address */
#define PEEK(addr)          (*(volatile unsigned char *)(addr))

/* Write byte to memory address */
#define POKE(addr, val)     (*(volatile unsigned char *)(addr) = (val))

/* Read word (16-bit) from memory address */
#define PEEKW(addr)         (*(volatile unsigned int *)(addr))

/* Write word (16-bit) to memory address */
#define POKEW(addr, val)    (*(volatile unsigned int *)(addr) = (val))

/* ============================================
 * MSX Version Detection
 * ============================================ */

#define MSXVER      0x002D  /* MSX version (ROM) */
                            /* 0 = MSX1, 1 = MSX2, 2 = MSX2+, 3 = turboR */

/* MSX version constants */
#define MSX_VERSION_1       0
#define MSX_VERSION_2       1
#define MSX_VERSION_2PLUS   2
#define MSX_VERSION_TURBOR  3

/* Get MSX version */
#define GET_MSX_VERSION()   PEEK(MSXVER)

/* ============================================
 * Screen Settings (Text Mode)
 * ============================================ */

#define LINL40      0xF3AE  /* Width for SCREEN 0 (default: 40) */
#define LINL32      0xF3AF  /* Width for SCREEN 1 (default: 32) */
#define LINLEN      0xF3B0  /* Current line width */
#define CRTCNT      0xF3B1  /* Lines per screen (default: 24) */
#define CLMLST      0xF3B2  /* Last column for TAB (comma) */

/* ============================================
 * VRAM Table Addresses
 * ============================================ */

/* SCREEN 0 (40x24 text) */
#define TXTNAM      0xF3B3  /* Name table (word) */
#define TXTCOL      0xF3B5  /* Color table (word) - not used in SCREEN 0 */
#define TXTCGP      0xF3B7  /* Pattern generator (word) */
#define TXTATR      0xF3B9  /* Sprite attribute (word) - not used */
#define TXTPAT      0xF3BB  /* Sprite pattern (word) - not used */

/* SCREEN 1 (32x24 text) */
#define T32NAM      0xF3BD  /* Name table (word) */
#define T32COL      0xF3BF  /* Color table (word) */
#define T32CGP      0xF3C1  /* Pattern generator (word) */
#define T32ATR      0xF3C3  /* Sprite attribute (word) */
#define T32PAT      0xF3C5  /* Sprite pattern (word) */

/* SCREEN 2 (256x192 graphics) */
#define GRPNAM      0xF3C7  /* Name table (word) */
#define GRPCOL      0xF3C9  /* Color table (word) */
#define GRPCGP      0xF3CB  /* Pattern generator (word) */
#define GRPATR      0xF3CD  /* Sprite attribute (word) */
#define GRPPAT      0xF3CF  /* Sprite pattern (word) */

/* SCREEN 3 (64x48 multicolor) */
#define MLTNAM      0xF3D1  /* Name table (word) */
#define MLTCOL      0xF3D3  /* Color table (word) */
#define MLTCGP      0xF3D5  /* Pattern generator (word) */
#define MLTATR      0xF3D7  /* Sprite attribute (word) */
#define MLTPAT      0xF3D9  /* Sprite pattern (word) */

/* ============================================
 * Screen Colors
 * ============================================ */

#define FORCLR      0xF3E9  /* Foreground color */
#define BAKCLR      0xF3EA  /* Background color */
#define BDRCLR      0xF3EB  /* Border color */

/* ============================================
 * Cursor Position
 * ============================================ */

#define CSRY        0xF3DC  /* Cursor Y position (1-24) */
#define CSRX        0xF3DD  /* Cursor X position (1-40 or 1-80) */

/* ============================================
 * VDP Register Shadows
 * ============================================ */

#define RG0SAV      0xF3DF  /* VDP register 0 shadow */
#define RG1SAV      0xF3E0  /* VDP register 1 shadow */
#define RG2SAV      0xF3E1  /* VDP register 2 shadow */
#define RG3SAV      0xF3E2  /* VDP register 3 shadow */
#define RG4SAV      0xF3E3  /* VDP register 4 shadow */
#define RG5SAV      0xF3E4  /* VDP register 5 shadow */
#define RG6SAV      0xF3E5  /* VDP register 6 shadow */
#define RG7SAV      0xF3E6  /* VDP register 7 shadow */

/* MSX2 VDP register shadows (V9938/V9958) */
#define RG8SAV      0xFFE7  /* VDP register 8 shadow */
#define RG9SAV      0xFFE8  /* VDP register 9 shadow */
#define RG10SAV     0xFFE9  /* VDP register 10 shadow */
#define RG11SAV     0xFFEA  /* VDP register 11 shadow */
#define RG12SAV     0xFFEB  /* VDP register 12 shadow */
#define RG13SAV     0xFFEC  /* VDP register 13 shadow */
#define RG14SAV     0xFFED  /* VDP register 14 shadow */
#define RG15SAV     0xFFEE  /* VDP register 15 shadow */
#define RG16SAV     0xFFEF  /* VDP register 16 shadow */
#define RG17SAV     0xFFF0  /* VDP register 17 shadow */
#define RG18SAV     0xFFF1  /* VDP register 18 shadow */
#define RG19SAV     0xFFF2  /* VDP register 19 shadow */
#define RG20SAV     0xFFF3  /* VDP register 20 shadow */
#define RG21SAV     0xFFF4  /* VDP register 21 shadow */
#define RG22SAV     0xFFF5  /* VDP register 22 shadow */
#define RG23SAV     0xFFF6  /* VDP register 23 shadow */

/* ============================================
 * VDP Status
 * ============================================ */

#define STATFL      0xF3E7  /* VDP status register copy */

/* Status flag bits */
#define STAT_INT    0x80    /* Interrupt flag */
#define STAT_5S     0x40    /* 5th sprite flag */
#define STAT_COL    0x20    /* Sprite collision flag */
#define STAT_5SN    0x1F    /* 5th sprite number mask */

/* ============================================
 * Input Device Status
 * ============================================ */

#define TRGFLG      0xF3E8  /* Trigger button flag */
#define OLDKEY      0xFBDA  /* Old keyboard matrix (11 bytes) */
#define NEWKEY      0xFBE5  /* New keyboard matrix (11 bytes) */
#define KEYBUF      0xFBF0  /* Keyboard buffer (40 bytes) */

/* ============================================
 * Click Sound Control
 * ============================================ */

#define CLIKSW      0xF3DB  /* Key click switch (0=off, non-0=on) */
#define CLIKFL      0xF3DC  /* Key click flag */

/* ============================================
 * Screen Mode
 * ============================================ */

#define SCRMOD      0xFCAF  /* Current screen mode (0-8) */
#define OLDSCR      0xFCB0  /* Previous screen mode */
#define CATEFG      0xFCAE  /* MSX2: Character set flag */

/* ============================================
 * Console Flags
 * ============================================ */

#define CONSDFG     0xF3DE  /* Console status */
                            /* Bit 0: Function key display */
                            /* Bit 1: Key click enable */

/* ============================================
 * Timer/Interrupt
 * ============================================ */

#define JIFFY       0xFC9E  /* Timer counter (word, increments every VSYNC) */
#define INTCNT      0xFCA2  /* Interrupt counter */

/* ============================================
 * Music/Sound
 * ============================================ */

#define MUSICF      0xFB3E  /* Music flag */
#define PLESSION    0xFB3F  /* Music queue pointer */
#define VOTEFG      0xFBAD  /* Voice flag */

/* ============================================
 * Cassette Tape
 * ============================================ */

#define LOWLIM      0xFCA0  /* Tape low limit */
#define WINWID      0xFCA1  /* Tape window width */
#define HEADER      0xF3BE  /* Tape header type */
#define ASPTEFG     0xF3BF  /* Tape aspect flag */

/* ============================================
 * Slot Management
 * ============================================ */

#define EXPTBL      0xFCC1  /* Slot expansion table (4 bytes) */
                            /* Bit 7: 1=expanded, 0=not expanded */
#define SLTTBL      0xFCC5  /* Current slot selections (4 bytes) */
#define SLTATR      0xFCC9  /* Slot attributes (64 bytes) */
#define SLTWRK      0xFD09  /* Slot work area (128 bytes) */

/* ============================================
 * Device Control
 * ============================================ */

#define RAMTOP      0xFC4A  /* Top of RAM (word) */
#define HIMEM       0xFC4A  /* Same as RAMTOP */
#define STKTOP      0xF674  /* Stack top address (word) */
#define BOTTOM      0xFC48  /* Bottom of free area (word) */

/* ============================================
 * Disk/DOS Variables
 * ============================================ */

#define DISKVE      0xFFA7  /* Disk error vector (word) */
#define BREAKV      0xFFAB  /* Break vector (word) */

/* ============================================
 * MSX2 Specific Variables
 * ============================================ */

/* VDP ports (MSX2) */
#define VDP_PORT0   0x98    /* VRAM data read/write */
#define VDP_PORT1   0x99    /* VDP register/status */
#define VDP_PORT2   0x9A    /* Palette register */
#define VDP_PORT3   0x9B    /* Indirect register */

/* RTC (Real Time Clock) - MSX2 */
#define RTCBLK      0xFFCA  /* RTC block register */
#define RTCMOD      0xFFCB  /* RTC mode register */

/* ============================================
 * Hooks (Interrupt/Event Handlers)
 * ============================================ */

#define HTIMI       0xFD9F  /* Timer interrupt hook (5 bytes) */
#define HKEYI       0xFD9A  /* Key interrupt hook (5 bytes) */
#define HCHPU       0xFDA4  /* Character output hook */
#define HDSKO       0xFE21  /* Disk hook base */

/* ============================================
 * Utility Macros
 * ============================================ */

/* Get current screen mode */
#define GET_SCREEN_MODE()       PEEK(SCRMOD)

/* Get/Set foreground color */
#define GET_FORE_COLOR()        PEEK(FORCLR)
#define SET_FORE_COLOR(c)       POKE(FORCLR, (c))

/* Get/Set background color */
#define GET_BACK_COLOR()        PEEK(BAKCLR)
#define SET_BACK_COLOR(c)       POKE(BAKCLR, (c))

/* Get/Set border color */
#define GET_BORDER_COLOR()      PEEK(BDRCLR)
#define SET_BORDER_COLOR(c)     POKE(BDRCLR, (c))

/* Get cursor position */
#define GET_CURSOR_X()          PEEK(CSRX)
#define GET_CURSOR_Y()          PEEK(CSRY)

/* Get system timer (increments at VSYNC rate, ~50/60 Hz) */
#define GET_TIMER()             PEEKW(JIFFY)

/* Check if slot is expanded */
#define IS_SLOT_EXPANDED(slot)  (PEEK(EXPTBL + (slot)) & 0x80)

/* Enable/Disable key click */
#define KEY_CLICK_ON()          POKE(CLIKSW, 1)
#define KEY_CLICK_OFF()         POKE(CLIKSW, 0)

/* ============================================
 * System Information Functions
 * ============================================ */

/* Returns MSX version (0=MSX1, 1=MSX2, 2=MSX2+, 3=turboR) */
#define msx_version()           PEEK(MSXVER)

/* Returns non-zero if MSX2 or higher */
#define is_msx2()               (PEEK(MSXVER) >= 1)

/* Returns non-zero if MSX2+ or higher */
#define is_msx2plus()           (PEEK(MSXVER) >= 2)

/* Returns non-zero if turboR */
#define is_turbor()             (PEEK(MSXVER) >= 3)

#endif /* _MSX_SYSTEM_H */
