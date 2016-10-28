#! /bin/bash

source ../data/info.sh

################################################################
# Descripción: Compila un ejemplo de uso de la libreria libSVM #
# haciendo uso de iris dataset.                                #
################################################################

# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$IRIS_LIBSVM_BUILD_DIR
cd ../$IRIS_LIBSVM_BUILD_DIR

# Compilo la aplicación.
cmake $IRIS_LIBSVM_SOURCE_DIR && make
