/* Program used for bidirectional motor drive
 * -------------------------------------------
 * Motor is connected between PB0 and PB1 through proper buffers
 * If PD0 is made high, the motor will rotate forward, else it rotates backwards
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
    DDRD = 0x00;  // PORTD as INPUT
    PORTD = 0xff; // To enable internal pullups

    while(1) // Infinite loop
    {
        if(is_high(PIND, PD0))
        {
            sbi(PORTB, PB0); // Motor runs forward
            cbi(PORTB, PB1);
        }
        else
        {
            sbi(PORTB, PB1); // Now runs backwards
            cbi(PORTB, PB0);
        }
    }
    return 0;
}
