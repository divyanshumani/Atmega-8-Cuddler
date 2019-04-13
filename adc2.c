/* adc2.c
 * This program demonstrates the use of ADMUX for selecting the ADC input pin
 */

#include <avr/io.h>

int main()
{
    DDRB = 0xFF; // port B output

    ADCSRA = _BV(ADEN) | _BV(ADPS2); // Enable ADC with prescaler=16

    while(1)
    {
        unsigned char compare_value = 0x7f;
        unsigned char x[4]; // Array to store values from multiple ADC inputs
        unsigned char i;
        for(i = 0; i < 4; i++)
        {
            // Select pin ADC[0..3] using MUX
            ADMUX = _BV(ADLAR) + i;

            // Start conversion
            ADCSRA |= _BV(ADSC);

            // wait until converstion completed
            while(ADCSRA & _BV(ADSC))
            {
            }

            if(ADCH > compare_value)
                x[i] = 1; // if value at the pin is greater than compare value
            else
                x[i] = 0;
        }
        if(x[0] == 1 || x[1] == 1 || x[2] == 1 || x[3] == 1)
            PORTB = 0xFF; // If voltage at all the four pins is greater than the threshold voltage
        else
            PORTB = 0x00;
    }
}
