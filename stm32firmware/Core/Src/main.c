/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// maximum rows/cols/depths that the cube is anticipated to have
#define MAX_DIM 6

// number of corners on a cube
#define NUM_CORNERS 8

// actual cube dims
#define CUBE_ROWS 4
#define CUBE_COLS 4
#define CUBE_DEPTH 4

#define CORNER_PORT GPIOA
#define TRANSISTOR_PORT GPIOB

// PCA9685 stuff
#define PCA9685_ADDR 0xE0
#define ALL_LED_ON_L 0xFA
#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define LED1_ON_H 0x0A
#define LED1_OFF_H 0x0B

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */

/**
 * Pins A5-7 and B0 should be reserved for SPI (assuming that's what we're using to communicate between Pi and STM32).
 *
 * The transistors and corner LEDs will be controlled directly by the microcontroller, while
 * the other 32 LEDs will be controlled through the PCA9685.
 */

// Corner Pins (assume on port CORNER_PORT)
static const uint16_t cornerPinMap[NUM_CORNERS] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};

// Transistor Pins (assume on port TRANSISTOR_PORT)
static const uint16_t transistorPinMap[MAX_DIM] = {GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/**
 * TODO write function header comment explaining functionality here
 */
bool isCornerLED(uint8_t row, uint8_t col, uint8_t depth) {
  return (depth == 0 && row == 0 && col == 0) ||
         (depth == 0 && row == 0 && col == CUBE_COLS-1) ||
         (depth == 0 && row == CUBE_ROWS-1 && col == 0) ||
         (depth == 0 && row == CUBE_ROWS-1 && col == CUBE_COLS-1) ||
         (depth == CUBE_DEPTH-1 && row == 0 && col == 0) ||
         (depth == CUBE_DEPTH-1 && row == 0 && col == CUBE_COLS-1) ||
         (depth == CUBE_DEPTH-1 && row == CUBE_ROWS-1 && col == 0) ||
         (depth == CUBE_DEPTH-1 && row == CUBE_ROWS-1 && col == CUBE_COLS-1);
}

/**
 * TODO write function header comment explaining functionality here
 */
uint8_t cornerToDigit(uint8_t row, uint8_t col, uint8_t depth) {
  return ((row != 0) << 2) | ((col != 0) << 1) | (depth != 0);
}

/**
 * Given a 3D array representing the target state of the LED cube,
 * drive each LED to match that state.
 *
 * @param cubeState: The 3D array representing the next frame of the LED cube.
 */
void driveLEDs(uint8_t*** cubeState) {
  for (uint8_t depth = 0; depth < CUBE_DEPTH; depth++) {
    // turn the corresponding depth transistor on (pull it high)
    HAL_GPIO_WritePin(TRANSISTOR_PORT, transistorPinMap[depth], GPIO_PIN_SET);
    // write to each LED at that depth
    for (uint8_t row = 0; row < CUBE_ROWS; row++) {
      for (uint8_t col = 0; col < CUBE_COLS; col++) {
        // if it's a corner LED, write directly using GPIOs. otherwise, write to the corresponding pca9685 pin
        if (isCornerLED(row, col, depth)) {
          HAL_GPIO_WritePin(CORNER_PORT, cornerPinMap[cornerToDigit(row,col,depth)], cubeState[row][col][depth]);
        } else {
          // TODO: map to PCA9685 pins somehow (another pin map??) also could translate row * numRows + col
        }
      }
    }
    // turn off the depth transistor (pull it low)
    HAL_GPIO_WritePin(TRANSISTOR_PORT, transistorPinMap[depth], GPIO_PIN_RESET);
  }
}

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
  uint8_t buf[10];

  // write to mode register 1 (needed to turn off the PWM "sleep")
  buf[0] = 0x00;
  buf[1] = 0b00100001;
  HAL_I2C_Master_Transmit(&hi2c2, PCA9685_ADDR, buf, 2, HAL_MAX_DELAY);

//  HAL_Delay(1); // necessary before driving PWM pins (according to pca9685 datasheet)

//  buf[0] = 0x01;
//  buf[1] = 0b00001100;
//  HAL_I2C_Master_Transmit(&hi2c2, PCA9685_ADDR, buf, 2, HAL_MAX_DELAY);

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
  MX_I2C2_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */

  uint8_t ledID = 0;
  buf[0] = (ledID == 16) ? ALL_LED_ON_L : LED0_ON_L + (4 * ledID);
  buf[1] = 0;
  buf[2] = 0 >> 8; // on high byte
  buf[3] = 0;
  buf[4] = 0 >> 8; // off high byte
  HAL_I2C_Master_Transmit(&hi2c2, PCA9685_ADDR, buf, 5, HAL_MAX_DELAY);

  ledID = 1;
  buf[0] = (ledID == 16) ? ALL_LED_ON_L : LED0_ON_L + (4 * ledID);
  buf[1] = 0;
  buf[2] = 0; // on high byte
  buf[3] = 0;
  buf[4] = 0b00010000; // off high byte
  HAL_I2C_Master_Transmit(&hi2c2, PCA9685_ADDR, buf, 5, HAL_MAX_DELAY);


  ledID = 2;
  buf[0] = (ledID == 16) ? ALL_LED_ON_L : LED0_ON_L + (4 * ledID);
  buf[1] = 0;
  buf[2] = 0; // on high byte
  buf[3] = 0;
  buf[4] = 0b00010000; // off high byte
  HAL_I2C_Master_Transmit(&hi2c2, PCA9685_ADDR, buf, 5, HAL_MAX_DELAY);

  ledID = 3;
  buf[0] = (ledID == 16) ? ALL_LED_ON_L : LED0_ON_L + (4 * ledID);
  buf[1] = 0;
  buf[2] = 0 >> 8; // on high byte
  buf[3] = 700;
  buf[4] = 700 >> 8; // off high byte
  HAL_I2C_Master_Transmit(&hi2c2, PCA9685_ADDR, buf, 5, HAL_MAX_DELAY);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    HAL_Delay(500);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 400000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Test_LED_GPIO_Port, Test_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CORNER_LED_0_Pin|CORNER_LED_1_Pin|CORNER_LED_2_Pin|CORNER_LED_3_Pin
                          |CORNER_LED_4_Pin|CORNER_LED_5_Pin|CORNER_LED_6_Pin|CORNER_LED_7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TRANSISTOR_0_Pin|TRANSISTOR_1_Pin|TRANSISTOR_2_Pin|TRANSISTOR_3_Pin
                          |TRANSISTOR_4_Pin|TRANSISTOR_5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Test_LED_Pin */
  GPIO_InitStruct.Pin = Test_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Test_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CORNER_LED_0_Pin CORNER_LED_1_Pin CORNER_LED_2_Pin CORNER_LED_3_Pin
                           CORNER_LED_4_Pin CORNER_LED_5_Pin CORNER_LED_6_Pin CORNER_LED_7_Pin */
  GPIO_InitStruct.Pin = CORNER_LED_0_Pin|CORNER_LED_1_Pin|CORNER_LED_2_Pin|CORNER_LED_3_Pin
                          |CORNER_LED_4_Pin|CORNER_LED_5_Pin|CORNER_LED_6_Pin|CORNER_LED_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : TRANSISTOR_0_Pin TRANSISTOR_1_Pin TRANSISTOR_2_Pin TRANSISTOR_3_Pin
                           TRANSISTOR_4_Pin TRANSISTOR_5_Pin */
  GPIO_InitStruct.Pin = TRANSISTOR_0_Pin|TRANSISTOR_1_Pin|TRANSISTOR_2_Pin|TRANSISTOR_3_Pin
                          |TRANSISTOR_4_Pin|TRANSISTOR_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
