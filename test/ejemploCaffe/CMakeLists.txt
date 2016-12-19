CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(PROJ_NAME					"ejemploCaffe"	)
SET(PROJ_PATH					${CMAKE_SOURCE_DIR}	)
SET(PROJ_OUT_PATH			${CMAKE_BINARY_DIR}	)

# Caffe and CUDA files path
SET(Caffe_INCLUDE_DIRS "/usr/local/caffe/include/;/usr/local/caffe/;/usr/local/cuda-8.0/include")
SET(Caffe_LIBRARIES "/usr/local/caffe/build/lib/libcaffe.so")

# Genero el ejecutable.
PROJECT( ${PROJ_NAME} )
FIND_PACKAGE( OpenCV REQUIRED )
FIND_PACKAGE(Boost 1.60.0 COMPONENTS filesystem system REQUIRED)
INCLUDE_DIRECTORIES( ${Caffe_INCLUDE_DIRS} )
ADD_EXECUTABLE( ${PROJ_NAME} main.cpp )
TARGET_LINK_LIBRARIES( ${PROJ_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES} ${Caffe_LIBRARIES})

### Si se obtiene un error al compilar de "caffe/proto/caffe.pb.h: No such file or directory"
### hacer lo siguiente:
# ** In the directory you installed Caffe to **
# protoc src/caffe/proto/caffe.proto --cpp_out=.
# mkdir include/caffe/proto
# mv src/caffe/proto/caffe.pb.h include/caffe/proto
