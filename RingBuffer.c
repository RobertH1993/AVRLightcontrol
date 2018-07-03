/*
 * RingBuffer.c
 *
 *  Created on: Jun 29, 2018
 *      Author: robert
 */

#include "RingBuffer.h"

void add_to_buffer(struct _RING_BUFFER* buffer, uint8_t byte){
	//If buffer is full do not accept new data
	if(buffer->count == BUFFER_LENGTH){ return; }

	//Add the byte to the buffer
	uint8_t index = (buffer->start_pointer + buffer->count) % BUFFER_LENGTH;
	buffer->data[index] = byte;

	//Increase the count
	buffer->count += 1;
}

uint8_t get_byte_from_buffer(struct _RING_BUFFER* buffer){
	//If buffer is empty return a zero
	if(buffer->count == 0) return 0;

	//Get the first byte from the buffer
	uint8_t byte = buffer->data[buffer->start_pointer];

	//Update internal variables
	buffer->count -= 1;
	buffer->start_pointer = (buffer->start_pointer + 1) % BUFFER_LENGTH;

	return byte;
}

void clear_buffer(struct _RING_BUFFER* buffer){
	buffer->count = 0;
}
