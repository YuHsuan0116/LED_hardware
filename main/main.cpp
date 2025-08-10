extern "C" void app_main();
#include "LedDriver.hpp"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MAXIMUM_BRIGTNESS 15

#define COLOR_GRB(g, r, b)                                                      \
    {                                                                           \
        .green = (uint8_t)(((float)g / (float)255) * (float)MAXIMUM_BRIGTNESS), \
        .red = (uint8_t)(((float)r / (float)255) * (float)MAXIMUM_BRIGTNESS),   \
        .blue = (uint8_t)(((float)b / (float)255) * (float)MAXIMUM_BRIGTNESS),  \
    }

const static led_config_t config[] = {
    {
        .type = LED_TYPE_STRIP,
        .led_count = 100,
        .gpio_or_addr = 4,
        .pca_channel = 0,
    },
    {
        .type = LED_TYPE_STRIP,
        .led_count = 100,
        .gpio_or_addr = 16,
        .pca_channel = 0,
    },
    {
        .type = LED_TYPE_STRIP,
        .led_count = 100,
        .gpio_or_addr = 17,
        .pca_channel = 0,
    },
    {
        .type = LED_TYPE_STRIP,
        .led_count = 100,
        .gpio_or_addr = 5,
        .pca_channel = 0,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5B,
        .pca_channel = 4,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5B,
        .pca_channel = 3,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5B,
        .pca_channel = 2,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5B,
        .pca_channel = 1,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5B,
        .pca_channel = 0,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5C,
        .pca_channel = 4,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5C,
        .pca_channel = 3,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5C,
        .pca_channel = 2,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5C,
        .pca_channel = 1,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5C,
        .pca_channel = 0,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5E,
        .pca_channel = 4,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5E,
        .pca_channel = 3,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5E,
        .pca_channel = 2,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5E,
        .pca_channel = 1,
    },
    {
        .type = LED_TYPE_OF,
        .led_count = 1,
        .gpio_or_addr = 0x5E,
        .pca_channel = 0,
    },
    {
        .type = LED_TYPE_STRIP,
        .led_count = 100,
        .gpio_or_addr = 33,
        .pca_channel = 0,
    },
    // {
    //     .type = LED_TYPE_OF,
    //     .led_count = 1,
    //     .gpio_or_addr = 0x5B,
    //     .pca_channel = 4,
    // },
    // {
    //     .type = LED_TYPE_OF,
    //     .led_count = 1,
    //     .gpio_or_addr = 0x5B,
    //     .pca_channel = 3,
    // },
    // {
    //     .type = LED_TYPE_OF,
    //     .led_count = 1,
    //     .gpio_or_addr = 0x5B,
    //     .pca_channel = 2,
    // },
    // {
    //     .type = LED_TYPE_OF,
    //     .led_count = 1,
    //     .gpio_or_addr = 0x5B,
    //     .pca_channel = 1,
    // },
    // {
    //     .type = LED_TYPE_OF,
    //     .led_count = 1,
    //     .gpio_or_addr = 0x5B,
    //     .pca_channel = 0,
    // },
    {
        .type = LED_TYPE_STRIP,
        .led_count = 100,
        .gpio_or_addr = 26,
        .pca_channel = 0,
    },
    {
        .type = LED_TYPE_STRIP,
        .led_count = 100,
        .gpio_or_addr = 27,
        .pca_channel = 0,
    },
    {
        .type = LED_TYPE_STRIP,
        .led_count = 100,
        .gpio_or_addr = 32,
        .pca_channel = 0,
    },

};

