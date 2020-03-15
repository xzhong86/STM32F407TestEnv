
#include "usbd_hid.h"
#include "usbd_ctlreq.h"
#include "usbd_report.h"


#define HAS_KEYBOARD      1

#define HID_MOUSE_EPIN_ADDR           0x81U
#define HID_MOUSE_EPIN_SIZE           0x05U

#define HID_KEYBD_EPIN_ADDR           0x82U
#define HID_KEYBD_EPIN_SIZE           0x08U

#ifdef HAS_KEYBOARD
# define HID_INTF_NUM                  2
# define USB_HID_CONFIG_DESC_SIZ       59U
#else
# define HID_INTF_NUM                  1
# define USB_HID_CONFIG_DESC_SIZ       34U
#endif

#define USB_HID_DESC_SIZ              9U

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


// keyboard descrptor, from tmk_keyboard code, base on LUFA
__ALIGN_BEGIN static uint8_t HID_KEYBD_ReportDesc[]  __ALIGN_END =
{
    HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
    HID_RI_USAGE(8, 0x06), /* Keyboard */
    HID_RI_COLLECTION(8, 0x01), /* Application */
        HID_RI_USAGE_PAGE(8, 0x07), /* Key Codes */
        HID_RI_USAGE_MINIMUM(8, 0xE0), /* Keyboard Left Control */
        HID_RI_USAGE_MAXIMUM(8, 0xE7), /* Keyboard Right GUI */
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(8, 0x01),
        HID_RI_REPORT_COUNT(8, 0x08),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_CONSTANT),  /* reserved */

        HID_RI_USAGE_PAGE(8, 0x08), /* LEDs */
        HID_RI_USAGE_MINIMUM(8, 0x01), /* Num Lock */
        HID_RI_USAGE_MAXIMUM(8, 0x05), /* Kana */
        HID_RI_REPORT_COUNT(8, 0x05),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x03),
        HID_RI_OUTPUT(8, HID_IOF_CONSTANT),

        HID_RI_USAGE_PAGE(8, 0x07), /* Keyboard */
        HID_RI_USAGE_MINIMUM(8, 0x00),
        HID_RI_USAGE_MAXIMUM(8, 0xFF), /* Usage ID 0x00-0xFF */
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00FF), /* needs 16 bit to indicate positive value */
        HID_RI_REPORT_COUNT(8, 0x06),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_ARRAY | HID_IOF_ABSOLUTE),
    HID_RI_END_COLLECTION(0),
};
#define HID_KEYBD_REPORT_DESC_SIZE  sizeof(HID_KEYBD_ReportDesc)

// mouse descrptor, from tmk_keyboard code, base on LUFA
__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[]  __ALIGN_END =
 {
    HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
    HID_RI_USAGE(8, 0x02), /* Mouse */
    HID_RI_COLLECTION(8, 0x01), /* Application */
        HID_RI_USAGE(8, 0x01), /* Pointer */
        HID_RI_COLLECTION(8, 0x00), /* Physical */

            HID_RI_USAGE_PAGE(8, 0x09), /* Button */
            HID_RI_USAGE_MINIMUM(8, 0x01),  /* Button 1 */
            HID_RI_USAGE_MAXIMUM(8, 0x05),  /* Button 5 */
            HID_RI_LOGICAL_MINIMUM(8, 0x00),
            HID_RI_LOGICAL_MAXIMUM(8, 0x01),
            HID_RI_REPORT_COUNT(8, 0x05),
            HID_RI_REPORT_SIZE(8, 0x01),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x03),
            HID_RI_INPUT(8, HID_IOF_CONSTANT),

            HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
            HID_RI_USAGE(8, 0x30), /* Usage X */
            HID_RI_USAGE(8, 0x31), /* Usage Y */
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x02),
            HID_RI_REPORT_SIZE(8, 0x08),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

            HID_RI_USAGE(8, 0x38), /* Wheel */
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x08),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

            HID_RI_USAGE_PAGE(8, 0x0C), /* Consumer */
            HID_RI_USAGE(16, 0x0238), /* AC Pan (Horizontal wheel) */
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x08),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

        HID_RI_END_COLLECTION(0),
    HID_RI_END_COLLECTION(0),
};

#define HID_MOUSE_REPORT_DESC_SIZE  sizeof(HID_MOUSE_ReportDesc)


#if 0
/* USB HID device FS Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_CfgFSDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xE0,         /*bmAttributes: bus powered and Support Remote Wake-up */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

  /************** Descriptor of Joystick Mouse interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of Joystick Mouse HID ********************/
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Mouse endpoint ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  HID_EPIN_SIZE, /*wMaxPacketSize: 4 Byte max */
  0x00,
  HID_FS_BINTERVAL,          /*bInterval: Polling Interval */
  /* 34 */
};
#else
__ALIGN_BEGIN static uint8_t USBD_HID_CfgFSDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
 // configuration descriptor
 0x09, 0x02, USB_HID_CONFIG_DESC_SIZ, 0x00, HID_INTF_NUM,
 0x01, 0x00, 0xa0, 0x32,

 // mouse interface descriptor
 0x09, 0x04, 0x00, 0x00, 0x01,
 0x03, 0x01, 0x02, 0x00,

 // mouse HID descriptor
 0x09, 0x21, 0x10, 0x01, 0x00,
 0x01, 0x22, HID_MOUSE_REPORT_DESC_SIZE, 0x00,

 // mouse Endpoint
 0x07, 0x05, HID_MOUSE_EPIN_ADDR, 0x03,
 0x08, 0x00, 0x0a,

