/*
 * bios.h - MSX BIOS function declarations
 *
 * MSX BIOS provides hardware abstraction for MSX computers.
 * These functions can be called from MSX-DOS programs or ROM software.
 *
 * Compatible with HI-TECH Z80 C Compiler.
 * This file does NOT modify any original HI-TECH C source files.
 */

#ifndef _MSX_BIOS_H
#define _MSX_BIOS_H

/* ============================================
 * Character I/O Functions
 * ============================================ */

/* Output character to screen (BIOS 0x00A2) */
void chput(char c);

/* Input character from keyboard (BIOS 0x009F) */
char chget(void);

/* Check keyboard buffer status (BIOS 0x009C) */
int chsns(void);

/* Output character to printer (BIOS 0x00A5) */
void lptout(char c);

/* Check printer status (BIOS 0x00A8) */
int lptstt(void);

/* ============================================
 * Screen Control Functions
 * ============================================ */

/* Clear screen (BIOS 0x00C3) */
void cls(void);

/* Set cursor position (BIOS 0x00C6) */
void posit(int x, int y);

/* Beep sound (BIOS 0x00C0) */
void beep(void);

/* Erase function key display (BIOS 0x00CC) */
void erafnk(void);

/* Display function key line (BIOS 0x00CF) */
void dspfnk(void);

/* Return to text mode (BIOS 0x00D2) */
void totext(void);

/* ============================================
 * Screen Mode Initialization
 * ============================================ */

/* Initialize SCREEN 0 - 40x24 text (BIOS 0x006C) */
void initxt(void);

/* Initialize SCREEN 1 - 32x24 text (BIOS 0x006F) */
void init32(void);

/* Initialize SCREEN 2 - 256x192 graphics (BIOS 0x0072) */
void inigrp(void);

/* Initialize SCREEN 3 - 64x48 multicolor (BIOS 0x0075) */
void inimlt(void);

/* Change screen mode (BIOS 0x005F) */
void chgmod(int mode);

/* Change screen colors (BIOS 0x0062) */
void chgclr(void);

/* ============================================
 * Input Device Functions
 * ============================================ */

/* Read joystick direction (BIOS 0x00D5)
 * stick: 0 = cursor keys, 1 = joystick A, 2 = joystick B
 * Returns: 0=center, 1=up, 2=up-right, 3=right, 4=down-right,
 *          5=down, 6=down-left, 7=left, 8=up-left
 */
int gtstck(int stick);

/* Read trigger button (BIOS 0x00D8)
 * trigger: 0=space, 1=joy A button 1, 2=joy B button 1,
 *          3=joy A button 2, 4=joy B button 2
 * Returns: 0=not pressed, -1(0xFF)=pressed
 */
int gttrig(int trigger);

/* Read paddle (BIOS 0x00DE) */
int gtpdl(int paddle);

/* Read touchpad (BIOS 0x00DB) */
int gtpad(int id);

/* ============================================
 * VDP Access Functions
 * ============================================ */

/* Write to VDP register (BIOS 0x0047) */
void wrtvdp(int reg, int data);

/* Read from VRAM (BIOS 0x004A) */
int rdvrm(unsigned addr);

/* Write to VRAM (BIOS 0x004D) */
void wrtvrm(unsigned addr, int data);

/* Set VDP for VRAM read (BIOS 0x0050) */
void setrd(unsigned addr);

/* Set VDP for VRAM write (BIOS 0x0053) */
void setwrt(unsigned addr);

/* Fill VRAM with value (BIOS 0x0056) */
void filvrm(unsigned addr, int data, unsigned count);

/* Copy from RAM to VRAM (BIOS 0x005C) */
void ldirvm(unsigned vram, void *ram, unsigned count);

/* Copy from VRAM to RAM (BIOS 0x0059) */
void ldirmv(void *ram, unsigned vram, unsigned count);

/* Disable screen display (BIOS 0x0041) */
void disscr(void);

/* Enable screen display (BIOS 0x0044) */
void enascr(void);

/* ============================================
 * Sprite Functions
 * ============================================ */

/* Clear all sprites (BIOS 0x0069) */
void clrspr(void);

/* Calculate sprite pattern address (BIOS 0x0084) */
unsigned calpat(int num);

