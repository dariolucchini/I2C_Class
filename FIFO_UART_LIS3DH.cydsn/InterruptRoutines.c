
// Include header
#include "InterruptRoutines.h"
// Include required header files
#include "project.h"

// Variables declaration
uint8_t ReceivedBytes=0;
uint8 ch_receveid;
uint8 SendBytesFlag=0;


char message[50] = {'\0'};
CY_ISR(Custom_ISR_FIFO)
{
    
    ErrorCode error= I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                       LIS3DH_OUT_X_L, 192, out_xyz);
    
    if(error == NO_ERROR) {
        PacketReadyFlag=1;
        
        
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_OUT_ADC_3L\r\n"); 
    }
    Pin_INTERRUPT_ClearInterrupt();
        
    
}

