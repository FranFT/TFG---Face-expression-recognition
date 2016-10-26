#! /bin/bash

source ../data/info.sh

#######################################################
# Descripción: Compila la libreria asmlib por defecto.#
#######################################################

# Creo el directorio de salida y me sitúo en él.
mkdir -p ../$BUILD_DIR_ASMLIB
cd ../$BUILD_DIR_ASMLIB

# Compilo la build de la librería necesaria.
cmake $LIB_DIR_ASMLIB && make

# Creo el scrip para ejecutar la demo.
echo "./demo/demo -pc -m ../lib/asmlib-opencv-master/data/muct76.model -f -C ../data/haarcascade_frontalface_alt2.xml" >> ejecutarDemo.sh
chmod +x ejecutarDemo.sh
