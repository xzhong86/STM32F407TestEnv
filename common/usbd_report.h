
// Copy form LUFA, LUFA/Drivers/USB/Class/Common/HIDReportData.h
//  for USB Report Descriptor

#ifndef __USBD_REPORT_H__
#define __USBD_REPORT_H__

#ifndef CONCAT_EXPANDED
# define CONCAT_EXPANDED(A, B)     A ## B
#endif

#define HID_RI_DATA_SIZE_MASK                   0x03
#define HID_RI_TYPE_MASK                        0x0C
#define HID_RI_TAG_MASK                         0xF0

#define HID_RI_TYPE_MAIN                        0x00
#define HID_RI_TYPE_GLOBAL                      0x04
#define HID_RI_TYPE_LOCAL                       0x08

#define HID_RI_DATA_BITS_0                      0x00
#define HID_RI_DATA_BITS_8                      0x01
#define HID_RI_DATA_BITS_16                     0x02
#define HID_RI_DATA_BITS_32                     0x03
#define HID_RI_DATA_BITS(DataBits)              CONCAT_EXPANDED(HID_RI_DATA_BITS_, DataBits)

#define _HID_RI_ENCODE_0(Data)
#define _HID_RI_ENCODE_8(Data)                  , (Data & 0xFF)
#define _HID_RI_ENCODE_16(Data)                 _HID_RI_ENCODE_8(Data)  _HID_RI_ENCODE_8(Data >> 8)
#define _HID_RI_ENCODE_32(Data)                 _HID_RI_ENCODE_16(Data) _HID_RI_ENCODE_16(Data >> 16)
#define _HID_RI_ENCODE(DataBits, ...)           CONCAT_EXPANDED(_HID_RI_ENCODE_, DataBits(__VA_ARGS__))

#define _HID_RI_ENTRY(Type, Tag, DataBits, ...) (Type | Tag | HID_RI_DATA_BITS(DataBits)) _HID_RI_ENCODE(DataBits, (__VA_ARGS__))

/** name HID Input, Output and Feature Report Descriptor Item Flags */
#define HID_IOF_CONSTANT                        (1 << 0)
#define HID_IOF_DATA                            (0 << 0)
#define HID_IOF_VARIABLE                        (1 << 1)
#define HID_IOF_ARRAY                           (0 << 1)
#define HID_IOF_RELATIVE                        (1 << 2)
#define HID_IOF_ABSOLUTE                        (0 << 2)
#define HID_IOF_WRAP                            (1 << 3)
#define HID_IOF_NO_WRAP                         (0 << 3)
#define HID_IOF_NON_LINEAR                      (1 << 4)
#define HID_IOF_LINEAR                          (0 << 4)
#define HID_IOF_NO_PREFERRED_STATE              (1 << 5)
#define HID_IOF_PREFERRED_STATE                 (0 << 5)
#define HID_IOF_NULLSTATE                       (1 << 6)
#define HID_IOF_NO_NULL_POSITION                (0 << 6)
#define HID_IOF_VOLATILE                        (1 << 7)
#define HID_IOF_NON_VOLATILE                    (0 << 7)
#define HID_IOF_BUFFERED_BYTES                  (1 << 8)
#define HID_IOF_BITFIELD                        (0 << 8)

