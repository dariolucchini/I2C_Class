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
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    
    #include "cytypes.h"
    #include "stdio.h"
    #include "../src_shared/I2C_Interface.h"
    #include "../src_shared/LIS3DH.h"
    #include "../src_shared/ErrorCodes.h"
    
    #define TRANSMIT_BUFFER_SIZE 16
    
    CY_ISR_PROTO (Custom_ISR_FIFO);
    CY_ISR_PROTO (Custom_ISR_RX);
    
    char DataBuffer[TRANSMIT_BUFFER_SIZE];
    volatile uint8 PacketReadyFlag;
    uint8_t out_xyz[192];
#endif

/* [] END OF FILE */
