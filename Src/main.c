#include "main.h"

void read_RTC()
{
	aTxBuffer[0]=0;
	I2C_WriteBuffer(hi2c1,(uint16_t)0xD0,1);

	while(HAL_I2C_GetState(&hi2c1)!=HAL_I2C_STATE_READY);

	I2C_ReadBuffer(hi2c1,(uint16_t)0xD0,7);
	date = aTxBuffer[4];
	date = RTC_ConvertFromDec(date);
	month = aTxBuffer[5];
	month = RTC_ConvertFromDec(month);

	year = aTxBuffer[6];
	year = RTC_ConvertFromDec(year);

	day = aTxBuffer[3];
	day = RTC_ConvertFromDec(day);

	hour = aTxBuffer[2];
	hour = RTC_ConvertFromDec(hour);

	min = aTxBuffer[1];
	min = RTC_ConvertFromDec(min);

	sec = aTxBuffer[0];
	sec = RTC_ConvertFromDec(sec);
}
void Set_Time_Bom()
{
	char timedat[20];
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String("CAI DAT THOI GIAN");
	LCD_SetPos(1,1);
	LCD_String("Bom:");
	LCD_SetPos(6,1);
	sprintf(timedat,"%02d:%02d_%02d:%02d",Gio1,Phut1,Gio2,Phut2);
	LCD_String(timedat);
	HAL_Delay(500);
}
void Set_Time_Quat()
{
	char timedat[20];
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String("CAI DAT THOI GIAN");
	LCD_SetPos(0,1);
	LCD_String("Quat:");
	LCD_SetPos(6,1);
	sprintf(timedat,"%02d:%02d_%02d:%02d",Gio3,Phut3,Gio4,Phut4);
	LCD_String(timedat);
	HAL_Delay(500);
}
void Set_Time_Den()
{
	char timedat[20];
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String("CAI DAT THOI GIAN");
	LCD_SetPos(1,1);
	LCD_String("Den:");
	LCD_SetPos(6,1);
	sprintf(timedat,"%02d:%02d_%02d:%02d",Gio5,Phut5,Gio6,Phut6);
	LCD_String(timedat);
	HAL_Delay(500);
}
void Set_Time_Say()
{
	char timedat[20];
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String("CAI DAT THOI GIAN");
	LCD_SetPos(1,1);
	LCD_String("Say:");
	LCD_SetPos(6,1);
	sprintf(timedat,"%02d:%02d_%02d:%02d",Gio7,Phut7,Gio8,Phut8);
	LCD_String(timedat);
	HAL_Delay(500);
}
void LCD_Auto_Time()
{
	char timeBOM[20];
	char timeQUAT[20];
	char timeDEN[20];
	char timeSAY[20];
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String("AUTO ");
	LCD_String("Bom ");
	sprintf(timeBOM,"%02d:%02d_%02d:%02d",Gio1,Phut1,Gio2,Phut2);
	LCD_String(timeBOM);
	
	LCD_SetPos(3,1);
	LCD_String("Quat: ");
	sprintf(timeQUAT,"%02d:%02d_%02d:%02d",Gio3,Phut3,Gio4,Phut4);
	LCD_String(timeQUAT);

	LCD_SetPos(4,2);
	LCD_String("Den: ");
	sprintf(timeDEN,"%02d:%02d_%02d:%02d",Gio5,Phut5,Gio6,Phut6);
	LCD_String(timeDEN);
	
	LCD_SetPos(4,3);
	LCD_String("Say: ");
	sprintf(timeSAY,"%02d:%02d_%02d:%02d",Gio7,Phut7,Gio8,Phut8);
	LCD_String(timeSAY);

	HAL_Delay(500);
}
void Write_SDCard()
{
	if(f_mount(&SDFatFs,(TCHAR const*)SD_Path,0)!=FR_OK)
		Error_Handler();
	else
	{
		if(f_open(&MyFile,"Mytext.txt",FA_CREATE_ALWAYS|FA_WRITE)!=FR_OK)
			Error_Handler();
		else
		{
			res=f_lseek(&MyFile,f_tell(&MyFile)+f_size(&MyFile));
			res=f_write(&MyFile,wtext,sizeof(wtext),(void*)&byteswritten);
			f_close(&MyFile);
		}

	}		
}
void Read_SDCard()
{
	if(f_mount(&SDFatFs,(TCHAR const*)SD_Path,0)!=FR_OK)
		Error_Handler();
	else
	{
		if(f_open(&MyFile,"mywrite.txt",FA_READ)!=FR_OK)
			Error_Handler();
		else
		{
			res=f_read(&MyFile,rtext,sizeof(rtext),(void*)&bytesread);
			if((bytesread==0)||(res!=FR_OK))
				Error_Handler();
			else
			{
				LCD_Clear();
				LCD_SetPos(0,3);
				rtext[bytesread]=0;
				LCD_String((char*)rtext);
			}
			f_close(&MyFile);
		}
	}
}
void pos_str_LCD(int posx, int posy, char * st)
{
	LCD_SetPos(posx, posy);
	LCD_String(st);
}
void display_LCD(char * return_data, int buffer_uart, int point_start)
{
	int i = 0;
	for(i = 0; i < buffer_uart; i++)
	{
		return_data[i] = str_uart[i + point_start];
		LCD_SendChar(return_data[i]);
	}
}
void send_char_temperature(char *st)
{
	LCD_SendChar(223);
	LCD_String(st);
}
void display_st_LCD(char * st)
{
	LCD_String(st);
}
void display_pos_LCD(int posx, int posy)
{
	LCD_SetPos(posx, posy);
}
void display_sensor_LCD(char * st, int T_dat, int H_dat)
{
	char dat_t[20],dat_h[20];
	LCD_Clear();
	pos_str_LCD(1,0,st);
	pos_str_LCD(0,1,"ND: ");
	display_LCD(buff_temp1, 2,6);
	LCD_String(";");
	display_LCD(buff_temp2, 2, 13);
	send_char_temperature("C");

	sprintf(dat_t,"%d",T_dat);
	pos_str_LCD(15,1,dat_t);

	send_char_temperature("C");

	pos_str_LCD(0,2,"AM: ");
	display_LCD(buff_humi1, 3,9);
	display_st_LCD(";");
	display_LCD(buff_humi2, 3, 16);
	display_st_LCD("%");
	sprintf(dat_h,"%d",H_dat);
	pos_str_LCD(15,2,dat_h);
	display_st_LCD("%");

	pos_str_LCD(0,3,"AS: ");
	display_LCD(buff_light, 5, 0);
	LCD_String(" lux");
	HAL_Delay(500);
}
void LCD_DK_TaiCho()
{
	LCD_Clear();
	pos_str_LCD(0,0, "MANUAL");
	 //anh sang
	pos_str_LCD(8, 0, "AS:");
	display_LCD(buff_light, 5, 0);
	display_st_LCD(" lux");

	//Nhiet do
	display_pos_LCD(2,1);
	display_LCD(buff_temp1, 2, 6);
	display_st_LCD("_");
	display_LCD(buff_temp2, 2, 13);
	send_char_temperature("C");
	 //do am
	display_pos_LCD(11,1);
	display_LCD(buff_humi1, 3, 9);
	display_st_LCD("_");

	display_LCD(buff_humi2, 3, 16);
	display_st_LCD("%");
	pos_str_LCD(0, 2, "1:Quat hut");
	pos_str_LCD(13, 2, "2:Den");
	pos_str_LCD(0,3,"3:Phun Suong");
	pos_str_LCD(13, 3, "4:Say"); 
	HAL_Delay(500);
}