/** \name HID Report Descriptor Item Macros */
#define HID_RI_INPUT(DataBits, ...)             _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0x80, DataBits, __VA_ARGS__)
#define HID_RI_OUTPUT(DataBits, ...)            _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0x90, DataBits, __VA_ARGS__)
#define HID_RI_COLLECTION(DataBits, ...)        _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0xA0, DataBits, __VA_ARGS__)
#define HID_RI_FEATURE(DataBits, ...)           _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0xB0, DataBits, __VA_ARGS__)
#define HID_RI_END_COLLECTION(DataBits, ...)    _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0xC0, DataBits, __VA_ARGS__)
#define HID_RI_USAGE_PAGE(DataBits, ...)        _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x00, DataBits, __VA_ARGS__)
#define HID_RI_LOGICAL_MINIMUM(DataBits, ...)   _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x10, DataBits, __VA_ARGS__)
#define HID_RI_LOGICAL_MAXIMUM(DataBits, ...)   _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x20, DataBits, __VA_ARGS__)
#define HID_RI_PHYSICAL_MINIMUM(DataBits, ...)  _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x30, DataBits, __VA_ARGS__)
#define HID_RI_PHYSICAL_MAXIMUM(DataBits, ...)  _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x40, DataBits, __VA_ARGS__)
#define HID_RI_UNIT_EXPONENT(DataBits, ...)     _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x50, DataBits, __VA_ARGS__)
#define HID_RI_UNIT(DataBits, ...)              _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x60, DataBits, __VA_ARGS__)
#define HID_RI_REPORT_SIZE(DataBits, ...)       _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x70, DataBits, __VA_ARGS__)
#define HID_RI_REPORT_ID(DataBits, ...)         _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x80, DataBits, __VA_ARGS__)
#define HID_RI_REPORT_COUNT(DataBits, ...)      _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x90, DataBits, __VA_ARGS__)
#define HID_RI_PUSH(DataBits, ...)              _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0xA0, DataBits, __VA_ARGS__)
#define HID_RI_POP(DataBits, ...)               _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0xB0, DataBits, __VA_ARGS__)
#define HID_RI_USAGE(DataBits, ...)             _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x00, DataBits, __VA_ARGS__)
#define HID_RI_USAGE_MINIMUM(DataBits, ...)     _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x10, DataBits, __VA_ARGS__)
#define HID_RI_USAGE_MAXIMUM(DataBits, ...)     _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x20, DataBits, __VA_ARGS__)


/* HID description */

/** \hideinitializer
 *  A list of HID report item array elements that describe a typical HID USB keyboard. The resulting report descriptor
 *  is compatible with \ref USB_KeyboardReport_Data_t when \c MaxKeys is equal to 6. For other values, the report will
 *  be structured according to the following layout:
 *
 *  \code
 *  struct
 *  {
 *	uint8_t Modifier; // Keyboard modifier byte indicating pressed modifier keys (\c HID_KEYBOARD_MODIFER_* masks)
 *	uint8_t Reserved; // Reserved for OEM use, always set to 0.
 *	uint8_t KeyCode[MaxKeys]; // Length determined by the number of keys that can be reported
 *  } Keyboard_Report;
 *  \endcode
 *
 *  \param[in] MaxKeys	Number of simultaneous keys that can be reported at the one time (8-bit).
 */
#define HID_DESCRIPTOR_KEYBOARD(MaxKeys)	    \
	HID_RI_USAGE_PAGE(8, 0x01),			\
	HID_RI_USAGE(8, 0x06),				\
	HID_RI_COLLECTION(8, 0x01),			\
		HID_RI_USAGE_PAGE(8, 0x07),		    \
		HID_RI_USAGE_MINIMUM(8, 0xE0),		    \
		HID_RI_USAGE_MAXIMUM(8, 0xE7),		    \
		HID_RI_LOGICAL_MINIMUM(8, 0x00),	    \
		HID_RI_LOGICAL_MAXIMUM(8, 0x01),	    \
		HID_RI_REPORT_SIZE(8, 0x01),		    \
		HID_RI_REPORT_COUNT(8, 0x08),		    \
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE), \
		HID_RI_REPORT_COUNT(8, 0x01),		    \
		HID_RI_REPORT_SIZE(8, 0x08),		    \
		HID_RI_INPUT(8, HID_IOF_CONSTANT),	    \
		HID_RI_USAGE_PAGE(8, 0x08),		    \
		HID_RI_USAGE_MINIMUM(8, 0x01),		    \
		HID_RI_USAGE_MAXIMUM(8, 0x05),		    \
		HID_RI_REPORT_COUNT(8, 0x05),		    \
		HID_RI_REPORT_SIZE(8, 0x01),		    \
		HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE), \
		HID_RI_REPORT_COUNT(8, 0x01),		    \
		HID_RI_REPORT_SIZE(8, 0x03),		    \
		HID_RI_OUTPUT(8, HID_IOF_CONSTANT),	    \
		HID_RI_LOGICAL_MINIMUM(8, 0x00),	    \
		HID_RI_LOGICAL_MAXIMUM(8, 0xFF),	    \
		HID_RI_USAGE_PAGE(8, 0x07),		    \
		HID_RI_USAGE_MINIMUM(8, 0x00),		    \
		HID_RI_USAGE_MAXIMUM(8, 0xFF),		    \
		HID_RI_REPORT_COUNT(8, MaxKeys),	    \
		HID_RI_REPORT_SIZE(8, 0x08),		    \
		HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_ARRAY | HID_IOF_ABSOLUTE), \
	HID_RI_END_COLLECTION(0)