/* Calculate sprite attribute address (BIOS 0x0087) */
unsigned calatr(int num);

/* Get sprite size (BIOS 0x008A) */
int gspsiz(void);

/* ============================================
 * PSG Sound Functions
 * ============================================ */

/* Initialize PSG (BIOS 0x0090) */
void gicini(void);

/* Write to PSG register (BIOS 0x0093) */
void wrtpsg(int reg, int data);

/* Read from PSG register (BIOS 0x0096) */
int rdpsg(int reg);

/* Start music (BIOS 0x0099) */
void strtms(void);

/* ============================================
 * Cassette Tape Functions
 * ============================================ */

/* Turn on cassette motor for read (BIOS 0x00E1) */
int tapion(void);

/* Read byte from cassette (BIOS 0x00E4) */
int tapin(void);

/* Turn off cassette motor after read (BIOS 0x00E7) */
void tapiof(void);

/* Turn on cassette motor for write (BIOS 0x00EA) */
int tapoon(int speed);

/* Write byte to cassette (BIOS 0x00ED) */
void tapout(int data);

/* Turn off cassette motor after write (BIOS 0x00F0) */
void tapoof(void);

/* Control cassette motor (BIOS 0x00F3) */
void stmotr(int action);

/* ============================================
 * Slot Management Functions
 * ============================================ */

/* Read from slot (BIOS 0x000C) */
int rdslt(int slot, unsigned addr);

/* Write to slot (BIOS 0x0014) */
void wrslt(int slot, unsigned addr, int data);

/* Call routine in slot (BIOS 0x001C) */
void calslt(int slot, unsigned addr);

/* Enable slot (BIOS 0x0024) */
void enaslt(int slot, unsigned addr);

/* ============================================
 * Keyboard Functions
 * ============================================ */

/* Check for break key (BIOS 0x00B7) */
int breakx(void);

/* Check for Ctrl-C (BIOS 0x00BA) */
int iscntc(void);

/* Check and execute Ctrl-C (BIOS 0x00BD) */
void ckcntc(void);

/* ============================================
 * BIOS Entry Point Addresses
 * ============================================ */

