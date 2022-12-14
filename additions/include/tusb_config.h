/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

// defined by compiler flags for flexibility
#ifndef CFG_TUSB_MCU
  #error CFG_TUSB_MCU must be defined
#endif

#ifndef CONFIG_ESP_TINYUSB_CDC_ENABLED
#   define CONFIG_ESP_TINYUSB_CDC_ENABLED 0
#endif

#ifndef CONFIG_ESP_TINYUSB_AUDIO_ENABLED
#   define CONFIG_ESP_TINYUSB_AUDIO_ENABLED 0
#endif

// RHPort number used for device can be defined by board.mk, default to port 0
#ifndef BOARD_DEVICE_RHPORT_NUM
  #define BOARD_DEVICE_RHPORT_NUM     0
#endif

#ifndef BOARD_DEVICE_RHPORT_SPEED
  #define BOARD_DEVICE_RHPORT_SPEED   OPT_MODE_FULL_SPEED
#endif

#define CFG_TUSB_RHPORT0_MODE       OPT_MODE_DEVICE

#ifndef CFG_TUSB_OS
  #define CFG_TUSB_OS                 OPT_OS_FREERTOS
#endif

// Espressif IDF requires "freertos/" prefix in include path
#if TU_CHECK_MCU(OPT_MCU_ESP32S2, OPT_MCU_ESP32S3)
  #define CFG_TUSB_OS_INC_PATH    freertos/
#endif

#ifndef CFG_TUSB_DEBUG
  #define CFG_TUSB_DEBUG              0
#endif

// CFG_TUSB_DEBUG is defined by compiler in DEBUG build
// #define CFG_TUSB_DEBUG           0

/* USB DMA on some MCUs can only access a specific SRAM region with restriction on alignment.
 * Tinyusb use follows macros to declare transferring memory so that they can be put
 * into those specific section.
 * e.g
 * - CFG_TUSB_MEM SECTION : __attribute__ (( section(".usb_ram") ))
 * - CFG_TUSB_MEM_ALIGN   : __attribute__ ((aligned(4)))
 */
#ifndef CFG_TUSB_MEM_SECTION
  #define CFG_TUSB_MEM_SECTION
#endif

#ifndef CFG_TUSB_MEM_ALIGN
  #define CFG_TUSB_MEM_ALIGN          __attribute__ ((aligned(4)))
#endif

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------

#ifndef CFG_TUD_ENDPOINT0_SIZE
#define CFG_TUD_ENDPOINT0_SIZE    64
#endif

//------------- CLASS -------------//
#define CFG_TUD_CDC               CONFIG_ESP_TINYUSB_CDC_ENABLED
#define CFG_TUD_MSC               0
#define CFG_TUD_HID               0
#define CFG_TUD_MIDI              0
#define CFG_TUD_AUDIO             CONFIG_ESP_TINYUSB_AUDIO_ENABLED
#define CFG_TUD_VENDOR            0


//--------------------------------------------------------------------
// CDC CLASS DRIVER CONFIGURATION
//--------------------------------------------------------------------

// CDC FIFO size of TX and RX
#define CFG_TUD_CDC_RX_BUFSIZE      CONFIG_ESP_TINYUSB_CDC_RX_BUFSIZE
#define CFG_TUD_CDC_TX_BUFSIZE      CONFIG_ESP_TINYUSB_CDC_TX_BUFSIZE

//--------------------------------------------------------------------
// AUDIO CLASS DRIVER CONFIGURATION
//--------------------------------------------------------------------

#define TUD_AUDIO_MIC_TWO_CH_DESC_LEN (TUD_AUDIO_DESC_IAD_LEN\
  + TUD_AUDIO_DESC_STD_AC_LEN\
  + TUD_AUDIO_DESC_CS_AC_LEN\
  + TUD_AUDIO_DESC_CLK_SRC_LEN\
  + TUD_AUDIO_DESC_INPUT_TERM_LEN\
  + TUD_AUDIO_DESC_OUTPUT_TERM_LEN\
  + TUD_AUDIO_DESC_FEATURE_UNIT_TWO_CHANNEL_LEN\
  + TUD_AUDIO_DESC_STD_AS_INT_LEN\
  + TUD_AUDIO_DESC_STD_AS_INT_LEN\
  + TUD_AUDIO_DESC_CS_AS_INT_LEN\
  + TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN\
  + TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN\
  + TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN)

// Have a look into audio_device.h for all configurations

#if CONFIG_AUDIO_CHANNELS == 4
  #define CFG_TUD_AUDIO_FUNC_1_DESC_LEN                                 TUD_AUDIO_MIC_FOUR_CH_DESC_LEN
#elif CONFIG_AUDIO_CHANNELS == 2
  #define CFG_TUD_AUDIO_FUNC_1_DESC_LEN                                 TUD_AUDIO_MIC_TWO_CH_DESC_LEN
#else
  #define CFG_TUD_AUDIO_FUNC_1_DESC_LEN                                 TUD_AUDIO_MIC_ONE_CH_DESC_LEN
#endif

#define CFG_TUD_AUDIO_FUNC_1_N_AS_INT                                 1
#define CFG_TUD_AUDIO_FUNC_1_CTRL_BUF_SZ                              64

#define CFG_TUD_AUDIO_ENABLE_EP_IN                                    1
#define CFG_TUD_AUDIO_FUNC_1_N_BYTES_PER_SAMPLE_TX                    CONFIG_AUDIO_BYTES_PER_SAMPLE         // This value is not required by the driver, it parses this information from the descriptor once the alternate interface is set by the host - we use it for the setup

#define CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_TX                            CONFIG_AUDIO_CHANNELS         // This value is not required by the driver, it parses this information from the descriptor once the alternate interface is set by the host - we use it for the setup

#define CFG_TUD_AUDIO_EP_SZ_IN                                        48 * CFG_TUD_AUDIO_FUNC_1_N_BYTES_PER_SAMPLE_TX * CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_TX     // 48 Samples (48 kHz) x 2 Bytes/Sample x CFG_TUD_AUDIO_N_CHANNELS_TX Channels - the Windows driver always needs an extra sample per channel of space more, otherwise it complains... found by trial and error
#define CFG_TUD_AUDIO_FUNC_1_EP_IN_SZ_MAX                             CFG_TUD_AUDIO_EP_SZ_IN
#define CFG_TUD_AUDIO_FUNC_1_EP_IN_SW_BUF_SZ                          CFG_TUD_AUDIO_EP_SZ_IN


#ifdef __cplusplus
}
#endif

#endif /* _TUSB_CONFIG_H_ */
