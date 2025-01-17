/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018, hathach for Adafruit
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
 */

#ifndef _TUSB_CONFIG_ESP32_H_
#define _TUSB_CONFIG_ESP32_H_

#ifdef __cplusplus
extern "C" {
#endif

// ESP32 Arduino core already integrated tinyusb using lib arduino_tinyusb
//    https://github.com/espressif/esp32-arduino-lib-builder/tree/master/components/arduino_tinyusb
// Although it is possible to use .c files in this library for linking instead
// of lib arduino_tinyusb. However, include path of lib arduino_tinyusb is first
// in order. Therefore, changes in this Adafruit TinyUSB library's header are
// not picked up by its .c file. Due to the version difference between the 2
// libraries, this file is used to make it compatible with ESP32 Arduino core.

// This file also contains additional configuration for EPS32 in addition to
// tools/sdk/esp32xx/include/arduino_tinyusb/include/tusb_config.h

//--------------------------------------------------------------------+
// ESP32 out-of-sync
//--------------------------------------------------------------------+
#ifndef tu_static
#define tu_static static

#include <stddef.h>
#include <string.h>
static inline int tu_memset_s(void *dest, size_t destsz, int ch, size_t count) {
  if (count > destsz) {
    return -1;
  }
  memset(dest, ch, count);
  return 0;
}
static inline int tu_memcpy_s(void *dest, size_t destsz, const void *src,
                              size_t count) {
  if (count > destsz) {
    return -1;
  }
  memcpy(dest, src, count);
  return 0;
}
#endif

#ifndef CFG_TUD_MEM_SECTION
#define CFG_TUD_MEM_SECTION CFG_TUSB_MEM_SECTION
#endif

#ifndef CFG_TUD_LOG_LEVEL
#define CFG_TUD_LOG_LEVEL 2
#endif

#if 0
//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUSB_MCU OPT_MCU_NRF5X

#define CFG_TUSB_OS OPT_OS_FREERTOS
#define CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_ALIGN __attribute__((aligned(4)))

#ifndef CFG_TUSB_DEBUG
#define CFG_TUSB_DEBUG 0
#endif

// For selectively disable device log (when > CFG_TUSB_DEBUG)
// #define CFG_TUD_LOG_LEVEL 3

#ifdef USE_TINYUSB
// Enable device stack
#define CFG_TUD_ENABLED 1

// Enable host stack with MAX3421E (host shield)
#define CFG_TUH_ENABLED 1
#define CFG_TUH_MAX3421 1

#else
#define CFG_TUD_ENABLED 0
#define CFG_TUH_ENABLED 0
#endif

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Host Configuration
//--------------------------------------------------------------------

// Size of buffer to hold descriptors and other data used for enumeration
#define CFG_TUH_ENUMERATION_BUFSIZE 256

// Number of hub devices
#define CFG_TUH_HUB 1

// max device support (excluding hub device): 1 hub typically has 4 ports
#define CFG_TUH_DEVICE_MAX (3 * CFG_TUH_HUB + 1)

// Enable tuh_edpt_xfer() API
// #define CFG_TUH_API_EDPT_XFER       1

// Number of mass storage
#define CFG_TUH_MSC 1

// Number of HIDs
// typical keyboard + mouse device can have 3,4 HID interfaces
#define CFG_TUH_HID (3 * CFG_TUH_DEVICE_MAX)

// Number of CDC interfaces
// FTDI and CP210x are not part of CDC class, only to re-use CDC driver API
#define CFG_TUH_CDC 1
#define CFG_TUH_CDC_FTDI 1
#define CFG_TUH_CDC_CP210X 1

// RX & TX fifo size
#define CFG_TUH_CDC_RX_BUFSIZE 64
#define CFG_TUH_CDC_TX_BUFSIZE 64

// Set Line Control state on enumeration/mounted:
// DTR ( bit 0), RTS (bit 1)
#define CFG_TUH_CDC_LINE_CONTROL_ON_ENUM 0x03

// Set Line Coding on enumeration/mounted, value for cdc_line_coding_t
// bit rate = 115200, 1 stop bit, no parity, 8 bit data width
// This need Pico-PIO-USB at least 0.5.1
#define CFG_TUH_CDC_LINE_CODING_ON_ENUM                                        \
  { 115200, CDC_LINE_CONDING_STOP_BITS_1, CDC_LINE_CODING_PARITY_NONE, 8 }

#endif

#ifdef __cplusplus
}
#endif

#endif
