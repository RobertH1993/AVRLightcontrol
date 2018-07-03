/*
 * Serial.c
 *
 *  Created on: Jun 29, 2018
 *      Author: robert
 */

#include "UART.h"

#include "RingBuffer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

volatile struct _RING_BUFFER rx_buff;


void UART_init(){
	//Clear the receive buffer
	memset(&rx_buff, 0, sizeof(rx_buff));

	//Enable UART receiver, transmitter and receive interrupt
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	//Setup aysnc mode with data size of 8 bits and a stop bit
	UCSR0C = (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);
	//Clear the uart status register
	UCSR0A = 0x00;


	//Load the baudrate
	UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = BAUD_PRESCALE;

	//Enable interrupts
	sei();
}

void UART_sendbyte(uint8_t byte){
	//Wait until transmit buffer is empty
	while ( !(UCSR0A & (1 << UDRE0)));

	//Put byte into TX buffer
	UDR0 = byte;
}

void UART_sendstring(char* szString){
	uint16_t i = 0;
	while(szString[i] != 0x00){
		UART_sendbyte(szString[i]);
		i += 1;
	}
}

void UART_disable_receive(){
	UCSR0B &= ~(1<<RXEN0);
}

void UART_enable_receive(){
	UCSR0B |= (1<<RXEN0);
}

uint8_t UART_receive_enabled(){
	return (UCSR0B & (1<<RXEN0));
}

uint8_t UART_get_byte(){
	return get_byte_from_buffer(&rx_buff);
}

uint8_t UART_rx_count(){
	return rx_buff.count;
}

//Private, ISR for handling incoming serial data from UART
ISR(USART_RX_vect){
	//Store byte in receive buffer
	add_to_buffer(&rx_buff, UDR0);
}
