#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define I2C_ADDR 0x27
#define READ 1
#define WRITE 0

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



    return 0;
}

