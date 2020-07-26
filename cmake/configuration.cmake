# Provides an initial configuration for the cmake system such as source and header directories, API path, and source and header files.
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(API_DIR ${PROJECT_SOURCE_DIR}/include)

set(SOURCES ${SOURCE_DIR}/kmz_color.c
    ${SOURCE_DIR}/kmz_core.c
    ${SOURCE_DIR}/kmz_draw.c
    ${SOURCE_DIR}/kmz_geometry.c
    ${SOURCE_DIR}/kmz_image.c
    ${SOURCE_DIR}/kmz_image_file.c
    ${SOURCE_DIR}/kmz_utilities.c)
set(HEADERS ${SOURCE_DIR}/kmz_color.h
    ${SOURCE_DIR}/kmz_core.h
    ${SOURCE_DIR}/kmz_draw.h
    ${SOURCE_DIR}/kmz_geometry.h
    ${SOURCE_DIR}/kmz_image.h
    ${SOURCE_DIR}/kmz_image_file.h
    ${SOURCE_DIR}/kmz_shared.h
    ${SOURCE_DIR}/kmz_utilities.h)
set(STD_API ${API_DIR}/libkempozer/color.h
    ${API_DIR}/libkempozer/colors.h
    ${API_DIR}/libkempozer/draw.h
    ${API_DIR}/libkempozer/geometries.h
    ${API_DIR}/libkempozer/geometry.h
    ${API_DIR}/libkempozer/image.h
    ${API_DIR}/libkempozer/io.h)

include_directories(BEFORE ${API_DIR})
configure_file(kmz_config.h.in ${SOURCE_DIR}/kmz_config.h)
