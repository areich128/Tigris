#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "i2c_funcs.h"
#include "esp_log.h"

#define BMP_ADDR 0x77

static const char *TAG = "BMP";

uint8_t BMP_CHIP_ID = 0x00;
uint8_t BMP_ERR_REG = 0x02;
uint8_t BMP_STATUS = 0x03;
uint8_t BMP_CMD = 0x7E;
uint8_t BMP_EVENT = 0x10;
uint8_t BMP_PWR_CTRL = 0x1B;

uint8_t BMP_P1 = 0x04;
uint8_t BMP_P2 = 0x05;
uint8_t BMP_P3 = 0x06;

uint8_t BMP_T1 = 0x07;
uint8_t BMP_T2 = 0x08;
uint8_t BMP_T3 = 0x09;

#endif