#define BIOS_CHKRAM  0x0000  /* Check RAM and set slot */
#define BIOS_SYNCHR  0x0008  /* Check BASIC character */
#define BIOS_RDSLT   0x000C  /* Read from slot */
#define BIOS_CHRGTR  0x0010  /* Get BASIC character */
#define BIOS_WRSLT   0x0014  /* Write to slot */
#define BIOS_OUTDO   0x0018  /* Output to device */
#define BIOS_CALSLT  0x001C  /* Call routine in slot */
#define BIOS_DCOMPR  0x0020  /* Compare HL and DE */
#define BIOS_ENASLT  0x0024  /* Enable slot */
#define BIOS_GETYPR  0x0028  /* Get BASIC type */
#define BIOS_CALLF   0x0030  /* Call far routine */
#define BIOS_KEYINT  0x0038  /* Keyboard interrupt handler */
#define BIOS_INITIO  0x003B  /* Initialize I/O */
#define BIOS_INIFNK  0x003E  /* Initialize function keys */
#define BIOS_DISSCR  0x0041  /* Disable screen */
#define BIOS_ENASCR  0x0044  /* Enable screen */
#define BIOS_WRTVDP  0x0047  /* Write to VDP register */
#define BIOS_RDVRM   0x004A  /* Read VRAM */
#define BIOS_WRTVRM  0x004D  /* Write VRAM */
#define BIOS_SETRD   0x0050  /* Set VDP for read */
#define BIOS_SETWRT  0x0053  /* Set VDP for write */
#define BIOS_FILVRM  0x0056  /* Fill VRAM */
#define BIOS_LDIRMV  0x0059  /* Copy VRAM to RAM */
#define BIOS_LDIRVM  0x005C  /* Copy RAM to VRAM */
#define BIOS_CHGMOD  0x005F  /* Change screen mode */
#define BIOS_CHGCLR  0x0062  /* Change colors */
#define BIOS_NMI     0x0066  /* NMI handler */
#define BIOS_CLRSPR  0x0069  /* Clear sprites */
#define BIOS_INITXT  0x006C  /* Initialize SCREEN 0 */
#define BIOS_INIT32  0x006F  /* Initialize SCREEN 1 */
#define BIOS_INIGRP  0x0072  /* Initialize SCREEN 2 */
#define BIOS_INIMLT  0x0075  /* Initialize SCREEN 3 */
#define BIOS_SETTXT  0x0078  /* Set SCREEN 0 */
#define BIOS_SETT32  0x007B  /* Set SCREEN 1 */
#define BIOS_SETGRP  0x007E  /* Set SCREEN 2 */
#define BIOS_SETMLT  0x0081  /* Set SCREEN 3 */
#define BIOS_CALPAT  0x0084  /* Calculate pattern address */
#define BIOS_CALATR  0x0087  /* Calculate attribute address */
#define BIOS_GSPSIZ  0x008A  /* Get sprite size */
#define BIOS_GRPPRT  0x008D  /* Print character in graphics mode */
#define BIOS_GICINI  0x0090  /* Initialize PSG */
#define BIOS_WRTPSG  0x0093  /* Write to PSG */
#define BIOS_RDPSG   0x0096  /* Read from PSG */
#define BIOS_STRTMS  0x0099  /* Start music */
#define BIOS_CHSNS   0x009C  /* Check keyboard buffer */
#define BIOS_CHGET   0x009F  /* Get character */
#define BIOS_CHPUT   0x00A2  /* Put character */
#define BIOS_LPTOUT  0x00A5  /* Output to printer */
#define BIOS_LPTSTT  0x00A8  /* Printer status */
#define BIOS_CNVCHR  0x00AB  /* Convert character */
#define BIOS_PINLIN  0x00AE  /* Input line */
#define BIOS_INLIN   0x00B1  /* Input line with prompt */
#define BIOS_QINLIN  0x00B4  /* Input line with '?' */
#define BIOS_BREAKX  0x00B7  /* Check STOP key */
#define BIOS_ISCNTC  0x00BA  /* Check Ctrl-C */
#define BIOS_CKCNTC  0x00BD  /* Execute Ctrl-C check */
#define BIOS_BEEP    0x00C0  /* Beep sound */
#define BIOS_CLS     0x00C3  /* Clear screen */
#define BIOS_POSIT   0x00C6  /* Set cursor position */
#define BIOS_FNKSB   0x00C9  /* Check function key display */
#define BIOS_ERAFNK  0x00CC  /* Erase function key line */
#define BIOS_DSPFNK  0x00CF  /* Display function key line */
#define BIOS_TOTEXT  0x00D2  /* Return to text mode */
#define BIOS_GTSTCK  0x00D5  /* Read joystick */
#define BIOS_GTTRIG  0x00D8  /* Read trigger button */
#define BIOS_GTPAD   0x00DB  /* Read touchpad */
#define BIOS_GTPDL   0x00DE  /* Read paddle */
#define BIOS_TAPION  0x00E1  /* Tape read motor on */
#define BIOS_TAPIN   0x00E4  /* Tape read byte */
#define BIOS_TAPIOF  0x00E7  /* Tape read motor off */
#define BIOS_TAPOON  0x00EA  /* Tape write motor on */
#define BIOS_TAPOUT  0x00ED  /* Tape write byte */
#define BIOS_TAPOOF  0x00F0  /* Tape write motor off */
#define BIOS_STMOTR  0x00F3  /* Tape motor control */
#define BIOS_LFTQ    0x00F6  /* Check PLAY queue */
#define BIOS_PUTQ    0x00F9  /* Put in PLAY queue */
#define BIOS_RIGHTC  0x00FC  /* Move cursor right */
#define BIOS_LEFTC   0x00FF  /* Move cursor left */
#define BIOS_UPC     0x0102  /* Move cursor up */
#define BIOS_TUPC    0x0105  /* Test and move up */
#define BIOS_DOWNC   0x0108  /* Move cursor down */
#define BIOS_TDOWNC  0x010B  /* Test and move down */
#define BIOS_SCALXY  0x010E  /* Scale X/Y coordinates */
#define BIOS_MAPXY   0x0111  /* Map X/Y to VRAM address */
#define BIOS_FETCHC  0x0114  /* Fetch cursor address */
#define BIOS_STOREC  0x0117  /* Store cursor address */
#define BIOS_SETATR  0x011A  /* Set attribute */
#define BIOS_READC   0x011D  /* Read character */
#define BIOS_SETC    0x0120  /* Set character */
#define BIOS_NSETCX  0x0123  /* Set characters */
#define BIOS_GTASPC  0x0126  /* Get aspect ratio */
#define BIOS_PNTINI  0x0129  /* Initialize PAINT */
#define BIOS_SCANR   0x012C  /* Scan right */
#define BIOS_SCANL   0x012F  /* Scan left */

