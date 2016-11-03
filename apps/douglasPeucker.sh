#! /bin/bash

source ../data/info.sh

#################################################################################
# Descripción: Compila un ejemplo de uso mi propia implementación del algoritmo #
# de simplificación de curvas de Douglas Peucker.                               #
# https://en.wikipedia.org/wiki/Ramer%E2%80%93Douglas%E2%80%93Peucker_algorithm #
#################################################################################

# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$DOUGLAS_PEUCKER_BUILD_DIR
cd ../$DOUGLAS_PEUCKER_BUILD_DIR

# Compilo la aplicación.
cmake $DOUGLAS_PEUCKER_SOURCE_DIR && make
