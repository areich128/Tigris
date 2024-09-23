#include "i2c_funcs.h"

// Function to initialize I2C master
void i2c_master_init() {
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;

    // Apply the configuration
    esp_err_t err = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (err != ESP_OK) {
        ESP_LOGE("I2C", "I2C parameter config failed: %s", esp_err_to_name(err));
        return;
    }

    // Install the driver
    err = i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    if (err != ESP_OK) {
        ESP_LOGE("I2C", "I2C driver initialization failed: %s", esp_err_to_name(err));
    } else {
        ESP_LOGI("I2C", "I2C driver installed successfully");
    }
}

// Function to read data from the sensor
esp_err_t i2c_read_sensor(uint8_t sensor_addr, uint8_t sensor_register, uint8_t *data, size_t length) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (sensor_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, sensor_register, true);
    i2c_master_start(cmd); 
    i2c_master_write_byte(cmd, (sensor_addr << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, length, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    
    return ret;
}

esp_err_t i2c_write_sensor(uint8_t sensor_addr, uint8_t reg_addr, uint8_t* data, size_t data_len) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (sensor_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);  // Write register address
    i2c_master_write(cmd, data, data_len, true); // Write data
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

void i2c_scan() {
    printf("Scanning...\n");
    for (uint8_t addr = 1; addr < 127; addr++) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);
        esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);

        if (ret == ESP_OK) {
            printf("Found device at address 0x%02X\n", addr);
        }
    }
    printf("Scan done.\n");
}