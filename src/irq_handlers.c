
#include "stm32f4xx_hal.h"

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

#define DeadLoop()  do { } while (1)

void NMI_Handler(void) { }

void HardFault_Handler(void)    { DeadLoop(); }
void MemManage_Handler(void)    { DeadLoop(); }
void BusFault_Handler(void)     { DeadLoop(); }
void UsageFault_Handler(void)   { DeadLoop(); }

void SVC_Handler(void)
{ }

void DebugMon_Handler(void)
{ }

void PendSV_Handler(void)
{ }

void SysTick_Handler(void)
{
  HAL_IncTick();
}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/******************************************************************************/

//extern HCD_HandleTypeDef hhcd;
// 
//void OTG_FS_IRQHandler(void)
//{
//  HAL_HCD_IRQHandler(&hhcd);
//}
