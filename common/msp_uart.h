
#pragma once

#include "stm32f4xx_hal.h"


extern UART_HandleTypeDef DAP_UartHandle;

void initDAP_USART();

extern void Error_Handler(void);

static inline void dap_putc(char ch) {
  if (HAL_UART_Transmit(&DAP_UartHandle, (uint8_t*)&ch, 1, 2000) != HAL_OK)
    Error_Handler();
}
static inline void dap_putc_r(char ch) {
  if (ch == '\n')
    dap_putc('\r');
  dap_putc(ch);
}
static inline void dap_puts(const char *str)
{
  for (const char *p = str; *p; ++p) {
    dap_putc_r(*p);
  }
}

static inline char dap_getc() {
  char buf[2];
  if (HAL_UART_Receive(&DAP_UartHandle, (uint8_t*)buf, 1, 2000) != HAL_OK)
    Error_Handler();
  return buf[0];
}
