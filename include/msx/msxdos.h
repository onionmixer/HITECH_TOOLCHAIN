/*
 * msxdos.h - MSX-DOS System Definitions
 *
 * MSX-DOS is highly compatible with CP/M 2.2.
 * This header provides MSX-DOS specific extensions.
 *
 * Compatible with HI-TECH Z80 C Compiler.
 * This file does NOT modify any original HI-TECH C source files.
 */

#ifndef _MSX_MSXDOS_H
#define _MSX_MSXDOS_H

/* ============================================
 * MSX-DOS System Addresses
 * ============================================ */

#define MSXDOS_BDOS     0x0005  /* BDOS entry point */
#define MSXDOS_CMDTAIL  0x0080  /* Command tail buffer */
#define MSXDOS_FCB1     0x005C  /* Default FCB 1 */
#define MSXDOS_FCB2     0x006C  /* Default FCB 2 */
#define MSXDOS_DMA      0x0080  /* Default DMA address */
#define MSXDOS_TPA      0x0100  /* Transient Program Area */

/* ============================================
 * BDOS Function Numbers (CP/M Compatible)
 * ============================================ */

#define BDOS_SYSTEM_RESET       0   /* Warm boot */
#define BDOS_CONSOLE_INPUT      1   /* Read character from console */
#define BDOS_CONSOLE_OUTPUT     2   /* Write character to console */
#define BDOS_READER_INPUT       3   /* Read from reader device */
#define BDOS_PUNCH_OUTPUT       4   /* Write to punch device */
#define BDOS_LIST_OUTPUT        5   /* Write to list device */
#define BDOS_DIRECT_CON_IO      6   /* Direct console I/O */
#define BDOS_GET_IOBYTE         7   /* Get I/O byte */
#define BDOS_SET_IOBYTE         8   /* Set I/O byte */
#define BDOS_PRINT_STRING       9   /* Print string ($ terminated) */
#define BDOS_READ_CONSOLE_BUF   10  /* Read console buffer */
#define BDOS_GET_CONSOLE_STATUS 11  /* Get console status */
#define BDOS_GET_VERSION        12  /* Return version number */
#define BDOS_DISK_RESET         13  /* Reset disk system */
#define BDOS_SELECT_DISK        14  /* Select disk */
#define BDOS_OPEN_FILE          15  /* Open file */
#define BDOS_CLOSE_FILE         16  /* Close file */
#define BDOS_SEARCH_FIRST       17  /* Search for first match */
#define BDOS_SEARCH_NEXT        18  /* Search for next match */
#define BDOS_DELETE_FILE        19  /* Delete file */
#define BDOS_SEQ_READ           20  /* Sequential read */
#define BDOS_SEQ_WRITE          21  /* Sequential write */
#define BDOS_CREATE_FILE        22  /* Create file */
#define BDOS_RENAME_FILE        23  /* Rename file */
#define BDOS_GET_LOGIN_VECTOR   24  /* Get login vector */
#define BDOS_GET_CURRENT_DISK   25  /* Get current disk */
#define BDOS_SET_DMA            26  /* Set DMA address */
#define BDOS_GET_ALLOC_VECTOR   27  /* Get allocation vector */
#define BDOS_WRITE_PROTECT      28  /* Write protect disk */
#define BDOS_GET_RO_VECTOR      29  /* Get read-only vector */
#define BDOS_SET_FILE_ATTR      30  /* Set file attributes */
#define BDOS_GET_DPB            31  /* Get disk parameter block */
#define BDOS_GET_SET_USER       32  /* Get/set user number */
#define BDOS_RANDOM_READ        33  /* Random read */
#define BDOS_RANDOM_WRITE       34  /* Random write */
#define BDOS_GET_FILE_SIZE      35  /* Compute file size */
#define BDOS_SET_RANDOM_REC     36  /* Set random record */
#define BDOS_RESET_DRIVE        37  /* Reset drive */
#define BDOS_RANDOM_WRITE_ZERO  40  /* Random write with zero fill */

/* ============================================
 * MSX-DOS 2.x Extensions
 * ============================================ */

#define BDOS_GET_DATE           42  /* Get date (DOS2) */
#define BDOS_SET_DATE           43  /* Set date (DOS2) */
#define BDOS_GET_TIME           44  /* Get time (DOS2) */
#define BDOS_SET_TIME           45  /* Set time (DOS2) */
#define BDOS_GET_ENV            46  /* Get environment string (DOS2) */
#define BDOS_SET_ENV            47  /* Set environment string (DOS2) */
#define BDOS_FIND_ENV           48  /* Find environment string (DOS2) */
#define BDOS_GET_DISK_PARAM     49  /* Get disk parameters (DOS2) */
#define BDOS_GET_VERIFY         50  /* Get verify flag (DOS2) */
#define BDOS_SET_VERIFY         51  /* Set verify flag (DOS2) */

/* Extended functions (DOS2 0x40+) */
#define BDOS_GET_DOSVER         0x6F    /* Get DOS version */

/* ============================================
 * FCB (File Control Block) Structure
 * ============================================ */

