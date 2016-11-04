#! /bin/bash

source ../data/info.sh

#################################################################################
# Descripción: 
#################################################################################

# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$SIMPLIFICACION_STASM_BUILD_DIR
cd ../$SIMPLIFICACION_STASM_BUILD_DIR

# Compilo la aplicación.
cmake $SIMPLIFICACION_STASM_SOURCE_DIR && make
