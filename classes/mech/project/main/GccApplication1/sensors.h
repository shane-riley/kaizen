/*
 * sensors.h
 *
 * Created: 4/7/2022 10:09:13 AM
 *  Author: Shane
 */ 

#ifndef SENSORS_H_
#define SENSORS_H_

// Photosensor interface
// MUST BE PORTC for A/D
#define photo_in_bit      PORTC0
#define photo_in_adc_bit  ADC0D 
#define photo_in_ddr      DDRC

// Moisture sensor interface
// MUST BE PORTC for A/D
#define moist_in_bit      PORTC1
#define moist_in_adc_bit  ADC1D
#define moist_in_ddr      DDRC

// Uses PC4 and PC5 for I2c

// Rocker switch interface
#define rocker_in_pin	  PIND
#define rocker_in_bit	  PORTD4
#define rocker_in_ddr	  DDRD

// Water switch interface
#define water_btn_int	  INT0
#define water_btn_bit	  PORTD2
#define water_btn_ddr	  DDRD

// Lamp switch interface
#define lamp_btn_int	  INT1
#define lamp_btn_bit	  PORTD3
#define lamp_btn_ddr	  DDRD

// Function prototypes
void init_sensors();
void init_buttons();
int read_light();
long int read_moist(); 
void test_sensors();
int read_rocker();

#endif /* SENSORS_H_ */