typedef struct {
    unsigned char dr;       /* Drive (0=default, 1=A, 2=B...) */
    unsigned char f[8];     /* Filename (space padded) */
    unsigned char t[3];     /* Extension (space padded) */
    unsigned char ex;       /* Extent number */
    unsigned char s1;       /* Reserved */
    unsigned char s2;       /* Reserved */
    unsigned char rc;       /* Record count */
    unsigned char d[16];    /* Reserved for DOS */
    unsigned char cr;       /* Current record */
    unsigned char r0;       /* Random record (low) */
    unsigned char r1;       /* Random record (mid) */
    unsigned char r2;       /* Random record (high) */
} FCB;

/* ============================================
 * Date/Time Structures (MSX-DOS 2)
 * ============================================ */

typedef struct {
    unsigned int year;      /* 1980-2079 */
    unsigned char month;    /* 1-12 */
    unsigned char day;      /* 1-31 */
} MSXDOS_DATE;

typedef struct {
    unsigned char hour;     /* 0-23 */
    unsigned char minute;   /* 0-59 */
    unsigned char second;   /* 0-59 */
} MSXDOS_TIME;

/* ============================================
 * BDOS Function Declarations
 * ============================================ */

/* Low-level BDOS call */
int bdos(int func, int de);

/* Console I/O */
int dos_getchar(void);              /* BDOS 1 */
void dos_putchar(char c);           /* BDOS 2 */
int dos_kbhit(void);                /* BDOS 11 */
void dos_puts(char *str);           /* BDOS 9 */
void dos_gets(char *buf, int max);  /* BDOS 10 */

/* Disk operations */
int dos_get_drive(void);            /* BDOS 25 */
void dos_set_drive(int drive);      /* BDOS 14 */
void dos_reset_disk(void);          /* BDOS 13 */

/* File operations */
int dos_open(FCB *fcb);             /* BDOS 15 */
int dos_close(FCB *fcb);            /* BDOS 16 */
int dos_create(FCB *fcb);           /* BDOS 22 */
int dos_delete(FCB *fcb);           /* BDOS 19 */
int dos_rename(FCB *fcb);           /* BDOS 23 */
int dos_read(FCB *fcb);             /* BDOS 20 */
int dos_write(FCB *fcb);            /* BDOS 21 */
void dos_set_dma(void *addr);       /* BDOS 26 */

/* Version info */
int dos_version(void);              /* BDOS 12 */

/* ============================================
 * MSX-DOS 2 Extensions
 * ============================================ */

/* Date/Time (DOS2 only) */
void dos2_get_date(MSXDOS_DATE *date);
void dos2_set_date(MSXDOS_DATE *date);
void dos2_get_time(MSXDOS_TIME *time);
void dos2_set_time(MSXDOS_TIME *time);

/* Environment (DOS2 only) */
int dos2_getenv(char *name, char *buf, int maxlen);
int dos2_setenv(char *name, char *value);

/* Directory functions (DOS2 only) */
int dos2_mkdir(char *path);             /* Create directory */
int dos2_rmdir(char *path);             /* Remove directory */
int dos2_chdir(char *path);             /* Change directory */
int dos2_getcwd(char *buf, int maxlen); /* Get current directory */

/* Memory mapper (DOS2 only) */
int dos2_get_mapper_info(void);         /* Get mapper info */
int dos2_alloc_segment(void);           /* Allocate segment */
void dos2_free_segment(int segment);    /* Free segment */
void dos2_put_segment(int page, int segment);  /* Put segment in page */
int dos2_get_segment(int page);         /* Get segment from page */

/* ============================================
 * Error Codes
 * ============================================ */

#define MSXDOS_ERR_NONE         0x00    /* No error */
#define MSXDOS_ERR_INCOMP       0x01    /* Incompatible disk */
#define MSXDOS_ERR_WRITE_ERR    0x02    /* Write error */
#define MSXDOS_ERR_READ_ERR     0x03    /* Read error */
#define MSXDOS_ERR_WRITE_PROT   0x04    /* Write protected */
#define MSXDOS_ERR_NOT_READY    0x05    /* Not ready */
#define MSXDOS_ERR_SEEK_ERR     0x06    /* Seek error */
#define MSXDOS_ERR_NOT_FOUND    0x07    /* File not found */
#define MSXDOS_ERR_EXISTS       0x08    /* File exists */
#define MSXDOS_ERR_CANT_DELETE  0x09    /* Cannot delete */
#define MSXDOS_ERR_NO_SPACE     0x0A    /* Insufficient space */
#define MSXDOS_ERR_DISK_ERR     0x0B    /* Disk error */
#define MSXDOS_ERR_FCB          0x0C    /* FCB error */
#define MSXDOS_ERR_EOF          0x0D    /* End of file */

/* ============================================
 * Inline BDOS Call Macro
 * ============================================ */

/* Call BDOS with function in C and argument in DE
 * Returns value in A (or HL for some functions)
 */
#define BDOS_CALL(func, arg) bdos((func), (arg))

#endif /* _MSX_MSXDOS_H */