color_t test[490] = {
    COLOR_GRB(0, 255, 0),   COLOR_GRB(31, 255, 0),  COLOR_GRB(62, 255, 0),  COLOR_GRB(93, 255, 0),  COLOR_GRB(124, 255, 0), COLOR_GRB(156, 255, 0),
    COLOR_GRB(187, 255, 0), COLOR_GRB(218, 255, 0), COLOR_GRB(249, 255, 0), COLOR_GRB(255, 228, 0), COLOR_GRB(255, 197, 0), COLOR_GRB(255, 166, 0),
    COLOR_GRB(255, 135, 0), COLOR_GRB(255, 104, 0), COLOR_GRB(255, 72, 0),  COLOR_GRB(255, 41, 0),  COLOR_GRB(255, 10, 0),  COLOR_GRB(255, 0, 20),
    COLOR_GRB(255, 0, 52),  COLOR_GRB(255, 0, 83),  COLOR_GRB(255, 0, 114), COLOR_GRB(255, 0, 145), COLOR_GRB(255, 0, 176), COLOR_GRB(255, 0, 208),
    COLOR_GRB(255, 0, 239), COLOR_GRB(239, 0, 255), COLOR_GRB(208, 0, 255), COLOR_GRB(176, 0, 255), COLOR_GRB(145, 0, 255), COLOR_GRB(114, 0, 255),
    COLOR_GRB(83, 0, 255),  COLOR_GRB(52, 0, 255),  COLOR_GRB(20, 0, 255),  COLOR_GRB(0, 10, 255),  COLOR_GRB(0, 41, 255),  COLOR_GRB(0, 72, 255),
    COLOR_GRB(0, 104, 255), COLOR_GRB(0, 135, 255), COLOR_GRB(0, 166, 255), COLOR_GRB(0, 197, 255), COLOR_GRB(0, 228, 255), COLOR_GRB(0, 255, 249),
    COLOR_GRB(0, 255, 218), COLOR_GRB(0, 255, 187), COLOR_GRB(0, 255, 156), COLOR_GRB(0, 255, 124), COLOR_GRB(0, 255, 93),  COLOR_GRB(0, 255, 62),
    COLOR_GRB(0, 255, 31),  COLOR_GRB(0, 255, 0),   COLOR_GRB(31, 255, 0),  COLOR_GRB(62, 255, 0),  COLOR_GRB(93, 255, 0),  COLOR_GRB(124, 255, 0),
    COLOR_GRB(156, 255, 0), COLOR_GRB(187, 255, 0), COLOR_GRB(218, 255, 0), COLOR_GRB(249, 255, 0), COLOR_GRB(255, 228, 0), COLOR_GRB(255, 197, 0),
    COLOR_GRB(255, 166, 0), COLOR_GRB(255, 135, 0), COLOR_GRB(255, 104, 0), COLOR_GRB(255, 72, 0),  COLOR_GRB(255, 41, 0),  COLOR_GRB(255, 10, 0),
    COLOR_GRB(255, 0, 20),  COLOR_GRB(255, 0, 52),  COLOR_GRB(255, 0, 83),  COLOR_GRB(255, 0, 114), COLOR_GRB(255, 0, 145), COLOR_GRB(255, 0, 176),
    COLOR_GRB(255, 0, 208), COLOR_GRB(255, 0, 239), COLOR_GRB(239, 0, 255), COLOR_GRB(208, 0, 255), COLOR_GRB(176, 0, 255), COLOR_GRB(145, 0, 255),
    COLOR_GRB(114, 0, 255), COLOR_GRB(83, 0, 255),  COLOR_GRB(52, 0, 255),  COLOR_GRB(20, 0, 255),  COLOR_GRB(0, 10, 255),  COLOR_GRB(0, 41, 255),
    COLOR_GRB(0, 72, 255),  COLOR_GRB(0, 104, 255), COLOR_GRB(0, 135, 255), COLOR_GRB(0, 166, 255), COLOR_GRB(0, 197, 255), COLOR_GRB(0, 228, 255),
    COLOR_GRB(0, 255, 249), COLOR_GRB(0, 255, 218), COLOR_GRB(0, 255, 187), COLOR_GRB(0, 255, 156), COLOR_GRB(0, 255, 124), COLOR_GRB(0, 255, 93),
    COLOR_GRB(0, 255, 62),  COLOR_GRB(0, 255, 31),  COLOR_GRB(0, 255, 0),   COLOR_GRB(31, 255, 0),  COLOR_GRB(62, 255, 0),  COLOR_GRB(93, 255, 0),
    COLOR_GRB(124, 255, 0), COLOR_GRB(156, 255, 0), COLOR_GRB(187, 255, 0), COLOR_GRB(218, 255, 0), COLOR_GRB(249, 255, 0), COLOR_GRB(255, 228, 0),
    COLOR_GRB(255, 197, 0), COLOR_GRB(255, 166, 0), COLOR_GRB(255, 135, 0), COLOR_GRB(255, 104, 0), COLOR_GRB(255, 72, 0),  COLOR_GRB(255, 41, 0),
    COLOR_GRB(255, 10, 0),  COLOR_GRB(255, 0, 20),  COLOR_GRB(255, 0, 52),  COLOR_GRB(255, 0, 83),  COLOR_GRB(255, 0, 114), COLOR_GRB(255, 0, 145),
    COLOR_GRB(255, 0, 176), COLOR_GRB(255, 0, 208), COLOR_GRB(255, 0, 239), COLOR_GRB(239, 0, 255), COLOR_GRB(208, 0, 255), COLOR_GRB(176, 0, 255),
    COLOR_GRB(145, 0, 255), COLOR_GRB(114, 0, 255), COLOR_GRB(83, 0, 255),  COLOR_GRB(52, 0, 255),  COLOR_GRB(20, 0, 255),  COLOR_GRB(0, 10, 255),
    COLOR_GRB(0, 41, 255),  COLOR_GRB(0, 72, 255),  COLOR_GRB(0, 104, 255), COLOR_GRB(0, 135, 255), COLOR_GRB(0, 166, 255), COLOR_GRB(0, 197, 255),
    COLOR_GRB(0, 228, 255), COLOR_GRB(0, 255, 249), COLOR_GRB(0, 255, 218), COLOR_GRB(0, 255, 187), COLOR_GRB(0, 255, 156), COLOR_GRB(0, 255, 124),
    COLOR_GRB(0, 255, 93),  COLOR_GRB(0, 255, 62),  COLOR_GRB(0, 255, 31),  COLOR_GRB(0, 255, 0),   COLOR_GRB(31, 255, 0),  COLOR_GRB(62, 255, 0),
    COLOR_GRB(93, 255, 0),  COLOR_GRB(124, 255, 0), COLOR_GRB(156, 255, 0), COLOR_GRB(187, 255, 0), COLOR_GRB(218, 255, 0), COLOR_GRB(249, 255, 0),
    COLOR_GRB(255, 228, 0), COLOR_GRB(255, 197, 0), COLOR_GRB(255, 166, 0), COLOR_GRB(255, 135, 0), COLOR_GRB(255, 104, 0), COLOR_GRB(255, 72, 0),
    COLOR_GRB(255, 41, 0),  COLOR_GRB(255, 10, 0),  COLOR_GRB(255, 0, 20),  COLOR_GRB(255, 0, 52),  COLOR_GRB(255, 0, 83),  COLOR_GRB(255, 0, 114),
    COLOR_GRB(255, 0, 145), COLOR_GRB(255, 0, 176), COLOR_GRB(255, 0, 208), COLOR_GRB(255, 0, 239), COLOR_GRB(239, 0, 255), COLOR_GRB(208, 0, 255),
    COLOR_GRB(176, 0, 255), COLOR_GRB(145, 0, 255), COLOR_GRB(114, 0, 255), COLOR_GRB(83, 0, 255),  COLOR_GRB(52, 0, 255),  COLOR_GRB(20, 0, 255),
    COLOR_GRB(0, 10, 255),  COLOR_GRB(0, 41, 255),  COLOR_GRB(0, 72, 255),  COLOR_GRB(0, 104, 255), COLOR_GRB(0, 135, 255), COLOR_GRB(0, 166, 255),
    COLOR_GRB(0, 197, 255), COLOR_GRB(0, 228, 255), COLOR_GRB(0, 255, 249), COLOR_GRB(0, 255, 218), COLOR_GRB(0, 255, 187), COLOR_GRB(0, 255, 156),
    COLOR_GRB(0, 255, 124), COLOR_GRB(0, 255, 93),  COLOR_GRB(0, 255, 62),  COLOR_GRB(0, 255, 31),  COLOR_GRB(0, 255, 0),   COLOR_GRB(31, 255, 0),
    COLOR_GRB(62, 255, 0),  COLOR_GRB(93, 255, 0),  COLOR_GRB(124, 255, 0), COLOR_GRB(156, 255, 0), COLOR_GRB(187, 255, 0), COLOR_GRB(218, 255, 0),
    COLOR_GRB(249, 255, 0), COLOR_GRB(255, 228, 0), COLOR_GRB(255, 197, 0), COLOR_GRB(255, 166, 0), COLOR_GRB(255, 135, 0), COLOR_GRB(255, 104, 0),
    COLOR_GRB(255, 72, 0),  COLOR_GRB(255, 41, 0),  COLOR_GRB(255, 10, 0),  COLOR_GRB(255, 0, 20),  COLOR_GRB(255, 0, 52),  COLOR_GRB(255, 0, 83),
    COLOR_GRB(255, 0, 114), COLOR_GRB(255, 0, 145), COLOR_GRB(255, 0, 176), COLOR_GRB(255, 0, 208), COLOR_GRB(255, 0, 239), COLOR_GRB(239, 0, 255),
    COLOR_GRB(208, 0, 255), COLOR_GRB(176, 0, 255), COLOR_GRB(145, 0, 255), COLOR_GRB(114, 0, 255), COLOR_GRB(83, 0, 255),  COLOR_GRB(52, 0, 255),
    COLOR_GRB(20, 0, 255),  COLOR_GRB(0, 10, 255),  COLOR_GRB(0, 41, 255),  COLOR_GRB(0, 72, 255),  COLOR_GRB(0, 104, 255), COLOR_GRB(0, 135, 255),
    COLOR_GRB(0, 166, 255), COLOR_GRB(0, 197, 255), COLOR_GRB(0, 228, 255), COLOR_GRB(0, 255, 249), COLOR_GRB(0, 255, 218), COLOR_GRB(0, 255, 187),
    COLOR_GRB(0, 255, 156), COLOR_GRB(0, 255, 124), COLOR_GRB(0, 255, 93),  COLOR_GRB(0, 255, 62),  COLOR_GRB(0, 255, 31),  COLOR_GRB(0, 255, 0),
    COLOR_GRB(31, 255, 0),  COLOR_GRB(62, 255, 0),  COLOR_GRB(93, 255, 0),  COLOR_GRB(124, 255, 0), COLOR_GRB(156, 255, 0), COLOR_GRB(187, 255, 0),
    COLOR_GRB(218, 255, 0), COLOR_GRB(249, 255, 0), COLOR_GRB(255, 228, 0), COLOR_GRB(255, 197, 0), COLOR_GRB(255, 166, 0), COLOR_GRB(255, 135, 0),
    COLOR_GRB(255, 104, 0), COLOR_GRB(255, 72, 0),  COLOR_GRB(255, 41, 0),  COLOR_GRB(255, 10, 0),  COLOR_GRB(255, 0, 20),  COLOR_GRB(255, 0, 52),
    COLOR_GRB(255, 0, 83),  COLOR_GRB(255, 0, 114), COLOR_GRB(255, 0, 145), COLOR_GRB(255, 0, 176), COLOR_GRB(255, 0, 208), COLOR_GRB(255, 0, 239),
    COLOR_GRB(239, 0, 255), COLOR_GRB(208, 0, 255), COLOR_GRB(176, 0, 255), COLOR_GRB(145, 0, 255), COLOR_GRB(114, 0, 255), COLOR_GRB(83, 0, 255),
    COLOR_GRB(52, 0, 255),  COLOR_GRB(20, 0, 255),  COLOR_GRB(0, 10, 255),  COLOR_GRB(0, 41, 255),  COLOR_GRB(0, 72, 255),  COLOR_GRB(0, 104, 255),
    COLOR_GRB(0, 135, 255), COLOR_GRB(0, 166, 255), COLOR_GRB(0, 197, 255), COLOR_GRB(0, 228, 255), COLOR_GRB(0, 255, 249), COLOR_GRB(0, 255, 218),
    COLOR_GRB(0, 255, 187), COLOR_GRB(0, 255, 156), COLOR_GRB(0, 255, 124), COLOR_GRB(0, 255, 93),  COLOR_GRB(0, 255, 62),  COLOR_GRB(0, 255, 31),
    COLOR_GRB(0, 255, 0),   COLOR_GRB(31, 255, 0),  COLOR_GRB(62, 255, 0),  COLOR_GRB(93, 255, 0),  COLOR_GRB(124, 255, 0), COLOR_GRB(156, 255, 0),
    COLOR_GRB(187, 255, 0), COLOR_GRB(218, 255, 0), COLOR_GRB(249, 255, 0), COLOR_GRB(255, 228, 0), COLOR_GRB(255, 197, 0), COLOR_GRB(255, 166, 0),
    COLOR_GRB(255, 135, 0), COLOR_GRB(255, 104, 0), COLOR_GRB(255, 72, 0),  COLOR_GRB(255, 41, 0),  COLOR_GRB(255, 10, 0),  COLOR_GRB(255, 0, 20),
    COLOR_GRB(255, 0, 52),  COLOR_GRB(255, 0, 83),  COLOR_GRB(255, 0, 114), COLOR_GRB(255, 0, 145), COLOR_GRB(255, 0, 176), COLOR_GRB(255, 0, 208),
    COLOR_GRB(255, 0, 239), COLOR_GRB(239, 0, 255), COLOR_GRB(208, 0, 255), COLOR_GRB(176, 0, 255), COLOR_GRB(145, 0, 255), COLOR_GRB(114, 0, 255),
    COLOR_GRB(83, 0, 255),  COLOR_GRB(52, 0, 255),  COLOR_GRB(20, 0, 255),  COLOR_GRB(0, 10, 255),  COLOR_GRB(0, 41, 255),  COLOR_GRB(0, 72, 255),
    COLOR_GRB(0, 104, 255), COLOR_GRB(0, 135, 255), COLOR_GRB(0, 166, 255), COLOR_GRB(0, 197, 255), COLOR_GRB(0, 228, 255), COLOR_GRB(0, 255, 249),
    COLOR_GRB(0, 255, 218), COLOR_GRB(0, 255, 187), COLOR_GRB(0, 255, 156), COLOR_GRB(0, 255, 124), COLOR_GRB(0, 255, 93),  COLOR_GRB(0, 255, 62),
    COLOR_GRB(0, 255, 31),  COLOR_GRB(0, 255, 0),   COLOR_GRB(31, 255, 0),  COLOR_GRB(62, 255, 0),  COLOR_GRB(93, 255, 0),  COLOR_GRB(124, 255, 0),
    COLOR_GRB(156, 255, 0), COLOR_GRB(187, 255, 0), COLOR_GRB(218, 255, 0), COLOR_GRB(249, 255, 0), COLOR_GRB(255, 228, 0), COLOR_GRB(255, 197, 0),
    COLOR_GRB(255, 166, 0), COLOR_GRB(255, 135, 0), COLOR_GRB(255, 104, 0), COLOR_GRB(255, 72, 0),  COLOR_GRB(255, 41, 0),  COLOR_GRB(255, 10, 0),
    COLOR_GRB(255, 0, 20),  COLOR_GRB(255, 0, 52),  COLOR_GRB(255, 0, 83),  COLOR_GRB(255, 0, 114), COLOR_GRB(255, 0, 145), COLOR_GRB(255, 0, 176),
    COLOR_GRB(255, 0, 208), COLOR_GRB(255, 0, 239), COLOR_GRB(239, 0, 255), COLOR_GRB(208, 0, 255), COLOR_GRB(176, 0, 255), COLOR_GRB(145, 0, 255),
    COLOR_GRB(114, 0, 255), COLOR_GRB(83, 0, 255),  COLOR_GRB(52, 0, 255),  COLOR_GRB(20, 0, 255),  COLOR_GRB(0, 10, 255),  COLOR_GRB(0, 41, 255),
    COLOR_GRB(0, 72, 255),  COLOR_GRB(0, 104, 255), COLOR_GRB(0, 135, 255), COLOR_GRB(0, 166, 255), COLOR_GRB(0, 197, 255), COLOR_GRB(0, 228, 255),
    COLOR_GRB(0, 255, 249), COLOR_GRB(0, 255, 218), COLOR_GRB(0, 255, 187), COLOR_GRB(0, 255, 156), COLOR_GRB(0, 255, 124), COLOR_GRB(0, 255, 93),
    COLOR_GRB(0, 255, 62),  COLOR_GRB(0, 255, 31),  COLOR_GRB(0, 255, 0),   COLOR_GRB(31, 255, 0),  COLOR_GRB(62, 255, 0),  COLOR_GRB(93, 255, 0),
    COLOR_GRB(124, 255, 0), COLOR_GRB(156, 255, 0), COLOR_GRB(187, 255, 0), COLOR_GRB(218, 255, 0), COLOR_GRB(249, 255, 0), COLOR_GRB(255, 228, 0),
    COLOR_GRB(255, 197, 0), COLOR_GRB(255, 166, 0), COLOR_GRB(255, 135, 0), COLOR_GRB(255, 104, 0), COLOR_GRB(255, 72, 0),  COLOR_GRB(255, 41, 0),
    COLOR_GRB(255, 10, 0),  COLOR_GRB(255, 0, 20),  COLOR_GRB(255, 0, 52),  COLOR_GRB(255, 0, 83),  COLOR_GRB(255, 0, 114), COLOR_GRB(255, 0, 145),
    COLOR_GRB(255, 0, 176), COLOR_GRB(255, 0, 208), COLOR_GRB(255, 0, 239), COLOR_GRB(239, 0, 255), COLOR_GRB(208, 0, 255), COLOR_GRB(176, 0, 255),
    COLOR_GRB(145, 0, 255), COLOR_GRB(114, 0, 255), COLOR_GRB(83, 0, 255),  COLOR_GRB(52, 0, 255),  COLOR_GRB(20, 0, 255),  COLOR_GRB(0, 10, 255),
    COLOR_GRB(0, 41, 255),  COLOR_GRB(0, 72, 255),  COLOR_GRB(0, 104, 255), COLOR_GRB(0, 135, 255), COLOR_GRB(0, 166, 255), COLOR_GRB(0, 197, 255),
    COLOR_GRB(0, 228, 255), COLOR_GRB(0, 255, 249), COLOR_GRB(0, 255, 218), COLOR_GRB(0, 255, 187), COLOR_GRB(0, 255, 156), COLOR_GRB(0, 255, 124),
    COLOR_GRB(0, 255, 93),  COLOR_GRB(0, 255, 62),  COLOR_GRB(0, 255, 31),  COLOR_GRB(0, 255, 0),   COLOR_GRB(31, 255, 0),  COLOR_GRB(62, 255, 0),
    COLOR_GRB(93, 255, 0),  COLOR_GRB(124, 255, 0), COLOR_GRB(156, 255, 0), COLOR_GRB(187, 255, 0), COLOR_GRB(218, 255, 0), COLOR_GRB(249, 255, 0),
    COLOR_GRB(255, 228, 0), COLOR_GRB(255, 197, 0), COLOR_GRB(255, 166, 0), COLOR_GRB(255, 135, 0), COLOR_GRB(255, 104, 0), COLOR_GRB(255, 72, 0),
    COLOR_GRB(255, 41, 0),  COLOR_GRB(255, 10, 0),  COLOR_GRB(255, 0, 20),  COLOR_GRB(255, 0, 52),  COLOR_GRB(255, 0, 83),  COLOR_GRB(255, 0, 114),
    COLOR_GRB(255, 0, 145), COLOR_GRB(255, 0, 176), COLOR_GRB(255, 0, 208), COLOR_GRB(255, 0, 239), COLOR_GRB(239, 0, 255), COLOR_GRB(208, 0, 255),
    COLOR_GRB(176, 0, 255), COLOR_GRB(145, 0, 255), COLOR_GRB(114, 0, 255), COLOR_GRB(83, 0, 255),  COLOR_GRB(52, 0, 255),  COLOR_GRB(20, 0, 255),
    COLOR_GRB(0, 10, 255),  COLOR_GRB(0, 41, 255),  COLOR_GRB(0, 72, 255),  COLOR_GRB(0, 104, 255), COLOR_GRB(0, 135, 255), COLOR_GRB(0, 166, 255),
    COLOR_GRB(0, 197, 255), COLOR_GRB(0, 228, 255), COLOR_GRB(0, 255, 249), COLOR_GRB(0, 255, 218), COLOR_GRB(0, 255, 187), COLOR_GRB(0, 255, 156),
    COLOR_GRB(0, 255, 124), COLOR_GRB(0, 255, 93),  COLOR_GRB(0, 255, 62),  COLOR_GRB(0, 255, 31),
};

uint64_t start;
uint64_t end;
color_t* ptr[23];

void app_main() {
    LedDriver driver;
    driver.config(config, 23);
    driver.clear_frame();

    vTaskDelay(pdMS_TO_TICKS(1000));
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 23; j++) {
            ptr[j] = &test[i + j];
        }
        start = esp_timer_get_time();
        driver.write((const color_t**)ptr);
        end = esp_timer_get_time();
        printf("timer: %lld\n", end - start);
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    driver.clear_frame();

    vTaskDelay(pdMS_TO_TICKS(100));
}
