/* adc1.c
 * Basic usage of the ADC as a comparator
 */

#include <avr/io.h>

#define sbi(x, y) x |= _BV(y)
#define cbi(x, y) x &= ~_BV(y)

#define COMPARE_VALUE 125

int main()
{
    DDRB = 0xff; // PORTB as output
    PORTB = 0x00;
    DDRA = 0x00;  // PORTA set as input (since we want to take inputs for the ADC)
    PORTA = 0xff; // Enable the pull-ups on PORTA

    ADMUX = _BV(ADLAR); // Enable the Left aligning of the ADC result

    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // Enable the ADC with prescaler=128

    ADCSRA |= _BV(ADSC); // Set the bit to start the conversion

    while(1)
    {
        while(ADCSRA & _BV(ADSC)) // Wait for ADC conversion to complete
        {
        }

        if(ADCH >= COMPARE_VALUE)
        {
            sbi(PORTB, PB1); // Suppose a motor between PB0 and PB1 with proper buffers
            cbi(PORTB, PB0); // In this case, the motor runs forward
        }
        else if(ADCH < COMPARE_VALUE)
        {
            sbi(PORTB, PB0); // Here the motor runs backward
            cbi(PORTB, PB1);
        }
        ADCSRA |= _BV(ADSC); // Set the bit to start conversion again
    }
    return 0;
}
