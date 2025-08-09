#include "pca9955driver.hpp"
#include "esp_timer.h"

static const char* TAG = "pca9955driver.cpp";
static uint8_t cmd[4];

// 1xxxxxxx: auto increment
static const uint8_t PWM_addr[5] = {0x88, 0x8B, 0x8E, 0x91, 0x94};

pca9955Driver::pca9955Driver() {
    i2c_activate = false;
}

esp_err_t pca9955Driver::config(const led_config_t config) {
    pca_channel = config.pca_channel;
    addr = config.gpio_or_addr;
    i2c_activate = true;
    i2c_master_get_bus_handle(I2C_NUM_0, &bus_handle);
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = addr,
        .scl_speed_hz = 100000,
    };
    i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle);
    cmd[0] = IREFALL_addr;
    cmd[1] = (uint8_t)OF_MAXIMUM_BRIGHTNESS;
    // uint8_t cmd[] = {IREFALL_addr, (uint8_t)OF_MAXIMUM_BRIGHTNESS};
    i2c_master_transmit(dev_handle, cmd, sizeof(uint8_t) * 2, -1);
    return ESP_OK;
}

esp_err_t pca9955Driver::write(const color_t* colors) {
    cmd[0] = PWM_addr[pca_channel];
    cmd[1] = colors[0].red;
    cmd[2] = colors[0].green;
    cmd[3] = colors[0].blue;
    // uint8_t cmd[] = {PWM_addr[pca_channel], colors[0].red, colors[0].green, colors[0].blue};
    // uint64_t start = esp_timer_get_time();
    i2c_master_transmit(dev_handle, cmd, sizeof(uint8_t) * 4, -1);
    // uint64_t end = esp_timer_get_time();
    // printf("timer: %lld\n", end - start);
    // i2c_master_bus_wait_all_done(bus_handle, -1);
    return ESP_OK;
}

esp_err_t pca9955Driver::detach() {
    if(i2c_activate) {
        i2c_master_bus_rm_device(dev_handle);
        i2c_activate = false;
    }
    return ESP_OK;
}

esp_err_t pca9955Driver::wait_done() {
    return ESP_OK;
}