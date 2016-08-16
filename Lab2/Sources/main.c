/* ###################################################################
**     Filename    : main.c
**     Project     : Lab2
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-08-09, 09:33, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "I2C.h"
#include "IntI2cLdd1.h"
#include "CsIO1.h"
#include "IO1.h"
#include "TU1.h"
#include "Red.h"
#include "PwmLdd1.h"
#include "Blue.h"
#include "PwmLdd2.h"
#include "Green.h"
#include "PwmLdd3.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU2.h"
#include "AS1.h"
#include "Inhr1.h"
#include "ASerialLdd2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdio.h>
#include <string.h>

void EmptyByteArray(byte *array, int len){
	int i;
	for (i=0; i<len; i++){
		array[i] = 0;
	}
}

void send_string(char *str){
	AS1_SendStr(str);
}

/*
void send_string(char *str){
	size_t i, len; // a size_t is an unsigned integer
	len = strlen(str); // returns the number of chars in str
	byte err;
	for (i = 0; i < len; i++) {
		// send this character
		do {
			err = AS1_SendChar(str[i]);
		} while (err != ERR_OK);
	}
	//Add new line after strings
	do {
		err = AS1_SendChar('\n');
	} while (err != ERR_OK);
	//Remove indent (move to left)
	do {
			err = AS1_SendChar('\r');
		} while (err != ERR_OK);
}//End of send_string function
*/

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  	/* Write your code here */
	byte error_code = ERR_OK;
	word data_sent = 0;
	int i = 0; //delay loop index

	//I2C_SelectSlave(0x1D); // 0x1C is the 1st slave address, see p17 at http://cache.nxp.com/files/sensors/doc/data_sheet/MMA8451Q.pdf

	// note 1byte = 8bits

	//Turn on I2C
	byte control_register_buffer[2] = {0x02A, 1}; // of form: {register,valueToPutInRegister}
	  //"register" part: Request write to control register 1
	  //value part: set bit 0 (ACTIVE bit) to 1, see p45 of MMA8451Q data sheet
	error_code = I2C_SendBlock(control_register_buffer, 2, &data_sent);
	  if(error_code != ERR_OK){
		  send_string("Error: Activating I2C");
	  }

	char data_str_buffer[64];

	short int data[3];			//EmptyByteArray(data, data_size);
	byte read_buffer[2] = { }; //of form: {register,valueToPutInRegister}
	data[0] = 0;	data[1] = 0;	data[2] = 0;
	word amount_sent = 0;
	word amount_of_data = 0;
	for(;;) {
	  //delay
		for(i=0; i<1000000; i++)
		{}

	  //Retrieve x, y, z movement
	  read_buffer[0] = 0x01; //Request data register to read from, see p20 of MMA8451Q data sheet for register addresses
	  error_code = I2C_SendChar(0x01);
	  //error_code = I2C_SendBlock(read_buffer, 1, &data_sent);
		  if(error_code != ERR_OK){
			  send_string("Error: Requesting register to read");
		  }
	  error_code = I2C_RecvBlock(data, 6, &amount_of_data);
		  if(error_code != ERR_OK){
			  send_string("Error: Receiving data");
		  }
	  printf("%d %d\n", amount_of_data, data);
	  //printf("%*.d\n",amount_of_data, data);

	  snprintf(data_str_buffer,63, "x: %5d\t y: %5d\t z: %5d\n\r", data[0], data[1], data[2]);
	  data_str_buffer[63] = '\0'; //ensure null termination
	  send_string(data_str_buffer);

	  //Testing if console works
	  printf("This is a string\n");
	  //AS1_SendChar('a');
	  //AS1_SendChar('\n');
	  //AS1_SendChar('\r');

	  word redlight = fabs(data[0]);
	  word bluelight = fabs(data[1]);
	  word greenlight = fabs(data[2]);
	  Red_SetRatio16(redlight);
	  Blue_SetRatio16(bluelight);
	  Green_SetRatio16(greenlight);
//	  //Retrieve x, y, z movement
//	  I2C_SendChar(0x04); //Request data register to read from, see p20 of MMA8451Q data sheet for register addresses
//	  I2C_RecvBlock(data, data_size, &amount_of_data);
//	  printf("%d %*.d\t", amount_of_data, data_size, data);
//
//	  //Retrieve x, y, z movement
//	  I2C_SendChar(0x06); //Request data register to read from, see p20 of MMA8451Q data sheet for register addresses
//	  I2C_RecvBlock(data, data_size, &amount_of_data);
//	  printf("%d %*.d", amount_of_data, data_size, data);
//
//	  printf("\n");

	  //Print movement
	  //printf("X axis:%x\n",x);

	  //Refresh console window
	  //printf("\f");
	}








  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