//string to uint
void strToUint()
{
//	  UART_Receive();
	L=(str_uart[0]-48)*10000+(str_uart[1]-48)*1000+(str_uart[2]-48)*100+(str_uart[3]-48)*10+(str_uart[4]-48);
	T1=(str_uart[6]-48)*10+(str_uart[7]-48);
	H1=(str_uart[9]-48)*100+(str_uart[10]-48)*10+(str_uart[11]-48);
	T2=(str_uart[13]-48)*10+(str_uart[14]-48);
	H2=(str_uart[16]-48)*100+(str_uart[17]-48)*10+(str_uart[18]-48);
}
void InitialSoftwareProgram()
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_I2C1_Init();
	MX_SDIO_SD_Init();
	MX_FATFS_Init();
	MX_TIM2_Init();
	
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_TC);
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
	HAL_TIM_Base_Start_IT(&htim2);
	//Write_SDCard();
	LCD_ini();
	LCD_Clear();
}
void blink_question_mask(int posx, int posy)
{
	LCD_SetPos(posx,posy);
	LCD_String("?");
	HAL_Delay(300);
}
void which_setting(void * funcion_call, int posx, int posy)
{
	void (*call_a_funcion_running)(void) = NULL;
	call_a_funcion_running = funcion_call;
	call_a_funcion_running();
	blink_question_mask(posx, posy);
}

