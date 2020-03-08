
#include "board_bsp.h"

#include "stm32f4xx_hal.h"

#define LED2_PIN                         GPIO_PIN_13
#define LED2_GPIO_PORT                   GPIOC
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()  
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()  

void initBSP_LED()
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /* -1- Enable GPIO Clock (to be able to program the configuration registers) */
  LED2_GPIO_CLK_ENABLE();

  /* -2- Configure IO in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Pin = LED2_PIN;
  HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
}

void bsp_led_set(int on, int toggle)
{
  if (toggle)
    HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
  else if (on)
    HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_RESET);
}

#define true 1
#define false 0

void BSP_Error_Handler(void)
{
  while (1) {
    bsp_led_set(true,  false);  HAL_Delay(100);
    bsp_led_set(false, false);  HAL_Delay(100);
    bsp_led_set(true,  false);  HAL_Delay(100);
    bsp_led_set(false, false);  HAL_Delay(100);
    HAL_Delay(600);
  }
}

__attribute__((weak)) void Error_Handler(void)
{
  BSP_Error_Handler();
}
