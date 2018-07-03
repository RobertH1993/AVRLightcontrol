/**
 * Author: Robert Hendriks (robert.hendriks1993@gmail.com)
 * Description: A device for realtime monitoring of 433Mhz communications.
 * Date: 29-jun-2018
 */

#include "UART.h"
#include "RFSwitch433.h"
#include "SerialProto.h"

int main(){
	UART_init();
	RFS_init();
	SP_init();

	while(1){
		SP_check();
	}
}
