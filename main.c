#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

/*--------------------Libraries---------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#include "inc/uart.h"

/*--------------------Variables---------------------------*/
char String[25]; // Stores sequence of characters
char PrintChar[25]; // Used to print character
volatile int start = 0; // Stores tick at which button was pressed down
volatile int end = 0; // Stores tick at which button was lifted
volatile int duration = 0; // Stores duration of button press
volatile int prior_duration = 0; // Stores duration of prior button press
volatile int count = 0; // Stores number of spaces printed consecutively
volatile int k = 0; // Length of morse
/*-----------------------------------------------------------*/

void Initialize()
{
    cli(); // Disable global interrupts

    DDRB &= ~(1<<DDB0); // Set PB0 to be input pin
    DDRB |= (1<<DDB1);// Set PB5 to the output pin (blue LED)
    DDRB |= (1<<DDB2);// Set PB5 to the output pin (red LED)

    // Timer1 Setup
    // Set Timer 1 clock to have prescaler of 256
    TCCR1B &= ~(1<<CS10);
    TCCR1B &= ~(1<<CS11);
    TCCR1B |= (1<<CS12);

    // Set timer 1 to normal
    TCCR1A &= ~(1 << WGM10);
    TCCR1A &= ~(1 << WGM11);
    TCCR1B &= ~(1 << WGM12);
    TCCR1B &= ~(1 << WGM13);

    TCCR1B |= (1<<ICES1); // Looking for rising edge

    TIMSK1 |= (1<<ICIE1); // Enable input capture interrupt

    TIFR1 |= (1<<ICF1); // Clear input capture flag

    sei(); // Enable global interrupts

}

ISR(TIMER1_CAPT_vect)
{
    if (TCCR1B & (1<<ICES1)) { // rising edge is occurring
        start = TCNT1;
    }
    else {
        end = TCNT1;

        if (end >= start) {
            duration = end - start;
        } else {
            duration = end - start + 65536; // 2^16 = 65536 = no. of ticks before overflow
        }
    }
    TIFR1 |= (1<<ICF1); // Clear input capture flag
    TCCR1B ^= (1<<ICES1); // Toggle trigger

}

void Letter() {
   // Comparing current string with morse code for each letter

   if (strcmp(String, "._") == 0) {
       sprintf(PrintChar,"A");
       UART_putstring(PrintChar);
   }else if (strcmp(String, "_...") == 0) {
       // B
       sprintf(PrintChar, "B");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "_._.") == 0) {
       // C
       sprintf(PrintChar, "C");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "_..") == 0) {
       // D
       sprintf(PrintChar, "D");
       UART_putstring(PrintChar);
   } else if (strcmp(String, ".") == 0) {
       // E
       sprintf(PrintChar, "E");
       UART_putstring(PrintChar);
   } else if (strcmp(String, ".._.") == 0) {
       // F
       sprintf(PrintChar, "F");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "__.") == 0) {
       // G
       sprintf(PrintChar, "G");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "....") == 0) {
       // H
       sprintf(PrintChar, "H");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "..") == 0) {
       // I
       sprintf(PrintChar, "I");
       UART_putstring(PrintChar);
   } else if (strcmp(String, ".___") == 0) {
       // J
       sprintf(PrintChar, "J");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "_._") == 0) {
       // K
       sprintf(PrintChar, "K");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "._..") == 0) {
       // L
       sprintf(PrintChar, "L");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "__") == 0) {
       // M
       sprintf(PrintChar, "M");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "_.") == 0) {
       // N
       sprintf(PrintChar, "N");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "___") == 0) {
       // O
       sprintf(PrintChar, "O");
       UART_putstring(PrintChar);
   } else if (strcmp(String, ".__.") == 0) {
       // P
       sprintf(PrintChar, "P");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "__._") == 0) {
       // Q
       sprintf(PrintChar, "Q");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "._.") == 0) {
       // R
       sprintf(PrintChar, "R");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "...") == 0) {
       // S
       sprintf(PrintChar, "S");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "_") == 0) {
       // T
       sprintf(PrintChar, "T");
       UART_putstring(PrintChar);
   } else if (strcmp(String, ".._") == 0) {
       // U
       sprintf(PrintChar, "U");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "..._") == 0) {
       // V
       sprintf(PrintChar, "V");
       UART_putstring(PrintChar);
   } else if (strcmp(String, ".__") == 0) {
       // W
       sprintf(PrintChar, "W");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "_.._") == 0) {
       // X
       sprintf(PrintChar, "X");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "_.__") == 0) {
       // Y
       sprintf(PrintChar, "Y");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "__..") == 0) {
       // Z
       sprintf(PrintChar, "Z");
       UART_putstring(PrintChar);
   } else if (strcmp(String, ".____") == 0) {
       // 1
       sprintf(PrintChar, "1");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "..___") == 0) {
       // 2
       sprintf(PrintChar, "2");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "...__") == 0) {
       // 3
       sprintf(PrintChar, "3");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "...._") == 0) {
       // 4
       sprintf(PrintChar, "4");
       UART_putstring(PrintChar);
   } else if (strcmp(String, ".....") == 0) {
       // 5
       sprintf(PrintChar, "5");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "_....") == 0) {
       // 6
       sprintf(PrintChar, "6");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "__...") == 0) {
       // 7
       sprintf(PrintChar, "7");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "___..") == 0) {
       // 8
       sprintf(PrintChar, "8");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "____.") == 0) {
       // 9
       sprintf(PrintChar, "9");
       UART_putstring(PrintChar);
   } else if (strcmp(String, "_____") == 0) {
       // 0
       sprintf(PrintChar, "0");
       UART_putstring(PrintChar);
   }
    for (int i = 0; i < 25; i++) {
        String[i] = '\0';
        k = 0;
    }

}

int main(void)
{
    UART_init(BAUD_PRESCALER);

    Initialize();
    while(1)
    {

        // desired tick count = ((16*10^16) / (256 * 1000)) * 30 or 200 or 400

        if (duration != prior_duration) {
            if (duration >= 1875 && duration < 12500) {
                String[k] = '.';
                k ++;
                PORTB |= (1<<PORTB1);
                _delay_ms(50);
                PORTB &= ~(1<<PORTB1);
            }
            else if (duration >= 12500 && duration < 25000) {
                String[k] = '_';
                k ++;
                PORTB |= (1<<PORTB2);
                _delay_ms(50);
                PORTB &= ~(1<<PORTB2);
            }

            prior_duration = duration;
            count = 0;
        }

        if (TCNT1 - end >= 62500 && count == 0) { // 400 ms is 25000 ticks but I'm choosing 1000 ms
            count = 1;
            Letter();
        }

    }

}


