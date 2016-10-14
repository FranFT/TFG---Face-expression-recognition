#! /bin/bash

#####################################################################
# Descripción: Genera la aplicación para el reconocimiento de manos.#
#####################################################################

### Variables ###
DIRECTORIO_BUILD="build"

### Inicio del script ###
# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$DIRECTORIO_BUILD
cd ../$DIRECTORIO_BUILD

# Compilo la build de la librería necesaria.
cmake ../lib/STASM_hands/ && make

