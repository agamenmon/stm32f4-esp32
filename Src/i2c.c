#include "i2c.h"
//--------------------------------------
extern uint8_t aTxBuffer[8];
char str[100];

//--------------------------------------
void I2C_WriteBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf)
{
	while(HAL_I2C_Master_Transmit(&hi, (uint16_t) DEV_ADDR, (uint8_t*) &aTxBuffer, (uint16_t) sizebuf, (uint32_t)1000)!=HAL_OK)
	{
			if(HAL_I2C_GetError(&hi)!=HAL_I2C_ERROR_AF)
			{
				sprintf(str,"Buffer error");
				LCD_SetPos(0, 3);
				LCD_String(str);
			}
	}
}
//--------------------------------------
void I2C_ReadBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t sizebuf)
{
	while(HAL_I2C_Master_Receive(&hi, (uint16_t) DEV_ADDR, (uint8_t*) &aTxBuffer, (uint16_t) sizebuf, (uint32_t)1000)!=HAL_OK)
	{
			if(HAL_I2C_GetError(&hi)!=HAL_I2C_ERROR_AF)
			{
				sprintf(str,"Buffer error");
				LCD_SetPos(0, 3);
				LCD_String(str);
			}
	}
}
