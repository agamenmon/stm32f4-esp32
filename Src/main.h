#ifndef __main_H
#define __main_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "fatfs.h"
#include "lcd.h"
#include "i2c.h"
#include "RTC.h"

I2C_HandleTypeDef hi2c1;
SD_HandleTypeDef hsd;
HAL_SD_CardInfoTypedef SDCardInfo;
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart2;

FATFS SDFatFs;
FIL MyFile;
FIL file_tam;
extern char SD_Path[4]; 

//UART_1
#define MAX_STRLEN 19
char buff_rx[MAX_STRLEN];
char buff_tx[MAX_STRLEN];
char str_uart[MAX_STRLEN]={0};

//Sensor
char buff_light[5];
char buff_temp1[2];
char buff_temp2[2];
char buff_humi1[3];
char buff_humi2[3];

//RTC
uint8_t aTxBuffer[8];
//uint8_t aRxBuffer[8];
uint8_t sec=0,min=0,hour=0,day=0,date=0,month=0,year=0;
extern signed char Gio1,Phut1,Gio2,Phut2;
extern signed char Gio3,Phut3,Gio4,Phut4;
extern signed char Gio5,Phut5,Gio6,Phut6;
extern signed char Gio7,Phut7,Gio8,Phut8;
//SD_Card
FRESULT res;
//uint8_t x=100;
uint32_t byteswritten,bytesread;
uint8_t wtext[]="Nha";
uint8_t rtext[100]={0};

//che do auto/manual
//uint8_t cnt=0,cnt1=0,cnt2=0;
uint8_t cnt_timer=0;
uint8_t cnt_timer1=0;
//che do u to
uint8_t T1_max=37,T1_min=33,T1_dat=35;
uint8_t H1_max=83,H1_min=77,H1_dat=80;
uint8_t L1_max=50,L1_min=20;

//che do qua the
uint8_t T2_max=32,T2_min=28,T2_dat=30;
uint8_t H2_max=87,H2_min=93,H2_dat=90;
uint8_t L2_max=50,L2_min=20;


uint8_t L,T1,H1,T2,H2;
char set_L1[20],set_L2[20];

extern uint8_t mode;
extern uint8_t cnt1;
extern uint8_t cnt2;
extern uint8_t cnt3;
extern uint8_t cnt4;
extern uint8_t cnt5;
extern uint8_t cnt6;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_SDIO_SD_Init(void);
static void MX_TIM2_Init(void);
void Error_Handler(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void strToUint(void);
void LCD_DK_TaiCho(void);
void LCD_TuDong_QuaThe(void);
void LCD_TuDong_UTo(void);
void Read_SDCard(void);
void Write_SDCard(void);
void read_RTC(void);
/*-------------------------*/
void send_char_temperature(char *st);
void display_LCD(char * return_data, int buffer_uart, int point_start);
void display_st_LCD(char * st);
void display_sensor_LCD(char * st, int T_dat, int H_dat);
void display_pos_LCD(int posx, int posy);
void InitialSoftwareProgram();
void blink_question_mask(int posx, int posy);
void which_setting(void * funcion_call, int posx, int posy);
void mode_programing(int count);
void setting_time(void);
void setting_auto_uto(void);
void setting_auto_quathe(void);
void setting_auto_timming(void);
void setting_manual(void);
void reset_value(void);


#ifdef __cplusplus
}
#endif
#endif /*__main_H */
