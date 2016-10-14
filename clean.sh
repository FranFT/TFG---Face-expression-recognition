#! /bin/bash

####################################################
# Descripción: Limpia todos los ficheros generados.#
####################################################

#Variables
DIRETORIO_BUILD_HANDS=buildHands
DIRETORIO_BUILD_CARS=buildCars

DIRECTORIO_HANDS_LOG=lib/STASM_hands/stasm/MOD_1/log/
DIRECTORIO_CARS_LOG=lib/STASM_cars/stasm/MOD_1/log/

#Borrado
# Directorios de Build
if [ -d $DIRETORIO_BUILD_HANDS ];
then
	rm -r $DIRETORIO_BUILD_HANDS
fi

if [ -d $DIRETORIO_BUILD_CARS ];
then
	rm -r $DIRETORIO_BUILD_CARS
fi

# Archivos log
rm $DIRECTORIO_HANDS_LOG*
rm $DIRECTORIO_CARS_LOG*

