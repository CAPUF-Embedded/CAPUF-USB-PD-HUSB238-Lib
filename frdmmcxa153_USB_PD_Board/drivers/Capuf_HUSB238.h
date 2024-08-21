/*
 * usb_pdo.h
 *
 *  Created on: 16-Aug-2024
 *      Author: guru N
 */

#include <stdint.h>
#ifndef USB_PDO_H_
#define USB_PDO_H_

//macro for function return
#define PD_OK			0
#define PD_ERROR		1

//Registers Address
#define PD_STATUS0		0x00
#define PD_STATUS1		0x01
#define SRC_PDO_5V		0x02
#define SRC_PDO_9V		0x03
#define SRC_PDO_12V		0x04
#define SRC_PDO_15V		0x05
#define SRC_PDO_18V		0x06
#define SRC_PDO_20V		0x07
#define SRC_PDO			0x08
#define GO_COMMAND		0x09

//PDO response
typedef enum
{
	noResponse,
	Success,
	invalidCommand=3,
	unsupportedCmd,
	transactionFail
}pd_response_t;

//enum for reading source Voltage
typedef enum
{
	unAttached,
	PD5V,
	PD9V,
	PD12V,
	PD15V,
	PD18V,
	PD20V
}pd_src_volt_t;

////enum for reading source current
typedef enum
{
	PD050A,
	PD070A,
	PD100A,
	PD125A,
	PD150A,
	PD175A,
	PD200A,
	PD225A,
	PD250A,
	PD275A,
	PD300A,
	PD325A,
	PD350A,
	PD400A,
	PD450A,
	PD500A
}pd_src_curr_t;
//enum for source voltage select
typedef enum
{
	notSelected,
	sourcePDO5v,
	sourcePDO9v,
	sourcePDO12v,
	sourcePDO15v=8,
	sourcePDO18v,
	sourcePDO20v,
}pd_src_set_volt_t;

/*enum for command function */
typedef enum
{
	setPDOSelect=1,
	getSRCCap = 4,
	hardReset = 16,
}command_func_t;


// structure for PD_STATUS0 reg
typedef struct
{
	uint8_t sourceCurr : 4;
	uint8_t sourceVolt : 4;

}pd_status0_t;


//structure for PD_STATUS1 reg
typedef struct
{
	uint8_t curr5V : 2;
	uint8_t volt5V : 1;
	uint8_t pdResponse : 3;
	uint8_t attach : 1;
	uint8_t cc_dir : 1;
}pd_status1_t;


// structure for SRC_PDO_5V
typedef struct
{
	uint8_t src5VCurrent : 4;
	uint8_t unused : 3;
	uint8_t src5VDetect : 1;
}src_pdo_5V_t;

// structure for SRC_PDO_9V
typedef struct
{
	uint8_t src9VCurrent : 4;
	uint8_t unused : 3;
	uint8_t src9VDetect : 1;
}src_pdo_9V_t;

// structure for SRC_PDO_12V
typedef struct
{
	uint8_t src12VCurrent : 4;
	uint8_t unused : 3;
	uint8_t src12VDetect : 1;
}src_pdo_12V_t;


// structure for SRC_PDO_15V
typedef struct
{
	uint8_t src15VCurrent : 4;
	uint8_t unused : 3;
	uint8_t src15VDetect : 1;
}src_pdo_15V_t;


// structure for SRC_PDO_18V
typedef struct
{
	uint8_t src18VCurrent : 4;
	uint8_t unused : 3;
	uint8_t src18VDetect : 1;
}src_pdo_18V_t;


// structure for SRC_PDO_20V
typedef struct
{
	uint8_t src20VCurrent : 4;
	uint8_t unused : 3;
	uint8_t src20VDetect : 1;
}src_pdo_20V_t;


// struct for SRC_PDO
typedef struct
{
	uint8_t unused : 4;
	uint8_t selectPDO : 4;
}src_pdo_t;

//struct for GO_COMMAND
typedef struct
{
	uint8_t commandFunction : 5;
	uint8_t unused : 3;
}go_command_t;

/*@brief
 * This function checks the PD source delivered voltage and current.
 * @param deviceAddress : 7-bit I2C slave address
 * @param voltage : pointer to buffer to store voltage setting
 * @param current : pointer to buffer to store current setting
 * return : PD_OK : Read source voltage and current successful
 * 			ERR_NOACK : No ACK from I2C Slave device
 * 			ERR_I2CBUSY : I2C is busy
 */
uint8_t ReadPDSourceVandI(uint8_t deviceAddress, uint8_t *voltage, uint8_t *current);

/*@brief
 * This function checks the PD source adapter if attached to USB PD board.
 * @param deviceAddress : 7-bit I2C slave address
 * @param attachStatus : pointer to buffer to store attached status of PD source(adapter charger)
 * return : PD_OK : Read source attach status successful
 * 			ERR_NOACK : No ACK from I2C Slave device
 * 			ERR_I2CBUSY : I2C is busy
 */
uint8_t CheckPDAttachStatus(uint8_t deviceAddress, uint8_t *attachStatus);

/*@brief
 * This function reads the PD source adapter's response to USB PD board's request
 * @param deviceAddress : 7-bit I2C slave address
 * @param pdResponse : pointer to a buffer, to store response  of PD source(adapter charger)
 * return : PD_OK : Read PD source response  successful
 * 			ERR_NOACK : No ACK from I2C Slave device
 * 			ERR_I2CBUSY : I2C is busy
 */
static uint8_t CheckPDResponse(uint8_t deviceAddress, uint32_t *pdResponse);

/*@brief
 * This function selects the PD source adapter's voltage to USB PD board's request
 * @param deviceAddress : 7-bit I2C slave address
 * @param sourceVolt :  voltage value
 * return : PD_OK : selected  PD source voltage  successful
 * 			ERR_NOACK : No ACK from I2C Slave device
 * 			ERR_I2CBUSY : I2C is busy
 */
uint8_t SelectPDSourceVoltage(uint8_t deviceAddress, uint8_t sourceVolt);

/*@brief
 * This function reads the PD source adapter's response to USB PD board's request
 * @param deviceAddress : 7-bit I2C slave address
 * return : PD_OK : request sent to pd source  successfully
 * 			ERR_NOACK : No ACK from I2C Slave device
 * 			ERR_I2CBUSY : I2C is busy
 * 			PD_ERROR    : Transaction failed
 */
static uint8_t RequestPDO(uint8_t deviceAddress);

/*@brief
 * This function requests hardware reset for PD source adapter
 * @param deviceAddress : 7-bit I2C slave address
 * return : PD_OK : request sent to pd source  successfully
 * 			ERR_NOACK : No ACK from I2C Slave device
 * 			ERR_I2CBUSY : I2C is busy
 * 			PD_ERROR    : Transaction failed
 */
uint8_t RequestHardwareReset(uint8_t deviceAddress);

/*@brief
 * This function requests to get Source capabilities of PD source adapter
 * @param deviceAddress : 7-bit I2C slave address
 * return : PD_OK : request sent to pd source  successfully
 * 			ERR_NOACK : No ACK from I2C Slave device
 * 			ERR_I2CBUSY : I2C is busy
 * 			PD_ERROR    : Transaction failed
 */
uint8_t GetSourceCapabilities(uint8_t deviceAddress);

#endif /* USB_PDO_H_ */
