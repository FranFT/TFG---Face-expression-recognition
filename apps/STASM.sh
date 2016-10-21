#! /bin/bash

source ../data/info.sh

######################################################
# Descripción: Compila la libreria STASM por defecto.#
######################################################

# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$BUILD_DIR_STASM
cd ../$BUILD_DIR_STASM

# Compilo la build de la librería necesaria.
cmake $LIB_DIR_STASM && make
