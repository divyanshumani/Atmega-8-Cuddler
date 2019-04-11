/* port_test3.c
 * Turns one of the pins PB0,PB1,PB2,PB3 high depending on the inputs PD0 and PD1
 * Can be used for controlling two motors bidirectionally only one motor runs at a time.
 */

#include <avr/io.h> // Standard include for AVR

#define sbi(x, y) x |= _BV(y)                  // set bit
#define cbi(x, y) x &= ~(_BV(y))               // clear bit
#define tbi(x, y) x ^= _BV(y)                  // toggle bit
#define is_high(x, y) ((x & _BV(y)) == _BV(y)) //(for input) checks if the input is high (Logic 1)

int main()
{
    DDRB = 0xff; // PORTB as OUTPUT
    PORTB = 0x00;
    DDRD = 0x00; // PORTD as INPUT
    PORTD = 0xff;

    while(1) // Infinite loop
    {
        if(is_high(PIND, PD0) && is_high(PIND, PD1))
        {
            cbi(PORTB, PB0); // First motor stopped
            cbi(PORTB, PB1);
            cbi(PORTB, PB2); // Second motor running forward
            sbi(PORTB, PB3);
        }
        else if(is_high(PIND, PD0) && !is_high(PIND, PD1))
        {
            cbi(PORTB, PB0); // First motor running forward
            sbi(PORTB, PB1);
            cbi(PORTB, PB2); // Second motor stopped
            cbi(PORTB, PB3);
        }
        else if(!is_high(PIND, PD0) && is_high(PIND, PD1))
        {
            cbi(PORTB, PB0); // First motor stopped
            cbi(PORTB, PB1);
            sbi(PORTB, PB2); // Second motor running backwards
            cbi(PORTB, PB3);
        }
        else if(!is_high(PIND, PD0) && !is_high(PIND, PD1))
        {
            sbi(PORTB, PB0); // First motor running backwards
            cbi(PORTB, PB1);
            cbi(PORTB, PB2); // Second motor stopped
            cbi(PORTB, PB3);
        }
    }
    return 0;
}
