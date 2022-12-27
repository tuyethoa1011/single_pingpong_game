/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include <stdio.h>
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"
#include "stm32f429i_discovery_gyroscope.h"
#include "usbd_cdc_if.h"
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
TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */
float valxyz[3]; //gyroscope value 3 axis rotation value
uint8_t buffer[200]; //text buffer rotation
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */
void delay_1ms(void);
void delay(long int time); //delay ms
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM6_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
      BSP_LCD_Init();// khoi tao doi tuong man hinh LCD
      BSP_LCD_LayerDefaultInit(1,SDRAM_DEVICE_ADDR); //dat dia chi buffer o lop man dau tien vao SDRAM
      BSP_LCD_SelectLayer(1); //chon lop layer chung se ghi len
      BSP_LCD_DisplayOn(); //bat man hinh lCD len
      BSP_LCD_Clear(LCD_COLOR_DARKGREEN); //clear man hinh LCD truoc khi bat dau hien thi
      BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN); //dat cho mau vien bong mau den


      BSP_LCD_SetTextColor(LCD_COLOR_WHITE); //mau cua bong mau trang
      BSP_LCD_SetFont(&Font20); //set kich thuoc font cho viec hien thi text ra man hinh LCD
      BSP_LCD_GetFont();
  
      //khoi tao Gyroscope
      BSP_GYRO_Init();
      /* USER CODE END 2 */
       int count_score = 0; //khởi tạo biến tính điểm trò chơi
    	 char str[10]; //mang tam chua chuoi diem de chuyen doi int sang char
    	 uint8_t display_score[] = "Score:"; //chuỗi hiển thị điểm số đạt được ra màn hình LCD
       /* Infinite loop */
      /* USER CODE BEGIN WHILE */
      while (1)
      {
    	  /* USER CODE END WHILE */
    	  //----- BEGIN GIAO DIEN BAN DAU -----
    	  //o giao dien ban dau day la trang thai can bang cua bong
    	  //ve hinh tron
    	    BSP_LCD_DrawCircle(BSP_LCD_GetXSize() - 120, 160, 30);
    	    BSP_LCD_FillCircle(BSP_LCD_GetXSize() - 120, 160, 30);
    	  //Test KIT de xem no ve hinh tron nhu nao roi minh se set lai gia tri cho no hop ly
    	    sprintf(str,"%d",count_score);
    	  //hien thi diem dat duoc tren man hinh
    	  //noi ket chuoi
    	  //BSP_LCD_DisplayStringAtLine(1,display_score);
    	    BSP_LCD_DisplayStringAt(11,13,display_score,LEFT_MODE);
    	    BSP_LCD_DisplayStringAt(100,13,(uint8_t*)str,LEFT_MODE);

    	    memset(str,0,sizeof(str));

    	    count_score++;

        //----- END GIAO DIEN BAN DAU -----
    	  //lay truc goc toa do x y z cua Gyroscope
    	    BSP_GYRO_GetXYZ(valxyz);

        //--- BEGIN KIEM TRA TOC DO QUAY CUA GYRO --- 
    	  //hien thi truc quay qua USB COM UART - Test USB COM
    	  //hien thi truc quay x
    	     sprintf(buffer,"X rotation = %f; ",valxyz[0]);
    	     CDC_Transmit_HS(buffer, sizeof(buffer));
    	     HAL_Delay(50);
    	  //hien thi truc quay y
    	     sprintf(buffer,"Y rotation = %f; ",valxyz[1]);
    	     CDC_Transmit_HS(buffer, sizeof(buffer));
    	     HAL_Delay(50);
    	     sprintf(buffer,"Z rotation = %f\n",valxyz[2]);
    	     CDC_Transmit_HS(buffer, sizeof(buffer));
        //--- END KIEM TRA TOC DO QUAY CUA GYRO --- 
    	     HAL_Delay(1200);
                      
      }
    /*USER CODE END WHILE*/     	  
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
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 10000;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
//code ham delay su dung Timer tai day
//---- BEGIN DELAY FUNCTION TIMER ----
void delay_1ms(void)
{
 __HAL_TIM_SetCounter(&htim6, 0);
 while (__HAL_TIM_GetCounter(&htim6)<10);
}

void delay(long int time) //delay mss
{
 long int i = 0;
 for(i = 0; i < time; i++)
 {
   delay_1ms();
 }

}

//---- END DELAY FUNCTION TIMER ----

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
