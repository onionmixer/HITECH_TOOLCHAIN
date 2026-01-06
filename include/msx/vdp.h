/*
 * vdp.h - MSX VDP (TMS9918/V9938/V9958) definitions
 *
 * Provides constants and function declarations for VDP access.
 * Compatible with HI-TECH Z80 C Compiler.
 *
 * This file does NOT modify any original HI-TECH C source files.
 */

#ifndef _MSX_VDP_H
#define _MSX_VDP_H

/* ============================================
 * Screen Mode Constants
 * ============================================ */

#define SCREEN0     0   /* 40x24 text mode (TEXT1) */
#define SCREEN1     1   /* 32x24 text mode (GRAPHIC1) */
#define SCREEN2     2   /* 256x192 graphics (GRAPHIC2) */
#define SCREEN3     3   /* 64x48 multicolor (MULTICOLOR) */

/* MSX2 screen modes (V9938/V9958) */
#define SCREEN4     4   /* 256x192 graphics (GRAPHIC3) */
#define SCREEN5     5   /* 256x212 16-color (GRAPHIC4) */
#define SCREEN6     6   /* 512x212 4-color (GRAPHIC5) */
#define SCREEN7     7   /* 512x212 16-color (GRAPHIC6) */
#define SCREEN8     8   /* 256x212 256-color (GRAPHIC7) */

/* MSX2+ screen modes (V9958) */
#define SCREEN10    10  /* 256x212 YJK+YAE */
#define SCREEN11    11  /* 256x212 YJK */
#define SCREEN12    12  /* 256x212 YJK (256 colors) */

/* ============================================
 * VDP I/O Ports
 * ============================================ */

#define VDP_DATA    0x98    /* VRAM data read/write */
#define VDP_CMD     0x99    /* VDP register write/status read */
#define VDP_PALET   0x9A    /* Palette register (MSX2) */
#define VDP_IREG    0x9B    /* Indirect register (MSX2) */

/* ============================================
 * Color Constants
 * ============================================ */

#define COLOR_TRANSPARENT   0
#define COLOR_BLACK         1
#define COLOR_GREEN         2
#define COLOR_LIGHT_GREEN   3
#define COLOR_BLUE          4
#define COLOR_LIGHT_BLUE    5
#define COLOR_DARK_RED      6
#define COLOR_CYAN          7
#define COLOR_RED           8
#define COLOR_LIGHT_RED     9
#define COLOR_YELLOW        10
#define COLOR_LIGHT_YELLOW  11
#define COLOR_DARK_GREEN    12
#define COLOR_MAGENTA       13
#define COLOR_GRAY          14
#define COLOR_WHITE         15

/* Short color names */
#define TRANSPARENT     COLOR_TRANSPARENT
#define BLACK           COLOR_BLACK
#define GREEN           COLOR_GREEN
#define LIGHT_GREEN     COLOR_LIGHT_GREEN
#define BLUE            COLOR_BLUE
#define LIGHT_BLUE      COLOR_LIGHT_BLUE
#define DARK_RED        COLOR_DARK_RED
#define CYAN            COLOR_CYAN
#define RED             COLOR_RED
#define LIGHT_RED       COLOR_LIGHT_RED
#define YELLOW          COLOR_YELLOW
#define LIGHT_YELLOW    COLOR_LIGHT_YELLOW
#define DARK_GREEN      COLOR_DARK_GREEN
#define MAGENTA         COLOR_MAGENTA
#define GRAY            COLOR_GRAY
#define WHITE           COLOR_WHITE

/* ============================================
 * Sprite Constants
 * ============================================ */

#define SPRITE_8X8      0   /* 8x8 pixel sprites */
#define SPRITE_16X16    1   /* 16x16 pixel sprites */
#define SPRITE_MAGNIFY  2   /* Double size display */

#define MAX_SPRITES     32  /* Maximum sprites (MSX1) */
#define SPRITE_DISABLE  208 /* Y coordinate to disable sprite */

/* ============================================
 * VRAM Addresses (SCREEN 1 default)
 * ============================================ */

/* Screen 1 (32x24 text) */
#define S1_NAME_TBL     0x1800  /* Name table */
#define S1_COLOR_TBL    0x2000  /* Color table */
#define S1_PATTERN_TBL  0x0000  /* Pattern table */
#define S1_SPRITE_ATTR  0x1B00  /* Sprite attributes */
#define S1_SPRITE_PAT   0x3800  /* Sprite patterns */

/* Screen 2 (256x192 graphics) */
#define S2_NAME_TBL     0x1800  /* Name table */
#define S2_COLOR_TBL    0x2000  /* Color table */
#define S2_PATTERN_TBL  0x0000  /* Pattern table */
#define S2_SPRITE_ATTR  0x1B00  /* Sprite attributes */
#define S2_SPRITE_PAT   0x3800  /* Sprite patterns */

