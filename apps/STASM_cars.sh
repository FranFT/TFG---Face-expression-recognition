#! /bin/bash

source ../data/info.sh

###################################################################################
# Descripción: Entrena un modelo para el reconocimiento de vehículos usando STASM.#
###################################################################################

# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$BUILD_DIR_CARS
cd ../$BUILD_DIR_CARS

# Compilo la build de la librería necesaria.
cmake $LIB_DIR_CARS && make

# Entreno el modelo de puntos de los vehículos.
./tasm -d $LIB_DIR_CARS/stasm/MOD_1 $LIB_DIR_CARS/tasm/shapes/$CARS_SHAPEFILE

# Vuelvo a compilar los ejecutables con el nuevo modelo.
make
