/**
  ******************************************************************************
  * @file    usbd_hid.h
  * @author  MCD Application Team
  * @brief   Header file for the usbd_hid_core.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

#ifndef __USB_HID_H
#define __USB_HID_H

#ifdef __cplusplus
 extern "C" {
#endif

#include  "usbd_ioreq.h"


typedef enum
{
  HID_IDLE = 0,
  HID_BUSY,
}
HID_StateTypeDef;


typedef struct
{
  uint32_t             Protocol;
  uint32_t             IdleState;
  uint32_t             AltSetting;
  HID_StateTypeDef     state;
}
USBD_HID_HandleTypeDef;


extern USBD_ClassTypeDef  USBD_HID;
#define USBD_HID_CLASS    &USBD_HID


uint8_t USBD_HID_SendReport (USBD_HandleTypeDef *pdev,
                                 uint8_t *report,
                                 uint16_t len);

uint32_t USBD_HID_GetPollingInterval (USBD_HandleTypeDef *pdev);


// copy form tmk_keyboard project, tmk_core/common/report.h
typedef struct {
    uint8_t buttons;
    int8_t x;
    int8_t y;
    int8_t v;
    int8_t h;
} __attribute__ ((packed)) report_mouse_t;

static inline uint8_t USBD_HID_SendMouseReport(USBD_HandleTypeDef *pdev, report_mouse_t *report)
{
  return USBD_HID_SendReport(pdev, (uint8_t*)report, sizeof(*report));
}


#define KEYBOARD_REPORT_KEYS  6
#define KEYBOARD_REPORT_SIZE  8
typedef union {
    uint8_t raw[KEYBOARD_REPORT_SIZE];
    struct {
        uint8_t mods;
        uint8_t reserved;
        uint8_t keys[KEYBOARD_REPORT_KEYS];
    };
} __attribute__ ((packed)) report_keyboard_t;
static inline uint8_t USBD_HID_SendKeyboardReport(USBD_HandleTypeDef *pdev, report_keyboard_t *report)
{
  return USBD_HID_SendReport(pdev, (uint8_t*)report, sizeof(*report));
}


#ifdef __cplusplus
}
#endif

#endif  /* __USB_HID_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
