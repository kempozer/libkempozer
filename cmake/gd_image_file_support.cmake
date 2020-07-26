set(GD_IMAGE_FILE_SOURCES ${SOURCE_DIR}/kmz_gd_2x_image_file.c)
set(GD_IMAGE_FILE_HEADERS ${SOURCE_DIR}/kmz_gd_2x_image_file.h)

target_sources(kempozer PUBLIC ${GD_IMAGE_FILE_SOURCES} ${GD_IMAGE_FILE_HEADERS})
install(FILES ${API_DIR}/libkempozer/gdfile.h
    DESTINATION include/libkempozer)
