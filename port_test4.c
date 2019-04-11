/* port_test4.c
 * This program checks the 0th pin of port D for input and if it is ON (Logic 1), keeps writing 1 to
 * 0th pin of port B else if it is OFF (Logic 0), it toggles pin 0 of port B
 */

#include <inttypes.h> // short forms for various integer types

#include <avr/io.h> // Standard include for AVR

#define F_CPU 16000000UL // Crystal frequency required for delay functions

#include <util/delay.h> // Delay functions

#define sbi(x, y) x |= _BV(y)                  // set bit
#define cbi(x, y) x &= ~(_BV(y))               // clear bit
#define tbi(x, y) x ^= _BV(y)                  // toggle bit
#define is_high(x, y) ((x & _BV(y)) == _BV(y)) // check if the input pin is high
#define is_low(x, y) ((x & _BV(y)) == 0)       // check if the input pin is low

int main()
{
    DDRB = 0xff; // PORTB as OUTPUT
    PORTB = 0x00;
    DDRD = 0x00;  // PORTD as INPUT
    PORTD = 0xff; // Enable Pull-up on the input port

    while(1) // Infinite loop
    {
        uint8_t i;

        for(i = 0; i < 2; i++)
        {
            if(i == 0)
            {
                sbi(PORTB, PB0);
            }
            else if(i == 1)
            {
                if(is_low(PIND, PD0))
                {
                    cbi(PORTB, PB0);
                }
                else
                {
                    sbi(PORTB, PB0);
                }
            }
            _delay_ms(100);
        }
    }
    return 0;
}
