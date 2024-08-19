/*
 * i2c_common.c
 *
 *  Created on: 08-Aug-2024
 *      Author: guru n
 */
#include "i2c_common.h"


uint32_t I2CWrite(uint8_t deviceAddress, uint8_t *dataBuffer, size_t bufLength)
{
	uint32_t reVal = SUCCESS;
	if(SUCCESS == LPI2C_MasterStart(I2C_INSTANCE, deviceAddress, kLPI2C_Write))	//MCXA153 specific I2C driver function
	{
		if(LPI2C_MasterGetStatusFlags(I2C_INSTANCE) & kLPI2C_MasterNackDetectFlag)	////MCXA153 specific I2C driver function
		{
		   	return  ERR_NOACK;
		}
		else
		{
		   	reVal = I2C_Send(I2C_INSTANCE, dataBuffer, bufLength);	//generic i2c send
		   	if(reVal != SUCCESS)
		   	{
		  		if(reVal == ERR_NOACK)
		   	    {
		  			LPI2C_MasterStop(I2C_INSTANCE);
		   	        return ERR_NOACK;
		   	    }
        	}
        	else if(reVal == SUCCESS)
        	{
        		LPI2C_MasterStop(I2C_INSTANCE);
        		return SUCCESS;
        	}
		}
	}
	else
	{
		return ERR_I2CBUSY;
	}
}


uint32_t I2CRead(uint8_t deviceAddress,uint8_t *dataBuffer, size_t readLength)
{
	uint32_t reVal = SUCCESS;
	if(SUCCESS == LPI2C_MasterStart(I2C_INSTANCE, deviceAddress, kLPI2C_Read))
	{
		if(LPI2C_MasterGetStatusFlags(I2C_INSTANCE) & kLPI2C_MasterNackDetectFlag)
		{
        	return  ERR_NOACK;
        }
        else
        {
        	reVal = I2C_Receive(I2C_INSTANCE, dataBuffer, readLength);	////generic i2c receive function
        	if(reVal != SUCCESS)
        	{
        		if(reVal == ERR_NOACK)
        		{
        			LPI2C_MasterStop(I2C_INSTANCE);
        			return ERR_NOACK;
        		}
        	}
        	else if(reVal == SUCCESS)
        	{
        		LPI2C_MasterStop(I2C_INSTANCE);
        		return SUCCESS;
        	}
        }
	}
	else
	{
	   	return ERR_I2CBUSY;
	}
}


void I2CInit(uint32_t baudRate)
{
	lpi2c_master_config_t masterConfig;
	uint32_t sourceClock_Hz = I2C_CLOCK_FREQUENCY;
		/*
	     * masterConfig.debugEnable = false;
	     * masterConfig.ignoreAck = false;
	     * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
	     * masterConfig.baudRate_Hz = 100000U;
	     * masterConfig.busIdleTimeout_ns = 0;
	     * masterConfig.pinLowTimeout_ns = 0;
	     * masterConfig.sdaGlitchFilterWidth_ns = 0;
	     * masterConfig.sclGlitchFilterWidth_ns = 0;
	     */
	    LPI2C_MasterGetDefaultConfig(&masterConfig);

	    /* Change the default baudrate configuration */
	    masterConfig.baudRate_Hz = baudRate;

	    /* Initialize the LPI2C master peripheral */
	    LPI2C_MasterInit(I2C_INSTANCE, &masterConfig, sourceClock_Hz);
}
