// -*- c -*-
/////////////////////////////////////////////////////////////
//// Auto generate by TeenyDT, http://dt.tusb.org
/////////////////////////////////////////////////////////////
//#include "teeny_usb.h"

#define  UU_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t UU_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  UU_CONFIG_DESCRIPTOR_SIZE  (73)
__ALIGN_BEGIN  const uint8_t UU_ConfigDescriptor [73] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x49, 0x00,                                       /* wTotalLength */
  0x02,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x03,                                             /* bInterfaceClass */
  0x01,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// hid descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x3f, 0x00,                                       /* wDescriptorLength1 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x08, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x08, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x01,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x03,                                             /* bInterfaceClass */
  0x01,                                             /* bInterfaceSubClass */
  0x02,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// hid descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x32, 0x00,                                       /* wDescriptorLength1 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x82,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x08, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x02,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x08, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  UU_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  UU_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t UU_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  UU_STRING_DESCRIPTOR1_STR   "ZhongU2U"
#define  UU_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t UU_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'Z', 0x00,                                        /* wcChar0 */
  'h', 0x00,                                        /* wcChar1 */
  'o', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'g', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  '2', 0x00,                                        /* wcChar6 */
  'U', 0x00,                                        /* wcChar7 */
};
#define  UU_STRING_DESCRIPTOR2_STR   "USB2USB KM Convertor"
#define  UU_STRING_DESCRIPTOR2_SIZE   (42)
WEAK __ALIGN_BEGIN  const uint8_t UU_StringDescriptor2 [42] __ALIGN_END = {
  0x2a,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'U', 0x00,                                        /* wcChar0 */
  'S', 0x00,                                        /* wcChar1 */
  'B', 0x00,                                        /* wcChar2 */
  '2', 0x00,                                        /* wcChar3 */
  'U', 0x00,                                        /* wcChar4 */
  'S', 0x00,                                        /* wcChar5 */
  'B', 0x00,                                        /* wcChar6 */
  ' ', 0x00,                                        /* wcChar7 */
  'K', 0x00,                                        /* wcChar8 */
  'M', 0x00,                                        /* wcChar9 */
  ' ', 0x00,                                        /* wcChar10 */
  'C', 0x00,                                        /* wcChar11 */
  'o', 0x00,                                        /* wcChar12 */
  'n', 0x00,                                        /* wcChar13 */
  'v', 0x00,                                        /* wcChar14 */
  'e', 0x00,                                        /* wcChar15 */
  'r', 0x00,                                        /* wcChar16 */
  't', 0x00,                                        /* wcChar17 */
  'o', 0x00,                                        /* wcChar18 */
  'r', 0x00,                                        /* wcChar19 */
};
#define  UU_STRING_DESCRIPTOR3_STR   "U2U123456"
#define  UU_STRING_DESCRIPTOR3_SIZE   (20)
WEAK __ALIGN_BEGIN  const uint8_t UU_StringDescriptor3 [20] __ALIGN_END = {
  0x14,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'U', 0x00,                                        /* wcChar0 */
  '2', 0x00,                                        /* wcChar1 */
  'U', 0x00,                                        /* wcChar2 */
  '1', 0x00,                                        /* wcChar3 */
  '2', 0x00,                                        /* wcChar4 */
  '3', 0x00,                                        /* wcChar5 */
  '4', 0x00,                                        /* wcChar6 */
  '5', 0x00,                                        /* wcChar7 */
  '6', 0x00,                                        /* wcChar8 */
};
#define UU_STRING_COUNT    (4)
const uint8_t* const UU_StringDescriptors[4] = {
  UU_StringDescriptor0,
  UU_StringDescriptor1,
  UU_StringDescriptor2,
  UU_StringDescriptor3,
};
#define UU_REPORT_DESCRIPTOR_SIZE_IF0  (63)
WEAK __ALIGN_BEGIN const uint8_t UU_ReportDescriptor_if0[UU_REPORT_DESCRIPTOR_SIZE_IF0] __ALIGN_END = {
        //  Boot keyboad report descriptor
        0x05, 0x01,     // USAGE_PAGE (Generic Desktop)
        0x09, 0x06,     // USAGE (Keyboard)
        0xa1, 0x01,     // COLLECTION (Application)
        0x05, 0x07,     //   USAGE_PAGE (Keyboard)
        0x19, 0xe0,     //   USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7,     //   USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00,     //   LOGICAL_MINIMUM (0)
        0x25, 0x01,     //   LOGICAL_MAXIMUM (1)
        0x75, 0x01,     //   REPORT_SIZE (1)
        0x95, 0x08,     //   REPORT_COUNT (8)
        0x81, 0x02,     //   INPUT (Data,Var,Abs)
        0x95, 0x01,     //   REPORT_COUNT (1)
        0x75, 0x08,     //   REPORT_SIZE (8)
        0x81, 0x03,     //   INPUT (Cnst,Var,Abs)
        0x95, 0x05,     //   REPORT_COUNT (5)
        0x75, 0x01,     //   REPORT_SIZE (1)
        0x05, 0x08,     //   USAGE_PAGE (LEDs)
        0x19, 0x01,     //   USAGE_MINIMUM (Num Lock)
        0x29, 0x05,     //   USAGE_MAXIMUM (Kana)
        0x91, 0x02,     //   OUTPUT (Data,Var,Abs)
        0x95, 0x01,     //   REPORT_COUNT (1)
        0x75, 0x03,     //   REPORT_SIZE (3)
        0x91, 0x03,     //   OUTPUT (Cnst,Var,Abs)
        0x95, 0x06,     //   REPORT_COUNT (6)
        0x75, 0x08,     //   REPORT_SIZE (8)
        0x15, 0x00,     //   LOGICAL_MINIMUM (0)
        0x25, 0x65,     //   LOGICAL_MAXIMUM (101)
        0x05, 0x07,     //   USAGE_PAGE (Keyboard)
        0x19, 0x00,     //   USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x65,     //   USAGE_MAXIMUM (Keyboard Application)
        0x81, 0x00,     //   INPUT (Data,Ary,Abs)
        0xc0            // END_COLLECTION
    };

