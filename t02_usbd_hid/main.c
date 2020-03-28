
#include "main.h"
#include "msp_uart.h"
#include "board_bsp.h"
#include <stdio.h>


USBD_HandleTypeDef USBD_Device;
extern PCD_HandleTypeDef hpcd;

int __io_putchar(int ch) { dap_putc_r(ch); }

static void test_keyboard(report_keyboard_t *keybd) {
  if (keybd->keys[0]) keybd->keys[0] = 0;
  else                keybd->keys[0] = 0x10;
  //printf("send HID Keyboard report\n");
  USBD_HID_SendKeyboardReport(&USBD_Device, keybd);
}
static void test_mouse(report_mouse_t *mouse) {
  mouse->buttons = 0;
  mouse->x = 5;
  mouse->y = 5;
  //printf("send HID Mouse report\n");
  USBD_HID_SendMouseReport(&USBD_Device, mouse);
}

int main(void)
{
  uint8_t HID_Buffer[4];
  /* STM32F412xx HAL library initialization */
  HAL_Init();

  /* Configure the System clock to have a frequency of 100 MHz */
  SystemClock_Config();

  initBSP_LED();
  initDAP_USART(); 
  printf("finish uart init.\n");
 
  /* Init Device Library */
  USBD_Init(&USBD_Device, &HID_Desc, 0);
  printf("finish usbd init.\n");

  /* Add Supported Class */
  USBD_RegisterClass(&USBD_Device, USBD_HID_CLASS);

  /* Start Device Process */
  USBD_Start(&USBD_Device); 

  printf("finish init. go into loop.\n");

  report_keyboard_t keybd;
  memset(&keybd, 0, sizeof(keybd));
  report_mouse_t mouse;
  memset(&mouse, 0, sizeof(mouse));
  while (1)
  {
    HAL_Delay(100);

    //test_mouse(&mouse);
    test_keyboard(&keybd);

    /* Toggle LEDs */
    //BSP_LED_Toggle(LED1);
    HAL_Delay(800);
  }
}

void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);


  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
 
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }  
}


#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t * file, uint32_t line)
{
  while (1)
  {
  }
}
#endif

