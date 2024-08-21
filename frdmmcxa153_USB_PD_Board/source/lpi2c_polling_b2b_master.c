/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */
#include <Capuf_HUSB238.h>
#include <stdio.h>
#include <string.h>
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_clock.h"
#include "fsl_debug_console.h"
#include "i2c_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
//#define LPI2C_MASTER_CLOCK_FREQUENCY CLOCK_GetLpi2cClkFreq()


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/



/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */


void SystickSetDelay(uint32_t time_ms);


volatile uint32_t systickCounter  = 20U;


void SysTick_Handler(void)
{
    if(systickCounter != 0U)
    {
        systickCounter--;
    }
}

void SystickSetDelay(uint32_t time_ms)
{
	systickCounter = time_ms;
	while(systickCounter != 0)
	{
		;
	}
}


int main(void)
{
//    lpi2c_master_config_t masterConfig;
    status_t reVal        = kStatus_Fail;
    uint8_t deviceAddress = 0x01U;
    size_t txCount        = 0xFFU;


    //PDO I2C register structures
    pd_status0_t status0 = {0};
    pd_status1_t status1 = {0};
    src_pdo_5V_t pdo5V = {0};
    src_pdo_9V_t pdo9V = {0};
    src_pdo_12V_t pdo12V = {0};

    src_pdo_t setPDO ={0};
    go_command_t goCommand ={0};


    /* Attach peripheral clock for I2C*/
    CLOCK_SetClockDiv(kCLOCK_DivLPI2C0, 1u);
    CLOCK_AttachClk(kFRO12M_to_LPI2C0);
    RESET_PeripheralReset(kLPI2C0_RST_SHIFT_RSTn);

    BOARD_InitPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    PRINTF("\r\nLPI2C USB PD Board example.\r\n");
    uint32_t baudRate = 100000;
    I2CInit(baudRate);
    PRINTF("I2C initialized\r\n");
    SysTick_Config(SystemCoreClock / 1000U);
    SystickSetDelay(2000);
    /* CHECK for ACK from slave device */
//    if (kStatus_Success == LPI2C_MasterStart(I2C_INSTANCE, I2C_DEVICE_ADDR_7BIT, kLPI2C_Write))
//    {
//        /* Check communicate with slave successful or not */
//        if (LPI2C_MasterGetStatusFlags(I2C_INSTANCE) & kLPI2C_MasterNackDetectFlag)
//        {
//// 			slave did not acknowledge
//        	PRINTF("No ACK from slave\r\n");
//        }
//        else
//        {
//        	//slave acknowledged
//        	PRINTF("Ack from slave\r\n");
//        }
//    }
//    else
//    {
//    	//i2c bus busy
//    	PRINTF("I2C Busy\r\n");
//    }
    //delay in milliseconds
    SystickSetDelay(2000);

     uint32_t status ;
     uint8_t voltage=0,current=0;
     // check for Slave i2c device ACK
     status = ReadPDSourceVandI(I2C_DEVICE_ADDR_7BIT, &voltage, &current);
     if(status == PD_OK)
     {
    	 PRINTF("ACK from I2C Slave Successful\r\n");
     }
     else
     {
    	 PRINTF("No ACK from Slave I2C Device\r\n");
     }
//     status = RequestHardwareReset(I2C_DEVICE_ADDR_7BIT);
//     if(status == PD_OK)
//     {
//    	 PRINTF("Hardware Reset\r\n");
//     }
     SystickSetDelay(2000);
     uint8_t attach = 0;
     // check if power adapter attached or not
     status = CheckPDAttachStatus(I2C_DEVICE_ADDR_7BIT, &attach);
     if(status == PD_OK)
     {
    	 if(attach)
    	 {
    		 PRINTF("adapter attached\r\n");
    	 }
    	 else
    	 {
    		 PRINTF("adapter not attached\r\n");
//    		 return 0;
    	 }
     }
     SystickSetDelay(1000);
     /* select voltage to be requested*/
     uint8_t sourceVolt = sourcePDO12v;
     status = SelectPDSourceVoltage(I2C_DEVICE_ADDR_7BIT, sourceVolt);
     if(status == PD_OK)
     {
    	 switch(sourceVolt)
    	 {
    	     	 case unAttached :
    	     		 	 	 	 PRINTF("voltage not selected\r\n");
    	     		 	 	 	 break;
    	     	 case sourcePDO5v :
    	     		 	 	 	 PRINTF("voltage set to 5V\r\n");
    	     		 	 	 	 break;
    	     	 case sourcePDO9v :
    	     		 	 	 	 PRINTF("voltage set to 9V\r\n");
    	     		 	 	 	 break;
    	     	 case sourcePDO12v :
    	     		 	 	 	 PRINTF("voltage set to 12V\r\n");
    	     		 	 	 	 break;
    	     	 case sourcePDO15v :
    	     		 	 	 	 PRINTF("voltage set to 15V\r\n");
    	     		 	 	 	 break;
    	     	 case sourcePDO18v :
    	     		 	 	 	 PRINTF("voltage set to 18V\r\n");
    	     		 	 	 	 break;
    	     	 case sourcePDO20v :
    	     		 	 	 	 PRINTF("voltage set to 20V\r\n");
    	     		 	 	 	 break;
    	 }
     }
     else
     {
    	 PRINTF("Failed to select voltage \r\n");
//    	 return 0;
     }


     SystickSetDelay(3000);


//     /* read the current PD source voltage and current */
     status = ReadPDSourceVandI(I2C_DEVICE_ADDR_7BIT, &voltage, &current);
     if(status == PD_OK)
     {
    	 switch(voltage)
    	 {
    	 case unAttached :
    		 	 	 	 PRINTF("adapter unattached\r\n");
    		 	 	 	 break;
    	 case PD5V :
    		 	 	 	 PRINTF("source voltage : 5V\r\n");
    		 	 	 	 break;
    	 case PD9V :
    		 	 	 	 PRINTF("source voltage : 9V\r\n");
    		 	 	 	 break;
    	 case PD12V :
    		 	 	 	 PRINTF("source voltage : 12V\r\n");
    		 	 	 	 break;
    	 case PD15V :
    		 	 	 	 PRINTF("source voltage : 15V\r\n");
    		 	 	 	 break;
    	 case PD18V :
    		 	 	 	 PRINTF("source voltage : 18V\r\n");
    		 	 	 	 break;
    	 case PD20V :
    		 	 	 	 PRINTF("source voltage : 20V\r\n");
    		 	 	 	 break;
    	 }
    	 switch(current)
    	 {
    	 	 case PD050A :
    	     		 	 	 	 PRINTF("source current : 0.5A\r\n");
    	     		 	 	 	 break;
    	 	 case PD070A :
    	     		 	 	 	 PRINTF("source current : 0.7A\r\n");
    	     		 	 	 	 break;
    	     case PD100A :
    	     		 	 	 	 PRINTF("source current : 1.0A\r\n");
    	     		 	 	 	 break;
    	     case PD125A :
    	     		 	 	 	 PRINTF("source current : 1.25A\r\n");
    	     		 	 	 	 break;
    	     case PD150A :
    	     		 	 	 	 PRINTF("source current : 1.5A\r\n");
    	     		 	 	 	 break;
    	     case PD175A :
    	     		 	 	 	 PRINTF("source current : 1.75A\r\n");
    	     		 	 	 	 break;
    	     case PD200A :
    	     		 	 	 	 PRINTF("source current : 2.0A\r\n");
    	     		 	 	 	 break;
    	     case PD225A :
    	    	 	 	 	 	 PRINTF("source current : 2.25A\r\n");
    	    	 	 	 	 	 break;
    	     case PD250A :
    	    	 	 	 	 	 PRINTF("source current : 2.5A\r\n");
    	    	 	 	 	 	 break;
    	     case PD275A :
    	    	 	 	 	 	 PRINTF("source current : 2.75A\r\n");
    	    	 	 	 	 	 break;
    	     case PD300A :
    	    	 	 	 	 	 PRINTF("source current : 3.0A\r\n");
    	    	 	 	 	 	 break;
    	     case PD325A :
    	    	 	 	 	 	 PRINTF("source current : 3.25A\r\n");
    	    	 	 	 	 	 break;
    	     case PD350A :
    	    	 	 	 	 	 PRINTF("source current : 3.5A\r\n");
    	    	 	 	 	 	 break;
    	     case PD400A :
    	    	 	 	 	 	 PRINTF("source current : 4.0A\r\n");
    	    	 	 	 	 	 break;
    	     case PD450A :
    	    	 	 	 	 	 PRINTF("source current : 4.5A\r\n");
    	    	 	 	 	 	 break;
    	     case PD500A :
    	    	 	 	 	 	 PRINTF("source current : 5.0A\r\n");
    	    	 	 	 	 	 break;
    	  }
     }
     else
     {
    	 PRINTF("Failed to check voltage and current\r\n");
//    	 return 0;
     }


    while (1)
    {
    }
}


