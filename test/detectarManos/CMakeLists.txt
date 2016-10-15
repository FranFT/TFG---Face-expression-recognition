CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(PROJ_NAME					"Prueba"	)
SET(PROJ_PATH					${CMAKE_SOURCE_DIR}	)
SET(PROJ_OUT_PATH			${CMAKE_BINARY_DIR}	)
#SET(PROJ_LIBRARIES		"../librerias/libstasm.a"	)
SET(PROJ_INCLUDES			"./stasm4.1.0/stasm" )
#SET(PROJ_LIBSTASM			"stasm_library")

#FILE( GLOB_RECURSE PROJ_SOURCES src/*.cpp )
#FILE( GLOB_RECURSE PROJ_HEADERS inc/*.h )

# Para compilar la libreria, se añaden los .cpp y .h de esta.
FILE( GLOB_RECURSE PROJ_SOURCES ./main.cpp ./stasm4.1.0/stasm/*.cpp )
FILE( GLOB_RECURSE PROJ_HEADERS ./stasm4.1.0/stasm/*.h )

# Se añade la localización de la librería estática.
#ADD_LIBRARY( ${PROJ_LIBSTASM} STATIC IMPORTED )
#SET_TARGET_PROPERTIES( ${PROJ_LIBSTASM} PROPERTIES IMPORTED_LOCATION ${PROJ_LIBRARIES} )

PROJECT( ${PROJ_NAME} )
INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )
FIND_PACKAGE( OpenCV REQUIRED )
ADD_EXECUTABLE( ${PROJ_NAME} ${PROJ_SOURCES} )
TARGET_LINK_LIBRARIES( ${PROJ_NAME} ${OpenCV_LIBS} )#${PROJ_LIBSTASM} )




#cmake_minimum_required(VERSION 2.8)
#set(PROJ_INCLUDES	"stasm" )
#file(GLOB_RECURSE PROJ_SOURCES /stasm/*.cpp )
#file(GLOB_RECURSE PROJ_HEADERS /stasm/*.h )
#project( PruebaVid )
#find_package( OpenCV REQUIRED )

# Ejecutables
#include_directories( ${PROJ_INCLUDES} )
#add_executable( main main.cpp ${PROJ_SOURCES} )
#target_link_libraries( main ${OpenCV_LIBS} ) 


#add_executable( ejemplo ejemplo.cpp )
#target_link_libraries( ejemplo ${OpenCV_LIBS} )


#add_executable( detectarCoche detectarCoche.cpp)
#target_link_libraries( detectarCoche ${OpenCV_LIBS} )
