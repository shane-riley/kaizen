/*
 * GccApplication1.c
 *
 * Created: 3/30/2022 11:09:40 AM
 * Author : Shane
 */ 

#include <avr/io.h>



#define MAX_CMD_DIG0 0x1
#define MAX_CMD_DIG1 0x2
#define MAX_CMD_DECODING_ON 0x09
#define MAX_DAT_DECODING_ON 0x03
#define MAX_CMD_SCAN_LIMIT_2 0x0B
#define MAX_DAT_SCAN_LIMIT_2 0x02
#define MAX_CMD_POWER 0x0C
#define MAX_DAT_TURN_ON 0x01
#define MAX_DAT_TURN_OFF 0x00

#define TEMP_ADDRESS 0x18
#define TEMP_RESOLUTION_REGISTER 0x8
#define TEMP_RESOLUTION_DATA 0x0
#define TEMP_DATA_REGISTER 0x5

// Function prototypes

// wait (borrowed from lab document)
void wait(volatile int multiple);

// Setup max
void setup_max();

// Send to max
void send_to_max();

// Write two digits
void write_digits(int digits);

// Read temp
int read_temp();

// Setup temp
void setup_temp();

// I2c helpers
void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_repeated_start(void);
void i2c_write_to_address(unsigned char address);
void i2c_read_from_address(unsigned char address);
void i2c_write_data(unsigned char data);
unsigned char i2c_read_data(unsigned char ack);

int main(void)
{
	
	// Set up
	setup_max();
	setup_temp();
	
	// Turn on
	send_to_max(MAX_CMD_POWER, MAX_DAT_TURN_ON);
	
    /* Replace with your application code */
    while (1) 
    {
		// Read temperature
		int temperature = read_temp();
		write_digits(temperature);
		
		// Wait
		wait(100);
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
	send_to_max(MAX_CMD_DECODING_ON, MAX_DAT_DECODING_ON);
	
	// Set scan limit to 2
	send_to_max(MAX_CMD_SCAN_LIMIT_2, MAX_DAT_SCAN_LIMIT_2);
	
} // end setup_max()

// send to max
void send_to_max(int command, int data) {
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

// Setup temp
void setup_temp() {
	// PC4 and PC5 as input
	// Set pull-up resistors
	DDRC &= !(1 << 4) & !(1 << 5);
	PORTC |= (1 << 4) | (1 << 5);
	
	// Call init
	i2c_init();
	
	// Set resolution to .5C
	i2c_start();
	i2c_write_to_address(TEMP_ADDRESS);
	i2c_write_data(TEMP_RESOLUTION_REGISTER);
	i2c_write_data(TEMP_RESOLUTION_DATA);
}

int read_temp() {
	
	i2c_start();
	i2c_write_to_address(TEMP_ADDRESS);
	i2c_write_data(TEMP_DATA_REGISTER);
	i2c_repeated_start();
	i2c_read_from_address(TEMP_ADDRESS);
	int data1 = i2c_read_data(1);  // ACK
	int data0 = i2c_read_data(0);  // NO ACK
	i2c_stop();
	
	// Compute temperature
	int temperature;
	data1 = data1 & 0x1F;  // Clear upper three bits
	if ((data1 & 0x10) == 0x10) {
		data1 = data1 & 0x0F;
		temperature = 256 - (data1 * 16 + data0 / 16);
	} else {
		temperature = (data1 * 16 + data0 / 16);
	}
	
	// Still in celsius, convert to F
	temperature = (int) (temperature * 9.0/5.0) + 32;
	
	return temperature;
}

void i2c_init(void) { // initialize i2c
	TWSR = 0b00000000; // prescaler is set to 1
	TWBR = 72; // Put 72 into TWBR to define SCL frequency as 100kHz for 16MHz oscillator
	TWCR = 0b00000100; // TWEN = 1 (enable TWI)
}

void i2c_start(void) { // send start command
	//while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000));   // wait for idle condition -- TWINT bit must be high to proceed -- not needed if single main is used
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);  //TWCR | 0b10100100;       // initiate START condition -- write 1 to TWINT to clear it and initiate action, set TWSTA bit, set TWEN bit
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000));   // wait for action to finish (poll TWINT bit)
	// if ((TWSR & 0xF8) != START) // error checking -- need to predefine START = 0x08 and ERROR() function.
	// ERROR();
}

