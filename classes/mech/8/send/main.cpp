/*
 * Lab8receiver.cpp
 *
 * Created: 4/4/2022 10:44:49 PM
 * Author : kathe
 */ 

#include <avr/io.h>

void initialize_usart(); // function to set up USART
void wait(volatile int multiple, volatile char time_choice);
void delay_T_msec_timer0(char choice);

int main(void)
{	
	int data; // variable with which to receive incoming data
	
	//Serial Receiving
	initialize_usart(); // Initialize the USART with desired parameters
	
	//PWM
	DDRD = 1<<PD6;// Make OC0A (PD6) output bit -- this is the PWM pins;
		
	OCR0A = 0xFF;       // Load 0 into OCR0 to set initial duty cycle to 0 (LED on)
	TCCR0A = 0b10000011; //1<<COM0A1 | 0<<COM0A0 | 1<<WGM01 | 1<<WGM00;      // Set non-inverting mode on OC0A pin (COMA1:0 = 10; Fast PWM (WGM1:0 bits = bits 1:0 = 11) (Note that we are not affecting OC0B because COMB0:1 bits stay at default = 00)
	TCCR0B = 0b00000011; 
	// PWM is now running on selected pin at selected base frequency.  Duty cycle is set by loading/changing value in OCR0A register.

    while (1) 
    {
		while (!(UCSR0A & 0b10000000)); // ((! (UCSR0A & (1<<RXC0)));  // Wait until new data arrives
		data =  UDR0; // read the data
		OCR0A = data;
		wait(50,2); //pause
    }
}


void initialize_usart(void) // function to set up USART
{
	UCSR0B = 0b00010000; // enable serial transmission
	UCSR0C = 0b00000110; // Asynchronous mode, 8-bit data; no parity; 1 stop bit
	UBRR0L = 0x67; // 9,600 baud if Fosc = 16MHz
}

void wait(volatile int multiple, volatile char time_choice) {
	/* This subroutine calls others to create a delay.
		 Total delay = multiple*T, where T is in msec and is the delay created by the called function.
	
		Inputs: multiple = number of multiples to delay, where multiple is the number of times an actual delay loop is called.
		Outputs: None
	*/
	
	while (multiple > 0) {
		delay_T_msec_timer0(time_choice); 
		multiple--;
	}
} // end wait()


void delay_T_msec_timer0(volatile char choice) {
    //*** delay T ms **
    /* This subroutine creates a delay of T msec using TIMER0 with prescaler on clock, where, for a 16MHz clock:
    		for Choice = 1: T = 0.125 msec for prescaler set to 8 and count of 250 (preload counter with 5)
    		for Choice = 2: T = 1 msec for prescaler set to 64 and count of 250 (preload counter with 5)
    		for Choice = 3: T = 4 msec for prescaler set to 256 and count of 250 (preload counter with 5)
    		for Choice = 4: T = 16 msec for prescaler set to 1,024 and count of 250 (preload counter with 5)
			for Choice = Default: T = .0156 msec for no prescaler and count of 250 (preload counter with 5)
	
			Inputs: None
			Outputs: None
	*/
	
	TCCR0A = 0x00; // clears WGM00 and WGM01 (bits 0 and 1) to ensure Timer/Counter is in normal mode.
	TCNT0 = 0;  // preload value for testing on count = 250
	// preload value for alternate test on while loop: TCNT0 = 5;  // preload load TIMER0  (count must reach 255-5 = 250)
	
	switch ( choice ) { // choose prescaler
		case 1:
			TCCR0B = 0b00000010; //1<<CS01;	TCCR0B = 0x02; // Start TIMER0, Normal mode, crystal clock, prescaler = 8
		break;
		case 2:
			TCCR0B =  0b00000011; //1<<CS01 | 1<<CS00;	TCCR0B = 0x03;  // Start TIMER0, Normal mode, crystal clock, prescaler = 64
		break;
		case 3:
			TCCR0B = 0b00000100; //1<<CS02;	TCCR0B = 0x04; // Start TIMER0, Normal mode, crystal clock, prescaler = 256
		break; 
		case 4:
			TCCR0B = 0b00000101; //1<<CS02 | 1<<CS00; TCCR0B = 0x05; // Start TIMER0, Normal mode, crystal clock, prescaler = 1024
		break;
		default:
			TCCR0B = 0b00000001; //1<<CS00; TCCR0B = 0x01; Start TIMER0, Normal mode, crystal clock, no prescaler
		break;
	}
	
	while (TCNT0 < 0xFA); // exits when count = 250 (requires preload of 0 to make count = 250)
	// alternate test on while loop: while ((TIFR0 & (0x1<<TOV0)) == 0); // wait for TOV0 to roll over:
	// How does this while loop work?? See notes
	
	TCCR0B = 0x00; // Stop TIMER0
	//TIFR0 = 0x1<<TOV0;  // Alternate while loop: Clear TOV0 (note that this is a nonintuitive bit in that it is cleared by writing a 1 to it)
	
} // end delay_T_msec_timer0()
