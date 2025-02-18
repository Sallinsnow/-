/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "ltdc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "ui.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int FLAG1 = 1;
int FLAG2 = 1;
int FLAG3 = 0;
int FLAG4 = 0;
int FLAG5 = 0;

uint16_t buffer[700];
uint16_t in0Array[350];
uint16_t in8Array[350];
extern lv_chart_series_t* ui_Chart1_series_1 ;
extern lv_chart_series_t* ui_Chart1_series_2 ;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t lcd_disp_buf[480*272]={0};

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	int oddIndex = 0;
	int evenIndex = 0;
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
	for (int i = 0; i < 700; i++) {
        if (i % 2 == 0) {
            in0Array[evenIndex] = buffer[i]*3300/4096;
            evenIndex++;
        } else {
            in8Array[oddIndex] = buffer[i]*3300/4096;
            oddIndex++;
        }
		}
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */if(FLAG3 == 1) FLAG3 = 0;
	if(FLAG3 == 0) {
	FLAG3 = 1;
	__HAL_TIM_SET_PRESCALER(&htim13, 21600-1);
	}if(FLAG3 == 1) FLAG3 = 0;
	if(FLAG3 == 0) {
	FLAG3 = 1;
	__HAL_TIM_SET_PRESCALER(&htim13, 21600-1);
	}

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_ADC3_Init();
  MX_LTDC_Init();
  MX_I2C3_Init();
  MX_TIM13_Init();
  /* USER CODE BEGIN 2 */
	HAL_ADC_Start_DMA(&hadc3, (uint32_t *)buffer, 700);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

		
  lv_init();
	lv_port_disp_init();
	ui_init();
	lv_port_indev_init();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
  while (1)
  {
    /* USER CODE END WHILE */
	
    /* USER CODE BEGIN 3 */
			if(FLAG3 == 1 || FLAG4==1 || FLAG5==1)
		{
		HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
		}
		HAL_Delay(1);
		lv_task_handler();
    
		uint16_t maxVal1 = in0Array[0];
		uint16_t minVal1 = in0Array[0];
		uint16_t VppCH1 = 0;
		uint16_t maxVal2 = in8Array[0];
		uint16_t minVal2 = in8Array[0];
		uint16_t VppCH2 = 0;
    for(int i=0; i<350; i++)
    {
        if(in0Array[i] > maxVal1)
        {
            maxVal1 = in0Array[i];
        }
        if(in0Array[i] < minVal1)
        {
            minVal1 = in0Array[i];
        }
    }
		VppCH1 =  maxVal1 - minVal1;
		
    
		for(int j=0; j<350; j++)
    {
        if(in8Array[j] > maxVal2)
        {
            maxVal2 = in8Array[j];
        }
        if(in8Array[j] < minVal2)
        {
            minVal2 = in8Array[j];
        }
    }
    VppCH2 = maxVal2 - minVal2;
		lv_label_set_text_fmt(ui_Label7,"%d",VppCH1);
		lv_label_set_text_fmt(ui_Label8,"%d",maxVal2);
		
		if(FLAG1 == 1)
		{
		  lv_chart_hide_series(ui_Chart1, ui_Chart1_series_1, 0);
			lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_1, (lv_coord_t*)  in0Array);
		}
		if(FLAG2 == 1)
		{
       lv_chart_hide_series(ui_Chart1, ui_Chart1_series_2, 0);
		   lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_2, (lv_coord_t*)  in8Array);
		}
		if(FLAG1 == 0)
		{
			lv_chart_hide_series(ui_Chart1, ui_Chart1_series_1, 1);
		}
		if(FLAG2 == 0)
		{
			lv_chart_hide_series(ui_Chart1, ui_Chart1_series_2, 1);
		}
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
