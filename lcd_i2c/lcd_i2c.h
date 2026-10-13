#pragma once

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

typedef struct {
    i2c_inst_t *i2c;
    uint8_t address;
} i2c_device;

void lcd_print(i2c_device *lcd, char *text);
void lcd_init(i2c_device *lcd);
