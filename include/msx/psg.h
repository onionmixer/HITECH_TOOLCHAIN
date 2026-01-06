/*
 * psg.h - MSX PSG (AY-3-8910) Sound Chip Definitions
 *
 * The PSG (Programmable Sound Generator) provides 3 tone channels,
 * 1 noise channel, and envelope generation for MSX computers.
 *
 * Compatible with HI-TECH Z80 C Compiler.
 * This file does NOT modify any original HI-TECH C source files.
 */

#ifndef _MSX_PSG_H
#define _MSX_PSG_H

/* ============================================
 * PSG I/O Ports
 * ============================================ */

#define PSG_ADDR    0xA0    /* Register address port */
#define PSG_WRITE   0xA1    /* Data write port */
#define PSG_READ    0xA2    /* Data read port */

/* ============================================
 * PSG Register Numbers
 * ============================================ */

/* Channel A (tone) */
#define PSG_REG_A_FINE      0   /* Channel A fine tune (8 bits) */
#define PSG_REG_A_COARSE    1   /* Channel A coarse tune (4 bits) */

/* Channel B (tone) */
#define PSG_REG_B_FINE      2   /* Channel B fine tune (8 bits) */
#define PSG_REG_B_COARSE    3   /* Channel B coarse tune (4 bits) */

/* Channel C (tone) */
#define PSG_REG_C_FINE      4   /* Channel C fine tune (8 bits) */
#define PSG_REG_C_COARSE    5   /* Channel C coarse tune (4 bits) */

/* Noise */
#define PSG_REG_NOISE       6   /* Noise period (5 bits) */

/* Mixer */
#define PSG_REG_MIXER       7   /* Tone/Noise enable (6 bits) + I/O */

/* Volume */
#define PSG_REG_A_VOL       8   /* Channel A volume (4 bits) + envelope */
#define PSG_REG_B_VOL       9   /* Channel B volume (4 bits) + envelope */
#define PSG_REG_C_VOL       10  /* Channel C volume (4 bits) + envelope */

/* Envelope */
#define PSG_REG_ENV_FINE    11  /* Envelope period fine (8 bits) */
#define PSG_REG_ENV_COARSE  12  /* Envelope period coarse (8 bits) */
#define PSG_REG_ENV_SHAPE   13  /* Envelope shape (4 bits) */

/* I/O ports (accent mark on PSG) */
#define PSG_REG_IO_A        14  /* I/O port A data */
#define PSG_REG_IO_B        15  /* I/O port B data */

/* ============================================
 * Mixer Control Bits
 * ============================================ */

/* Tone enable (0=enable, 1=disable) */
#define PSG_TONE_A_OFF      0x01
#define PSG_TONE_B_OFF      0x02
#define PSG_TONE_C_OFF      0x04

/* Noise enable (0=enable, 1=disable) */
#define PSG_NOISE_A_OFF     0x08
#define PSG_NOISE_B_OFF     0x10
#define PSG_NOISE_C_OFF     0x20

/* I/O port direction (0=input, 1=output) */
#define PSG_IO_A_OUT        0x40
#define PSG_IO_B_OUT        0x80

/* Common mixer configurations */
#define PSG_ALL_OFF         0x3F    /* All tone and noise off */
#define PSG_TONE_ONLY       0x38    /* Tone on, noise off */
#define PSG_NOISE_ONLY      0x07    /* Noise on, tone off */
#define PSG_ALL_ON          0x00    /* All tone and noise on */

/* ============================================
 * Volume Control
 * ============================================ */

#define PSG_VOL_OFF         0x00    /* Volume off */
#define PSG_VOL_MIN         0x01    /* Minimum volume */
#define PSG_VOL_MAX         0x0F    /* Maximum volume */
#define PSG_VOL_ENV         0x10    /* Use envelope for volume */

/* ============================================
 * Envelope Shapes
 * ============================================ */

/*
 * Envelope shape bits: CONT|ATT|ALT|HOLD
 *
 * CONT (Continue): 0=stop at 0, 1=continue
 * ATT (Attack): 0=decay, 1=attack
 * ALT (Alternate): 0=same direction, 1=reverse direction
 * HOLD (Hold): 0=continue cycling, 1=hold at end
 */

