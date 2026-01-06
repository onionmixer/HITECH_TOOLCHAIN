/*
 * keycode.h - MSX Keyboard Codes and Matrix Definitions
 *
 * MSX keyboard is organized as an 11x8 matrix.
 * This header provides scan codes, ASCII codes, and matrix definitions.
 *
 * Compatible with HI-TECH Z80 C Compiler.
 * This file does NOT modify any original HI-TECH C source files.
 */

#ifndef _MSX_KEYCODE_H
#define _MSX_KEYCODE_H

/* ============================================
 * Keyboard Matrix Layout (MSX Standard)
 * ============================================
 *
 * Row 0: 7 6 5 4 3 2 1 0
 * Row 1: ; ] [ \ = - 9 8
 * Row 2: B A _ / . , ` '
 * Row 3: J I H G F E D C
 * Row 4: R Q P O N M L K
 * Row 5: Z Y X W V U T S
 * Row 6: F3 F2 F1 CODE CAP GRAPH CTRL SHIFT
 * Row 7: RET SEL BS STOP TAB ESC F5 F4
 * Row 8: RIGHT DOWN UP LEFT DEL INS HOME SPACE
 * Row 9: NUM4 NUM3 NUM2 NUM1 NUM0 NUM/ NUM+ NUM*
 * Row 10: NUM. NUM, NUM- NUM9 NUM8 NUM7 NUM6 NUM5
 *
 * ============================================ */

/* ============================================
 * Keyboard Matrix Row/Column
 * ============================================ */

/* Keyboard matrix system addresses */
#define NEWKEY_BASE     0xFBE5  /* Current key state (11 bytes) */
#define OLDKEY_BASE     0xFBDA  /* Previous key state (11 bytes) */

/* Keyboard row definitions */
#define KEY_ROW_0       0
#define KEY_ROW_1       1
#define KEY_ROW_2       2
#define KEY_ROW_3       3
#define KEY_ROW_4       4
#define KEY_ROW_5       5
#define KEY_ROW_6       6
#define KEY_ROW_7       7
#define KEY_ROW_8       8
#define KEY_ROW_9       9
#define KEY_ROW_10      10

/* ============================================
 * Key Matrix Positions (row, bit)
 * ============================================ */

/* Row 0: 7 6 5 4 3 2 1 0 */
#define KEY_0           0, 0x01
#define KEY_1           0, 0x02
#define KEY_2           0, 0x04
#define KEY_3           0, 0x08
#define KEY_4           0, 0x10
#define KEY_5           0, 0x20
#define KEY_6           0, 0x40
#define KEY_7           0, 0x80

/* Row 1: ; ] [ \ = - 9 8 */
#define KEY_8           1, 0x01
#define KEY_9           1, 0x02
#define KEY_MINUS       1, 0x04
#define KEY_EQUAL       1, 0x08
#define KEY_BACKSLASH   1, 0x10
#define KEY_LBRACKET    1, 0x20
#define KEY_RBRACKET    1, 0x40
#define KEY_SEMICOLON   1, 0x80

/* Row 2: B A accent / . , grave ' */
#define KEY_APOSTROPHE  2, 0x01
#define KEY_GRAVE       2, 0x02
#define KEY_COMMA       2, 0x04
#define KEY_PERIOD      2, 0x08
#define KEY_SLASH       2, 0x10
#define KEY_ACCENT      2, 0x20
#define KEY_A           2, 0x40
#define KEY_B           2, 0x80

/* Row 3: J I H G F E D C */
#define KEY_C           3, 0x01
#define KEY_D           3, 0x02
#define KEY_E           3, 0x04
#define KEY_F           3, 0x08
#define KEY_G           3, 0x10
#define KEY_H           3, 0x20
#define KEY_I           3, 0x40
#define KEY_J           3, 0x80

/* Row 4: R Q P O N M L K */
#define KEY_K           4, 0x01
#define KEY_L           4, 0x02
#define KEY_M           4, 0x04
#define KEY_N           4, 0x08
#define KEY_O           4, 0x10
#define KEY_P           4, 0x20
#define KEY_Q           4, 0x40
#define KEY_R           4, 0x80

