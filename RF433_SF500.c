/*
 * RFSwitch433.c
 *
 *  Created on: Jun 30, 2018
 *      Author: robert
 */
#include <avr/io.h>
#include <util/delay.h>
#include "RF433_SF500.h"

//Kudos to the Arduino NewRFSwitch library for the timings and parts of the code


//Private, send the stoppulse
void send_stoppulse(){
	PORTD |= (1<<PD4);
	_delay_us(PERIOD_US);
	PORTD &= ~(1<<PD4);
	_delay_us(PERIOD_US*40);
}

void send_bit(uint8_t bit){
	if (bit) {
		// Send '1'
		PORTD |= (1<<PD4);
		_delay_us(PERIOD_US);
		PORTD &= ~(1<<PD4);
		_delay_us(PERIOD_US * 5);
		PORTD |= (1<<PD4);
		_delay_us(PERIOD_US);
		PORTD &= ~(1<<PD4);
		_delay_us(PERIOD_US);
	} else {
		// Send '0'
		PORTD |= (1<<PD4);
		_delay_us(PERIOD_US);
		PORTD &= ~(1<<PD4);
		_delay_us(PERIOD_US);
		PORTD |= (1<<PD4);
		_delay_us(PERIOD_US);
		PORTD &= ~(1<<PD4);
		_delay_us(PERIOD_US * 5);
	}
}

//Private, send the address of the unit
void send_unit_address(uint8_t unit){
	for (int8_t i=3; i>=0; i--) {
	   send_bit(unit & 1<<i);
	}
}

//Private, send the address to the device
void send_address(uint32_t address){
	for (int8_t i=25; i>=0; i--) {
	   send_bit((address >> i) & 1);
	}
}

//Private, send start pulse to the device
void send_startpulse(){
	PORTD |= (1<<PD4);
	_delay_us(PERIOD_US);
	PORTD &= ~(1<<PD4);
	_delay_us(PERIOD_US * 10 + (PERIOD_US >> 1));
}


void RFS_init(){
	//Set the TX pin to output
	DDRD |= (1<<PD4);
	//Set the TX pin to low
	PORTD &= ~(1<<PD4);
}

void RFS_send_unit(uint32_t address, uint8_t unit, uint8_t state){
	send_startpulse();
	send_address(address);
	//No group bit
	send_bit(0);
	//Send state
	send_bit(state);
	send_unit_address(unit);
	send_stoppulse();
}
