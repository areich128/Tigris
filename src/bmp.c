#include "bmp.h"

const char *TAG = "BMP";

// const uint8_t BMP_CHIP_ID = 0x00;
// const uint8_t BMP_ERR_REG = 0x02;
// const uint8_t BMP_STATUS = 0x03;
// const uint8_t BMP_CMD = 0x7E;
// const uint8_t BMP_EVENT = 0x10;
// const uint8_t BMP_PWR_CTRL = 0x1B;

// const uint8_t BMP_P1 = 0x04;
// const uint8_t BMP_P2 = 0x05;
// const uint8_t BMP_P3 = 0x06;

// const uint8_t BMP_T1 = 0x07;
// const uint8_t BMP_T2 = 0x08;
// const uint8_t BMP_T3 = 0x09;

// setting mode to normal and enabling pressure and data sensors
esp_err_t BMP_set_active(){
    uint8_t ctrl_buff[1] = {0x33};
    
    if (i2c_write_sensor(BMP_ADDR, BMP_PWR_CTRL, ctrl_buff, 1) == ESP_OK){
        ESP_LOGI(TAG, "Pressure and temp sensors enabled, mode set NORMAL.");
    } else {
        ESP_LOGW(TAG, "I2C write to PWR_CTRL failed.");
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t BMP_calibrate(){
    return ESP_OK;
}

esp_err_t BMP_startup(){
    uint8_t sens_status[1] = {0}, bmp_id[1] = {0}, pwr_status[1] = {0};

    i2c_scan();

    // initial I2C read checking
    if (i2c_read_sensor(BMP_ADDR, BMP_CHIP_ID, bmp_id, 1) == ESP_OK){
        ESP_LOGI(TAG, "Initial read successful, chip id %.4x\n", bmp_id[0]);
    } else {
        ESP_LOGE(TAG, "Initial read unsuccessful, read %.4x\n", bmp_id[0]);
        return ESP_FAIL;
    }

    // waiting 0.5sec for power up sequence to complete
    ESP_LOGI(TAG, "LAUNCHING BMP388 DRIVER");
    vTaskDelay(500 / portTICK_PERIOD_MS);
    while (!(sens_status[0] & 0x01)){
        if (i2c_read_sensor(BMP_ADDR, BMP_PWR_CTRL, sens_status, 1) == ESP_OK){
            ESP_LOGI(TAG, "BMP startup successful.");
            ESP_LOGI(TAG, "%.4x", sens_status[0]);
        } else {
            ESP_LOGI(TAG, "BMP startup incomplete.");
            ESP_LOGI(TAG, "%.4x", sens_status[0]);
            BMP_set_active();
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    // reading pwr_status
    if (i2c_read_sensor(BMP_ADDR, BMP_PWR_CTRL, pwr_status, 1) == ESP_OK){
        if ((pwr_status[0] & 0x30) == 0x30 ){
            ESP_LOGI(TAG, "PWR_STATUS: Normal");
        } else if (((pwr_status[0] & 0x10) == 0x10) || ((pwr_status[0] & 0x20) == 0x20)){
            ESP_LOGI(TAG, "PWR_STATUS: Forced");
        } else if ((pwr_status[0] == 0x00)){
            ESP_LOGI(TAG, "PWR_STATUS: Sleep");
        }
    } else {
        ESP_LOGW(TAG, "PWR_STATUS read failed");
        return ESP_FAIL;
    }

    // TO BE DISABLED LATER when stage detection is enabled
    BMP_set_active();

    BMP_calibrate();

    ESP_LOGI(TAG, "BMP startup sequence finished.");
    return ESP_OK;
}

esp_err_t BMP_read(uint8_t *data){

    // CHANGE TO DATA READING REGISTER/BUFFER
    // if (i2c_read_sensor(BMP_ADDR, BMP_CHIP_ID, bmp_id, 1) == ESP_OK){
    //     ESP_LOGI(TAG, "Data read successful", bmp_id[0]);
    // } else {
    //     ESP_LOGE(TAG, "Data read unsuccessful");
    //     return ESP_FAIL;
    // }
    return ESP_OK;
}