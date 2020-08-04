cmake_minimum_required(VERSION 3.10)
project(kempozer VERSION 0.1.0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

include(cmake/arguments.cmake)
include(cmake/configuration.cmake)

add_library(kempozer SHARED)
target_sources(kempozer PUBLIC ${SOURCES} ${HEADERS})

if (GD_IMAGE_FILE_SUPPORTED)
    include(cmake/gd_image_file_support.cmake)
endif()

install(TARGETS kempozer
    DESTINATION lib)
install(FILES ${API_DIR}/libkempozer.h
    DESTINATION include)
install(FILES ${STD_API}
    DESTINATION include/libkempozer) 