#ifdef HAS_KEYBOARD
 // keyboard interface descriptor
 0x09, 0x04, 0x01, 0x00, 0x01,
 0x03, 0x01, 0x01, 0x00,

 // keyboard HID descriptor
 0x09, 0x21, 0x10, 0x01, 0x00,
 0x01, 0x22, HID_KEYBD_REPORT_DESC_SIZE, 0x00,

 // keyboard Endpoint
 0x07, 0x05, HID_KEYBD_EPIN_ADDR, 0x03,
 0x08, 0x00, 0x0a,
#endif
};
#endif 

/* USB HID device HS Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_CfgHSDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,     /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xE0,         /*bmAttributes: bus powered and Support Remote Wake-up */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

  /************** Descriptor of Joystick Mouse interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of Joystick Mouse HID ********************/
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Mouse endpoint ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  HID_MOUSE_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  HID_MOUSE_EPIN_SIZE, /*wMaxPacketSize: 4 Byte max */
  0x00,
  HID_HS_BINTERVAL,          /*bInterval: Polling Interval */
  /* 34 */


};


/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_MOUSE_Desc[]  __ALIGN_END  =
{
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x10, 0x01,   /*bcdHID: HID Class Spec release number*/
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
};
__ALIGN_BEGIN static uint8_t USBD_HID_KEYBD_Desc[]  __ALIGN_END  =
{
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x10, 0x01,   /*bcdHID: HID Class Spec release number*/
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_KEYBD_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
};

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]  __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};



static uint8_t  USBD_HID_Init (USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  /* Open EP IN */
  //USBD_LL_OpenEP(pdev, HID_KEYBD_EPIN_ADDR, USBD_EP_TYPE_INTR, HID_KEYBD_EPIN_SIZE);
  USBD_LL_OpenEP(pdev, HID_MOUSE_EPIN_ADDR, USBD_EP_TYPE_INTR, HID_MOUSE_EPIN_SIZE);
  //pdev->ep_in[HID_KEYBD_EPIN_ADDR & 0xFU].is_used = 1U;
  pdev->ep_in[HID_MOUSE_EPIN_ADDR & 0xFU].is_used = 1U;

  pdev->pClassData = USBD_malloc(sizeof (USBD_HID_HandleTypeDef));

  if (pdev->pClassData == NULL)
  {
    return USBD_FAIL;
  }

  ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;

  return USBD_OK;
}

static uint8_t  USBD_HID_DeInit (USBD_HandleTypeDef *pdev,
                                 uint8_t cfgidx)
{
  /* Close HID EPs */
  //USBD_LL_CloseEP(pdev, HID_KEYBD_EPIN_ADDR);
  USBD_LL_CloseEP(pdev, HID_MOUSE_EPIN_ADDR);
  //pdev->ep_in[HID_KEYBD_EPIN_ADDR & 0xFU].is_used = 0U;
  pdev->ep_in[HID_MOUSE_EPIN_ADDR & 0xFU].is_used = 0U;

  /* FRee allocated memory */
  if(pdev->pClassData != NULL)
  {
    USBD_free(pdev->pClassData);
    pdev->pClassData = NULL;
  }

  return USBD_OK;
}

