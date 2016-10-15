#! /bin/bash

source ../data/info.sh

###############################################################################
# Descripción: Entrena un modelo para el reconocimiento de manos usando STASM.#
###############################################################################

# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$BUILD_DIR_HANDS
cd ../$BUILD_DIR_HANDS

# Compilo la build de la librería necesaria.
cmake $LIB_DIR_HANDS && make

# Entreno el modelo de puntos de las manos.
./tasm -d $LIB_DIR_HANDS/stasm/MOD_1 $LIB_DIR_HANDS/tasm/shapes/$HANDS_SHAPEFILE

# Vuelvo a compilar los ejecutables con el nuevo modelo.
make
