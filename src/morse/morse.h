#ifndef MORSE_H
#define MORSE_H

// delays for morse code dot and dashes
#define DOT_DELAY 70
#define DASH_DELAY 300

// misc delays
#define SPACE_DELAY 200
#define CHAR_PAUSE_DELAY 300
#define NEXT_DELAY 300
#define FINISHED_DELAY 1500

// hold translation info
typedef struct morse_code {
        uint8_t list[4];
            uint8_t count;
                char letter;
} morse_code;

// definitions
void morse_converter(uint8_t list[], uint8_t size);
void morse_dot(void);
void morse_dash(void);
void delay_ms(uint16_t count);

#endif
