/**
 * @file tusb_audio.h
 * @author Kasper Nyhus (kank@bang-olufsen.dk)
 * @brief
 * @version 0.1
 * @date 2022-10-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/ringbuf.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "tusb.h"

esp_err_t tusb_audio_init(void);

#ifdef __cplusplus
}
#endif
