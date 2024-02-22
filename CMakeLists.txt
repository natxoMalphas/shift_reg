# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(shift_reg C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(shift_reg shift_reg.c )

pico_set_program_name(shift_reg "shift_reg")
pico_set_program_version(shift_reg "0.1")

pico_enable_stdio_uart(shift_reg 1)
pico_enable_stdio_usb(shift_reg 0)

# Add the standard library to the build
target_link_libraries(shift_reg
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(shift_reg PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

pico_add_extra_outputs(shift_reg)