void setting_time(void)
{
	switch(cnt5)
	{
		case 0:
			LCD_Clear();
			pos_str_LCD(0,0, "Setting TIME");
			HAL_Delay(500);
			break;
		case 1:
			which_setting(Set_Time_Bom,6,2);
			break;
		case 2:
			which_setting(Set_Time_Bom,9,2);
			break;
		case 3:
			which_setting(Set_Time_Bom,12,2);
			break;
		case 4:
			which_setting(Set_Time_Bom,15,2);
			break;
		case 5:
			which_setting(Set_Time_Quat,6,2);
			break;
		case 6:
			which_setting(Set_Time_Quat,9,2);
			break;
		case 7:
			which_setting(Set_Time_Quat,12,2);
			break;
		case 8:
			which_setting(Set_Time_Quat,15,2);
			break;
		case 9:
			which_setting(Set_Time_Den,6,2);
			break;
		case 10:
			which_setting(Set_Time_Den,9,2);
			break;
		case 11:
			which_setting(Set_Time_Den,12,2);
			break;
		case 12:
			which_setting(Set_Time_Den,15,2);
			break;
		case 13:
			which_setting(Set_Time_Say,6,2);
			break;
		case 14:
			which_setting(Set_Time_Say,9,2);
			break;
		case 15:
			which_setting(Set_Time_Say,12,2);
			break;
		case 16:
			which_setting(Set_Time_Say,15,2);
			break;

		default: break;
	}
}
void setting_auto_uto(void)
{
	HAL_UART_Receive_IT(&huart2,(uint8_t *)str_uart,MAX_STRLEN);
	display_sensor_LCD("ABUTO: G/D U TO", T1_dat, H1_dat);
	strToUint();
      //write_SD();
      //HAL_TIM_PeriodElapsedCallback(&htim2);					       
      //anh sang
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);  //tat den
	if(T1>=T1_max || T2>=T1_max)
	    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET);  //bat quat hut
	else if(T1==T1_dat || T2==T1_dat || T1>100 || T2>100)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET);  //tat quat hut	
	//nhiet do thap
	if(T1<=T1_min || T2<=T1_min)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET); //bat may say	
	else if(T1==T1_dat || T2==T1_dat || T2>100 || T1>100)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_RESET); //tat may say
	 //do am cao
	if(H1>=H1_max || H2>=H1_max)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET);  //bat quat hut	
	else if(H1==H1_dat || H2==H1_dat || H1>100 || H2>100)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET);  //tat quat hut
	//do am thap
	if(H1<=H1_min || H2<=H1_min)
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);  //bat phun suong
	else if(H1==H1_dat || H2==H1_dat || H1>100 || H2>100)
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);  //tat phun suong
}
void setting_auto_quathe(void)
{
	HAL_UART_Receive_IT(&huart2,(uint8_t *)str_uart,MAX_STRLEN);
	display_sensor_LCD("AUTO: G/D QUA THE", T2_dat, H2_dat);
	strToUint();
	//write_SD();
	//HAL_TIM_PeriodElapsedCallback(&htim2);
	if(T1>=T2_max || T2>=T2_max)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET);  //bat quat hut
	else if(T1==T2_dat || T2==T2_dat || T1>100 || T2>100)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET);  //tat quat hut
	//nhiet do thap
    if(T1<=T2_min || T2<=T2_min)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET); //bat may say	
	else if(T1==T2_dat || T2==T2_dat || T2>100 || T1>100)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_RESET); //tat may say
	//do am cao
	if(H1>=H2_max || H2>=H2_max)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET);  //bat quat hut
	else if(H1==H2_dat || H2==H2_dat || H1>100 || H2>100)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET);  //tat quat hut
	//do am thap
	if(H1<=H2_min || H2<=H2_min)
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);  //bat phun suong
	else if(H1==H2_dat || H2==H2_dat || H1>100 || H2>100)
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);  //tat phun suong
	//anh sang thap
	if(L<=L2_min)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_SET);  //bat den
       else
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);  //tat den
}
void setting_auto_timming(void)
{
	LCD_Auto_Time();
}
void setting_manual(void)
{
	HAL_UART_Receive_IT(&huart2,(uint8_t *)str_uart,MAX_STRLEN);
	LCD_DK_TaiCho();
	//write_SD();
	//HAL_TIM_PeriodElapsedCallback(&htim2);
  if(cnt1==1)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET);  //bat quat hut
	else
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET);  //tat quat hut
	if(cnt2==1)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_SET);  //bat den
	else
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);  //tat den
	if(cnt3==1)
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);  //bat phun suong
	else
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);  //tat phun suong	
	if(cnt4==1)
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET); //bat may say	
	else
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_RESET); //tat may say	
}
void introduce(void)
{
	HAL_UART_Receive_IT(&huart2,(uint8_t *)str_uart,MAX_STRLEN);
	LCD_Clear();
	//pos_str_LCD(0,0, "MENU");
	//pos_str_LCD(0,1, "1:Che Do");
	//pos_str_LCD(0,2, "2:Cai Dat Thoi Gian");
	pos_str_LCD(8,1, "HELLO");
	pos_str_LCD(0,2, "Continue --> Press");
	HAL_Delay(400);
}
void reset_value(void)
{
	cnt1 = 0;
	cnt2 = 0;
	cnt3 = 0;
	cnt4 = 0;
	cnt5 = 0;
}
void mode_programing(int count)
{

	switch(count)
	{
		case 0:
			introduce();
			reset_value();
			break;
		case 1:
			setting_time();
			break;
		case 2:
			setting_auto_uto();
			break;
		case 3:
			setting_auto_quathe();
			break;
		case 4:
			setting_auto_timming();
			break;
		case 5:
			setting_manual();
			break;
		default: break;
	}
}
int main(void)
{
	InitialSoftwareProgram();
	mode=0;
	cnt1=0;
	//Write_SDCard();
	while (1)
	{
		mode_programing(mode);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if(htim->Instance==htim2.Instance)
	{

		cnt_timer++;
		cnt_timer1++;
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==huart2.Instance)
	{

		HAL_UART_Receive_IT(&huart2,(uint8_t *)str_uart,MAX_STRLEN);
		HAL_UART_Transmit_IT(&huart2,(uint8_t *)str_uart,MAX_STRLEN);			  
	}
}
void SystemClock_Config(void)
{

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	__HAL_RCC_PWR_CLK_ENABLE();

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C1 init function */
void MX_I2C1_Init(void)
{

	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}

}

/* SDIO init function */
void MX_SDIO_SD_Init(void)
{

	hsd.Instance = SDIO;
	hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
	hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
	hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
	hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
	hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
	hsd.Init.ClockDiv = 0;

}

/* TIM2 init function */
void MX_TIM2_Init(void)
{

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 42000;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 119999;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_Base_Init(&htim2);

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

}

/* USART2 init function */
void MX_USART2_UART_Init(void)
{

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart2);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

/*Configure GPIO pins : PA4 PA5 PA6 PA7 */
	GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/*Configure GPIO pin : PB0 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/*Configure GPIO pins : PE7 PE8 PE9 PE10 */
	GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

/*Configure GPIO pin : PD12 */
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin */
	GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/*Configure GPIO pins : RS_Pin EN_Pin */
	GPIO_InitStruct.Pin = RS_Pin|EN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|D4_Pin|D5_Pin|D6_Pin 
		|D7_Pin, GPIO_PIN_RESET);

/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, RS_Pin|EN_Pin, GPIO_PIN_RESET);

/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

void Error_Handler(void)
{
/* USER CODE BEGIN Error_Handler */
/* User can add his own implementation to report the HAL error return state */
	while(1) 
	{
	}
/* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
/* USER CODE BEGIN 6 */
/* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
/* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
