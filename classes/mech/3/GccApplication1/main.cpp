/*
 * lab3 main
 *
 * Created: 1/29/2022
 * Author : Shane Riley
 */ 

/*
This program is a solution to Lab 3 -- 
	LED back and forth sweep (receiving current, PC0-PC3) 
	Push and hold pause button (low == pressed) to PD2 
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#define DEBOUNCE 50

// check button
int button_pressed();

// wait (borrowed from lab document)
void wait(volatile int multiple);

// set led
void set_which_led(int led);

// set binary led
void set_binary_led(int num);

// main 
int main(void)
{
	// SETUP
	DDRC = 0xFF;  // Set all PORTC pins as output
	PORTC = 0xFF; // Turn off PORTC pins
	DDRD = 0;     // Set PORTD as input
	EICRA = 1 << ISC01 | 1 << ISC00 | 1 << ISC11 | 1 << ISC10;  // Trigger INT0 and INT1 on rising edge
	EIMSK = 1 << INT1 | 1 << INT0;  // Enable INT1 and INT0
	sei();
	
	// UNINTERRUPTED STATE
	int led = 0;
	int is_increasing = 1;
		 
    // MAINLOOP
	while(1)
    {
		led += is_increasing ? 1 : -1;
		if (led == 0) is_increasing = 1;
		if (led == 3) is_increasing = 0;
		set_which_led(led);
		wait(1000);
	}
	
return 0;	
} // end main()

// ============================================
// S U B R O U T I N E S
// ============================================

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

void set_which_led(int led) {
	
	if (led >= 0) {
		PORTC = ~(1 << led);
	} else {
		PORTC = 0xFF;
	}
} // end set_one_led()

void set_binary_led(int num) {
	
	// Calculate binary representation
	int binary = 0;
	int shift = 0;
	while (num > 0) {
		if (num % 2 == 1) {
			binary = binary | (1 << shift);
		}
		shift++;
		num /= 2;
	}
	
	// Invert to get active low
	PORTC = ~binary;
	
} // end set_binary_led

// INT0 Service routine
ISR(INT0_vect) {
	
	// Save context for later
	int PORTC_d = PORTC;
	int TCCR0A_d = TCCR0A;
	int TCCR0B_d = TCCR0B;
	int TCNT0_d = TCNT0;
	
	// Turn off led
	set_which_led(-1);
	
	// Wait two seconds
	wait(2000);
	
	// Tick up in binary
	for (int i = 0; i < 16; i++) {
		set_binary_led(i);
		wait(250);
	}
	
	// Resume context from before interrupt signal
	PORTC = PORTC_d;
	TCCR0A = TCCR0A_d;
	TCCR0B = TCCR0B_d;
	TCNT0 = TCNT0_d;
	
	// Make sure INT0 not queued
	EIFR = 1;
}

// INT1 Service routine
ISR(INT1_vect) {
	
	// Queuing INT1 allowed, not INT0
	
	// Save context for later
	int PORTC_d = PORTC;
	int TCCR0A_d = TCCR0A;
	int TCCR0B_d = TCCR0B;
	int TCNT0_d = TCNT0;
	
	// Turn on all leds
	PORTC = 0xF0;
	
	// Wait two seconds
	wait(2000);
	
	// Turn off in intervals
	for (int i = 0; i < 4; i++) {
		PORTC = PORTC | 1 << i;
		wait(500);
	}
	
	// Resume context from before interrupt signal
	PORTC = PORTC_d;
	TCCR0A = TCCR0A_d;
	TCCR0B = TCCR0B_d;
	TCNT0 = TCNT0_d;
	
	// Make sure INT0 not queued
	EIFR = 1;
}

