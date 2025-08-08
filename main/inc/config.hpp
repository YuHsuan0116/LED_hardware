#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "stdint.h"
#define I2C_MASTER_SCL_IO 22    //i2c pin for scl
#define I2C_MASTER_SDA_IO 21    //i2c pin for sda

#define COLOR_GRB(g, r, b) {.green = (g / 4), .red = (r / 4), .blue = (b / 4)}  //generate color_t
#define COLOR_RED COLOR_GRB(0, 255, 0)  //common colors
#define COLOR_GREEN COLOR_GRB(255, 0, 0)
#define COLOR_BLUE COLOR_GRB(0, 0, 255)
#define LED_MAXIMUM_BRIGHTNESS 63   //from 0 to 255, avoid LED from burning. define twice in PCA9955.h

struct color_t {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
};

enum Type : uint8_t {
    PCA9955 = 0,
    WS2812 = 1,
};

struct led_config_t {
    Type type : 1;
    uint8_t led_count : 7;
    uint8_t gpio_or_addr;
    uint8_t pca_channel;
};

#endif