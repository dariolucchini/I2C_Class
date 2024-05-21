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

#ifndef __LIS3DH_H
    #define __LIS3DH_H
    
    #include "cytypes.h"
    #include "..\src_shared\ErrorCodes.h"
    #include "../src_shared/I2C_Interface.h"
    #include "project.h"
    #include "stdio.h"

    /**
    *   \brief 7-bit I2C address of the slave device.
    */
    #define LIS3DH_DEVICE_ADDRESS 0x18

    /**
    *   \brief Address of the WHO AM I register
    */
    #define LIS3DH_WHO_AM_I_REG_ADDR 0x0F
    
    /**
    *   \brief WHOAMI return value
    */
    #define LIS3DH_WHOAMI_RETVAL     0x33

    /**
    *   \brief Address of the Status register
    */
    #define LIS3DH_STATUS_REG 0x27

    /**
    *   \brief Address of the Control register 1
    */
    #define LIS3DH_CTRL_REG1 0x20
    
    /**
    *   \brief Address of the Control register 2
    */
    #define LIS3DH_CTRL_REG2 0x21
    
    /**
    *   \brief Address of the Control register 3
    */
    #define LIS3DH_CTRL_REG3 0x22
    
    /**
    *   \brief Address of the Control register 4
    */
    #define LIS3DH_CTRL_REG4 0x23
    
    /**
    *   \brief Address of the Control register 5
    */
    #define LIS3DH_CTRL_REG5 0x24

    /**
    *   \brief Hex value to set normal mode to the accelerator
    */
    #define LIS3DH_NORMAL_MODE_CTRL_REG1 0x47
    
    /**
    *   \brief Hex value to set normal mode (powered off)
    **/
    #define LIS3DH_NORMAL_MODE_OFF_CTRL_REG1 0x07

    /**
    *   \brief  Address of the Temperature Sensor Configuration register
    */
    #define LIS3DH_TEMP_CFG_REG 0x1F 

    #define LIS3DH_TEMP_CFG_REG_ACTIVE 0xC0
   
    /////////////////////////////////////////////////
    //EX.3
    
    // Brief Address of CTRL REG 4
    #define LIS3DH_CTRL_REG4 0x23
        
    // brief Block Data Update (BDU) Flag
    
    #define LIS3DH_CTRL_REG4_BDU_ACTIVE 0x80

    // Brief Address of the ADC output LSB register
    
    #define LIS3DH_OUT_ADC_3L 0x0C

    // Brief Address of the ADC output MSB register
    
    #define LIS3DH_OUT_ADC_3H 0x0D
    ////////////////////////////////////////////////
    /* MY REGISTERS ADDRESS */

    #define LIS3DH_FIFO_CTRL_REG 0x2E // \brief FIFO CTRL REG ADDRESS
    #define LIS3DH_FIFO_SRC_REG 0x2F // \brief FIFO SRC REG ADDRESS
    
    #define LIS3DH_OUT_X_L 0x28 // \breaf OUTPUT REGISTER for LSB of the X and FIRST ADDRESS OF THE FIFO
    #define LIS3DH_OUT_X_H 0x29 // \breaf OUTPUT REGISTER for MSB of the X
    #define LIS3DH_OUT_Y_L 0x2A // \breaf OUTPUT REGISTER for LSB of the Y
    #define LIS3DH_OUT_Y_H 0x2B // \breaf OUTPUT REGISTER for MSB of the Y
    #define LIS3DH_OUT_Z_L 0x2C // \breaf OUTPUT REGISTER for LSB of the Z
    #define LIS3DH_OUT_Z_H 0x2D // \breaf OUTPUT REGISTER for MSB of the Z
    
    /* My REGISTERS CONFIG  */
    #define LIS3DH_CTRL_REG1_POWER_DOWN 0b00000000//Normal Mode 25Hz all axis enabled
    #define LIS3DH_CTRL_REG1_NM_25HZ 0b00110111//Normal Mode 25Hz all axis enabled
    #define LIS3DH_CTRL_REG1_NM_50HZ 0b01000111//Normal Mode 50Hz all axis enabled
    #define LIS3DH_CTRL_REG1_NM_100HZ 0b01010111 //Normal Mode 100Hz all axis enabled
    #define LIS3DH_CTRL_REG1_NM_200HZ 0b01100111 //Normal Mode 200Hz all axis enabled
    #define LIS3DH_CTRL_REG2_HP_FILTER 0x00 //Normal Mode High Pass Filter
    #define LIS3DH_CTRL_REG3_WTM_ENABLE 0b00000100 // FIFO Watermark Enable
    #define LIS3DH_CTRL_REG3_OVRN_ENABLE 0b00000010 // FIFO OVRN Enable
    #define LIS3DH_CTRL_REG4_FS_2G 0x00 // Set FS at +-2g
    #define LIS3DH_CTRL_REG5_FIFO_ENABLE 0b01000000 // brief FIFO Update
    #define LIS3DH_FIFO_CTRL_REG_STREAM_MODE 0b10011101 // brief FIFO MODE STREAM MODE FM 1 0 and WTM set to 29 (the 30th value)
    
    void Init_LIS3DH(void);
    
#endif// Initialize send flag



/* [] END OF FILE */
