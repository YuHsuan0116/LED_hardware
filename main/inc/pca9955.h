#ifndef PCA9955_H
#define PCA9955_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include "driver/i2c_master.h"
#include "esp_check.h"
#include "esp_log.h"

#define IREFALL 0x45    //iref all register address
#define MAXIMUM_BRIGHTNESS 63   // from 0 to 255, avoid LED from burning

esp_err_t i2c_bus_init(int SCL_GPIO, int SDA_GPIO, i2c_master_bus_handle_t* ret_i2c_bus);

#ifdef __cplusplus
}
#endif

#endif