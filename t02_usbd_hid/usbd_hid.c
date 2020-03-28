
#include "usbd_hid.h"
#include "usbd_ctlreq.h"
#include "usbd_report.h"

// for including teeny desc
#define WEAK  /* nothing */
#define USB_DEVICE_DESCRIPTOR_TYPE          USB_DESC_TYPE_DEVICE
#define USB_CONFIGURATION_DESCRIPTOR_TYPE   USB_DESC_TYPE_CONFIGURATION
#define USB_INTERFACE_DESCRIPTOR_TYPE       USB_DESC_TYPE_INTERFACE
#define USB_ENDPOINT_DESCRIPTOR_TYPE        USB_DESC_TYPE_ENDPOINT
#define USB_STRING_DESCRIPTOR_TYPE          USB_DESC_TYPE_STRING
#include "teeny_usb_desc.c.inc"

#define USBD_HID_CfgFSDesc   UU_ConfigDescriptor


#define HID_DESCRIPTOR_TYPE           0x21U
#define HID_REPORT_DESC               0x22U

#define HID_KEYBD_EPIN_ADDR           0x81U
#define HID_KEYBD_EPIN_SIZE           0x08U
#define HID_KEYBD_INTF_ID             1

#define HID_MOUSE_EPIN_ADDR           0x82U
#define HID_MOUSE_EPIN_SIZE           0x08U
#define HID_MOUSE_INTF_ID             2



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



/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_KEYBD_Desc[]  __ALIGN_END  =
{
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x3f, 0x00,                                       /* wDescriptorLength1 */
};
__ALIGN_BEGIN static uint8_t USBD_HID_MOUSE_Desc[]  __ALIGN_END  =
{
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x32, 0x00,                                       /* wDescriptorLength1 */
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
  USBD_LL_OpenEP(pdev, HID_KEYBD_EPIN_ADDR, USBD_EP_TYPE_INTR, HID_KEYBD_EPIN_SIZE);
  USBD_LL_OpenEP(pdev, HID_MOUSE_EPIN_ADDR, USBD_EP_TYPE_INTR, HID_MOUSE_EPIN_SIZE);
  pdev->ep_in[HID_KEYBD_EPIN_ADDR & 0xFU].is_used = 1U;
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
  USBD_LL_CloseEP(pdev, HID_KEYBD_EPIN_ADDR);
  USBD_LL_CloseEP(pdev, HID_MOUSE_EPIN_ADDR);
  pdev->ep_in[HID_KEYBD_EPIN_ADDR & 0xFU].is_used = 0U;
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
        if (req->wIndex == 0) {
          len = MIN(UU_REPORT_DESCRIPTOR_SIZE_IF0, req->wLength);
          pbuf = (void*)UU_ReportDescriptor_if0;
        } else {
          len = MIN(UU_REPORT_DESCRIPTOR_SIZE_IF1, req->wLength);
          pbuf = (void*)UU_ReportDescriptor_if1;
        }
      }
      else if(req->wValue >> 8 == HID_DESCRIPTOR_TYPE)
      {
        if (req->wIndex == 0) {
          pbuf = USBD_HID_KEYBD_Desc;
          len = MIN(sizeof(USBD_HID_KEYBD_Desc), req->wLength);
        } else {
          pbuf = USBD_HID_MOUSE_Desc;
          len = MIN(sizeof(USBD_HID_MOUSE_Desc), req->wLength);
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
#if 1
  int hid_addr = len < 8 ? HID_MOUSE_EPIN_ADDR : HID_KEYBD_EPIN_ADDR;
#else
  int hid_addr = HID_KEYBD_EPIN_ADDR;
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
  return (void*)USBD_HID_CfgFSDesc;
}

static uint8_t  *USBD_HID_GetHSCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgFSDesc);
  return (void*)USBD_HID_CfgFSDesc;
}

static uint8_t  *USBD_HID_GetOtherSpeedCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgFSDesc);
  return (void*)USBD_HID_CfgFSDesc;
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
