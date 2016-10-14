#! /bin/bash

#########################################################################
# Descripción: Genera la aplicación para el reconocimiento de vehículos.#
#########################################################################

### Variables ###
DIRECTORIO_BUILD="buildCars"
DIRECTORIO_LIB="../lib/STASM_cars"

### Inicio del script ###
# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$DIRECTORIO_BUILD
cd ../$DIRECTORIO_BUILD


# Compilo la build de la librería necesaria.
cmake ../lib/STASM_cars/ && make

# Entreno el modelo de puntos de los vehículos.
./tasm -d $DIRECTORIO_LIB/stasm/MOD_1 $DIRECTORIO_LIB/tasm/shapes/cars1.shape

# Vuelvo a compilar los ejecutables con el nuevo modelo.
make
