#! /bin/bash

source data/info.sh

####################################################
# Descripción: Limpia todos los ficheros generados.#
####################################################

# Directorios de Build
if [ -d $BUILD_DIR_STASM ];
then
	echo "Borrando el directorio '$BUILD_DIR_STASM'..."
	rm -r $BUILD_DIR_STASM
fi

if [ -d $BUILD_DIR_CARS ];
then
	echo "Borrando el directorio '$BUILD_DIR_CARS'..."
	rm -r $BUILD_DIR_CARS
fi

if [ -d $BUILD_DIR_HANDS ];
then
	echo "Borrando el directorio '$BUILD_DIR_HANDS'..."
	rm -r $BUILD_DIR_HANDS
fi

if [ -d $BUILD_DIR_ASMLIB ];
then
	echo "Borrando el directorio '$BUILD_DIR_ASMLIB'..."
	rm -r $BUILD_DIR_ASMLIB
fi

if [ -d $DETECTAR_MANOS_BUILD_DIR ];
then
	echo "Borrando el directorio '$DETECTAR_MANOS_BUILD_DIR'..."
	rm -r $DETECTAR_MANOS_BUILD_DIR
fi

if [ -d $DETECTAR_COCHES_BUILD_DIR ];
then
	echo "Borrando el directorio '$DETECTAR_COCHES_BUILD_DIR'..."
	rm -r $DETECTAR_COCHES_BUILD_DIR
fi

if [ -d $DETECTAR_CARA_BUILD_DIR ];
then
	echo "Borrando el directorio '$DETECTAR_CARA_BUILD_DIR'..."
	rm -r $DETECTAR_CARA_BUILD_DIR
fi

if [ -d $IRIS_LIBSVM_BUILD_DIR ];
then
	echo "Borrando el directorio '$IRIS_LIBSVM_BUILD_DIR'..."
	rm -r $IRIS_LIBSVM_BUILD_DIR
fi

if [ -d $DOUGLAS_PEUCKER_BUILD_DIR ];
then
	echo "Borrando el directorio '$DOUGLAS_PEUCKER_BUILD_DIR'..."
	rm -r $DOUGLAS_PEUCKER_BUILD_DIR
fi



if [ -d $SIMPLIFICACION_STASM_BUILD_DIR ];
then
	echo "Borrando el directorio '$SIMPLIFICACION_STASM_BUILD_DIR'..."
	rm -r $SIMPLIFICACION_STASM_BUILD_DIR
fi



# Archivos log: Si hay ficheros en el directorio 'log' correspondiente, se borran.
if [ `ls $LOG_DIR_STASM | wc -l` -gt "0" ];
then
	echo "Borrando archivos 'log' en '$LOG_DIR_STASM'..."
	rm $LOG_DIR_STASM*
fi

if [ `ls $LOG_DIR_CARS | wc -l` -gt "0" ];
then
	echo "Borrando archivos 'log' en '$LOG_DIR_CARS'..."
	rm $LOG_DIR_CARS*
fi

if [ `ls $LOG_DIR_HANDS | wc -l` -gt "0" ];
then
	echo "Borrando archivos 'log' en '$LOG_DIR_HANDS'..."
	rm $LOG_DIR_HANDS*
fi
