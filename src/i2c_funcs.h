#ifndef I2C_FUNCS_H
#define I2C_FUNCS_H

#include <stdio.h>
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"

#define I2C_MASTER_SCL_IO    22    // SCL pin
#define I2C_MASTER_SDA_IO    21    // SDA pin
#define I2C_MASTER_NUM       I2C_NUM_0   // I2C port number
#define I2C_MASTER_FREQ_HZ   100000      // I2C frequency
#define I2C_MASTER_TX_BUF_DISABLE   0    // I2C master does not need buffer
#define I2C_MASTER_RX_BUF_DISABLE   0    // I2C master does not need buffer
#define I2C_MASTER_TIMEOUT_MS 1000 // i2c timeout 1 second

#endif