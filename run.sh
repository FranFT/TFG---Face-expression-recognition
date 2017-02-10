#! /bin/bash

#############################################
###	Script que lleva la ejecución general	###
#############################################

############################## Includes ########################################
source apps/funciones.sh
source data/yalefaces.sh

############################## Variables #######################################
# Directorios.
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_DIR="apps"
DATA_DIR="data"
CAFFE_DIR="caffe-master"
PHASE_1_DIR="dataPreprocessing"

# Scripts
CLEAN="clean.sh"
PHASE_1="$PHASE_1_DIR.sh"


############################### Script #########################################
log_msg "Cleaning previous files"
./$CLEAN

if [ ! -d "$CAFFE_DIR/" ]
then
  echoR "No se encontró el directorio raiz de Caffe."
  echoY "Descárgalo y copialo dentro de esta carpeta (TFG---Face---)"
fi

######## Fase - 1 ########
# ------------------------------------------ #
# --- Preprocesamiento de la información --- #
# ------------------------------------------ #
log_msg "Executing Phase_1"
cd $APP_DIR

# Do phase_1 for every expression in Yalefaces Database.
for i in "${YALEFACES_EXPR[@]}"
do
  echoY "-- Preprocessing '$i' expression..."
  ./$PHASE_1 $i

  if [ $? -eq 0 ]; then
    echoG "-- $1 expression preprocessed SUCCESSFULLY."
  else
    echoR "-- Execution of \"$PHASE_1\" for '$i': FAILED."
    echoY "-- Exiting script..."
    exit 1
  fi
done

echoG "-- PHASE-1 completed..."



######## Fase - 2 ########
# ------------------------------------------ #
# --------- Entrenamiento de la red -------- #
# ------------------------------------------ #
#log_msg "Executing Phase_2"
# Getting mean image needed by the model.
#if [ -f "data/nets/mean.binaryproto" ]
#then
#  $CAFFE_DIR/build/tools/compute_image_mean -backend=lmdb $PHASE_1_DIR/yalefaces_train_lmdb/ data/nets/mean.binaryproto
#fi
# Training model using "Fine-tune" technique through "bvlc_reference_caffenet"
#cd ..
#./$CAFFE_DIR/build/tools/caffe train -solver data/nets/solver.prototxt -weights $CAFFE_DIR/models/bvlc_reference_caffenet/bvlc_reference_caffenet.caffemodel
