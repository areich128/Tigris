#include <stdio.h>
#include "driver/i2c.h"
#include "bmp.h"

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
    // Initialize I2C master
    // i2c_master_init();

    // uint8_t sensor_data[2];
    // while (1) {

    //     // Read 2 bytes of data from the sensor
    //     if (i2c_read_sensor(BMP_ADDR, sensor_data, 2) == ESP_OK) {
    //         printf("Sensor Data: %02x %02x\n", sensor_data[0], sensor_data[1]);
    //     } else {
    //         printf("Failed to read from sensor\n");
    //     }
    //     vTaskDelay(1000 / portTICK_RATE_MS);  // Delay 1 second
    // }

    i2c_master_init();
    BMP_startup();

    while (1) {
                
    }

    return;

}