#pragma once

#include "stdint.h"
#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_SDA_IO 21

#define IREFALL_addr 0x45
#define OF_MAXIMUM_BRIGHTNESS 63
#define STRIP_MAXIMUM_BRIGTNESS 63
#define MAX_CHANNEL_NUM 50

// 1xxxxxxx: auto increment
static const uint8_t PWM_addr[5] = {0x88, 0x8B, 0x8E, 0x91, 0x94};

#define COLOR_GRB(g, r, b) {.green = (g / 4), .red = (r / 4), .blue = (b / 4)}
#define COLOR_RED COLOR_GRB(0, 255, 0)
#define COLOR_GREEN COLOR_GRB(255, 0, 0)
#define COLOR_BLUE COLOR_GRB(0, 0, 255)

struct color_t {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
};

enum LED_TYPE_t : uint8_t {
    LED_TYPE_OF = 0,
    LED_TYPE_STRIP = 1,
};

struct led_config_t {
    LED_TYPE_t type : 1;
    uint8_t led_count : 7;
    uint8_t gpio_or_addr;
    uint8_t pca_channel;
};