#! /bin/bash

source ../data/info.sh

################################################################
# Descripción: Compila un ejemplo de uso de la libreria libSVM #
# haciendo uso de iris dataset.                                #
################################################################

INDICE=`basename "$0"`
INDICE="${INDICE%.*}"

./$BUILD_APP $INDICE TEST
