/*
 * RFSwitch433.h
 *
 *  Created on: Jun 30, 2018
 *      Author: robert
 */

#ifndef RFSWITCH433_H_
#define RFSWITCH433_H_
#include <stdint.h>

#define PERIOD_US 266
#define REPEATS 4


/**
 * @brief Init the RFSwitching component
 * @warning must be called before any other function in this header file
 */
void RFS_init();


/**
 * @brief Send a control message to a certain unit
 * @param address The address of the units
 * @param unit The unit id
 * @param state The state, 0 for off 1 for on
 */
void RFS_send_unit(uint32_t address, uint8_t unit, uint8_t state);



#endif /* RFSWITCH433_H_ */
