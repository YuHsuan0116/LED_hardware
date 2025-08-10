#include "channelhandle.hpp"
#include <string.h>
#include "esp_log.h"

static const char* tag = "channel handle";

esp_err_t ChannelHandle::config(const led_config_t config) {
    type = config.type;
    if(type == LED_TYPE_STRIP) {
        esp_err_t ret = ws2812.config(config);
        if(ret != ESP_OK)
            ESP_LOGE(tag, "channel handle config for ws2812 failed");
        return ret;
    }
    if(type == LED_TYPE_OF) {
        esp_err_t ret = pca9955.config(config);
        if(ret != ESP_OK)
            ESP_LOGE(tag, "channel handle config for ws2812 failed");
        return ret;
    }
    return ESP_FAIL;
}

esp_err_t ChannelHandle::write(const color_t* colors) {
    if(type == LED_TYPE_STRIP) {
        esp_err_t ret = ws2812.write(colors);
        if(ret != ESP_OK)
            ESP_LOGE(tag, "channel handle write for ws2812 failed");
        return ret;
    }
    if(type == LED_TYPE_OF) {
        esp_err_t ret = pca9955.write(colors);
        if(ret != ESP_OK)
            ESP_LOGE(tag, "channel handle write for pca9955 failed");
        return ret;
    }
    return ESP_FAIL;
}

esp_err_t ChannelHandle::write_verify(const color_t* colors) {
    if(type == LED_TYPE_STRIP) {
        return ws2812.write(colors);
    }
    if(type == LED_TYPE_OF) {
        pca9955.write(colors);
        memset(read_buf, 0, sizeof(read_buf));
        pca9955.read(read_buf);
        if(memcmp(&colors[0], &read_buf[0], sizeof(color_t))) {
            return ESP_OK;
        } else {
            return ESP_FAIL;
            ESP_LOGE("pca9955", "verify failure");
        }
    }
    return ESP_FAIL;
}

esp_err_t ChannelHandle::detach() {
    if(type == LED_TYPE_STRIP) {
        return ws2812.detach();
    }
    if(type == LED_TYPE_OF) {
        return pca9955.detach();
    }
    return ESP_FAIL;
}

esp_err_t ChannelHandle::wait_done() {
    if(type == LED_TYPE_STRIP) {
        return ws2812.wait_done();
    }
    if(type == LED_TYPE_OF) {
        return pca9955.wait_done();
    }
    return ESP_FAIL;
}