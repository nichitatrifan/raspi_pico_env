cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFTW3 REQUIRED fftw3)
include_directories(${FFTW3_INCLUDE_DIRS})

if(FFTW3_FOUND)
    message(STATUS "Included FFTW library: " ${FFTW_INCLUDES})
endif()


pico_sdk_init()

add_executable(blink
    blink.c
    )

add_executable(sound
    analog_sound.c
    )

# pull in common dependencies
target_link_libraries(blink pico_stdlib)
target_link_libraries(sound pico_stdlib hardware_adc)

# enable usb output, disable uart output
pico_enable_stdio_usb(blink 1)
pico_enable_stdio_uart(blink 0)

pico_enable_stdio_usb(sound 1)
pico_enable_stdio_uart(sound 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(blink)
pico_add_extra_outputs(sound)

# get more useful warnings
add_definitions("-Wall")