/**
  * @brief  USBD_HID_Setup
  *         Handle the HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_HID_Setup (USBD_HandleTypeDef *pdev,
                                USBD_SetupReqTypedef *req)
{
  USBD_HID_HandleTypeDef *hhid = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  uint16_t len = 0U;
  uint8_t *pbuf = NULL;
  uint16_t status_info = 0U;
  USBD_StatusTypeDef ret = USBD_OK;

  //printf("req bmRequest=%x bRequest=%x wValue=%x wIndex=%x wLength=%x\n",
  //       req->bmRequest, req->bRequest, req->wValue, req->wIndex, req->wLength);
  
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_CLASS :
    switch (req->bRequest)
    {
    case HID_REQ_SET_PROTOCOL:
      hhid->Protocol = (uint8_t)(req->wValue);
      break;

    case HID_REQ_GET_PROTOCOL:
      USBD_CtlSendData (pdev, (uint8_t *)(void *)&hhid->Protocol, 1U);
      break;

    case HID_REQ_SET_IDLE:
      hhid->IdleState = (uint8_t)(req->wValue >> 8);
      break;

    case HID_REQ_GET_IDLE:
      USBD_CtlSendData (pdev, (uint8_t *)(void *)&hhid->IdleState, 1U);
      break;

    default:
      goto failed;
    }
    break;
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {
    case USB_REQ_GET_STATUS:
      if (pdev->dev_state == USBD_STATE_CONFIGURED) {
        USBD_CtlSendData (pdev, (uint8_t *)(void *)&status_info, 2U);
      }
      else {
        goto failed;
      }
      break;

    case USB_REQ_GET_DESCRIPTOR:
      if(req->wValue >> 8 == HID_REPORT_DESC)
      {
        if (req->wIndex == 1) {
          len = MIN(sizeof(HID_KEYBD_ReportDesc) , req->wLength);
          pbuf = HID_KEYBD_ReportDesc;
        }
        else {
          len = MIN(sizeof(HID_MOUSE_ReportDesc) , req->wLength);
          pbuf = HID_MOUSE_ReportDesc;
        }
      }
      else if(req->wValue >> 8 == HID_DESCRIPTOR_TYPE)
      {
        if (req->wIndex == 1) {
          pbuf = USBD_HID_KEYBD_Desc;
          len = MIN(sizeof(USBD_HID_KEYBD_Desc), req->wLength);
        }
        else {
          pbuf = USBD_HID_MOUSE_Desc;
          len = MIN(sizeof(USBD_HID_MOUSE_Desc), req->wLength);
          //goto failed;
        }
      }
      else {
        goto failed;
      }
      USBD_CtlSendData (pdev, pbuf, len);
      break;

    case USB_REQ_GET_INTERFACE :
      if (pdev->dev_state == USBD_STATE_CONFIGURED) {
        USBD_CtlSendData (pdev, (uint8_t *)(void *)&hhid->AltSetting, 1U);
      }
      else {
        goto failed;
      }
      break;

    case USB_REQ_SET_INTERFACE :
      if (pdev->dev_state == USBD_STATE_CONFIGURED) {
        hhid->AltSetting = (uint8_t)(req->wValue);
      }
      else {
        goto failed;
      }
      break;

    default:
      goto failed;
    }
    break;

  default:
    goto failed;
  }
  return ret;
 failed:
  USBD_CtlError (pdev, req);
  return USBD_FAIL;
}


uint8_t USBD_HID_SendReport(USBD_HandleTypeDef  *pdev,
                            uint8_t *report,
                            uint16_t len)
{
  USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef*)pdev->pClassData;
#ifdef HAS_KEYBOARD
  int hid_addr = len < 8 ? HID_MOUSE_EPIN_ADDR : HID_KEYBD_EPIN_ADDR;
#else
  int hid_addr = HID_MOUSE_EPIN_ADDR;
#endif

  if (pdev->dev_state == USBD_STATE_CONFIGURED )
  {
    if(hhid->state == HID_IDLE)
    {
      hhid->state = HID_BUSY;
      USBD_LL_Transmit (pdev, hid_addr, report, len);
    }
  }
  return USBD_OK;
}

uint32_t USBD_HID_GetPollingInterval (USBD_HandleTypeDef *pdev)
{
  uint32_t polling_interval = 0U;

  /* HIGH-speed endpoints */
  if (pdev->dev_speed == USBD_SPEED_HIGH)
  {
   /* Sets the data transfer polling interval for high speed transfers.
    Values between 1..16 are allowed. Values correspond to interval
    of 2 ^ (bInterval-1). This option (8 ms, corresponds to HID_HS_BINTERVAL */
    polling_interval = (((1U <<(HID_HS_BINTERVAL - 1U))) / 8U);
  }
  else   /* LOW and FULL-speed endpoints */
  {
    /* Sets the data transfer polling interval for low and full
    speed transfers */
    polling_interval =  HID_FS_BINTERVAL;
  }

  return ((uint32_t)(polling_interval));
}

static uint8_t  *USBD_HID_GetFSCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgFSDesc);
  return USBD_HID_CfgFSDesc;
}

static uint8_t  *USBD_HID_GetHSCfgDesc (uint16_t *length)
{
  //*length = sizeof (USBD_HID_CfgFSDesc);
  //return USBD_HID_CfgFSDesc;
  *length = sizeof (USBD_HID_CfgHSDesc);
  return USBD_HID_CfgHSDesc;
}

static uint8_t  *USBD_HID_GetOtherSpeedCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgFSDesc);
  return USBD_HID_CfgFSDesc;
}

static uint8_t  USBD_HID_DataIn (USBD_HandleTypeDef *pdev,
                              uint8_t epnum)
{
  /* Ensure that the FIFO is empty before a new transfer, this condition could
  be caused by  a new transfer before the end of the previous transfer */
  ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;
  return USBD_OK;
}

static uint8_t  *USBD_HID_GetDeviceQualifierDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_DeviceQualifierDesc);
  return USBD_HID_DeviceQualifierDesc;
}


USBD_ClassTypeDef  USBD_HID =
{
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  NULL, /*EP0_TxSent*/
  NULL, /*EP0_RxReady*/
  USBD_HID_DataIn, /*DataIn*/
  NULL, /*DataOut*/
  NULL, /*SOF */
  NULL,
  NULL,
  USBD_HID_GetHSCfgDesc, /* High Speed */
  USBD_HID_GetFSCfgDesc, /* Full Speed */
  USBD_HID_GetFSCfgDesc, /* Other Speed */
  USBD_HID_GetDeviceQualifierDesc,
};


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
