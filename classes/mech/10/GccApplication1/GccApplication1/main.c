/*
 * GccApplication1.c
 *
 * Created: 3/30/2022 11:09:40 AM
 * Author : Shane
 */ 

#include <avr/io.h>


#define MONTH 04
#define DAY 06
#define MAX_CMD_DIG0 0x1
#define MAX_CMD_DIG1 0x2
#define MAX_CMD_DECODING_ON 0x9
#define MAX_DAT_DECODING_ON 0x3
#define MAX_CMD_SCAN_LIMIT_2 0xB
#define MAX_DAT_SCAN_LIMIT_2 0x2
#define MAX_CMD_POWER 0xC
#define MAX_DAT_TURN_ON 0x1
#define MAX_DAT_TURN_OFF 0x0

// Function prototypes

// wait (borrowed from lab document)
void wait(volatile int multiple);

// Setup max
void setup_max();

// Send to max
void send_to_max(unsigned char command, unsigned char data);

// Write two digits
void write_digits(int digits);

int main(void)
{
	
	// Set up
	setup_max();
	
    /* Replace with your application code */
    while (1) 
    {
		// Push month
		write_digits(MONTH);
		
		// Turn on
		send_to_max(MAX_CMD_POWER, MAX_DAT_TURN_ON);
		
		// Wait
		wait(500);
		
		// Push day
		write_digits(DAY);
		
		// Wait
		wait(500);
		
		// Turn off
		send_to_max(MAX_CMD_POWER, MAX_DAT_TURN_OFF);
		
		// Wait
		wait(2000);
    }
}


// wait function
void wait(volatile int multiple) {
	// This subroutine creates a delay equal to multiple*T, where T is 1 msec
	// Assumes a 16MHz clock frequency ? FOR DIFFERENT CLOCK, CHANGE THE COUNT EXIT VALUE IN WHILE LOOP
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

// Setup max
void setup_max() {
	
	// SS, SCK, MOSI as output
	DDRB |= (1<<2) | (1<<3) | (1<<5);
	
	// Setup SPCR
	// Main mode 0, SCK = Fosc / 16, lead with MSB
	SPCR = 0b01010001;
	
	// Send packet to ensure
	// numeric decoding for digits 0 and 1
	send_to_max(MAX_CMD_DECODING_ON, 0xFF);
	
	// Set scan limit to 2
	send_to_max(MAX_CMD_SCAN_LIMIT_2, MAX_DAT_SCAN_LIMIT_2);
	
	send_to_max(0xF, 0);
	
} // end setup_max()

// send to max
void send_to_max(unsigned char command, unsigned char data) {
	// Clear SS bit
	PORTB &= 0b11111011;
	
	// Send cmd and wait
	SPDR = command;
	while(!(SPSR & (1<<SPIF)));
	
	// Send data and wait
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	
	// Set SS bit
	PORTB |= 0b00000100;
} // end send_to_max()

// Write two digits
void write_digits(int digits) {
	
	// Unpack digits
	int digit_0 = digits % 10;
	int digit_1 = (digits / 10) % 10;
	
	send_to_max(MAX_CMD_DIG0, digit_0);
	send_to_max(MAX_CMD_DIG1, digit_1);
	
} // end write_digits()
