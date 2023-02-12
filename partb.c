#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void Initialize()
{
cli();
DDRB |= (1<<DDB5);// Set PB5 to the output pin
DDRB &= ~(1<<DDB0); // Set PB0 to be input pin

    // Looking for rising edge
    TCCR1B |= (1<<ICES1);

    // Enable input capture interrupt
    TIMSK1 |= (1<<ICIE1);

    sei(); // Enable global interrupts

}
int main(void)
{
Initialize();
while(1)
{
}

}

ISR(TIMER1_CAPT_vect)
{
TIFR1 |= (1<<ICF1); // Clear input capture flag
PORTB ^= (1<<PORTB5);
TCCR1B ^= (1<<ICES1);
}
