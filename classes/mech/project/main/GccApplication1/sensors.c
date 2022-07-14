/*
 * sensors.c
 *
 * Created: 3/22/2022 3:08:09 PM
 *  Author: Shane
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define ADC_PRESCALER 0b00000111

// Initialization check
static int initialized_sensors = 0;
static int initialized_buttons = 0;

// External prototypes
#include "sensors.h"
#include "screen.h"

// Test strings
static char test_string_one[] = "Lit/Moist/Rock";
static char test_string_two[] = "%d/%d/%d";

// Internal prototypes
int read_adc();
void switch_adc(int pin);

/******************************* Test Program Code *************************/
void test_sensors()
{

	// Allocate space on stack
	char line_two[17];

	// Init screen
	init_screen();

	// Init sensors
	init_sensors();

	// Read sensors
	int light = read_light();
	int moist = read_moist();
	int rocker = read_rocker();

	// Print onto lines
	sprintf(line_two, test_string_two, light, moist, rocker);

	// Write lines to screen
	write_to_screen(test_string_one, line_two);

	// Wait 3s
	_delay_ms(5000);

	// Clear screen
	clear_screen();
}
/******************************* End of Test Program Code ******************/

/******************************* External Functions *************************/

// Init sensors
void init_sensors()
{

	if (!initialized_sensors)
	{
		// Rocker setup

		// Set DDR as input
		rocker_in_ddr &= ~(1 << rocker_in_bit);

		// Photosensor setup
		// Simple A/D conversion

		// Set DDR
		photo_in_ddr &= ~(1 << photo_in_bit);
		moist_in_ddr &= ~(1 << moist_in_bit);

		// ADMUX set in switch_adc, default to photo for now
		switch_adc(moist_in_adc_bit);

		// Turn on ADC
		PRR = 0x00;

		// Enable ADC
		ADCSRA = ADC_PRESCALER; // Set prescaler
		ADCSRA |= (1 << ADEN);	// Set bit

		// Ensure no duplicate call
		initialized_sensors = 1;
	}
}

void init_buttons()
{
	if (!initialized_buttons)
	{
		// Set pins as input
		water_btn_ddr &= ~(1 << water_btn_bit);
		lamp_btn_ddr &= ~(1 << lamp_btn_bit);

		// Set interrupts on rising edge
		EICRA = 1 << ISC01 | 1 << ISC00 | 1 << ISC11 | 1 << ISC10;

		// Set both interrupts
		EIMSK = (1 << water_btn_int) | (1 << lamp_btn_int);

		// Enable global interrupts
		sei();

		// No duplication
		initialized_buttons = 1;
	}
}

// Read light
int read_light()
{
	switch_adc(photo_in_adc_bit);
	return read_adc();
}

// Read moisture
long int read_moist()
{
	switch_adc(moist_in_adc_bit);
	return read_adc();
}

// Read rocker
int read_rocker()
{
	return !((1 << rocker_in_bit) & rocker_in_pin);
}

/******************************* End of External Functions ******************/

int read_adc()
{
	// Start ADC
	ADCSRA |= (1 << ADSC);

	// Wait for completion
	while (((1 << ADIF) & ADCSRA) == 0)
		;

	// Return left-justify
	return ADCH;
}

void switch_adc(int pin)
{

	// Set ADMUX
	ADMUX = (pin);			// set pin
	ADMUX |= (1 << REFS0) | // set mode
			 (1 << ADLAR);	// set left-justify
}