/* ============================================
 * MSX System Variables (Work Area)
 * ============================================ */

#define SYSVARS_BASE  0xF380  /* Base of system variables */
#define LINL40        0xF3AE  /* Width for SCREEN 0 */
#define LINL32        0xF3AF  /* Width for SCREEN 1 */
#define LINLEN        0xF3B0  /* Current line width */
#define CRTCNT        0xF3B1  /* Lines per screen */
#define CLMLST        0xF3B2  /* Last column for comma */
#define TXTNAM        0xF3B3  /* SCREEN 0 name table */
#define TXTCOL        0xF3B5  /* SCREEN 0 color table */
#define TXTCGP        0xF3B7  /* SCREEN 0 pattern table */
#define TXTATR        0xF3B9  /* SCREEN 0 sprite attr */
#define TXTPAT        0xF3BB  /* SCREEN 0 sprite pattern */
#define T32NAM        0xF3BD  /* SCREEN 1 name table */
#define T32COL        0xF3BF  /* SCREEN 1 color table */
#define T32CGP        0xF3C1  /* SCREEN 1 pattern table */
#define T32ATR        0xF3C3  /* SCREEN 1 sprite attr */
#define T32PAT        0xF3C5  /* SCREEN 1 sprite pattern */
#define GRPNAM        0xF3C7  /* SCREEN 2 name table */
#define GRPCOL        0xF3C9  /* SCREEN 2 color table */
#define GRPCGP        0xF3CB  /* SCREEN 2 pattern table */
#define GRPATR        0xF3CD  /* SCREEN 2 sprite attr */
#define GRPPAT        0xF3CF  /* SCREEN 2 sprite pattern */
#define MLTNAM        0xF3D1  /* SCREEN 3 name table */
#define MLTCOL        0xF3D3  /* SCREEN 3 color table */
#define MLTCGP        0xF3D5  /* SCREEN 3 pattern table */
#define MLTATR        0xF3D7  /* SCREEN 3 sprite attr */
#define MLTPAT        0xF3D9  /* SCREEN 3 sprite pattern */
#define CLIKSW        0xF3DB  /* Key click switch */
#define CSRY          0xF3DC  /* Cursor Y position */
#define CSRX          0xF3DD  /* Cursor X position */
#define CONSDFG       0xF3DE  /* Console status */
#define RG0SAV        0xF3DF  /* VDP register 0 save */
#define RG1SAV        0xF3E0  /* VDP register 1 save */
#define RG2SAV        0xF3E1  /* VDP register 2 save */
#define RG3SAV        0xF3E2  /* VDP register 3 save */
#define RG4SAV        0xF3E3  /* VDP register 4 save */
#define RG5SAV        0xF3E4  /* VDP register 5 save */
#define RG6SAV        0xF3E5  /* VDP register 6 save */
#define RG7SAV        0xF3E6  /* VDP register 7 save */
#define STATFL        0xF3E7  /* VDP status register */
#define TRGFLG        0xF3E8  /* Trigger button status */
#define FORCLR        0xF3E9  /* Foreground color */
#define BAKCLR        0xF3EA  /* Background color */
#define BDRCLR        0xF3EB  /* Border color */
#define MAXUPD        0xF3EC  /* Max line update count */
#define MINUPD        0xF3EE  /* Min line update count */
#define ATTEFG        0xF3F0  /* Attribute flag */
#define JIFFY         0xFC9E  /* Timer counter (2 bytes) */
#define EXPTBL        0xFCC1  /* Slot expansion table */
#define SLTTBL        0xFCC5  /* Slot select table */
#define SLTATR        0xFCC9  /* Slot attributes */

#endif /* _MSX_BIOS_H */
