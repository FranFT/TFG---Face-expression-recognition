#! /bin/bash

source ../data/info.sh

EJECUTABLE=simplificacionSTASM
FICHERO_LANDMARK_TABLE=landtab_hands.h
FICHERO_STASM_LIB=stasm_lib.h
FICHERO_SHAPEFILE=hands_simplificado.shape
DIRECTORIO_STASM_SIMPLIFICADO=../lib/STASM_handsSimplificado

###################################################################################
# Descripción: Modifica la versión de STASM llamada "STASM_handsSimplificado" del #
# directorio 'lib' haciendo uso del algoritmo de Douglas Peucker para reducir     #
# el número de puntos a detectar.                                                 #
###################################################################################

cd ..
./clean.sh

# Creo el directorio de salida y me sitúo en él.
mkdir -p $SIMPLIFICACION_STASM_BUILD_DIR
cd $SIMPLIFICACION_STASM_BUILD_DIR

# Compilo la aplicación.
cmake $SIMPLIFICACION_STASM_SOURCE_DIR && make

# Ejecuto la aplicación para generar los ficheros modificados.
./$EJECUTABLE

# Muevo los ficheros generados a su ubicación.
mv $FICHERO_LANDMARK_TABLE $DIRECTORIO_STASM_SIMPLIFICADO/tasm/landtab/$FICHERO_LANDMARK_TABLE
mv $FICHERO_SHAPEFILE $DIRECTORIO_STASM_SIMPLIFICADO/tasm/shapes/$FICHERO_SHAPEFILE
mv $FICHERO_STASM_LIB $DIRECTORIO_STASM_SIMPLIFICADO/stasm/$FICHERO_STASM_LIB

# Borro el directorio de la aplicación.
cd ..
./clean.sh

# Creo el directorio para la librería y me sitúo en el.
mkdir -p $BUILD_DIR_HANDS_SIMPLIFICADO
cd $BUILD_DIR_HANDS_SIMPLIFICADO

# Compilo la librería.
cmake $LIB_DIR_HANDS_SIMPLIFICADO && make

# Entreno la librería con los puntos simplificados.
./tasm -d $LIB_DIR_HANDS_SIMPLIFICADO/stasm/MOD_1 $LIB_DIR_HANDS_SIMPLIFICADO/tasm/shapes/$FICHERO_SHAPEFILE

# Vuelvo a compilar la librería con los nuevos modelos.
make