void i2c_stop(void) { // send stop command
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000)) ;  // wait for action to finish (poll TWINT bit)
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); //TWCR = TWCR | 0b10010100;       // initiate STOP condition -- write 1 to TWINT to clear it and initiate action, set TWSTO bit and set TWEN bit
}

void i2c_repeated_start(void) {
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);  //TWCR | 0b10100100;       // initiate START condition -- write 1 to TWINT to clear it and initiate action, set TWSTA bit, set TWEN bit
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000));   // wait for action to finish (poll TWINT bit)
	// if ((TWSR & 0xF8) != START) // error checking -- need to predefine START = 0x10 and ERROR() function.
	// ERROR();
}

void i2c_write_to_address( unsigned char address) { //Write an address byte to the I2C2 bus in form of SLA_W (address to write to)
	unsigned char SLA_W = address<<1; // create SLA_W byte by shifting address and leaving R/W bit clear
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000)) ;  // wait for idle condition -- TWINT bit must be high to proceed
	TWDR = SLA_W;       // Load TWDR with address plus R/W bit
	TWCR = (1<<TWINT) | (1<<TWEN); //TWCR = TWCR | 0b10000100;       // initiate Write -- write 1 to TWINT to clear it and initiate action, and set TWEN
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000)) ;  // wait for action to finish (poll TWINT bit)
	// if ((TWSR & 0xF8) != MT_SLA_ACK) // error checking -- need to predefine MT_SLA_ACK and ERROR() function depending on possible outcomes: 0x18, 0x20, or 0x38.
	//ERROR();
}

void i2c_read_from_address(unsigned char address) { //Write an address byte to the I2C bus in form of SLA_R (address to read from)
	unsigned char SLA_R = address<<1 | 1; // create SLA_R byte by shifting address and setting R/W bit
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000)) ;  // wait for idle condition -- TWINT bit must be high to proceed
	TWDR = SLA_R;       // Load TWDR with address plus R/W bit
	TWCR = (1<<TWINT) | (1<<TWEN); //TWCR = TWCR | 0b10000100;       // initiate Write -- write 1 to TWINT to clear it and initiate action, and set TWEN
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000)) ;  // wait for action to finish (poll TWINT bit)
	// if ((TWSR & 0xF8) != MR_SLA_ACK) // error checking -- need to predefine MR_SLA_ACK and ERROR() function depending on possible outcomes: 0x38, 0x40, or 0x48.
	//ERROR();
}

void i2c_write_data( unsigned char data) { //Write data byte to the I2C2 bus
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000)) ;  // wait for idle condition -- TWINT bit must be high to proceed
	TWDR = data;       // Load TWDR with data to be sent
	TWCR = (1<<TWINT) | (1<<TWEN); //TWCR = TWCR | 0b10000100;       // initiate Write -- write 1 to TWINT to clear it and initiate action, and set TWEN
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000)) ;  // wait for action to finish (poll TWINT bit)
	// if ((TWSR & 0xF8) != MT_DATA_ACK) // error checking -- need to predefine MT_DATA_ACK and ERROR() function depending on possible outcomes: 0x28 or 0x30.
	//ERROR();
}


unsigned char i2c_read_data(unsigned char ACK) { //Read a byte of data from a secondary on the I2C2 bus
	unsigned char data;
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000)) ;  // wait for idle condition -- TWINT bit must be high to proceed
	if (ACK) // check for whether ACK or NO_ACK should be sent upon receipt of byte from secondary
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN); //TWCR = TWCR | 0b11000100;       // initiate Read with ACK -- write 1 to TWINT to clear it and initiate action, and set TWEA and TWEN
	else
	TWCR = (1<<TWINT) | (1<<TWEN); //TWCR = TWCR | 0b10000100;       // initiate Read with NO_ACK-- write 1 to TWINT to clear it and initiate action, and set TWEN
	while (!(TWCR & (1<<TWINT))); //while (!(TWCR & 0b10000000)) ;  // wait for action to finish (poll TWINT bit)
	// if ((TWSR & 0xF8) != MR_SLA_ACK) // error checking -- need to predefine MR_SLA_ACK and ERROR() function depending on possible outcomes: 0x50 or 0x58.
	//ERROR();
	//If multiple bytes are to be read, this function can be repeated with proper ACK or NO_ACK until done.
	data = TWDR;  // read the received data from secondary
	return(data);
}