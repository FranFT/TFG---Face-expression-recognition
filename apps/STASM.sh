#! /bin/bash

source ../data/info.sh

######################################################
# Descripción: Compila la libreria STASM por defecto.#
######################################################
INDICE=`basename "$0"`
INDICE="${INDICE%.*}"

./$BUILD_APP $INDICE STASM
