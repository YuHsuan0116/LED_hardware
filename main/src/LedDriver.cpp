#include "LedDriver.hpp"
#include "esp_timer.h"

const static color_t blank[127] = {{
    .green = 0,
    .red = 0,
    .blue = 0,
}};

ChannelHandle LedDriver::channel_handle[MAX_CHANNEL_NUM];

LedDriver::LedDriver() {
    i2c_bus_init(I2C_MASTER_SCL_IO, I2C_MASTER_SDA_IO, &bus_handle);
    ch_num = -1;
    bus_handle = NULL;
}

LedDriver::~LedDriver() {
    // clear_frame();
    // reset();
    // i2c_del_master_bus(bus_handle);
}

esp_err_t LedDriver::config(const led_config_t* configs, const int _ch_num) {
    ch_num = _ch_num;
    for(int i = 0; i < ch_num; i++) {
        channel_handle[i].config(configs[i]);
    }
    clear_frame();
    return ESP_OK;
}

esp_err_t LedDriver::write(const color_t** frame) {
    for(int i = 0; i < ch_num; i++) {
        channel_handle[i].write(frame[i]);
    }
    wait_all_done();
    return ESP_OK;
}

esp_err_t LedDriver::part_test(const int ch_idx, const color_t* colors) {
    channel_handle[ch_idx].write(colors);
    channel_handle[ch_idx].wait_done();
    return ESP_OK;
}

esp_err_t LedDriver::reset() {
    for(int i = 0; i < ch_num; i++) {
        channel_handle[i].detach();
    }
    return ESP_OK;
}

esp_err_t LedDriver::clear_frame() {
    for(int i = 0; i < ch_num; i++) {
        channel_handle[i].write(blank);
    }
    wait_all_done();
    return ESP_OK;
}

esp_err_t LedDriver::wait_all_done() {
    for(int i = 0; i < ch_num; i++) {
        channel_handle[i].wait_done();
    }
    return ESP_OK;
}