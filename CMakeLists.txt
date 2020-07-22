cmake_minimum_required(VERSION 3.17)
project(kempozer VERSION 0.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(API_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCES ${SOURCE_DIR}/kmz_color.c
    ${SOURCE_DIR}/kmz_core.c
    ${SOURCE_DIR}/kmz_draw.c
    ${SOURCE_DIR}/kmz_gd_2x_image_file.c
    ${SOURCE_DIR}/kmz_geometry.c
    ${SOURCE_DIR}/kmz_image.c)
set(HEADERS ${SOURCE_DIR}/kmz_color.h
    ${SOURCE_DIR}/kmz_core.h
    ${SOURCE_DIR}/kmz_draw.h
    ${SOURCE_DIR}/kmz_gd_2x_image_file.h
    ${SOURCE_DIR}/kmz_geometry.h
    ${SOURCE_DIR}/kmz_image.h
    ${SOURCE_DIR}/kmz_shared.h)

add_library(kempozer SHARED ${SOURCES} ${HEADERS})
configure_file(kmz_config.h.in ${SOURCE_DIR}/kmz_config.h)

install(TARGETS kempozer DESTINATION lib)
install(FILES ${API_DIR}/libkempozer.h DESTINATION include)
install(DIRECTORY ${API_DIR}/libkempozer/ DESTINATION include/libkempozer)
