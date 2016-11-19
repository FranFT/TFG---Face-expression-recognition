###################################################################################
# Descripción: Modifica la versión de STASM llamada "STASM_handsSimplificado" del #
# directorio 'lib' haciendo uso del algoritmo de Douglas Peucker para reducir     #
# el número de puntos a detectar.                                                 #
###################################################################################

#! /bin/bash

# Comprobación de parámetros de entrada.
if [ $# -ne 1 ]
then
	echo "Falta el argumento 'epsilon': ./simplificacionSTASM.sh <valor_epsilon>"
	exit 1
fi

# Importo variables externas del proyecto.
source ../data/info.sh

INDICE=`basename "$0"`
INDICE="${INDICE%.*}"
INDICE1=STASM_handsSimplificado

# Defino variables locales.
EJECUTABLE=simplificacionSTASM
FICHERO_LANDMARK_TABLE=landtab_hands.h
FICHERO_STASM_LIB=stasm_lib.h
FICHERO_SHAPEFILE=hands_simplificado.shape
EPSILON=$1

cd ..
./clean.sh

# Creo el directorio de salida y me sitúo en él.
mkdir -p ${BUILD_DIR[$INDICE]} #$SIMPLIFICACION_STASM_BUILD_DIR
cd ${BUILD_DIR[$INDICE]}

# Compilo la aplicación.
cmake ${SOURCE_DIR[$INDICE]} && make

# Ejecuto la aplicación para generar los ficheros modificados.
./$EJECUTABLE $EPSILON

# Muevo los ficheros generados a su ubicación.
echo "Moviendo el fichero '$FICHERO_LANDMARK_TABLE' a '${LIB_DIR[$INDICE1]}/tasm/landtab/$FICHERO_LANDMARK_TABLE'..."
mv $FICHERO_LANDMARK_TABLE ${LIB_DIR[$INDICE1]}/tasm/landtab/$FICHERO_LANDMARK_TABLE

echo "Moviendo el fichero '$FICHERO_SHAPEFILE' a '${LIB_DIR[$INDICE1]}/tasm/shapes/$FICHERO_SHAPEFILE'..."
mv $FICHERO_SHAPEFILE ${LIB_DIR[$INDICE1]}/tasm/shapes/$FICHERO_SHAPEFILE

echo "Moviendo el fichero '$FICHERO_STASM_LIB' a '${LIB_DIR[$INDICE1]}/stasm/$FICHERO_STASM_LIB'..."
mv $FICHERO_STASM_LIB ${LIB_DIR[$INDICE1]}/stasm/$FICHERO_STASM_LIB

# Borro el directorio de la aplicación.
cd ..
./clean.sh

# Creo el directorio para la librería y me sitúo en el.
mkdir -p ${BUILD_DIR[$INDICE1]}
cd ${BUILD_DIR[$INDICE1]}

# Compilo la librería.
cmake ${LIB_DIR[$INDICE1]} && make

# Entreno la librería con los puntos simplificados.
./tasm -d ${LIB_DIR[$INDICE1]}/stasm/MOD_1 ${LIB_DIR[$INDICE1]}/tasm/shapes/$FICHERO_SHAPEFILE

# Vuelvo a compilar la librería con los nuevos modelos.
make

# Genero una imagen de prueba.
echo "Generando imagen de prueba."
./stasmMain ../res/Hands/images/0000.jpg