/* Row 5: Z Y X W V U T S */
#define KEY_S           5, 0x01
#define KEY_T           5, 0x02
#define KEY_U           5, 0x04
#define KEY_V           5, 0x08
#define KEY_W           5, 0x10
#define KEY_X           5, 0x20
#define KEY_Y           5, 0x40
#define KEY_Z           5, 0x80

/* Row 6: F3 F2 F1 CODE CAP GRAPH CTRL SHIFT */
#define KEY_SHIFT       6, 0x01
#define KEY_CTRL        6, 0x02
#define KEY_GRAPH       6, 0x04
#define KEY_CAPS        6, 0x08
#define KEY_CODE        6, 0x10
#define KEY_F1          6, 0x20
#define KEY_F2          6, 0x40
#define KEY_F3          6, 0x80

/* Row 7: RET SEL BS STOP TAB ESC F5 F4 */
#define KEY_F4          7, 0x01
#define KEY_F5          7, 0x02
#define KEY_ESC         7, 0x04
#define KEY_TAB         7, 0x08
#define KEY_STOP        7, 0x10
#define KEY_BS          7, 0x20
#define KEY_SELECT      7, 0x40
#define KEY_RETURN      7, 0x80
#define KEY_ENTER       7, 0x80  /* Alias */

/* Row 8: RIGHT DOWN UP LEFT DEL INS HOME SPACE */
#define KEY_SPACE       8, 0x01
#define KEY_HOME        8, 0x02
#define KEY_INS         8, 0x04
#define KEY_DEL         8, 0x08
#define KEY_LEFT        8, 0x10
#define KEY_UP          8, 0x20
#define KEY_DOWN        8, 0x40
#define KEY_RIGHT       8, 0x80

/* Row 9: NUM4 NUM3 NUM2 NUM1 NUM0 NUM/ NUM+ NUM* */
#define KEY_NUM_MULT    9, 0x01
#define KEY_NUM_PLUS    9, 0x02
#define KEY_NUM_DIV     9, 0x04
#define KEY_NUM_0       9, 0x08
#define KEY_NUM_1       9, 0x10
#define KEY_NUM_2       9, 0x20
#define KEY_NUM_3       9, 0x40
#define KEY_NUM_4       9, 0x80

/* Row 10: NUM. NUM, NUM- NUM9 NUM8 NUM7 NUM6 NUM5 */
#define KEY_NUM_5       10, 0x01
#define KEY_NUM_6       10, 0x02
#define KEY_NUM_7       10, 0x04
#define KEY_NUM_8       10, 0x08
#define KEY_NUM_9       10, 0x10
#define KEY_NUM_MINUS   10, 0x20
#define KEY_NUM_COMMA   10, 0x40
#define KEY_NUM_PERIOD  10, 0x80

/* ============================================
 * ASCII Character Codes
 * ============================================ */

/* Control characters */
#define CHAR_NUL        0x00
#define CHAR_SOH        0x01
#define CHAR_STX        0x02
#define CHAR_ETX        0x03    /* Ctrl+C */
#define CHAR_EOT        0x04
#define CHAR_ENQ        0x05
#define CHAR_ACK        0x06
#define CHAR_BEL        0x07    /* Bell */
#define CHAR_BS         0x08    /* Backspace */
#define CHAR_TAB        0x09    /* Tab */
#define CHAR_LF         0x0A    /* Line Feed */
#define CHAR_VT         0x0B
#define CHAR_FF         0x0C    /* Form Feed (CLS) */
#define CHAR_CR         0x0D    /* Carriage Return */
#define CHAR_SO         0x0E
#define CHAR_SI         0x0F
#define CHAR_DLE        0x10
#define CHAR_HOME       0x0B    /* Home (same as VT) */
#define CHAR_CLS        0x0C    /* Clear screen (same as FF) */
#define CHAR_INS        0x12    /* Insert mode */
#define CHAR_DEL        0x7F    /* Delete */
#define CHAR_ESC        0x1B    /* Escape */
#define CHAR_SPACE      0x20    /* Space */

/* Cursor movement (MSX specific codes) */
#define CHAR_RIGHT      0x1C    /* Cursor right */
#define CHAR_LEFT       0x1D    /* Cursor left */
#define CHAR_UP         0x1E    /* Cursor up */
#define CHAR_DOWN       0x1F    /* Cursor down */

