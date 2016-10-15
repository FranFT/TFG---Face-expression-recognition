CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(PROJ_NAME					"detectarManos"	)
SET(PROJ_PATH					${CMAKE_SOURCE_DIR}	)
SET(PROJ_OUT_PATH			${CMAKE_BINARY_DIR}	)
SET(PROJ_INCLUDES			"../../lib/STASM_hands/stasm" )

# Para compilar la libreria, se añaden los .cpp y .h de esta.
FILE( GLOB_RECURSE PROJ_SOURCES main.cpp ../../lib/STASM_hands/stasm/*.cpp )
FILE( GLOB_RECURSE PROJ_HEADERS ../../lib/STASM_hands/stasm/*.h )

# Genero el ejecutable.
PROJECT( ${PROJ_NAME} )
INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )
FIND_PACKAGE( OpenCV REQUIRED )
ADD_EXECUTABLE( ${PROJ_NAME} ${PROJ_SOURCES} )
TARGET_LINK_LIBRARIES( ${PROJ_NAME} ${OpenCV_LIBS} )
