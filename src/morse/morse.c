#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define DOT_DELAY 70
#define DASH_DELAY 300
#define CHAR_PAUSE_DELAY 300
#define NEXT_DELAY 300
#define FINISHED_DELAY 1500

typedef struct morse_code {
    uint8_t list[4];
    uint8_t count;
    char letter;
} morse_code;

void morse_converter(uint8_t list[], uint8_t size);
void morse_dot(void);
void morse_dash(void);
void delay_ms(uint16_t count);

int main(void)
{
    const char phrase[] = "an example message abcdefghijklmnopqrstuvwxyz";

    // set pin 5 of PORTB for output
    DDRB |= _BV(DDB5);

    // used for morse code translation
    morse_code codes[] = {
        {{-1, -1, -1, -1},  0, ' '},
        {{0, 1, -1, -1},    2, 'a'},
        {{1, 0, 0, 0},      4, 'b'},
        {{1, 0, 1, 0},      4, 'c'},
        {{1, 0, 0, -1},     3, 'd'},
        {{0, -1, -1, -1},   1, 'e'},
        {{0, 0, 1, 0},      4, 'f'},
        {{1, 1, 0, -1},     3, 'g'},
        {{0, 0, 0, 0},      4, 'h'},
        {{0, 0, -1, -1},    2, 'i'},
        {{0, 1, 1, 1},      4, 'j'},
        {{1, 0, 1, -1},     3, 'k'},
        {{0, 1, 0, 0},      4, 'l'},
        {{1, 1, -1, -1},    2, 'm'},
        {{1, 0, -1, -1},    2, 'n'},
        {{1, 1, 1, -1},     3, 'o'},
        {{0, 1, 1, 0},      4, 'p'},
        {{1, 1, 0, 1},      4, 'q'},
        {{0, 1, 0, -1},     3, 'r'},
        {{0, 0, 0, -1},     3, 's'},
        {{1, -1, -1, -1},   1, 't'},
        {{0, 0, 1, -1},     3, 'u'},
        {{0, 0, 0, 1},      4, 'v'},
        {{0, 1, 1, -1},     3, 'w'},
        {{1, 0, 0, 1},      4, 'x'},
        {{1, 0, 1, 1},      4, 'y'},
        {{1, 1, 0, 0},      4, 'z'}
    };

    for(;;) {
        uint8_t i;
        for(i = 0; i < sizeof(phrase) - 1; i++) {
            uint8_t j;
            for(j = 0; j < (sizeof(codes) / sizeof(morse_code)); j++) {
                if(codes[j].letter == tolower(phrase[i])) {
                    morse_converter(codes[j].list, codes[j].count);
                }
            }

            delay_ms(NEXT_DELAY);
        }

        delay_ms(FINISHED_DELAY);
    }
}

void morse_converter(uint8_t list[], uint8_t size) {
    uint8_t i;
    for(i = 0; i < size; i++) {
        if(list[i] == 0) {
            morse_dot();
        } else if(list[i] == 1) {
            morse_dash();
        }
    }
}

// Morse code dot
void morse_dot(void) {
    PORTB |= _BV(PORTB5);
    delay_ms(DOT_DELAY);

    PORTB &= ~_BV(PORTB5);
    delay_ms(CHAR_PAUSE_DELAY);
}

// Morse code dash
void morse_dash(void) {
    PORTB |= _BV(PORTB5);
    delay_ms(DASH_DELAY);

    PORTB &= ~_BV(PORTB5);
    delay_ms(CHAR_PAUSE_DELAY);
}

// Delay by count ms
void delay_ms(uint16_t count) {
    while(count--) {
        _delay_ms(1);
    }
}
