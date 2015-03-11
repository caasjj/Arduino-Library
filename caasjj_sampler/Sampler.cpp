/**********************************************************************************************
 * Arduino ADC Sampler Library - Version 0.0.1
 * by Walid Hosseini <caasjj@gmail.com> walidhosseini.com
 *
 * Uses the selected timer to sample the selected ADC channel at the selected smaple rate.
 * Data is provided to the caller via callback, thereby decoupling this call from the caller.
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#include <Sampler.h>

void (*_callback)(int);

/********************************************************************************************* 
 *
 * Sampler Constructure
 *
 *********************************************************************************************/ 
Sampler::Sampler(char adcChannel, int rateInHz, void (*callback)(int)) 
{

	_callback = callback;

	_rateInHz = rateInHz;
	_adcChannel = adcChannel;

    cli();

	timer_setup(rateInHz);

	// set up ADC
  	ADMUX  = B01000000 | (0xF & adcChannel);
  	ADCSRB = B00000000;
  
 	sei();

}

bool Sampler::start() {

	cli();

	timer_start();

	sei();
}

bool Sampler::stop() {

	cli();

	timer_stop();

	sei();
}


ISR(TIMER_VECTOR) {

	ADCSRA = B11001111;

}

ISR(ADC_vect) {

 _callback( ADCH << 8 | ADCL);

}