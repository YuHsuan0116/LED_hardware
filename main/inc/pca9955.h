#pragma once

#include <stdint.h>
#include "driver/i2c_master.h"
#include "esp_check.h"
#include "esp_log.h"

esp_err_t i2c_bus_init(int SCL_GPIO, int SDA_GPIO, i2c_master_bus_handle_t* ret_i2c_bus);