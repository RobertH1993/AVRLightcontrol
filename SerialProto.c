/*
 * SerialProto.c
 *
 *  Created on: Jul 1, 2018
 *      Author: robert
 */

#include "SerialProto.h"
#include "UART.h"
#include "RFSwitch433.h"
#include <avr/io.h>

#define COMMAND_LENGTH 4

//Stores the current command that is being processed
unsigned char current_command[COMMAND_LENGTH];

void SP_init(){
	//Set PD5 as input with pull-up
	DDRD &= ~(1<<PD5);
	PORTD |= (1<<PD5);
}

//Private, get a command from RX buffer and store it inside current command
void get_command_from_buffer(){
	//Check if we have at least the amount of bytes needed for a command
	//And check if we are not processing a command already
	if(UART_rx_count() >= COMMAND_LENGTH && current_command == ""){
		//Get command from RX buffer and store inside current command
		for(uint8_t i = 0; i < COMMAND_LENGTH; i++){
			current_command[i] = UART_get_byte();
		}
	}
}

void update_rx_enabled_status(){
	//Check if a certain pin is low, if so enable RX on UART
	//This is to prevent debugging data send by the connected device to fill our buffer
	//with stuff we don't need for operating
	if(!(PIND & (1<<PD5)) && UART_receive_enabled()){
		UART_enable_receive();
	}
	//Check if UART receiving needs to be enabled
	if((PIND & (1<<PD5)) && UART_receive_enabled()){
		UART_disable_receive();
	}
}

void SP_check(){
	//TODO: rebuild whole function according to documentation

	update_rx_enabled_status();
	get_command_from_buffer();

	/* TODO: improvement of the communication protocol
	if(strcmp(current_command, "RF01") == 0){
		//RF messages for other nodes
	}
	else if(strcmp(current_command, "RF02") == 0){
		//RF messages for the SF500S wall-sockets
	}*/


	//Get the first two bytes because thats the command (see docs)
	//Command is like 11 (1 high) or 10 (1 low)
	//This identifies the unit and the state to set it into
	if(UART_rx_count() >= 2){
		unsigned char command[2];
		command[0] = UART_get_byte();
		command[1] = UART_get_byte();

		//Check if both are digits
		if(!isdigit(command[0]) || !isdigit(command[1])){
			return;
		}

		//Get string as uint
		uint8_t device = command[0] - '0';
		uint8_t state = command[1] - '0';

		//Send the RF signal
		for(uint8_t i = 0; i < 5; i++){
			RFS_send_unit(28060672, device, state);
		}
	}
}
