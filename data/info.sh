#! /bin/bash

###################################################################
# Descripción: Contiene las variables necesarias para cada script.#
###################################################################

BUILD_APP=build.sh

declare -A BUILD_DIR
declare -A LIB_DIR
declare -A LOG_DIR
declare -A SOURCE_DIR
declare -A SHAPEFILE

#############
### STASM ###
#############
BUILD_DIR[STASM]=buildSTASM
LIB_DIR[STASM]=../lib/STASM
LOG_DIR[STASM]=lib/STASM/stasm/MOD_1/log/
#SOURCE_DIR[]=' '


##################
### STASM_cars ###
##################
BUILD_DIR[STASM_cars]=buildCars
LIB_DIR[STASM_cars]=../lib/STASM_cars
LOG_DIR[STASM_cars]=lib/STASM_cars/stasm/MOD_1/log/
#SOURCE_DIR[]=' '

# Ficheros
SHAPEFILE[STASM_cars]="cars1.shape"


###################
### STASM_hands ###
###################
BUILD_DIR[STASM_hands]=buildHands
LIB_DIR[STASM_hands]=../lib/STASM_hands
LOG_DIR[STASM_hands]=lib/STASM_hands/stasm/MOD_1/log/
#SOURCE_DIR[]=' '

# Ficheros.
SHAPEFILE[STASM_hands]="hands.shape"

#####################
### asmlib-opencv ###
#####################
BUILD_DIR[asmlib-opencv]=buildASMLIB
#LIB_DIR[asmlib-opencv]=../lib/asmlib-opencv-master/src/
#LOG_DIR[asmlib-opencv]=' '
SOURCE_DIR[asmlib-opencv]=../lib/asmlib-opencv-master/src/


#####################
### detectarManos ###
#####################
BUILD_DIR[detectarManos]=buildDetectarManos
#LIB_DIR[]=' '
#LOG_DIR[]=' '
SOURCE_DIR[detectarManos]=../test/detectarManos


#################################
### detectarManosSimplificado ###
#################################
BUILD_DIR[detectarManosSimplificado]=buildDetectarManosSimplificado
#LIB_DIR[]=
#LOG_DIR[]=
SOURCE_DIR[detectarManosSimplificado]=../test/detectarManosSimplificado


######################
### detectarCoches ###
######################
BUILD_DIR[detectarCoches]=buildDetectarCoches
#LIB_DIR[]=' '
#LOG_DIR[]=' '
SOURCE_DIR[detectarCoches]=../test/detectarCoches


####################
### detectarCara ###
####################
BUILD_DIR[detectarCara]=buildDetectarCara
#LIB_DIR[]=
#LOG_DIR[]=
SOURCE_DIR[detectarCara]=../test/detectarCara


###################
### iris_libSVM ###
###################
BUILD_DIR[iris_libSVM]=buildIrisLibSVM
#LIB_DIR[]=' '
#LOG_DIR[]=' '
SOURCE_DIR[iris_libSVM]=../test/iris_libSVM


######################
### douglasPeucker ###
######################
BUILD_DIR[douglasPeucker]=buildDouglasPeucker
#LIB_DIR[]=' '
#LOG_DIR[]=' '
SOURCE_DIR[douglasPeucker]=../test/douglasPeucker


###########################
### simplificacionSTASM ###
###########################
# Librería simplificada.
BUILD_DIR[STASM_handsSimplificado]=buildSTASM_handsSimplificado
LIB_DIR[STASM_handsSimplificado]=../lib/STASM_handsSimplificado
LOG_DIR[STASM_handsSimplificado]=lib/STASM_handsSimplificado/stasm/MOD_1/log/
#SOURCE_DIR[]=' '


# Aplicación que simplifica.
BUILD_DIR[simplificacionSTASM]=buildSimplificacionSTASM
#LIB_DIR[]=' '
#LOG_DIR[]=' '
SOURCE_DIR[simplificacionSTASM]=../test/simplificacionSTASM

# Ejemplo de Caffe.
BUILD_DIR[ejemploCaffe]=buildEjemploCaffe
#LIB_DIR[]=' '
#LOG_DIR[]=' '
SOURCE_DIR[ejemploCaffe]=../test/ejemploCaffe

# Ejemplo dataPreprocessing
BUILD_DIR[dataPreprocessing]=buildDataPreprocessing
#LIB_DIR[]=' '
#LOG_DIR[]=' '
SOURCE_DIR[dataPreprocessing]=../test/dataPreprocessing
