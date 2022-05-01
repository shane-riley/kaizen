/*
 * screen.h
 *
 * Created: 4/7/2022 10:09:13 AM
 *  Author: Shane
 */ 

#ifndef SCREEN_H_
#define SCREEN_H_

// LCD interface
#define lcd_D7_port     PORTB                   // lcd D7 connection
#define lcd_D7_bit      PORTB2
#define lcd_D7_ddr      DDRB
#define lcd_D7_pin      PINB                    // busy flag

#define lcd_D6_port     PORTB                   // lcd D6 connection
#define lcd_D6_bit      PORTB3
#define lcd_D6_ddr      DDRB

#define lcd_D5_port     PORTB                   // lcd D5 connection
#define lcd_D5_bit      PORTB4
#define lcd_D5_ddr      DDRB

#define lcd_D4_port     PORTB                   // lcd D4 connection
#define lcd_D4_bit      PORTB5
#define lcd_D4_ddr      DDRB

#define lcd_E_port      PORTC                   // lcd Enable pin
#define lcd_E_bit       PORTC3
#define lcd_E_ddr       DDRC

#define lcd_RS_port     PORTC                   // lcd Register Select pin
#define lcd_RS_bit      PORTC5
#define lcd_RS_ddr      DDRC

#define lcd_RW_port     PORTC                   // lcd Read/Write pin
#define lcd_RW_bit      PORTC4
#define lcd_RW_ddr      DDRC

// Function prototypes
void init_screen();
void clear_screen();
void write_to_screen(char *line1, char *line2);
void test_screen();

#endif /* SCREEN_H_ */