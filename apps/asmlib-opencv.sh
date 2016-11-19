#! /bin/bash

source ../data/info.sh

#######################################################
# Descripción: Compila la libreria asmlib por defecto.#
#######################################################
INDICE=`basename "$0"`
INDICE="${INDICE%.*}"

./$BUILD_APP $INDICE TEST
