#include "channelhandle.hpp"

esp_err_t ChannelHandle::config(const led_config_t config) {
    type = config.type;
    if(type == LED_TYPE_STRIP) {
        return ws2812.config(config);
    }
    if(type == LED_TYPE_OF) {
        return pca9955.config(config);
    }
    return ESP_FAIL;
}

esp_err_t ChannelHandle::write(const color_t* colors) {
    if(type == LED_TYPE_STRIP) {
        return ws2812.write(colors);
    }
    if(type == LED_TYPE_OF) {
        return pca9955.write(colors);
    }
    return ESP_FAIL;
}

esp_err_t ChannelHandle::detach() {
    if(type == LED_TYPE_STRIP) {
        return ws2812.detach();
    }
    if(type == LED_TYPE_OF) {
        return ESP_OK;
        // return pca9955.detach();
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