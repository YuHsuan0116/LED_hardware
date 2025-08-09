#pragma once

#include "pca9955driver.hpp"
#include "ws2812driver.hpp"

class ChannelHandle {
  public:
    esp_err_t config(const led_config_t config);
    esp_err_t write(const color_t* colors);
    esp_err_t write_verify(const color_t* colors);
    esp_err_t detach();
    esp_err_t wait_done();

  private:
    LED_TYPE_t type;
    pca9955Driver pca9955;
    ws2812Driver ws2812;
    static color_t read_buf[1];
};