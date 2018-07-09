/**
 * Author: Robert
 * Description: A device to control RF wall sockets
 * Date: 29-jun-2018
 */

#include "RF433_SF500.h"
#include "UART.h"
#include "SerialProto.h"

//Test with python: ser.write(b'\x10\x01\xAC\x2C\x00\x01\x00')

int main(){
	UART_init();
	RFS_init();
	SP_init();

	UART_sendstring("Init complete\n");

	while(1){
		SP_check();
	}
}
