#include "RTC.h"

uint8_t RTC_ConvertFromDec(uint8_t c)
{
	uint8_t ch = ((c>>4)*10+(0x0F&c));
	return ch;
}

uint8_t RTC_ConvertFromBinDec(uint8_t c)
{
	uint8_t ch = ((c/10)<<4)|(c%10);
	return ch;
}
