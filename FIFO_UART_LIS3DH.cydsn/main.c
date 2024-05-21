/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include "InterruptRoutines.h"
#include "../src_shared/I2C_Interface.h"
#include "../src_shared/LIS3DH.h"
#include "../src_shared/ErrorCodes.h"


// Set this to 1 to send byte data for the Bridge Control Panel
// Otherwise set it to 0 to send temperature data as int16_t
#define USE_BRIDGECONTROLPANEL  0



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Peripheral_Start();
    UART_1_Start();
    
    
    CyDelay(5); //"The boot procedure is complete about 5 ms after device power-up."
    
    // Check if LIS3DH is connected
    uint32_t rval = I2C_Master_MasterSendStart(LIS3DH_DEVICE_ADDRESS, I2C_Master_WRITE_XFER_MODE);
    if( rval == I2C_Master_MSTR_NO_ERROR ) {
        UART_1_PutString("LIS3DH found @ address 0x18\r\n");
    }
    I2C_Master_MasterSendStop();
    
    // String to print out messages over UART
    char message[50] = {'\0'};
    
    UART_1_PutString("**************\r\n");
    UART_1_PutString("** I2C Scan **\r\n");
    UART_1_PutString("**************\r\n");
    
    CyDelay(10);
    
    // Setup the screen and print the header
	UART_1_PutString("\n\n   ");
	for(uint8_t i = 0; i<0x10; i++)
	{
        sprintf(message, "%02X ", i);
		UART_1_PutString(message);
	}
    
    // SCAN the I2C BUS for slaves
	for( uint8_t i2caddress = 0; i2caddress < 0x80; i2caddress++ ) {
        
		if(i2caddress % 0x10 == 0 ) {
            sprintf(message, "\n%02X ", i2caddress);
		    UART_1_PutString(message);
        }
 
		rval = I2C_Master_MasterSendStart(i2caddress, I2C_Master_WRITE_XFER_MODE);
        
        if( rval == I2C_Master_MSTR_NO_ERROR ) // If you get ACK then print the address
		{
            sprintf(message, "%02X ", i2caddress);
		    UART_1_PutString(message);
		}
		else //  Otherwise print a --
		{
		    UART_1_PutString("-- ");
		}
        I2C_Master_MasterSendStop();
	}
	UART_1_PutString("\n\n");
    
    /******************************************/
    /*            I2C Reading                 */
    /******************************************/
      
    isr_1_StartEx(Custom_ISR_FIFO);
    Init_LIS3DH();
    
    
    //variables
    
    int16_t OUT_Z;
    int16_t OUT_X;
    int16_t OUT_Y;
    PacketReadyFlag=0;
    //int8_t ctrl_reg5;
    
    for(;;)
    {

        if(PacketReadyFlag==1){         
            for(int i=0;i<192;i++){
                OUT_X = (int16_t)(out_xyz[i] | (out_xyz[i+1]<<8))>>6;
                OUT_Y = (int16_t)(out_xyz[i+2] | (out_xyz[i+3]<<8))>>6;
                OUT_Z = (int16_t)(out_xyz[i+4] | (out_xyz[i+5]<<8))>>6;
 
                sprintf(message, "X Output: %d\r\nY Output: %d\r\nZ Output: %d\r\n", OUT_X, OUT_Y,OUT_Z);

            }
            PacketReadyFlag=0;
        }
              
         
        
        

        
        
            
        
        
        
        
    }       

    
}

/* [] END OF FILE */
