#include "bmp.h"

// setting mode to normal and enabling pressure and data sensors
static esp_err_t BMP_set_active(){
    uint8_t ctrl_buff[1] = {0x33};
    
    if (i2c_write_sensor(BMP_ADDR, BMP_PWR_CTRL, ctrl_buff, 1) == ESP_OK){
        ESP_LOGI(TAG, "Pressure and temp sensors enabled, mode set NORMAL.");
    } else {
        ESP_LOGW(TAG, "I2C write to PWR_CTRL failed.");
        return ESP_FAIL;
    }

    return ESP_OK;
}

static esp_err_t BMP_calibrate(){
    return ESP_OK;
}

static esp_err_t BMP_startup(){
    uint8_t sens_status[1] = {0}, bmp_id[1] = {0}, pwr_status[1] = {0};

    // waiting 0.5sec for power up sequence to complete
    ESP_LOGI(TAG, "LAUNCHING BMP388 DRIVER");
    vTaskDelay(500 / portTICK_PERIOD_MS);
    while (!(sens_status[0] & 0x01)){
        if (i2c_read_sensor(BMP_ADDR, BMP_EVENT, sens_status, 1) == ESP_OK){
            ESP_LOGI(TAG, "BMP startup successful.");
        } else {
            ESP_LOGI(TAG, "BMP startup incomplete.");
        }
    }

    // initial I2C read checking
    if (i2c_read_sensor(BMP_ADDR, BMP_CHIP_ID, bmp_id, 1) == ESP_OK){
        ESP_LOGI(TAG, "Initial read successful, chip id %d\n", bmp_id[0]);
    } else {
        ESP_LOGE(TAG, "Initial read unsuccessful");
        return ESP_FAIL;
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

static esp_err_t BMP_read(uint8_t *data){

    // CHANGE TO DATA READING REGISTER/BUFFER
    // if (i2c_read_sensor(BMP_ADDR, BMP_CHIP_ID, bmp_id, 1) == ESP_OK){
    //     ESP_LOGI(TAG, "Data read successful", bmp_id[0]);
    // } else {
    //     ESP_LOGE(TAG, "Data read unsuccessful");
    //     return ESP_FAIL;
    // }
    return ESP_OK;
}