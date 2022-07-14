/*
 * lab2_2020.cpp
 *
 * Created: 1/20/2022
 * Author : Shane Riley
 */ 

/*
This program is a solution to Lab 2 -- 
	LED back and forth sweep (receiving current, PC0-PC3) 
	Push and hold pause button (low == pressed) to PD2 
*/

#include <avr/io.h>

// check button
int button_pressed();

// wait (borrowed from lab document)
void wait(volatile int multiple);

// set led
void set_led(int led);


int main(void)
{
	
	// Set all PORTC pins as output
	DDRC = 0xFF;
	
	// Turn off PORTC pins
	PORTC = 0xFF;
	
	// Set PORTD as input
	DDRD = 0;
	
	// State information
	int led = 0;
	int is_increasing = 1;
		 
    // ============================================
    // P R O G R A M L O O P
    // ============================================
	while(1)
    {
		if (button_pressed()) {
			set_led(-1);
		} else {
			// Tick led
			led += is_increasing ? 1 : -1;
			if (led == 0) is_increasing = 1;
			if (led == 3) is_increasing = 0;
			set_led(led);
		}
		wait(1000);
	}
	
return 0;	
} // end main()
// ============================================
// S U B R O U T I N E S
// ============================================

// Check PD2 for low
int button_pressed() {
	return !(PIND & 0b00000100);
} // end button_pressed()

void wait(volatile int multiple) {
	// This subroutine creates a delay equal to multiple*T, where T is 1 msec
	// Assumes a 16MHz clock frequency – FOR DIFFERENT CLOCK, CHANGE THE COUNT EXIT VALUE IN WHILE LOOP
	while (multiple > 0) {
		TCCR0A = 0x00; // clears WGM00 and WGM01 (bits 0 and 1) to ensure Timer/Counter is in normal mode.
		TCNT0 = 0; // preload value for testing on count = 250
		TCCR0B = 0b00000011; //1<<CS01 | 1<<CS00; TCCR0B = 0x03; //
		// Start TIMER0, Normal mode, crystal clock, prescaler = 64
		while (TCNT0 < 0xFA); // exits when count = 250 (requires preload of 0 to make count = 250) CHANGE THIS VALUE FOR CLOCK OTHER THAN 16MHz
		TCCR0B = 0x00; // Stop TIMER0
		multiple--;
	}
} // end wait()

void set_led(int led) {
	switch(led) {
		case 0:
			PORTC = 0xFE;
			break;
		case 1:
			PORTC = 0xFD;
			break;
		case 2:
			PORTC = 0xFB;
			break;
		case 3:
			PORTC = 0xF7;
			break;
		case -1:
			PORTC = 0xFF;
	}
} // end set_led()

