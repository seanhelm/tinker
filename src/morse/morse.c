#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "morse.h"

int main(void)
{
    // phrase to translate
    const char phrase[] = "ab cdefz";

    // set pin 5 of PORTB for output
    DDRB |= _BV(DDB5);

    // used for morse code translation
    const morse_code codes[] = {
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
        //translate every letter
        for(i = 0; i < sizeof(phrase) - 1; i++) {
            uint8_t j;

            // use ASCII for index
            char letter = tolower(phrase[i]);
            
            // if the current letter is a space
            if(letter == 32) {
                delay_ms(SPACE_DELAY);
            } else if(letter >= 97 && letter <= 122
                    && codes[letter - 97].letter == letter) {
                // otherwise translate letter
                morse_converter(codes[letter - 97].list, codes[letter - 97].count);
            }
            delay_ms(NEXT_DELAY);
        }
        delay_ms(FINISHED_DELAY);
    }
}

// output morse code to pin
void morse_converter(const uint8_t list[], uint8_t size) {
    uint8_t i;
    for(i = 0; i < size; i++) {
        if(list[i] == 0) {
            morse_dot();
        } else if(list[i] == 1) {
            morse_dash();
        }
    }
}

// morse code dot
void morse_dot(void) {
    PORTB |= _BV(PORTB5);
    delay_ms(DOT_DELAY);

    PORTB &= ~_BV(PORTB5);
    delay_ms(CHAR_PAUSE_DELAY);
}

// morse code dash
void morse_dash(void) {
    PORTB |= _BV(PORTB5);
    delay_ms(DASH_DELAY);

    PORTB &= ~_BV(PORTB5);
    delay_ms(CHAR_PAUSE_DELAY);
}

// delay by count ms
void delay_ms(uint16_t count) {
    while(count--) {
        _delay_ms(1);
    }
}
