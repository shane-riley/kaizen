/*
 * GccApplication1.c
 *
 * Created: 4/7/2022 12:39:20 PM
 * Author : Shane
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "sensors.h"
#include "screen.h"
#include "actions.h"

#define WATER_THRESHOLD_HIGH 200
#define WATER_THRESHOLD_LOW 100
#define LIGHT_THRESHOLD 25
#define NUM_CYCLES_UNTIL_ROTATE 20
#define NUM_CYCLES_UNTIL_LAMP_OFF 20
#define CYCLE_DELAY_ms 1000
#define TASTEFUL_DELAY_ms 1000

int lamp_flag = 0;
int water_flag = 0;

static void init_all();
static void test_and_hang();
static void display_values(int light, int moist, int rocker);
static void display_flags();

int main(void)
{

	// Run in test mode
	//test_and_hang();

	// 	Setup
	init_all();

	int light;
	long int moist;
	int water_threshold;
	int rocker;
	int lamp_cycles = 0;
	int rot_cycles = NUM_CYCLES_UNTIL_ROTATE;
	while (1)
	{

		// Query sensors
		rocker = read_rocker();
		light = read_light();
		moist = read_moist();

		// Adjust threshold
		water_threshold = rocker ? WATER_THRESHOLD_HIGH : WATER_THRESHOLD_LOW;

		// Display values
		display_values(light, moist, rocker);

		// Raise flags if threshold
		if (light < LIGHT_THRESHOLD)
		{
			lamp_flag = 1;
		}
		if (moist < water_threshold)
		{
			water_flag = 1;
		}

		// Decrement lamp and rot cycles
		if (lamp_cycles > 0 && lamp_cycles <= NUM_CYCLES_UNTIL_LAMP_OFF)
		{
			lamp_cycles--;
		}
		if (rot_cycles > 0)
		{
			rot_cycles--;
		}

		// Turn on lamp
		if (lamp_flag && lamp_cycles == NUM_CYCLES_UNTIL_LAMP_OFF + 1)
		{
			lamp_flag = 0;
			clear_screen();
			write_to_screen("Turning on...", "LAMP");
			_delay_ms(TASTEFUL_DELAY_ms);
			turn_on_lamp();
			_delay_ms(TASTEFUL_DELAY_ms);
			lamp_cycles--;
		}

		// Turn on water
		if (water_flag)
		{
			water_flag = 0;
			clear_screen();
			write_to_screen("Turning on...", "WATER");
			water_plant();
		}

		// Turn off lamp
		if (lamp_cycles == 0)
		{
			clear_screen();
			write_to_screen("Turning off...", "LAMP");
			_delay_ms(TASTEFUL_DELAY_ms);
			turn_off_lamp();
			_delay_ms(TASTEFUL_DELAY_ms);
			lamp_cycles = NUM_CYCLES_UNTIL_LAMP_OFF + 1;
		}

		// Rotate
		if (rot_cycles == 0)
		{
			clear_screen();
			write_to_screen("Rotating...", "");
			rotate_plant();
			rot_cycles = NUM_CYCLES_UNTIL_ROTATE;
		}

		// Wait
		_delay_ms(CYCLE_DELAY_ms);
	}
}

// INT0 Service routine (set to water)
ISR(INT0_vect)
{
	// Raise the water flag
	water_flag = 1;
}

// INT1 Service routine (set to water)
ISR(INT1_vect)
{
	// Raise the water flag
	lamp_flag = 1;
}

// Init everything
void init_all()
{
	init_actions();
	init_screen();
	init_sensors();
	init_buttons();
}

// Test all
void test_and_hang()
{
	// Setup
	init_all();

	// Screen test
	test_screen();
	// Sensor test
	test_sensors();
	// Action test
	test_actions();
	// Display flags turned on
	display_flags();
	
	while(1) {}
}

// Display flags
void display_flags()
{
	char lamp_template_line[] = "Lamp flag: %s";
	char water_template_line[] = "Water flag: %s";
	char lamp_line[17];
	char water_line[17];
	sprintf(lamp_line, lamp_template_line, lamp_flag ? "ON" : "OFF");
	sprintf(water_line, water_template_line, water_flag ? "ON" : "OFF");
	clear_screen();
	write_to_screen(lamp_line, water_line);
}

// Display values
void display_values(int light, int moist, int rocker)
{

	// Initialize
	char string_one[] = "Lit/Moist/Thresh";
	char string_template_two[] = "%d/%d/%s";
	char string_two[17];

	// Print onto lines
	sprintf(string_two, string_template_two, light, moist, rocker ? "HIGH" : "LOW");
	clear_screen();
	write_to_screen(string_one, string_two);
}
