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


#define HID_EPIN_ADDR                 0x81U
#define HID_EPIN_SIZE                 0x04U

#define USB_HID_CONFIG_DESC_SIZ       34U
#define USB_HID_DESC_SIZ              9U
//#define HID_MOUSE_REPORT_DESC_SIZE    74U
//#define HID_MOUSE_REPORT_DESC_SIZE    62U

#define HID_DESCRIPTOR_TYPE           0x21U
#define HID_REPORT_DESC               0x22U

#ifndef HID_HS_BINTERVAL
  #define HID_HS_BINTERVAL            0x07U
#endif /* HID_HS_BINTERVAL */

#ifndef HID_FS_BINTERVAL
  #define HID_FS_BINTERVAL            0x0AU
#endif /* HID_FS_BINTERVAL */

#define HID_REQ_SET_PROTOCOL          0x0BU
#define HID_REQ_GET_PROTOCOL          0x03U

#define HID_REQ_SET_IDLE              0x0AU
#define HID_REQ_GET_IDLE              0x02U

#define HID_REQ_SET_REPORT            0x09U
#define HID_REQ_GET_REPORT            0x01U

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


#ifdef __cplusplus
}
#endif

#endif  /* __USB_HID_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
