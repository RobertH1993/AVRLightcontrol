/*
 * RF433_receive.c
 *
 *  Created on: Jul 8, 2018
 *      Author: robert
 */

#include <avr/io.h>


void RF433_receive_init(){
	//Put pin PD2 as input, PD2 is INT0
	DDRD |= (1<<PD2);
	//Set interrupt on change of logical level
	EICRA |= (1<<ISC00);
}

void RF433_receive_enable(){
	//Enable interrupt 0
	EIMSK |= (1<<INT0);
}

void RF433_receive_disable(){
	//Disable interrupt 0
	EIMSK &= ~(1<<INT0);
}

