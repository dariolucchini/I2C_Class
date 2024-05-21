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
#include <stdio.h>
#include "project.h"
#include "../src_shared/I2C_Interface.h"
#include "../src_shared/LIS3DH.h"

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
    
    uint8_t control_reg;
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, 
                                        LIS3DH_CTRL_REG1,
                                        &control_reg);
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG1 value: 0x%02X\r\n", control_reg);
        UART_1_PutString(message);
    }
    else {
        UART_1_PutString("I2C error while reading LIS3DH_CTRL_REG1\r\n");
    }
    
    
    /*   I2C Temperature CFG REG Reading from LIS3DH   */
       
    
    // Register variables
    uint8_t tmp_cfg_reg;
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_TEMP_CFG_REG,
                                        &tmp_cfg_reg);
    if( error == NO_ERROR ) 
    {
    sprintf(message, "\r\nLIS3DH_TEMP_CFG_REG: 0x%02X\r\n", tmp_cfg_reg);
    UART_1_PutString(message);
    }
    else 
    {
    UART_1_PutString("Error occurred during I2C comm to read LIS3DH_TEMP_CFG_REG\r\n");
    }
    
    tmp_cfg_reg|=0b11000000;
    error=I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_TEMP_CFG_REG,
                                        tmp_cfg_reg);
    /*   I2C Temperature CTRL REG 4 Reading from LIS3DH   */
    
    
    uint8_t ctrl_reg4; 
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG4,
                                        &ctrl_reg4);
    if( error == NO_ERROR ) 
    {
    sprintf(message, "\r\nCONTROL REGISTER 4: 0x%02X\r\n", ctrl_reg4);
    UART_1_PutString(message);
    }
    else 
    {
    UART_1_PutString("Error occurred during I2C comm to read LIS3DH_TEMP_CFG_REG\r\n");
    }    
    
    // TO DO...
  
    uint8_t reg;
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4,
                                        &reg);
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_??_REG: 0x%02X\r\n", reg);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_??_REG\r\n"); 
    }
    
    //register 1
    uint8_t ctr_reg1;
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1,
                                        &ctr_reg1);
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_??_REG: 0x%02X\r\n", ctr_reg1);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_??_REG\r\n"); 
    }
    
    ctr_reg1=0x77;
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1,ctr_reg1);
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1,&ctr_reg1);
    
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG1: 0x%02X\r\n", ctr_reg1);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_CTRL_REG1\r\n"); 
    }    
    
    //register 2
    
    uint8_t ctrl_reg2;
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG2,
                                        &ctrl_reg2);
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG2: 0x%02X\r\n", ctrl_reg2);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_??_REG\r\n"); 
    }
    
    
    
    ctrl_reg2=0x88;
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG2,ctrl_reg2);
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG2,&ctrl_reg2);
    
    if( error == NO_ERROR ) {
        sprintf(message, "LIS3DH_CTRL_REG1: 0x%02X\r\n", ctrl_reg2);
        UART_1_PutString(message); 
    }
    else {
        UART_1_PutString("Error occurred during I2C comm to read LIS3DH_CTRL_REG1\r\n"); 
    } 
    
    //variables
    
    uint8_t TemperatureData[2];
    uint16_t OutTemp;
    
    uint8_t out_z[2];
    uint8_t out_xyz[6];
    int16_t OUT_Z;
    int16_t OUT_X;
    int16_t OUT_Y;
    int16_t avg_x=0;
    int16_t avg_y=0;
    int16_t avg_z=0;

    float data_x[50];
    float data_y[50];
    float data_z[50];
    
    //initializzazione
    for(int i=0;i<50;i++){
        data_x[i]=0;
        data_y[i]=0;
        data_z[i]=0;
    }
    
    

    int16_t count=0;
    
    for(;;)
    {
        //CyDelay(100);
        
        uint8_t status_reg;
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, 
                                        LIS3DH_STATUS_REG, 
                                        &status_reg);
        CyDelay(10);
        uint8_t bit_mask=0x08;
        if(status_reg&bit_mask){
            
            error= I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                               LIS3DH_OUT_X_L, 6, out_xyz);            
            
 
            
        }
        if(error == NO_ERROR) { 
            OUT_X = (int16_t)(out_xyz[0] | (out_xyz[1]<<8))>>6;
            OUT_Y = (int16_t)(out_xyz[2] | (out_xyz[3]<<8))>>6;
            OUT_Z = (int16_t)(out_xyz[4] | (out_xyz[5]<<8))>>6;
            
            //add filtering
            /*
            //mobile mean
            avg_x-=data_x[count];
            avg_y-=data_y[count];
            avg_z-=data_z[count];
            data_x[count]=OUT_X/5;
            data_y[count]=OUT_Y/5;
            data_z[count]=OUT_Z/5;
            avg_x+=data_x[count];
            avg_y+=data_y[count];
            avg_z+=data_z[count];
            
            
            
            
            if(count==5){
                count=0;

            }
            
            */
            count++;
            sprintf(message, "X Output: %d\r\nY Output: %d\r\nZ Output: %d\r\n\r\n%d\r\n", OUT_X,OUT_Y,OUT_Z,count);
            //sprintf(message, "Z Output: %d\r\n", OUT_Z);
                UART_1_PutString(message);   
            
            //calculate velocity
            
            
            
            

        }
        else {
            UART_1_PutString("Error occurred during I2C comm to read LIS3DH_OUT_ADC_3L\r\n"); 
        }            
            

        
    }       

    
}

/* [] END OF FILE */