/** \hideinitializer
 *  A list of HID report item array elements that describe a typical HID USB mouse. The resulting report descriptor
 *  is compatible with \ref USB_MouseReport_Data_t if the \c MinAxisVal and \c MaxAxisVal values fit within a \c int8_t range
 *  and the number of Buttons is less than 8. For other values, the report is structured according to the following layout:
 *
 *  \code
 *  struct
 *  {
 *	uintA_t Buttons; // Pressed buttons bitmask
 *	intB_t X; // X axis value
 *	intB_t Y; // Y axis value
 *  } Mouse_Report;
 *  \endcode
 *
 *  Where \c intA_t is a type large enough to hold one bit per button, and \c intB_t is a type large enough to hold the
 *  ranges of the signed \c MinAxisVal and \c MaxAxisVal values.
 *
 *  \param[in] MinAxisVal      Minimum X/Y logical axis value (16-bit).
 *  \param[in] MaxAxisVal      Maximum X/Y logical axis value (16-bit).
 *  \param[in] MinPhysicalVal  Minimum X/Y physical axis value, for movement resolution calculations (16-bit).
 *  \param[in] MaxPhysicalVal  Maximum X/Y physical axis value, for movement resolution calculations (16-bit).
 *  \param[in] Buttons	       Total number of buttons in the device (8-bit).
 *  \param[in] AbsoluteCoords  Boolean \c true to use absolute X/Y coordinates (e.g. touchscreen).
 */
#define HID_DESCRIPTOR_MOUSE(MinAxisVal, MaxAxisVal, MinPhysicalVal, MaxPhysicalVal, Buttons, AbsoluteCoords) \
	HID_RI_USAGE_PAGE(8, 0x01),			\
	HID_RI_USAGE(8, 0x02),				\
	HID_RI_COLLECTION(8, 0x01),			\
		HID_RI_USAGE(8, 0x01),			    \
		HID_RI_COLLECTION(8, 0x00),		    \
			HID_RI_USAGE_PAGE(8, 0x09),		\
			HID_RI_USAGE_MINIMUM(8, 0x01),		\
			HID_RI_USAGE_MAXIMUM(8, Buttons),	\
			HID_RI_LOGICAL_MINIMUM(8, 0x00),	\
			HID_RI_LOGICAL_MAXIMUM(8, 0x01),	\
			HID_RI_REPORT_COUNT(8, Buttons),	\
			HID_RI_REPORT_SIZE(8, 0x01),		\
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE), \
			HID_RI_REPORT_COUNT(8, 0x01),		\
			HID_RI_REPORT_SIZE(8, (Buttons % 8) ? (8 - (Buttons % 8)) : 0), \
			HID_RI_INPUT(8, HID_IOF_CONSTANT),	\
			HID_RI_USAGE_PAGE(8, 0x01),		\
			HID_RI_USAGE(8, 0x30),			\
			HID_RI_USAGE(8, 0x31),			\
			HID_RI_LOGICAL_MINIMUM(16, MinAxisVal), \
			HID_RI_LOGICAL_MAXIMUM(16, MaxAxisVal), \
			HID_RI_PHYSICAL_MINIMUM(16, MinPhysicalVal), \
			HID_RI_PHYSICAL_MAXIMUM(16, MaxPhysicalVal), \
			HID_RI_REPORT_COUNT(8, 0x02),		\
			HID_RI_REPORT_SIZE(8, (((MinAxisVal >= -128) && (MaxAxisVal <= 127)) ? 8 : 16)), \
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | (AbsoluteCoords ? HID_IOF_ABSOLUTE : HID_IOF_RELATIVE)), \
		HID_RI_END_COLLECTION(0),		    \
	HID_RI_END_COLLECTION(0)


#endif
