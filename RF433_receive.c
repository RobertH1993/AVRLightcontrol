/*
 * RF433_receive.c
 *
 *  Created on: Jul 8, 2018
 *      Author: robert
 */

#include <avr/io.h>
#include "RF433_receive.h"
#include "RingBuffer.h"

//The receive buffer stores pulse times in format (T * i)
//Where T == PULSE_RESOLUTION and i the value stored inside the buffer.
//We don't need a resolution of 1 uS so to save space use the biggest number for PULSE_RESOLUTION
//Max pulse time is PULSE_RESOLUTION * sizeof(uint8_t)
//Min pulse time is PULSE_RESOLUTION
struct _RING_BUFFER rx_buff;
uint8_t start_state = 0;


void RF433_receive_init(){
	//Init the receive buffer
	rx_buff = create_buffer(RX_BUFFER_LENGTH);
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

