/*
 * lab6 main
 *
 * Created: 2/14/2022
 * Author : Shane Riley
 */ 

/*
This program is a solution to Lab 6 -- 
	5 LEDs correspond to motor speeds (receiving current, PB0-PB4)
	Analog input read in PC0
	Motor driven at varying speeds based on analog input
*/

#include <avr/io.h>

// wait (borrowed from lab document)
void wait(volatile int multiple);

// set led
void set_which_led(int led);

// read voltage
int read_voltage();

// Set motor
void set_motor(int mode, int speed);

// main 
int main(void)
{
	// SETUP
	DDRB = 0xFF;  // Set all PORTB pins as output
	PORTB = 0xFF; // Turn off PORTB pins
	
	DDRC = 0xFE;     // Set PORTC as output except PC0
	DDRD = (1 << 6) | (1 << 5);	 // Set PORTD as output
	
	// Preset duty cycle
	OCR0A = 0x00;
	TCCR0A = 0b10000011;  // Set up PWM on PD6, Fast PWM, TOP 0xFF
	TCCR0B = 0b00000011;  // Set 64x prescaler
	
	// SET UP ANALOG READ
	ADMUX = 0b01100000;  // PC0, LEFT JUSTIFY, USE VREF
	PRR = 0x00;  // POWER ON ADC
	ADCSRA = 0b10000111;  // TURN ON ND PRESCALER
	
	unsigned int voltage;
	int bin, speed;
	
    // MAINLOOP
	
	while(1)
    {
		voltage = read_voltage();
		bin = (voltage / 51);
		set_which_led(bin);
		speed = voltage;  // 40 to FF
		set_motor(bin-2, speed);
	}
	
return 0;	
} // end main()

// ============================================
// S U B R O U T I N E S
// ============================================

void wait(volatile int multiple) {
	// This subroutine creates a delay equal to multiple*T, where T is 1 msec
	// Assumes a 16MHz clock frequency � FOR DIFFERENT CLOCK, CHANGE THE COUNT EXIT VALUE IN WHILE LOOP
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

int read_voltage() {
	
	// Set starting bit
	ADCSRA = ADCSRA | 0b01000000;
	
	// Wait for completion
	while ((0b00010000 & ADCSRA) == 0);

	// Left-justify in register
	return (ADCH);
	
} // end read_voltage()

void set_which_led(int led) {
	if (led > 4) { led = 4; }
	if (led >= 0) {
		PORTB = ~(1 << led);
	} else {
		PORTB = 0xFF;
	}
} // end set_which_led()

void set_motor(int mode, int speed) {
	int forward = (mode > 0);
	int backward = (mode < 0);
	int duty;
	if (mode == 1 || mode == -1) {
		duty = 0x80;
	} else if (mode == -2) {
		duty = 0xD0;
	} else {
		duty = speed;
	}
	
	if (forward) {
		PORTC = PORTC | (1<<1);
	} else {
		PORTC = PORTC & ~(1<<1);
	}
	
	if (backward) {
		PORTC = PORTC | (1<<2);
		} else {
		PORTC = PORTC & ~(1<<2);
	}
	
	// Set duty
	OCR0A = duty;
	
} // end set_motor
