#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx_hal.h"
#include "lcd.h"

void I2C_WriteBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf);
void I2C_ReadBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf);

#endif /* I2C_H_ */
