/*
 * i2c_common.h
 *
 *  Created on: 08-Aug-2024
 *      Author: gurun
 */

#ifndef I2C_COMMON_H_
#define I2C_COMMON_H_

#define MCXA153

#if defined(MCXA153)

#include "fsl_lpi2c.h"	// LPI2C driver header file for MCXA153
#include "fsl_clock.h"	// CLock peripheral functions header of MCXA153
#define I2C_INSTANCE 				LPI2C0
#define LPI2C_BAUDRATE               100000U
#define I2C_DEVICE_ADDR_7BIT   	   	0x08U
#define I2C_REGISTER_LENGTH			1
#define I2C_CLOCK_FREQUENCY			CLOCK_GetLpi2cClkFreq()

#endif


#if defined(MCXA153)

#define I2C_Send(instance, buffer, length)			LPI2C_MasterSend(instance, buffer, length)
#define I2C_Receive(instance, rxBuffer, length) 	LPI2C_MasterReceive(instance, rxBuffer, length)
#define Delay_Ms(time)								SystickSetDelay(time)


#define ERR_NOACK 		kStatus_LPI2C_Nak
#define ERR_I2CBUSY 	kStatus_LPI2C_Busy
#define SUCCESS 		kStatus_Success

#endif

/*@brief
 * This function writes value to an I2C register.
 * @param deviceAddress : 7-bit I2C slave address
 * @param dataBuffer : pointer to data  buffer that is to be written to register(s)
 * @param bufLength : length of data buffer
 * @return : SUCCESS : Write is successful
 * 			ERR_I2CBUSY : I2C bus is busy
 * 			ERR_NOACK  :  No ACK from Slave */
uint32_t I2CWrite(uint8_t deviceAddress, uint8_t *dataBuffer, size_t bufLength);


/*@brief
 * This function reads value from an I2C register.
 * @param deviceAddress : 7-bit I2C slave address
 * @param dataBuffer : pointer to data  buffer that stores data read from register(s)
 * @param readLength : length of data to receive
 * @return : SUCCESS : Read is successful
 * 			ERR_I2CBUSY : I2C bus is busy
 * 			ERR_NOACK  :  No ACK from Slave */
uint32_t  I2CRead(uint8_t deviceAddress,uint8_t *dataBuffer, size_t readLength);

/*@brief
 * This function initializes an I2C instance.
 * @param baudRate : baudrate value for I2C peripheral
 * @return : None */
void I2CInit(uint32_t baudRate);

#endif /* I2C_COMMON_H_ */
