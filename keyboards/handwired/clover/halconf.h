#pragma once

#define HAL_USE_I2C TRUE
#define HAL_USE_SPI TRUE

#define I2C_DRIVER I2CD1
#undef I2C1_SCL_PIN
#define I2C1_SCL_PIN GP27
#undef I2C1_SDA_PIN
#define I2C1_SDA_PIN GP26

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#undef SPI_MISO_PIN
#define SPI_MISO_PIN GP16
#define SPI_MOSI_PIN GP19

#include_next <halconf.h>
