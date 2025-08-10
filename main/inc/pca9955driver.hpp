#pragma once

extern "C" {
#include "pca9955.h"
}

#define IREFALL_addr 0x45
#define OF_MAXIMUM_BRIGHTNESS 255

class pca9955Driver {
  public:
    pca9955Driver();
    esp_err_t config(const led_config_t config);
    esp_err_t write(const color_t* colors);
    esp_err_t read(const color_t* colors);
    esp_err_t detach();
    esp_err_t wait_done();

    int find(uint8_t addr);
    // find if addr is in pca_addr,
    // if true, return idx,
    // if not, put addr in pca_addr[registered] and new dev in dev_handles[registered]
    // and return registered++;

  private:
    uint8_t addr;
    uint8_t pca_channel;
    int idx;
    i2c_master_bus_handle_t bus_handle;
    i2c_master_dev_handle_t* dev_handle;
};