#pragma once

#include "stdint.h"
#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_SDA_IO 21

#define MAX_CHANNEL_NUM 50
#define MAX_PCA9955_NUM 10

typedef struct {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
} color_t;

typedef enum {
    LED_TYPE_OF = 0,
    LED_TYPE_STRIP = 1,
} LED_TYPE_t;

typedef struct {
    LED_TYPE_t type;
    uint8_t led_count;
    uint8_t gpio_or_addr;
    uint8_t pca_channel;
} led_config_t;
