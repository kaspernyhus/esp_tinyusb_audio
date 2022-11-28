/**
 * @file tusb_audio.h
 * @author your name (you@domain.com)
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

typedef void (*tusb_audio_callback_t)(uint8_t* buffer, uint16_t* bytes);

typedef struct {
    tusb_audio_callback_t audio_tx_callback;
} tinyusb_config_audio_t;

esp_err_t tusb_audio_init(const tinyusb_config_audio_t* cfg);

#ifdef __cplusplus
}
#endif
