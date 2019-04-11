/* port_test.c
 * The following program just keeps toggling pin 0 of port B
 */

#include <avr/io.h> // Standard include for AVR

#define F_CPU 16000000UL // Crystal frequency required for delay functions

#include <util/delay.h> // Delay functions

#define sbi(x, y) x |= _BV(y)                // set bit - using bitwise OR operator
#define cbi(x, y) x &= ~(_BV(y))             // clear bit - using bitwise AND operator
#define tbi(x, y) x ^= _BV(y)                // toggle bit - using bitwise XOR operator
#define is_high(x, y) (x & _BV(y) == _BV(y)) // check if the y'th bit of register 'x' is high

/* _BV(a) is a macro which returns the value corresponding to 2 to the power 'a'.
 * Thus _BV(PX3) would be 0x08 or 0b00001000. */

int main()
{
    DDRB = 0xff;  // PORTB as OUTPUT
    PORTB = 0x00; // All pins of PORTB LOW

    while(1) // Infinite loop
    {
        _delay_ms(500);  // Delay for 500 ms
        tbi(PORTB, PB0); // the toggling takes place here
    }

    return 0;
}
