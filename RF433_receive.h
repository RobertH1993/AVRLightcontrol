/*
 * RF433_receive.h
 *
 *  Created on: Jul 8, 2018
 *      Author: robert
 */

#ifndef RF433_RECEIVE_H_
#define RF433_RECEIVE_H_

#define RX_BUFFER_LENGTH 128
#define PULSE_RESOLUTION 266

/**
 * @brief Init the 433Mhz receiver
 */
void RF433_receive_init();

/**
 * @brief Enable the receiver
 *
 * @warning Do only use on set moments, this is a resource hog
 */
void RF433_receive_enable();

/**
 * @brief Disable the receiver
 */
void RF433_receive_disable();


#endif /* RF433_RECEIVE_H_ */
