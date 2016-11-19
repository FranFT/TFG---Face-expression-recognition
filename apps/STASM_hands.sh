#! /bin/bash

source ../data/info.sh

###############################################################################
# Descripción: Entrena un modelo para el reconocimiento de manos usando STASM.#
###############################################################################
INDICE=`basename "$0"`
INDICE="${INDICE%.*}"

./$BUILD_STASM $INDICE
