
// Include header
#include "InterruptRoutines.h"
// Include required header files
#include "project.h"
#include <stdio.h>
#include "project.h"
#include "../src_shared/I2C_Interface.h"
#include "../src_shared/LIS3DH.h"
#include "../src_shared/ErrorCodes.h"

// Variables declaration
int32 value_digit;
int32 value_mv;
uint8 ch_receveid;
uint8 SendBytesFlag=0;
int16_t OUT_X;
int16_t OUT_Y;
int16_t OUT_Z;
uint8_t out_xyz[192];
char message[50] = {'\0'};
CY_ISR(Custom_ISR_FIFO)
{
    if (SendBytesFlag == 1) {
            ErrorCode error= I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                               LIS3DH_OUT_X_L, 192, out_xyz);
        
            if(error == NO_ERROR) { 
                for(int i=0;i<192;i++){
                    OUT_X = (int16_t)(out_xyz[i] | (out_xyz[i+1]<<8))>>6;
                    OUT_Y = (int16_t)(out_xyz[i+2] | (out_xyz[i+3]<<8))>>6;
                    OUT_Z = (int16_t)(out_xyz[i+4] | (out_xyz[i+5]<<8))>>6;
                    
                    sprintf(message, "X Output: %d\r\nY Output: %d\r\nZ Output: %d\r\n", OUT_X, OUT_Y,OUT_Z);
                    UART_1_PutString(message);
                }
            }
            else {
                UART_1_PutString("Error occurred during I2C comm to read LIS3DH_OUT_ADC_3L\r\n"); 
            }
        
        
    }
}

