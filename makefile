CC 			= clang
FLAGS		=

SOURCEDIR	= src
BUILDDIR	= build
VPATH		= ${SOURCEDIR}

OBJECTS = ${BUILDDIR}/kmz_geometry.o ${BUILDDIR}/kmz_color.o ${BUILDDIR}/kmz_gd_2x_image_file.o ${BUILDDIR}/kmz_core.o ${BUILDDIR}/kmz_transform.o

all		: dir ${BUILDDIR}/libkempozer
dir		:
	mkdir -p ${BUILDDIR}
	
${BUILDDIR}/libkempozer	: ${OBJECTS}
	${CC} -shared -fpic ${OBJECTS} -o $@ -Wpedantic -lm

${OBJECTS}	: ${BUILDDIR}/%.o	: ${SOURCEDIR}/%.c
	${CC} ${FLAGS} -c $< -o $@ -Wpedantic
	
${BUILDDIR}/kmz_geometry.o																						:
${BUILDDIR}/kmz_color.o ${BUILDDIR}/kmz_gd_2x_image_file.o ${BUILDDIR}/kmz_core.o ${BUILDDIR}/kmz_transform.o	: ${SOURCEDIR}/kmz_geometry.h
${BUILDDIR}/kmz_gd_2x_image_file.o ${BUILDDIR}/kmz_core.o ${BUILDDIR}/kmz_transform								: ${SOURCEDIR}/kmz_color.h
${BUILDDIR}/kmz_core.o																							: ${SOURCEDIR}/kmz_gd_2x_image_file.h
${BUILDDIR}/kmz_transform.o																						: ${SOURCEDIR}/kmz_core.h

.PHONY	: clean
clean	:
	-rm ${OBJECTS}
