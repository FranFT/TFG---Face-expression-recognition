#! /bin/bash

#####################################################################
# Descripción: Genera la aplicación para el reconocimiento de manos.#
#####################################################################

### Variables ###
DIRECTORIO_BUILD="buildHands"
DIRECTORIO_LIB="../lib/STASM_hands"

### Inicio del script ###
# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$DIRECTORIO_BUILD
cd ../$DIRECTORIO_BUILD

# Compilo la build de la librería necesaria.
cmake ../lib/STASM_hands/ && make

# Entreno el modelo de puntos de las manos.
./tasm -d $DIRECTORIO_LIB/stasm/MOD_1 $DIRECTORIO_LIB/tasm/shapes/hands.shape

# Vuelvo a compilar los ejecutables con el nuevo modelo.
make
