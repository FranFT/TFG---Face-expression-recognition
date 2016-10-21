#! /bin/bash

source ../data/info.sh

#####################################################################
# Descripción: Genera la aplicación para el reconocimiento de manos.#
#####################################################################

# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$DETECTAR_COCHES_BUILD_DIR
cd ../$DETECTAR_COCHES_BUILD_DIR

# Compilo la aplicación.
cmake $DETECTAR_COCHES_SOURCE_DIR && make
