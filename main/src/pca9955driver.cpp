#include "pca9955driver.hpp"
#include "esp_log.h"
#include "esp_timer.h"

static const char* TAG = "pca9955driver.cpp";
static uint8_t cmd[4];
static uint8_t pca_addr[MAX_PCA9955_NUM];
static uint8_t use_count[MAX_PCA9955_NUM] = {0};
static i2c_master_dev_handle_t dev_handles[MAX_PCA9955_NUM];
static int registered = 0;

// 1xxxxxxx: auto increment
static const uint8_t PWM_addr[5] = {0x88, 0x8B, 0x8E, 0x91, 0x94};

pca9955Driver::pca9955Driver() {}

esp_err_t pca9955Driver::config(const led_config_t config) {
    pca_channel = config.pca_channel;
    addr = config.gpio_or_addr;
    i2c_master_get_bus_handle(I2C_NUM_0, &bus_handle);
    idx = find(addr);
    use_count[idx]++;
    dev_handle = &dev_handles[idx];
    return ESP_OK;
}

esp_err_t pca9955Driver::write(const color_t* colors) {
    cmd[0] = PWM_addr[pca_channel];
    cmd[1] = colors[0].red;
    cmd[2] = colors[0].green;
    cmd[3] = colors[0].blue;
    i2c_master_transmit(*dev_handle, cmd, sizeof(uint8_t) * 4, -1);
    return ESP_OK;
}

esp_err_t pca9955Driver::read(const color_t* colors) {
    uint8_t cmd[] = {PWM_addr[pca_channel], colors[0].red, colors[0].green, colors[0].blue};
    i2c_master_receive(*dev_handle, cmd, sizeof(cmd), -1);
    i2c_master_bus_wait_all_done(bus_handle, -1);
    return ESP_OK;
}

esp_err_t pca9955Driver::detach() {
    if(idx != -1 && --use_count[idx] == 0) {
        registered--;
        printf("remove %d registered %d \n", idx, registered);
        i2c_master_bus_rm_device(dev_handles[idx]);
        idx = -1;
    }
    return ESP_OK;
}

esp_err_t pca9955Driver::wait_done() {
    return ESP_OK;
}

int pca9955Driver::find(uint8_t addr) {
    for(int i = 0; i < MAX_PCA9955_NUM; i++) {
        if(addr == pca_addr[i]) {
            return i;
        }
    }
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = addr,
        .scl_speed_hz = 100000,
    };
    pca_addr[registered] = addr;
    i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handles[registered]);
    cmd[0] = IREFALL_addr;
    cmd[1] = (uint8_t)OF_MAXIMUM_BRIGHTNESS;
    i2c_master_transmit(dev_handles[registered], cmd, sizeof(uint8_t) * 2, -1);
    return registered++;
}