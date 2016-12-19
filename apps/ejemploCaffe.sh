#! /bin/bash

source ../data/info.sh

#################################################################################
# Descripción: Compila un ejemplo de uso mi propia implementación del algoritmo #
# de simplificación de curvas de Douglas Peucker.                               #
# https://en.wikipedia.org/wiki/Ramer%E2%80%93Douglas%E2%80%93Peucker_algorithm #
#################################################################################

INDICE=`basename "$0"`
INDICE="${INDICE%.*}"

./$BUILD_APP $INDICE TEST
