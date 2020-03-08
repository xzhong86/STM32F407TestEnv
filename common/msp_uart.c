
//#define USE_HAL_DRIVER
//#include "stm32f4xx.h"

#include "init_gpio.h"
#include "msp_uart.h"

#include "stm32f4xx_hal.h"

UART_HandleTypeDef DAP_UartHandle;

void initDAP_USART()
{
  UART_HandleTypeDef *uart;
  uart = &DAP_UartHandle;
  uart->Instance          = USART1;
  uart->Init.BaudRate     = 9600;
  uart->Init.WordLength   = UART_WORDLENGTH_8B;
  uart->Init.StopBits     = UART_STOPBITS_1;
  uart->Init.Parity       = UART_PARITY_NONE;
  uart->Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  uart->Init.Mode         = UART_MODE_TX_RX;
  uart->Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(uart) != HAL_OK)
    Error_Handler();
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;

  if (huart->Instance != USART1)
    return;
  
  /* Enable GPIO TX/RX clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE() ;
  /* Enable USART2 clock */
  __HAL_RCC_USART1_CLK_ENABLE();
  
  /* UART TX GPIO pin configuration: A9, A10  */
  Init_GPIO_a6(A,  9, AF_PP, NOPULL, FAST, AF7_USART1);
  Init_GPIO_a6(A, 10, AF_PP, NOPULL, FAST, AF7_USART1);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  if (huart->Instance != USART1)
    return;

  __HAL_RCC_USART1_FORCE_RESET();
  __HAL_RCC_USART1_RELEASE_RESET();

  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(GPIOA, 9);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(GPIOA, 10);
}

