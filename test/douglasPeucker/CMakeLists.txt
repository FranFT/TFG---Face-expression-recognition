CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(PROJ_NAME					"douglasPeucker"	)
SET(PROJ_PATH					${CMAKE_SOURCE_DIR}	)
SET(PROJ_OUT_PATH			${CMAKE_BINARY_DIR}	)


# Para compilar la libreria, se añaden los .cpp y .h de esta.
FILE( GLOB_RECURSE PROJ_SOURCES ./main.cpp )

# Se añade el ejecutable y sus dependencias.
PROJECT( ${PROJ_NAME} )
FIND_PACKAGE( OpenCV REQUIRED )
ADD_EXECUTABLE( ${PROJ_NAME} ${PROJ_SOURCES} )
TARGET_LINK_LIBRARIES( ${PROJ_NAME} ${OpenCV_LIBS} )
