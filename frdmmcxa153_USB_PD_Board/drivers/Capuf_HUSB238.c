/*
 * usb_pdo.c
 *
 *  Created on: 19-Aug-2024
 *      Author: gurun
 */

#include <Capuf_HUSB238.h>

#include "i2c_common.h"

uint8_t ReadPDSourceVandI(uint8_t deviceAddress, uint8_t *voltage, uint8_t *current)
{
	uint8_t dataBuf[I2C_REGISTER_LENGTH]={0};
	dataBuf[0] = (PD_STATUS0 & 0xFF);
	uint32_t status = 0;
	status = I2CWrite(deviceAddress, dataBuf, 1);	// write register read address (PD_STATUS0)
	if(status != SUCCESS)
	{
		return status;
	}
	pd_status0_t status0;
	status = I2CRead(deviceAddress, (uint8_t *)&status0, 1);	// read voltage and current value from PD_STATUS0 Register
	if(status != SUCCESS)
	{
		return status;
	}

	*voltage = (uint8_t)status0.sourceVolt;
	*current = (uint8_t)status0.sourceCurr;
	return PD_OK;
}


uint8_t CheckPDAttachStatus(uint8_t deviceAddress, uint8_t *attachStatus)
{
	uint8_t dataBuf[I2C_REGISTER_LENGTH]={0};
	dataBuf[0] = (PD_STATUS1 & 0xFF);
	uint32_t status = 0;
	status = I2CWrite(deviceAddress, dataBuf, 1);	// write register read address (PD_STATUS1)
	if(status != SUCCESS)
	{
		return status;
	}
	pd_status1_t status1;
	status = I2CRead(deviceAddress, (uint8_t *)&status1, 1);	// read register PD_STATUS1
	if(status != SUCCESS)
	{
		return status;
	}
	// attach status updated
	*attachStatus = status1.attach;
	return PD_OK;
}


uint8_t SelectPDSourceVoltage(uint8_t deviceAddress, uint8_t *sourceVolt)
{
	uint32_t response = 0;
	uint8_t dataBuf[I2C_REGISTER_LENGTH + 1]={0};
	dataBuf[0] = (SRC_PDO & 0xFF);
//	src_pdo_t sourcePDO ;
//	sourcePDO.selectPDO = (*sourceVolt) & 0x0F;
//	dataBuf[1] = sourcePDO ;
	dataBuf[1] = (((*sourceVolt) & 0x0F)<< 4);
	uint32_t status = 0;
	status = I2CWrite(deviceAddress, dataBuf, 2); // write voltage value in register SRC_PDO
	if(status != SUCCESS)
	{
		return status;
	}
	//send GO_Command to start transaction
	status = RequestPDO(deviceAddress);
	if(status != PD_OK)
	{
		return status;
	}
	// validate for successfull transaction
	status = CheckPDResponse(deviceAddress, &response);
	if(status != PD_OK)
	{
		return status;
	}
	if((response & 0x07)!= Success)
	{
		return PD_ERROR;
	}
	return PD_OK;
}


static uint8_t RequestPDO(uint8_t deviceAddress)
{
	uint32_t status = 0;
	uint8_t dataBuf[I2C_REGISTER_LENGTH + 1]={0};
	dataBuf[0] = (GO_COMMAND & 0xFF);
	uint8_t command = setPDOSelect;	// command to start transaction for configured voltage
//	go_command_t goCommand ;
//	goCommand.commandFunction = (command) & 0x1F;
	dataBuf[1] = (command) & 0x1F;
	status = I2CWrite(deviceAddress, dataBuf, 2);	// write command value to register GO_COMMAND;
	if(status != SUCCESS)
	{
		return status;
	}
	return PD_OK;
}


static uint8_t CheckPDResponse(uint8_t deviceAddress, uint32_t *pdResponse)
{
	uint8_t dataBuf[I2C_REGISTER_LENGTH]={0};
	dataBuf[0] = (PD_STATUS1 & 0xFF);
	uint32_t status = 0;
	status = I2CWrite(deviceAddress, dataBuf, 1);	//write register read address (PD_STATUS1)
	if(status != SUCCESS)
	{
		return status;
	}
	pd_status1_t status1;
	status = I2CRead(deviceAddress, (uint8_t *)&status1, 1);	// read response from register PD_STATUS1
	if(status != SUCCESS)
	{
		return status;
	}
	*pdResponse = status1.pdResponse;
	return PD_OK;
}



