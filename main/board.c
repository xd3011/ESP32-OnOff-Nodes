/* board.c - Board-specific hooks */

/*
 * SPDX-FileCopyrightText: 2017 Intel Corporation
 * SPDX-FileContributor: 2018-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "board.h"

#include <stdio.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "iot_button.h"

#define BUTTON_IO_NUM 0
#define BUTTON_ACTIVE_LEVEL 0

#define TAG "BOARD"

extern void server_send_to_client(uint8_t onoff);

void board_led_operation(uint8_t pin, uint8_t onoff) {
    gpio_set_level(pin, onoff);
}

static void board_led_init(void) {
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, LED_OFF);
}

static void button_tap_cb(void* arg) {
    ESP_LOGI(TAG, "tap cb (%s)", (char*)arg);
    server_send_to_client(1);
}

static void board_button_init(void) {
    button_handle_t btn_handle =
        iot_button_create(BUTTON_IO_NUM, BUTTON_ACTIVE_LEVEL);
    if (btn_handle) {
        iot_button_set_evt_cb(btn_handle, BUTTON_CB_RELEASE, button_tap_cb,
                              "RELEASE");
    }
}

void board_init(void) {
    board_led_init();
    board_button_init();
}
