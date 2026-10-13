# Driver LCD I2C (PCF8574) come libreria INTERFACE, come fa il Pico SDK
add_library(lcd_i2c INTERFACE)

# Il sorgente viene compilato nel target che usa la libreria
target_sources(lcd_i2c INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/lcd_i2c.c
)

# Rende lcd_i2c.h visibile a chi linka la libreria
target_include_directories(lcd_i2c INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Dipendenze del driver
target_link_libraries(lcd_i2c INTERFACE
    pico_stdlib
    hardware_i2c
)
