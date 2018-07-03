/*
 * SerialProto.h
 *
 *  Created on: Jul 1, 2018
 *      Author: robert
 */

#ifndef SERIALPROTO_H_
#define SERIALPROTO_H_

/**
 * @brief init the serial protocol functions
 */
void SP_init();

/**
 * @brief Check if we got a serial message from the ESP
 */
void SP_check();


#endif /* SERIALPROTO_H_ */
