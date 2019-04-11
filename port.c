/* port_test5.c
 * Generates a PWM wave on pin PB0
 * The PWM duty cycle rises from 0% to 100% and then jumps back to zero.
 */

#include <avr/io.h> // Standard include for AVR

#define sbi(x, y) x |= _BV(y)    // set bit
#define cbi(x, y) x &= ~(_BV(y)) // clear bit
#define tbi(x, y) x ^= _BV(y)    // toggle bit
#define is_high(x, y) ((x & _BV(y)) == _BV(y))

int main()
{
    DDRB = 0xff; // PORTB as OUTPUT
    PORTB = 0x00;

    while(1) // Infinite loop
    {
        unsigned char i, j, k;
        for(j = 0; j < 100; j++)
        {
            for(k = 0; k < 255; k++)
            {
                for(i = 0; i < 100; i++)
                {
                    if(i < j)
                        sbi(PORTB, PB0);
                    else
                        cbi(PORTB, PB0);
                }
            }
        }
    }
    return 0;
}