/* ============================================
 * VDP Register Bits
 * ============================================ */

/* Register 0 bits */
#define R0_EXTERNAL_VIDEO   0x01
#define R0_MODE_BIT1        0x02

/* Register 1 bits */
#define R1_SPRITE_MAG       0x01    /* Sprite magnify */
#define R1_SPRITE_SIZE      0x02    /* Sprite size (0=8x8, 1=16x16) */
#define R1_MODE_BIT3        0x08
#define R1_MODE_BIT2        0x10
#define R1_INT_ENABLE       0x20    /* Interrupt enable */
#define R1_SCREEN_ENABLE    0x40    /* Screen enable */
#define R1_VRAM_16K         0x80    /* 16KB VRAM */

/* Status register bits */
#define STATUS_INT          0x80    /* Interrupt flag */
#define STATUS_5S           0x40    /* 5th sprite flag */
#define STATUS_COLLISION    0x20    /* Sprite collision */
#define STATUS_5S_NUM       0x1F    /* 5th sprite number */

/* ============================================
 * VDP Function Declarations
 * ============================================ */

/* Screen mode control */
void vdp_set_mode(int mode);
int vdp_get_mode(void);

/* Color control */
void vdp_set_color(int fg, int bg, int border);
void vdp_set_color_table(unsigned addr, unsigned char *data, unsigned count);

/* VRAM access */
void vdp_write(unsigned addr, unsigned char data);
unsigned char vdp_read(unsigned addr);
void vdp_fill(unsigned addr, unsigned char data, unsigned count);
void vdp_copy_to_vram(unsigned addr, void *src, unsigned count);
void vdp_copy_from_vram(unsigned addr, void *dst, unsigned count);

/* VDP register access */
void vdp_set_reg(int reg, int data);
int vdp_get_status(void);

/* Screen enable/disable */
void vdp_screen_on(void);
void vdp_screen_off(void);

/* Sprite functions */
void vdp_set_sprite_mode(int size, int magnify);
void vdp_set_sprite_pattern(int num, void *pattern);
void vdp_set_sprite(int num, int x, int y, int pattern, int color);
void vdp_set_sprite_pos(int num, int x, int y);
void vdp_set_sprite_color(int num, int color);
void vdp_hide_sprite(int num);
void vdp_hide_all_sprites(void);
int vdp_sprite_collision(void);

/* Text output */
void vdp_locate(int x, int y);
void vdp_print(char *str);
void vdp_putchar(char c);
void vdp_cls(void);

/* Graphics primitives (SCREEN 2) */
void vdp_pset(int x, int y, int color);
int vdp_point(int x, int y);
void vdp_line(int x1, int y1, int x2, int y2, int color);
void vdp_box(int x1, int y1, int x2, int y2, int color);
void vdp_boxfill(int x1, int y1, int x2, int y2, int color);
void vdp_circle(int x, int y, int radius, int color);

/* Pattern/Tile functions */
void vdp_set_pattern(int num, void *pattern);
void vdp_put_tile(int x, int y, int tile);
int vdp_get_tile(int x, int y);

/* Wait for VSync */
void vdp_wait_vsync(void);

/* ============================================
 * Inline Port Access Macros
 * ============================================ */

/* Write data to VRAM port */
#define VDP_DATA_OUT(data)  outp(VDP_DATA, data)

/* Read data from VRAM port */
#define VDP_DATA_IN()       inp(VDP_DATA)

/* Write to VDP command port */
#define VDP_CMD_OUT(data)   outp(VDP_CMD, data)

/* Read VDP status */
#define VDP_STATUS_IN()     inp(VDP_CMD)

/* ============================================
 * Useful Macros
 * ============================================ */

/* Calculate VRAM address for Screen 1 name table */
#define S1_ADDR(x, y)       (S1_NAME_TBL + (y) * 32 + (x))

/* Calculate VRAM address for Screen 2 pattern table */
#define S2_PATTERN_ADDR(x, y)   (S2_PATTERN_TBL + ((y) >> 3) * 256 + ((y) & 7) + ((x) >> 3) * 8)

/* Make color byte (foreground << 4 | background) */
#define MAKE_COLOR(fg, bg)  (((fg) << 4) | (bg))

/* Sprite attribute byte format */
#define SPRITE_ATTR(y, x, pat, col) \
    { (y), (x), (pat), (col) }

/* Early clock bit for sprite X position */
#define SPRITE_EC           0x80

#endif /* _MSX_VDP_H */
