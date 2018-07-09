/*
 * SerialProto.c
 *
 *  Created on: Jul 1, 2018
 *      Author: robert
 */

#include "SerialProto.h"
#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "RF433_SF500.h"

#define NO_COMMAND 0
#define RF_SF500_COMMAND 16
#define RF_SF500_N_ARGS 6

union _RF_SF500_Address{
	uint32_t long_address;
	uint8_t byte_address[4];
};

//Store the current command inside a global because
//its possible that we don't have all arguments yet.
uint8_t current_command = NO_COMMAND;

volatile uint8_t timer_overflows = 0;

void SP_init(){
	//Set PD5 as input with pull-up
	DDRD &= ~(1<<PD5);
	PORTD |= (1<<PD5);
}

void start_timer(){
	//Use a timer to clear the command if no args are send, else the system will hang.
	//Using a 16Mhz clock, 1024 prescaler, and 8 bit timer, we get 240 overflows for 4 sec
	//Timeout after 4 sec, should be more then enough

	//No PWM so set controlreg A to 0
	TCCR0A = 0;
	//Reset timer value
	TCNT0 = 0;
	//Enable overflow interrupt
	TIMSK0 = (1 << TOIE0);
	//Set prescaler to 1024
	TCCR0B = (1<<CS02) | (1<<CS00);
}

void stop_timer(){
	//Remove clock source from timer
	TCCR0B &= ~(1<<CS02) | ~(1<<CS01) | ~(1<<CS00);

	//Disable overflow interrupt
	TIMSK0 &= ~(1 << TOIE0);

	timer_overflows = 0;
}

//Private, get a command from RX buffer and store it inside current command
void get_command_from_buffer(){
	//Check if we have at least the amount of bytes needed for a command
	//And check if we are not processing a command already
	if(UART_rx_count() > 0 && current_command == NO_COMMAND){
		current_command = UART_get_byte();
		start_timer();
	}
}

//Private, enable or disable RX
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

//Private, clears the current command that is being processed
void clear_current_command(){
	current_command = NO_COMMAND;
	stop_timer();
}

//Private
void handle_sf500_command(){
	//Transform 4 bytes into a uint32
	union _RF_SF500_Address address;
	for(int8_t i = 3; i >= 0; i--){
		address.byte_address[i] = UART_get_byte();
	}

	//Get the following two bytes, device and state
	uint8_t device = UART_get_byte();
	uint8_t state = UART_get_byte();

	//Repeat the signal 5 times
	for(uint8_t i = 0; i < 5; i++){
		RFS_send_unit(address.long_address, device, state);
	}

}

//Private ISR to handle timer overflow
ISR(TIMER0_OVF_vect){
	timer_overflows += 1;

	if(timer_overflows >= 240){ //4 sec
		clear_current_command();
	}
}

void SP_check(){
	update_rx_enabled_status();
	get_command_from_buffer();

	if(current_command == NO_COMMAND){
		return;
	} else if(current_command == RF_SF500_COMMAND){
		if(UART_rx_count() < RF_SF500_N_ARGS){ return; }
		handle_sf500_command();
		clear_current_command();
	} else { //We received a command that we cannot parse, clear the command
		clear_current_command();
	}
}
