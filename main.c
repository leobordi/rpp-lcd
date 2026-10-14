#include "lcd_i2c.h" 

int main() {
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    i2c_device lcd;
    lcd.i2c = i2c_default;
    lcd.address = 0x27;
    
    lcd_init(&lcd);

    lcd_print(&lcd, "Hello\nWorld !!!");

    return 0;
}
