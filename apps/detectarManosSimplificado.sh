#! /bin/bash

source ../data/info.sh

#####################################################################
# Descripción: Genera la aplicación para el reconocimiento de manos.#
#####################################################################

INDICE=`basename "$0"`
INDICE="${INDICE%.*}"

./$BUILD_APP $INDICE TEST
