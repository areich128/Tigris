#include "bmp.h"
#include "i2c_funcs.h"
// #include "driver/i2c.h"

#define LED_PIN GPIO_NUM_2

struct packet {
    uint32_t pressure;
    uint32_t temp;
    uint32_t alt;

    uint32_t accel_x;
    uint32_t accel_y;
    uint32_t accel_z;

    uint32_t mag_x;
    uint32_t mag_y;
    uint32_t mag_z;

    uint32_t gyro_x;
    uint32_t gyro_y;
    uint32_t gyro_z;

    uint32_t quat_x;
    uint32_t quat_y;
    uint32_t quat_z;
    uint32_t quat_w;
};

void app_main() {
    
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;    // Disable interrupt
    io_conf.mode = GPIO_MODE_OUTPUT;          // Set mode to output
    io_conf.pin_bit_mask = (1ULL << LED_PIN); // Select GPIO pin
    io_conf.pull_down_en = 0;                 // Disable pull-down
    io_conf.pull_up_en = 0;                   // Disable pull-up
    gpio_config(&io_conf); 

    i2c_master_init();
    BMP_startup();

    while (1) {
        gpio_set_level(LED_PIN, 1); // Turn on LED
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait for 1 second
        gpio_set_level(LED_PIN, 0); // Turn off LED
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    return;

}