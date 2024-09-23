#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "i2c_funcs.h"
#include "esp_log.h"

#define BMP_ADDR 0x77

// extern uint8_t BMP_CHIP_ID = 0x00;
// extern uint8_t BMP_ERR_REG = 0x02;
// extern uint8_t BMP_STATUS = 0x03;
// extern uint8_t BMP_CMD = 0x7E;
// extern uint8_t BMP_EVENT = 0x10;
// extern uint8_t BMP_PWR_CTRL = 0x1B;

// extern uint8_t BMP_P1 = 0x04;
// extern uint8_t BMP_P2 = 0x05;
// extern uint8_t BMP_P3 = 0x06;

// extern uint8_t BMP_T1 = 0x07;
// extern uint8_t BMP_T2 = 0x08;
// extern uint8_t BMP_T3 = 0x09;

#define BMP_CHIP_ID 0x00
#define BMP_ERR_REG 0x02
#define BMP_STATUS 0x03
#define BMP_CMD 0x7E
#define BMP_EVENT 0x10
#define BMP_PWR_CTRL 0x1B

#define BMP_P1 = 0x04
#define BMP_P2 = 0x05
#define BMP_P3 = 0x06

#define BMP_T1 = 0x07
#define BMP_T2 = 0x08
#define BMP_T3 = 0x09

esp_err_t BMP_set_active();
esp_err_t BMP_calibrate();
esp_err_t BMP_startup();
esp_err_t BMP_read(uint8_t *data);

#endif