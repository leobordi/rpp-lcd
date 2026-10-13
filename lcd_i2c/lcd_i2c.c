#include "lcd_i2c.h"

// Commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// Display entry mode
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYLEFT 0x02

// Display and cursor control
#define LCD_BLINKON 0x01
#define LCD_CURSORON 0x02
#define LCD_DISPLAYON 0x04

// Display and cursor shift
#define LCD_MOVERIGHT 0x04
#define LCD_DISPLAYMOVE 0x08

// Function set
#define LCD_5x10DOTS 0x04
#define LCD_2LINE 0x08
#define LCD_8BITMODE 0x10

#define LCD_BACKLIGHT 0x08

#define LCD_ENABLE_BIT 0x04

// Di default l'indirizzo nel bus i2c per questo lcd è 0x27 
#define LCD_I2C_ADDR 0x27

// Modalità di invio dei byte 
#define LCD_CHARACTER  1
#define LCD_COMMAND    0

#define MAX_LINES      2
#define MAX_CHARS      16

void lcd_toggle_enable(i2c_device *lcd, uint8_t val) {
    uint8_t up = val | LCD_ENABLE_BIT;
    uint8_t down = val & ~LCD_ENABLE_BIT;

    sleep_us(600);
    i2c_write_blocking(lcd->i2c, lcd->address, &up, 1, false);
    sleep_us(600);
    i2c_write_blocking(lcd->i2c, lcd->address, &down, 1, false);
    sleep_us(600);
}

void lcd_send_byte(i2c_device *lcd, uint8_t val, int mode) {
    uint8_t hi = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t lo = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_blocking(lcd->i2c, lcd->address, &hi, 1, false);
    lcd_toggle_enable(lcd, hi);
    i2c_write_blocking(lcd->i2c, lcd->address, &lo, 1, false);
    lcd_toggle_enable(lcd, lo);
}

void lcd_clear(i2c_device *lcd) {
    lcd_send_byte(lcd, LCD_CLEARDISPLAY, LCD_COMMAND);
}

void lcd_set_cursor(i2c_device *lcd, int line, int position) {
    int val = (line == 0) ? 0x80 + position : 0xC0 + position;
    lcd_send_byte(lcd, val, LCD_COMMAND);
}

void lcd_init(i2c_device *lcd) {
    /* Sequenza di reset del display */
    lcd_send_byte(lcd, 0x03, LCD_COMMAND);
    lcd_send_byte(lcd, 0x03, LCD_COMMAND);
    lcd_send_byte(lcd, 0x03, LCD_COMMAND);
	/* Passaggio alla modalità 4 bit */
    lcd_send_byte(lcd, 0x02, LCD_COMMAND);

	/* Testo da sx */
    lcd_send_byte(lcd, LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
	/* Modalità 2 righe*/
    lcd_send_byte(lcd, LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
	/* Display acceso */
    lcd_send_byte(lcd, LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
	
    lcd_clear(lcd);
    lcd_set_cursor(lcd, 0, 0);
}

void lcd_print(i2c_device *lcd, char *text) {
    while (*text) {
        lcd_send_byte(lcd, *text++, LCD_CHARACTER);
    }
}
