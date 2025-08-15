
# LEDDriver Component for ESP-IDF

This component provides a unified LED control framework for ESP32 using both:
- **WS2812 (RGB LED strip via RMT)**
- **PCA9955B (16-channel constant current LED driver via I2C)**

It wraps the low-level drivers into easy-to-use object-oriented interfaces and supports multiple channels with different LED types under a common `LedDriver` class.

---

## 📦 Component Structure

```
components/
└── LedDriver/
    ├── inc/                   # Public headers (included by other components)
    │   ├── config.h                # Common configuration & type definitions
    │   ├── channelhandle.hpp      # Abstract per-channel LED driver logic
    │   ├── pca9955.h              # Low-level PCA9955B control (C)
    │   ├── pca9955driver.hpp      # C++ wrapper for PCA9955B control
    │   ├── ws2812.h               # Low-level WS2812 control (C, with IRAM)
    │   ├── ws2812driver.hpp      # C++ wrapper for WS2812 LED driver
    │   └── LedDriver.hpp         # Unified LED driver for multiple channels
    ├── src/                   # Implementation source files
    │   ├── channelhandle.cpp      # Manages individual LED channels (wrapper)
    │   ├── pca9955.c              # Raw I2C control of PCA9955B (register-level)
    │   ├── pca9955driver.cpp      # PCA9955B driver logic and handle management
    │   ├── ws2812.c               # WS2812 RMT encoder implementation
    │   ├── ws2812driver.cpp       # WS2812 LED driver logic using RMT
    │   └── LedDriver.cpp          # Controls all LED channels at once
    └── CMakeLists.txt         # CMake config for registering this component
```

---

## 🚀 Features

- Unified LED driver with automatic channel assignment
- Supports both WS2812 and PCA9955 simultaneously
- Memory-safe `write()`, `reset()`, and `clear_frame()` operations
- Easy integration as ESP-IDF component
- Object-oriented C++ driver design

---

## 🧩 Usage Example

```cpp
#include "LedDriver.hpp"

LedDriver driver;

void app_main() {
    led_config_t configs[2] = {
        {.type = LED_TYPE_STRIP, .led_count = 8, .gpio_or_addr = 4},
        {.type = LED_TYPE_OF, .led_count = 1, .gpio_or_addr = 0x5C, .pca_channel = 0},
    };
    driver.config(configs, 2);

    color_t frame0[8] = {
        {.green = 0, .red = 10, .blue = 0},
        {.green = 0, .red = 10, .blue = 0},
        {.green = 0, .red = 10, .blue = 0},
        {.green = 0, .red = 10, .blue = 0},
        {.green = 0, .red = 10, .blue = 0},
        {.green = 0, .red = 10, .blue = 0},
        {.green = 0, .red = 10, .blue = 0},
        {.green = 0, .red = 10, .blue = 0},
    };
    color_t frame1[1] = {{.green = 10, .red = 0, .blue = 0}};
    const color_t* frame[] = {frame0, frame1};

    while(1) {
        driver.write(frame);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
```

---

## ⚠️ Notes

- `config()` must be called before any `write()` or `clear_frame()`.
- For PCA9955:
  - I2C address is provided in `gpio_or_addr`
  - `pca_channel` must be specified
- `i2c_bus_init()` is called automatically
- `ws2812` uses RMT encoder with IRAM execution to improve ISR performance

---

## 📄 CMake Integration

In your project-level `CMakeLists.txt`:

```cmake
set(EXTRA_COMPONENT_DIRS components/LedDriver)
```


---

## 📚 Reference

- [ESP-IDF I2C API](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/i2c.html)
- [ESP-IDF RMT API](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/rmt.html)
- PCA9955B Datasheet
- WS2812 Timing Specification

---