#define UU_REPORT_DESCRIPTOR_SIZE_IF1  (50)
WEAK __ALIGN_BEGIN const uint8_t UU_ReportDescriptor_if1[UU_REPORT_DESCRIPTOR_SIZE_IF1] __ALIGN_END = {
        //  Boot Mouse report descriptor
        0x05, 0x01,     // USAGE_PAGE (Generic Desktop)
        0x09, 0x02,     // USAGE (Mouse)
        0xa1, 0x01,     // COLLECTION (Application)
        0x09, 0x01,     //   USAGE (Pointer)
        0xa1, 0x00,     //   COLLECTION (Physical)
        0x05, 0x09,     //     USAGE_PAGE (Button)
        0x19, 0x01,     //     USAGE_MINIMUM (Button 1)
        0x29, 0x03,     //     USAGE_MAXIMUM (Button 3)
        0x15, 0x00,     //     LOGICAL_MINIMUM (0)
        0x25, 0x01,     //     LOGICAL_MAXIMUM (1)
        0x95, 0x03,     //     REPORT_COUNT (3)
        0x75, 0x01,     //     REPORT_SIZE (1)
        0x81, 0x02,     //     INPUT (Data,Var,Abs)
        0x95, 0x01,     //     REPORT_COUNT (1)
        0x75, 0x05,     //     REPORT_SIZE (5)
        0x81, 0x03,     //     INPUT (Cnst,Var,Abs)
        0x05, 0x01,     //     USAGE_PAGE (Generic Desktop)
        0x09, 0x30,     //     USAGE (X)
        0x09, 0x31,     //     USAGE (Y)
        0x15, 0x81,     //     LOGICAL_MINIMUM (-127)
        0x25, 0x7f,     //     LOGICAL_MAXIMUM (127)
        0x75, 0x08,     //     REPORT_SIZE (8)
        0x95, 0x02,     //     REPORT_COUNT (2)
        0x81, 0x06,     //     INPUT (Data,Var,Rel)
        0xc0,           //   END_COLLECTION
        0xc0            // END_COLLECTION
    };


#if 0
UU_TXEP_MAX_SIZE
UU_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors UU_descriptors = {
  .device = UU_DeviceDescriptor,
  .config = UU_ConfigDescriptor,
  .strings = UU_StringDescriptors,
  .string_cnt = UU_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(UU_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = UU_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // UU_WCID_DESCRIPTOR_SIZE)

#if defined(UU_WCID_PROPERTIES_SIZE)
  .wcid_properties = UU_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // UU_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(UU_WCID_BOS_SIZE)
  .wcid_bos = UU_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // UU_WCID_BOS_SIZE)

#if defined(UU_WCID_DESC_SET_SIZE)
  .wcid_desc_set = UU_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // UU_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
#endif
