cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED ENV{IDF_PATH})
    message(FATAL_ERROR "Open an ESP-IDF terminal or run the ESP-IDF export script first.")
endif()

include("$ENV{IDF_PATH}/tools/cmake/project.cmake")
project(cold_guard_main_controller)
