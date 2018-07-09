/*
 * RingBuffer.h
 *
 *  Created on: Jun 29, 2018
 *      Author: robert
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>

struct _RING_BUFFER{
	uint8_t start_pointer; //Index pointing to the first element in the buffer
	uint8_t count; //The number of elements currently in the buffer
	uint8_t *data; //The actual data inside the buffer
	uint8_t size;
} ring_buffer;

/**
 * @brief Create a dynamic allocated buffer
 * @param len The length in bytes of the buffer
 * @return Returns the freshly created buffer
 *
 * @warning Dynamic memory handling on embedded systems is dangerous, only init buffers on startup.
 * Always check if buffer is valid before using it!
 */
struct _RING_BUFFER create_buffer(uint8_t len);


/**
 * @brief Add a byte to the ring buffer
 * @param buffer The ring buffer to add the byte to
 * @param byte The byte to be added to the ring buffer
 * @warning If the byte is added while the buffer is full, nothing will happen.
 */
void add_to_buffer(struct _RING_BUFFER* buffer, uint8_t byte);

/**
 * @brief Get the first byte from the buffer
 * @param buffer The buffer to get the byte from
 * @return Returns the byte
 * @warning Always check if the buffer contains elements before calling this function
 */
uint8_t get_byte_from_buffer(struct _RING_BUFFER* buffer);

/**
 * @brief Clears the full ring buffer
 * @param buffer
 */
void clear_buffer(struct _RING_BUFFER* buffer);


#endif /* RINGBUFFER_H_ */
