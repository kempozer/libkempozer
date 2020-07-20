cmake_minimum_required(VERSION 3.17)
project(libkempozer VERSION 0.1)

set(SOURCE_DIR src)
set(SOURCES ${SOURCE_DIR}/kmz_color.c
            ${SOURCE_DIR}/kmz_core.c
            ${SOURCE_DIR}/kmz_draw.c
            ${SOURCE_DIR}/kmz_filter.c
            ${SOURCE_DIR}/kmz_gd_2x_image_file.c
            ${SOURCE_DIR}/kmz_image.c)
set(SUPPORT_GD_2X_IMAGE_FILE 0 CACHE BOOL "Whether or not to include GD 2x support. Disabled by default.")
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_library(libkempozer ${SOURCES})
configure_file(kmz_config.h.in kmz_config.h)

target_include_directories(libkempozer PUBLIC ${PROJECT_BINARY_DIR})
