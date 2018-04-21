/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */
uint8_t mode = 0;
uint8_t cnt1=0,cnt2=0,cnt3=0,cnt4=0,cnt5=0,cnt6=0;
signed char Gio1=20,Phut1=00,Gio2=20,Phut2=00;
signed char Gio3=20,Phut3=00,Gio4=20,Phut4=00;
signed char Gio5=20,Phut5=00,Gio6=20,Phut6=00;
signed char Gio7=20,Phut7=00,Gio8=20,Phut8=00;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart2;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */

  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/
int press_button(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  int Rvalue = 1;
  int timming = 0;
  if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == 0)
  {
    while(1)
    {
      if(timming >= 0xff)
      {
        if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) != 0)
        {
          Rvalue = 0;
          break;
        }
      }
      timming++;
    }
  }
  return Rvalue;
}
/**
* @brief This function handles EXTI line0 interrupt.
*/
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */
  //if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==0)
  if(press_button(GPIOB, GPIO_PIN_0) == 0)
  {
    if(mode==5)
    {
      cnt4++;
      if(cnt4>1)
      {
        cnt4=0;
      } 
    }
    if(mode == 1)
    {
      switch(cnt5)
      {
      case 1:
        Gio1--;
        if(Gio1<00)
          Gio1=23;
          break;
        case 2:
          Phut1--;
          if(Phut1<00)
            Phut1=59;
          break;
        case 3:
          Gio2--;
          if(Gio2<00)
            Gio2=23;
          break;
        case 4:
          Phut2--;
          if(Phut2<00)
            Phut2=59;
          break;
        case 5:
          Gio3--;
          if(Gio3<00)
            Gio3=23;
          break;
        case 6:
          Phut3--;
          if(Phut3<00)
            Phut3=59;
          break;
        case 7:
          Gio4--;
          if(Gio4<00)
            Gio4=23;
          break;
        case 8:
          Phut4--;
          if(Phut4<00)
            Phut4=59;
          break;
        case 9:
          Gio5--;
          if(Gio5<00)
            Gio5=23;
          break;
        case 10:
          Phut5--;
          if(Phut5<00)
            Phut5=59;
          break;
        case 11:
          Gio6--;
          if(Gio6<00)
            Gio6=23;
          break;
        case 12:
          Phut6--;
          if(Phut6<00)
            Phut6=59;
          break;
        case 13:
          Gio7--;
          if(Gio7<00)
            Gio7=23;
          break;
        case 14:
          Phut7--;
          if(Phut7<00)
            Phut7=59;
          break;
        case 15:
          Gio8--;
          if(Gio8<00)
            Gio8=23;
          break;
        case 16:
          Phut8--;
          if(Phut8<00)
            Phut8=59;
          break;
        default: break;
      }
    }
    //else 
    //  cnt5 = 0;
  }
}

/**
* @brief This function handles EXTI line4 interrupt.
*/
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */
/*  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==0)
  {
			   //while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==0){};
			   //HAL_Delay(200);
   mode++;
   if(mode>4)
     mode=0;
			   //HAL_Delay(100);
  }
*/
  if(press_button(GPIOA, GPIO_PIN_4) == 0)
  {
    mode++;
    if(mode > 5)
      mode = 0;
  }
  /* USER CODE END EXTI4_IRQn 1 */
}

/**
* @brief This function handles EXTI line[9:5] interrupts.
*/
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  //if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)==0)
  if(press_button(GPIOA, GPIO_PIN_5) == 0)
  {
    if(mode == 1)
    {
      cnt5++;
      if(cnt5 > 16)
        cnt5 = 0;
    }
    //else cnt5 = 0;

    if(mode==5)
    {
      cnt1++;
      if(cnt1>1)
       cnt1=0;
   }
  }

  //if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0)
  if(press_button(GPIOA, GPIO_PIN_6) == 0)
  {
    if(mode==5)
    {
     cnt2++;
     if(cnt2>1)
       cnt2=0;
    }
  }

  //if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==0)
  if(press_button(GPIOA, GPIO_PIN_7) == 0)
  {
    if(mode==5)
    {
      cnt3++;
      if(cnt3>1)
      cnt3=0;
    }
    if(mode == 1)
    {
      switch(cnt5)
      {
      case 1:
        Gio1++;
        if(Gio1>23)
          Gio1=0;
        break;
      case 2:
        Phut1++;
        if(Phut1>59)
          Phut1=00;
        break;
      case 3:
        Gio2++;
        if(Gio2>23)
          Gio2=0;
        break;
      case 4:
        Phut2++;
        if(Phut2>59)
          Phut2=00;
        break;
      case 5:
        Gio3++;
        if(Gio3>23)
          Gio3=0;
        break;
      case 6:
        Phut3++;
        if(Phut3>59)
          Phut3=00;
        break;
      case 7:
        Gio4++;
        if(Gio4>23)
          Gio4=0;
        break;
      case 8:
        Phut4++;
        if(Phut4>59)
          Phut4=00;
        break;
      case 9:
        Gio5++;
        if(Gio5>23)
          Gio5=0;
        break;
      case 10:
        Phut5++;
        if(Phut5>59)
          Phut5=00;
        break;
      case 11:
        Gio6++;
        if(Gio6>23)
          Gio6=0;
        break;
      case 12:
       Phut6++;
        if(Phut6>59)
          Phut6=00;
        break;
      case 13:
        Gio7++;
        if(Gio7>23)
          Gio7=0;
        break;
      case 14:
        Phut7++;
        if(Phut7>59)
          Phut7=00;
        break;
      case 15:
        Gio8++;
        if(Gio8>23)
          Gio8=0;
        break;
      case 16:
        Phut8++;
        if(Phut8>59)
          Phut8=00;
        break;
      default: break;
      }
    }
    //else cnt5 = 0;
    
  }
}

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles I2C1 event interrupt.
*/
void I2C1_EV_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_EV_IRQn 0 */

  /* USER CODE END I2C1_EV_IRQn 0 */
  HAL_I2C_EV_IRQHandler(&hi2c1);
  /* USER CODE BEGIN I2C1_EV_IRQn 1 */

  /* USER CODE END I2C1_EV_IRQn 1 */
}

/**
* @brief This function handles I2C1 error interrupt.
*/
void I2C1_ER_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_ER_IRQn 0 */

  /* USER CODE END I2C1_ER_IRQn 0 */
  HAL_I2C_ER_IRQHandler(&hi2c1);
  /* USER CODE BEGIN I2C1_ER_IRQn 1 */

  /* USER CODE END I2C1_ER_IRQn 1 */
}

/**
* @brief This function handles USART2 global interrupt.
*/
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
