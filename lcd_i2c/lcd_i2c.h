#pragma once

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

#define LCD_ROWS 20
#define LCD_COLS 16

typedef struct {
    i2c_inst_t *i2c;
    uint8_t address;
    char buffer[LCD_ROWS][LCD_COLS];
    int cur_row;
    int cur_col;
} i2c_device;

void lcd_clear(i2c_device *lcd);
void lcd_print(i2c_device *lcd, char *text);
void lcd_init(i2c_device *lcd);

static void lcd_clear_row(i2c_device *lcd, int row);
static void lcd_set_cursor(i2c_device *lcd, int line, int position);
static void lcd_send_byte(i2c_device *lcd, uint8_t val, int mode);
static void lcd_toggle_enable(i2c_device *lcd, uint8_t val);
