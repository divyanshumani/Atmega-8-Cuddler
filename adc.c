#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupts.h>	// file to be included if using interrupts

static volatile uint8_t adc_value = 0;

void avr_init(void);

ISR(ADC_vect)
{
    adc_value = ADCH;
    ADCSRA |= _BV(ADSC);
}

int main()
{
    avr_init();
    sei(); // Enable interrupts
    ADCSRA |= _BV(ADSC);
    while(1)
    {
        OCR0 = adc_value; // Instead of starting conversion and waiting for it here, it is done in the interrupt routine
    }
    return 0;
}

void avr_init()
{
    DDRB = 0xff; // PORTB output
    PORTB = 0x00;
    OCR0 = 0;
    TCCR0 = _BV(WGM01) | _BV(WGM00) | _BV(COM01) | _BV(CS00); // Fast pwm with 1 prescaler with 16Mhz to get pwm freq 62.5kHz
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADIE); // Prescaler 64 with 16Mhz to get sampling freq 19.2kHz
    ADMUX = _BV(ADLAR);
}