#define PSG_ENV_DECAY           0x00    /* \__________ */
#define PSG_ENV_ATTACK          0x04    /* /__________  */
#define PSG_ENV_SAW_DOWN        0x08    /* \|\|\|\|\|\ */
#define PSG_ENV_SAW_DOWN_HOLD   0x09    /* \__________ */
#define PSG_ENV_TRIANGLE_DOWN   0x0A    /* \/\/\/\/\/\ */
#define PSG_ENV_HOLD_HIGH       0x0B    /* \^^^^^^^^^^  */
#define PSG_ENV_SAW_UP          0x0C    /* /|/|/|/|/|/ */
#define PSG_ENV_HOLD_HIGH2      0x0D    /* /^^^^^^^^^^  */
#define PSG_ENV_TRIANGLE_UP     0x0E    /* /\/\/\/\/\/ */
#define PSG_ENV_SAW_UP_HOLD     0x0F    /* /__________  */

/* ============================================
 * Frequency/Period Calculations
 * ============================================ */

/* MSX clock frequency (Hz) */
#define PSG_CLOCK           1789772

/* Calculate tone period from frequency (Hz)
 * Period = Clock / (16 * Frequency)
 */
#define PSG_FREQ_TO_PERIOD(freq)    (PSG_CLOCK / (16 * (freq)))

/* Calculate envelope period from frequency (Hz)
 * Period = Clock / (256 * Frequency)
 */
#define PSG_ENV_FREQ_TO_PERIOD(freq)    (PSG_CLOCK / (256 * (freq)))

/* Note frequencies (Hz) - Middle octave */
#define NOTE_C4     262
#define NOTE_CS4    277     /* C# */
#define NOTE_D4     294
#define NOTE_DS4    311     /* D# */
#define NOTE_E4     330
#define NOTE_F4     349
#define NOTE_FS4    370     /* F# */
#define NOTE_G4     392
#define NOTE_GS4    415     /* G# */
#define NOTE_A4     440     /* Standard tuning */
#define NOTE_AS4    466     /* A# */
#define NOTE_B4     494

/* ============================================
 * PSG Function Declarations
 * ============================================ */

/* Initialization */
void psg_init(void);            /* Initialize PSG (silence all) */
void psg_silence(void);         /* Silence all channels */

/* Low-level register access */
void psg_write(int reg, int value);     /* Write to PSG register */
int psg_read(int reg);                  /* Read from PSG register */

/* Tone control */
void psg_tone(int channel, unsigned period);    /* Set tone period */
void psg_freq(int channel, unsigned freq);      /* Set frequency in Hz */
void psg_note(int channel, int note, int octave);   /* Set musical note */

/* Volume control */
void psg_volume(int channel, int vol);  /* Set channel volume (0-15) */
void psg_envelope_vol(int channel);     /* Use envelope for volume */

/* Noise control */
void psg_noise(int period);             /* Set noise period (0-31) */

/* Mixer control */
void psg_mixer(int value);              /* Set mixer directly */
void psg_channel_on(int channel, int tone, int noise); /* Enable channel */
void psg_channel_off(int channel);      /* Disable channel */

/* Envelope control */
void psg_envelope_period(unsigned period);  /* Set envelope period */
void psg_envelope_shape(int shape);         /* Set envelope shape */
void psg_envelope(unsigned period, int shape);  /* Set both */

/* Convenience functions */
void psg_play_tone(int channel, unsigned freq, int vol);
void psg_beep(unsigned freq, int duration); /* Simple beep */

/* ============================================
 * Inline Register Access Macros
 * ============================================ */

/* Write to PSG register (inline) */
#define PSG_WRITE(reg, val) do { \
    outp(PSG_ADDR, (reg)); \
    outp(PSG_WRITE, (val)); \
} while(0)

/* Read from PSG register (inline) */
#define PSG_READ(reg) (outp(PSG_ADDR, (reg)), inp(PSG_READ))

/* ============================================
 * Channel Number Constants
 * ============================================ */

#define PSG_CHANNEL_A   0
#define PSG_CHANNEL_B   1
#define PSG_CHANNEL_C   2

#endif /* _MSX_PSG_H */
