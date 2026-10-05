#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 0x8
#define ENABLE_PIN 0x4

void lcd_toggle_e(i2c_inst_t *i2c, uint8_t value) {
    sleep_us(600);
    i2c_write_byte(value | ENABLE_PIN);
    sleep_us(600);
    i2c_write_byte(value & ~ENABLE_PIN);
    sleep_us(600);
}

void lcd_write(i2c_inst_t *i2c, uint8_t value, int mode) {
    uint8_t hi = mode | (value & 0xF0) | BACKLIGHT;
    uint8_t lo = mode | ((value << 4) & 0xF0) | BACKLIGHT;

    i2c_write_blocking(i2c, I2C_ADDR, hi, 1, false); 
    lcd_toggle_e(i2c, hi);
    i2c_write_blocking(i2c, I2C_ADDR, lo, 1, false); 
    lcd_toggle_e(i2c, lo);
} 

void lcd_init(i2c_inst_t *i2c) {
    lcd_write(i2c, 0x3, 0);
    lcd_write(i2c, 0x3, 0);
    lcd_write(i2c, 0x3, 0);
    lcd_write(i2c, 0x2, 0);     // set modalità 4 bit
    lcd_write(i2c, 0x8, 0);

}

int main() {
    // inizializzo il modulo i2c0 (master di default) settando il baudrate a 100kHz
    i2c_init(i2c_default, 100 * 1000);
    
    // setto la funzione i2c nei pin sda e sdl
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    char messaggio[] = "Hello world!";

    // https://www.ti.com/lit/ds/symlink/pcf8574.pdf

    lcd_init(i2c_default);

    return 0;
}

