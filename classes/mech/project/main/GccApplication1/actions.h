/*
 * actions.h
 *
 * Created: 4/7/2022 10:09:13 AM
 *  Author: Shane
 */ 

#ifndef ACTIONS_H_
#define ACTIONS_H_

// Relay interface
#define relay_port     PORTB
#define relay_bit      PORTB1
#define relay_ddr      DDRB

// Rotation motor interface
#define rot_fw_port  PORTD
#define rot_fw_bit   PORTD0
#define rot_fw_ddr   DDRD

#define rot_bw_port  PORTD
#define rot_bw_bit   PORTD1
#define rot_bw_ddr   DDRD

// Water motor interface
#define water_1_port   PORTD
#define water_1_bit    PORTD5
#define water_1_ddr    DDRD

#define water_2_port   PORTD
#define water_2_bit    PORTD6
#define water_2_ddr    DDRD

#define water_3_port   PORTD
#define water_3_bit    PORTD7
#define water_3_ddr    DDRD

#define water_4_port   PORTB
#define water_4_bit    PORTB0
#define water_4_ddr    DDRB

// Constants
#define rot_time_ms    700
#define steps_per_rot  48
#define n_turns_water  3
#define water_turn_ms  2000
#define water_wait_ms  1000
#define per_step_ms    water_turn_ms / (steps_per_rot * n_turns_water)

// Function prototypes
void init_actions();
void rotate_plant();
void turn_on_lamp(); 
void turn_off_lamp(); 
void water_plant();
void test_actions();

#endif /* ACTIONS_H_ */