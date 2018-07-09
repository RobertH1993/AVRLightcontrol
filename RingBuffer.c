/*
 * RingBuffer.c
 *
 *  Created on: Jun 29, 2018
 *      Author: robert
 */

#include "RingBuffer.h"
#include <stdlib.h>

struct _RING_BUFFER create_buffer(uint8_t len){
	struct _RING_BUFFER new_buffer;
	memset(&new_buffer, '0', sizeof(new_buffer));
	new_buffer.data = (uint8_t*) malloc(len);

	//Set size of buffer to 0 if not valid
	//Setting size to 0 will prevent other function from using this buffer
	if(new_buffer.data == NULL){ new_buffer.size = 0; }
	else { new_buffer.size = len; }

	return new_buffer;
}

void add_to_buffer(struct _RING_BUFFER* buffer, uint8_t byte){
	//If buffer is full do not accept new data
	if(buffer->count == buffer->size){ return; }

	//Add the byte to the buffer
	uint8_t index = (buffer->start_pointer + buffer->count) % buffer->size;
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
	buffer->start_pointer = (buffer->start_pointer + 1) % buffer->size;

	return byte;
}

void clear_buffer(struct _RING_BUFFER* buffer){
	buffer->count = 0;
}
