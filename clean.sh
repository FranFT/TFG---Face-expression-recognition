#! /bin/bash

source data/info.sh

####################################################
# Descripción: Limpia todos los ficheros generados.#
####################################################

# Directorios de Build
if [ -d $BUILD_DIR_CARS ];
then
	rm -r $BUILD_DIR_CARS
fi

if [ -d $BUILD_DIR_HANDS ];
then
	rm -r $BUILD_DIR_HANDS
fi

if [ -d $DETECTAR_MANOS_BUILD_DIR ];
then
	rm -r $DETECTAR_MANOS_BUILD_DIR
fi

# Archivos log
rm $LOG_DIR_CARS*
rm $LOG_DIR_HANDS*