/* Function key codes (when pressed alone) */
#define CHAR_F1         0x81    /* F1 key */
#define CHAR_F2         0x82    /* F2 key */
#define CHAR_F3         0x83    /* F3 key */
#define CHAR_F4         0x84    /* F4 key */
#define CHAR_F5         0x85    /* F5 key */

/* Additional MSX special codes */
#define CHAR_SELECT     0x18    /* SELECT key */
#define CHAR_STOP       0x03    /* STOP key (same as Ctrl+C) */

/* ============================================
 * Keyboard Scan Functions
 * ============================================ */

/* Read keyboard matrix row (0-10)
 * Returns: bit mask of pressed keys in that row
 * Use with KEY_xxx bit definitions above
 */
unsigned char kb_read_row(unsigned char row);

/* Check if specific key is pressed
 * row: keyboard row (0-10)
 * mask: bit mask for the key
 * Returns: non-zero if pressed
 *
 * Example: if (kb_is_pressed(KEY_SPACE)) { ... }
 */
#define kb_is_pressed(row, mask) (kb_read_row(row) & (mask))

/* Wait for any key press and return ASCII code
 * Uses BIOS CHGET
 */
char kb_wait_key(void);

/* Check if key is in keyboard buffer
 * Uses BIOS CHSNS
 * Returns: non-zero if key available
 */
int kb_key_available(void);

/* ============================================
 * Keyboard Matrix Direct Access
 * ============================================ */

/* I/O port for keyboard scanning */
#define KB_ROW_SELECT   0xAA    /* PPI Port C - select row */
#define KB_COL_READ     0xA9    /* PPI Port B - read columns */

/* Direct matrix read via I/O ports */
#define KB_DIRECT_READ(row) \
    (outp(KB_ROW_SELECT, (row) | 0x40), inp(KB_COL_READ))

/* ============================================
 * Modifier Key Detection
 * ============================================ */

/* Check if SHIFT is pressed */
#define IS_SHIFT_PRESSED()  kb_is_pressed(KEY_SHIFT)

/* Check if CTRL is pressed */
#define IS_CTRL_PRESSED()   kb_is_pressed(KEY_CTRL)

/* Check if GRAPH is pressed */
#define IS_GRAPH_PRESSED()  kb_is_pressed(KEY_GRAPH)

/* Check if CODE is pressed */
#define IS_CODE_PRESSED()   kb_is_pressed(KEY_CODE)

/* Check if CAPS is active (toggle state in system area) */
#define IS_CAPS_ACTIVE()    (PEEK(0xFCAC) & 0x40)

/* ============================================
 * Joystick Direction Values (from GTSTCK)
 * ============================================ */

#define JOY_CENTER      0
#define JOY_UP          1
#define JOY_UP_RIGHT    2
#define JOY_RIGHT       3
#define JOY_DOWN_RIGHT  4
#define JOY_DOWN        5
#define JOY_DOWN_LEFT   6
#define JOY_LEFT        7
#define JOY_UP_LEFT     8

/* Joystick IDs for GTSTCK/GTTRIG */
#define JOY_CURSOR      0   /* Cursor keys */
#define JOY_PORT1       1   /* Joystick port 1 */
#define JOY_PORT2       2   /* Joystick port 2 */

/* Trigger button IDs for GTTRIG */
#define TRIG_SPACE      0   /* Space bar */
#define TRIG_JOY1_A     1   /* Joystick 1, button A */
#define TRIG_JOY2_A     2   /* Joystick 2, button A */
#define TRIG_JOY1_B     3   /* Joystick 1, button B */
#define TRIG_JOY2_B     4   /* Joystick 2, button B */

/* ============================================
 * Common Key Combinations
 * ============================================ */

/* Check for Ctrl+C (break) */
#define IS_CTRL_C() \
    (IS_CTRL_PRESSED() && kb_is_pressed(KEY_C))

/* Check for any arrow key */
#define IS_ANY_ARROW() \
    (kb_is_pressed(KEY_UP) || kb_is_pressed(KEY_DOWN) || \
     kb_is_pressed(KEY_LEFT) || kb_is_pressed(KEY_RIGHT))

#endif /* _MSX_KEYCODE_H */
