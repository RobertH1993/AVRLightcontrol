/**
 * Author: Robert
 * Description: A device to control RF wall sockets
 * Date: 29-jun-2018
 */

#include "UART.h"
#include "RFSwitch433.h"
#include "SerialProto.h"

int main(){
	UART_init();
	RFS_init();
	SP_init();

	UART_sendstring("Init complete\n");

	while(1){
		SP_check();
	}
}
