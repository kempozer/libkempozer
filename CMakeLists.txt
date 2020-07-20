cmake_minimum_required(VERSION 3.17)
project(kempozer VERSION 0.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(SOURCES ${SOURCE_DIR}/kmz_color.c
            ${SOURCE_DIR}/kmz_core.c
            ${SOURCE_DIR}/kmz_draw.c
            ${SOURCE_DIR}/kmz_gd_2x_image_file.c
            ${SOURCE_DIR}/kmz_image.c)

add_library(kempozer SHARED ${SOURCES})
configure_file(kmz_config.h.in ${SOURCE_DIR}/kmz_config.h)

install(TARGETS kempozer DESTINATION lib)
install(FILES ${SOURCE_DIR}/libkempozer.h DESTINATION include)
