# 1. Versione minima di CMake richiesta
cmake_minimum_required(VERSION 3.12)

# 2. Includi il file di importazione dell'SDK tramite la variabile d'ambiente
include(pico_sdk_import.cmake)

# 3. Nome del progetto e standard C/C++
project(rpp-lcd C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 4. Inizializza l'SDK del Pico
pico_sdk_init()

# 5. Dichiara il file eseguibile e il sorgente (es. main.c)
add_executable(rpp-lcd
    main.c
)

# 6. Collega le librerie standard dell'SDK (GPIO, temporizzazione, ecc.)
target_link_libraries(rpp-lcd 
    pico_stdlib
    hardware_i2c
)

# 7. Abilita la generazione dei file binari finali (es. UF2 per il Pico)
pico_add_extra_outputs(rpp-lcd)

