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
//INITIALIZATION OF LIS3DH

#include "../src_shared/LIS3DH.h"


void Init_LIS3DH(void){
    
    
    // String to print out messages over UART
    char message[50] = {'\0'};  
    /*      I2C Master Read - WHOAMI Register       */
    uint8_t whoami_reg;
    ErrorCode error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, 
                                                  LIS3DH_WHO_AM_I_REG_ADDR,
                                                  &whoami_reg);
    if( error == NO_ERROR ) {
        sprintf(message, "WHOAMI reg value: 0x%02X [Expected value: 0x%02X]\r\n", whoami_reg, LIS3DH_WHOAMI_RETVAL);
        UART_1_PutString(message);
    }
    else {
        UART_1_PutString("I2C error while reading LIS3DH_WHO_AM_I_REG_ADDR\r\n");
    }
    
    
    /*      I2C Master Read - STATUS Register       */
    
    uint8_t status_reg;
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, 
                                        LIS3DH_STATUS_REG,
                                        &status_reg);
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_STATUS_REG value: 0x%02X\r\n", status_reg);
        UART_1_PutString(message);
    }
    else {
        UART_1_PutString("I2C error while reading LIS3DH_STATUS_REG\r\n");
    }
    
    /*      I2C Master Read - CTRL Register 1       */
    
    uint8_t ctrl_reg_1;
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, 
                                        LIS3DH_CTRL_REG1,
                                        &ctrl_reg_1);
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG1 value: 0x%02X\r\n", ctrl_reg_1);
        UART_1_PutString(message);
    }
    else {
        UART_1_PutString("I2C error while reading LIS3DH_CTRL_REG1\r\n");
    }
    
    /*      I2C Master Write - CTRL Register 1       */
    
    ctrl_reg_1=0x37;  // low power mode 25 Hz
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1,ctrl_reg_1);
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1,&ctrl_reg_1);
    
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG1: 0x%02X\r\n", ctrl_reg_1);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_CTRL_REG1\r\n"); 
    }      
    

  
    
    /*      I2C Master Read - CTRL Register 2       */
    
    uint8_t ctrl_reg2;
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG2,
                                        &ctrl_reg2);
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG2: 0x%02X\r\n", ctrl_reg2);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_CTRL_REG2\r\n"); 
    }
    
    /*      I2C Master Write - CTRL Register 2      */
    
    ctrl_reg2=0x88; //HIGHPASS FILTER enabled
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG2,ctrl_reg2);
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG2,&ctrl_reg2);
    
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG2: 0x%02X\r\n", ctrl_reg2);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_CTRL_REG2\r\n"); 
    } 
    
    
    /*      I2C Master Read - CTRL Register 3      */
    
    uint8_t ctrl_reg3;
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG3,
                                        &ctrl_reg3);
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG3: 0x%02X\r\n", ctrl_reg3);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_CTRL_REG3\r\n"); 
    }
    
    /*      I2C Master Write - CTRL Register 3       */
    
    ctrl_reg3=0x02;  // OVERRUN enabled
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG3,ctrl_reg3);
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG3,&ctrl_reg3);
    
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG3: 0x%02X\r\n", ctrl_reg3);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_CTRL_REG3\r\n"); 
    }       
    
    /*   I2C CTRL REG 4 Reading from LIS3DH   */
  
    uint8_t ctrl_reg_4;
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4,
                                        &ctrl_reg_4);
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG_4: 0x%02X\r\n", ctrl_reg_4);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_CTRL_REG_4\r\n"); 
    }    
    
    
    ///*      I2C Master Read - CTRL Register 5      */ 
    
    uint8_t ctrl_reg5;
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG5,
                                        &ctrl_reg5);
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG5: 0x%02X\r\n", ctrl_reg5);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_CTRL_REG5\r\n"); 
    }
    
    /*      I2C Master Write - CTRL Register 5       */
    
    ctrl_reg5=0x40;  // FIFO enabled
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG5,ctrl_reg5);
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG5,&ctrl_reg5);
    
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG5: 0x%02X\r\n", ctrl_reg5);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_CTRL_REG5\r\n"); 
    }    
    
    /*      I2C Master Read - FIFO CTRL Register        */
    
    uint8_t fifo;
    error=I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG, &fifo); 
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_FIFO_CTRL_REG: 0x%02X\r\n", fifo);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_FIFO_CTRL_REG\r\n"); 
    }
    
    /*      I2C Master Write - FIFO CTRL Register        */
    
    fifo=0x80;   //STREAM MODE
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG,fifo);
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_FIFO_CTRL_REG,&fifo);
    
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_FIFO_CTRL_REG: 0x%02X\r\n", fifo);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_FIFO_CTRL_REG\r\n"); 
    } 
    


}

/* [] END OF FILE */
