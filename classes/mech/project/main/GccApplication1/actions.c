/*
 * actions.c
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

// Initialization check
static int initialized = 0;

// Stepper phase
static int stepper_phase = 1;

// Rotation state
static int rotation_state = 0;

// External prototypes
#include "actions.h"
#include "screen.h"

// Internal prototypes
void step_down();
void step_up();

/******************************* Test Program Code *************************/
void test_actions()
{
	init_screen();
	init_actions();

	clear_screen();
	write_to_screen("Lamp on!", "");
	turn_on_lamp();
	_delay_ms(5000);
	turn_off_lamp();
	write_to_screen("Lamp off!", "");
	_delay_ms(2000);
	write_to_screen("Rotate plant!", "");
	rotate_plant();
	_delay_ms(1000);
	rotate_plant();
	write_to_screen("Water plant!", "");
	water_plant();
	clear_screen();
}
/******************************* End of Test Program Code ******************/

/******************************* External Functions *************************/

// Init actions
void init_actions()
{
	if (!initialized)
	{
		// Set all DDR's as output
		relay_ddr |= (1 << relay_bit);
		rot_fw_ddr |= (1 << rot_fw_bit);
		rot_bw_ddr |= (1 << rot_bw_bit);
		water_1_ddr |= (1 << water_1_bit);
		water_2_ddr |= (1 << water_2_bit);
		water_3_ddr |= (1 << water_3_bit);
		water_4_ddr |= (1 << water_4_bit);

		// Set all pins to low
		relay_port &= ~(1 << relay_bit);
		rot_fw_port &= ~(1 << rot_fw_bit);
		rot_bw_port &= ~(1 << rot_bw_bit);
		water_1_port &= ~(1 << water_1_bit);
		water_2_port &= ~(1 << water_2_bit);
		water_3_port &= ~(1 << water_3_bit);
		water_4_port &= ~(1 << water_4_bit);

		// No PWM on the brushed motor
		// No PWM on the stepper motor

		// No duplication
		initialized = 1;
	}
}

// Rotate plant (synchronous)
void rotate_plant()
{

	// Check state
	if (rotation_state == 0)
	{

		// Go forward
		rot_fw_port |= (1 << rot_fw_bit);

		// Wait
		_delay_ms(rot_time_ms);

		// Stop
		rot_fw_port &= ~(1 << rot_fw_bit);

		// Switch state
		rotation_state = 1;
	}
	else
	{
		// Go backward
		rot_bw_port |= (1 << rot_bw_bit);

		// Wait
		_delay_ms(rot_time_ms);

		// Stop
		rot_bw_port &= ~(1 << rot_bw_bit);

		// Switch state
		rotation_state = 0;
	}
}

// Turn on lamp
void turn_on_lamp()
{
	// Make relay port high
	relay_port |= (1 << relay_bit);
}

// Turn off lamp
void turn_off_lamp()
{
	// Make relay port low
	relay_port &= ~(1 << relay_bit);
}

// Water plant (synchronous)
void water_plant()
{

	// Loop through steps
	for (int i = 0; i < (steps_per_rot * n_turns_water); i++)
	{
		// Step
		step_down();
		// Wait
		_delay_ms(per_step_ms);
	}
	
	_delay_ms(water_wait_ms);
	
	for (int i = 0; i < (steps_per_rot * n_turns_water); i++)
	{
		// Step
		step_up();
		// Wait
		_delay_ms(per_step_ms);
	}
}
/******************************* End of External Functions ******************/

// Step functions
void step_up()
{
	switch (stepper_phase)
	{

	case 1:
		// Set bit 2
		water_2_port |= (1 << water_2_bit);
		// Clear bits 134
		water_1_port &= ~(1 << water_1_bit);
		water_3_port &= ~(1 << water_3_bit);
		water_4_port &= ~(1 << water_4_bit);
		stepper_phase = 2;
		break;

	case 2:
		// Set bit 4
		water_4_port |= (1 << water_4_bit);
		// Clear bits 123
		water_1_port &= ~(1 << water_1_bit);
		water_2_port &= ~(1 << water_2_bit);
		water_3_port &= ~(1 << water_3_bit);
		stepper_phase = 3;
		break;

	case 3:
		// Set bit 1
		water_1_port |= (1 << water_1_bit);
		// Clear bits 234
		water_2_port &= ~(1 << water_2_bit);
		water_3_port &= ~(1 << water_3_bit);
		water_4_port &= ~(1 << water_4_bit);
		stepper_phase = 4;
		break;

	case 4:
		// Set bit 3
		water_3_port |= (1 << water_3_bit);
		// Clear bits 124
		water_1_port &= ~(1 << water_1_bit);
		water_2_port &= ~(1 << water_2_bit);
		water_4_port &= ~(1 << water_4_bit);
		stepper_phase = 1;
		break;
	}
}

void step_down()
{
	switch (stepper_phase)
	{

		case 1:
		// Set bit 1
		water_1_port |= (1 << water_1_bit);
		// Clear bits 234
		water_2_port &= ~(1 << water_2_bit);
		water_3_port &= ~(1 << water_3_bit);
		water_4_port &= ~(1 << water_4_bit);
		stepper_phase = 4;
		break;

		case 2:
		// Set bit 3
		water_3_port |= (1 << water_3_bit);
		// Clear bits 124
		water_1_port &= ~(1 << water_1_bit);
		water_2_port &= ~(1 << water_2_bit);
		water_4_port &= ~(1 << water_4_bit);
		stepper_phase = 1;
		break;

		case 3:
		// Set bit 2
		water_2_port |= (1 << water_2_bit);
		// Clear bits 134
		water_1_port &= ~(1 << water_1_bit);
		water_3_port &= ~(1 << water_3_bit);
		water_4_port &= ~(1 << water_4_bit);
		stepper_phase = 2;
		break;

		case 4:
		// Set bit 4
		water_4_port |= (1 << water_4_bit);
		// Clear bits 123
		water_1_port &= ~(1 << water_1_bit);
		water_2_port &= ~(1 << water_2_bit);
		water_3_port &= ~(1 << water_3_bit);
		stepper_phase = 3;
		break;
	}
}