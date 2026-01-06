/*
 * sprite.h - MSX Sprite definitions and structures
 *
 * Provides sprite structures and helper macros.
 * Compatible with HI-TECH Z80 C Compiler.
 */

#ifndef _MSX_SPRITE_H
#define _MSX_SPRITE_H

/* ============================================
 * Sprite Attribute Structure
 * ============================================ */

/* Sprite attribute entry (4 bytes) */
typedef struct {
    unsigned char y;        /* Y position (0-191, 208=disable) */
    unsigned char x;        /* X position (0-255) */
    unsigned char pattern;  /* Pattern number */
    unsigned char color;    /* Color (0-15) + EC bit */
} SPRITE_ATTR;

/* ============================================
 * Sprite Constants
 * ============================================ */

#define SPRITE_SIZE_8X8     0
#define SPRITE_SIZE_16X16   1

#define SPRITE_MAG_1X       0
#define SPRITE_MAG_2X       1

#define SPRITE_MAX          32
#define SPRITE_Y_DISABLE    208
#define SPRITE_Y_HIDDEN     209

/* Early clock bit (shift sprite 32 pixels left) */
#define SPRITE_EC_BIT       0x80

/* ============================================
 * Sprite Pattern Sizes
 * ============================================ */

#define SPRITE_PAT_SIZE_8   8   /* 8x8 sprite pattern size */
#define SPRITE_PAT_SIZE_16  32  /* 16x16 sprite pattern size */

/* ============================================
 * Sprite Helper Macros
 * ============================================ */

/* Create sprite attribute entry */
#define SPRITE_DEF(y, x, pat, col) { (y)-1, (x), (pat), (col) }

/* Disable sprite (set Y to 208) */
#define SPRITE_DISABLE(s)   ((s)->y = SPRITE_Y_DISABLE)

/* Set sprite color with early clock */
#define SPRITE_COLOR_EC(col)    ((col) | SPRITE_EC_BIT)

/* ============================================
 * 8x8 Sprite Pattern Template
 * ============================================ */

/* Define 8x8 sprite pattern */
#define SPRITE_8X8(name, b0,b1,b2,b3,b4,b5,b6,b7) \
    unsigned char name[8] = { b0,b1,b2,b3,b4,b5,b6,b7 }

/* ============================================
 * 16x16 Sprite Pattern Template
 * 16x16 sprites are stored as 4 8x8 quadrants:
 * Top-left, Bottom-left, Top-right, Bottom-right
 * ============================================ */

/* 16x16 sprite quadrant structure */
typedef struct {
    unsigned char tl[8];    /* Top-left quadrant */
    unsigned char bl[8];    /* Bottom-left quadrant */
    unsigned char tr[8];    /* Top-right quadrant */
    unsigned char br[8];    /* Bottom-right quadrant */
} SPRITE_16X16;

/* ============================================
 * Common Sprite Shapes (8x8)
 * ============================================ */

/* Arrow pointing right */
#define SPRITE_ARROW_RIGHT \
    { 0x10, 0x18, 0xFC, 0xFE, 0xFC, 0x18, 0x10, 0x00 }

/* Arrow pointing down */
#define SPRITE_ARROW_DOWN \
    { 0x10, 0x10, 0x10, 0xD6, 0x7C, 0x38, 0x10, 0x00 }

/* Simple ball/circle */
#define SPRITE_BALL \
    { 0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C }

/* Diamond shape */
#define SPRITE_DIAMOND \
    { 0x10, 0x38, 0x7C, 0xFE, 0x7C, 0x38, 0x10, 0x00 }

/* Cross/plus sign */
#define SPRITE_CROSS \
    { 0x10, 0x10, 0x10, 0xFE, 0x10, 0x10, 0x10, 0x00 }

/* Square */
#define SPRITE_SQUARE \
    { 0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF }

/* Filled square */
#define SPRITE_SQUARE_FILL \
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }

#endif /* _MSX_SPRITE_H */
