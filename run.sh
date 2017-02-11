#! /bin/bash

#############################################
###	Script que lleva la ejecución general	###
#############################################

############################## Includes ########################################
source apps/funciones.sh
source data/yalefaces.sh
source data/info.sh

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
log_msg "Executing Phase_1"
cd $APP_DIR

# training a CNN for every expression in yalefaces.
for i in "${YALEFACES_EXPR[@]}"
do
  # ------------------------------------------ #
  # --- Preprocesamiento de la información --- #
  # ------------------------------------------ #
  echoY "-- Preprocessing '$i' expression..."
  ./$PHASE_1 $i

  # Checking if Preprocessing succeeded.
  if [ $? -eq 0 ]; then
    echoG "-- '$1' expression preprocessed SUCCESSFULLY."
  else
    echoR "-- Execution of \"$PHASE_1\" for '$i': FAILED."
    echoY "-- Exiting script..."
    exit 1
  fi

  cd ..

  # Copying the CNN once.
  if [ ! -f "${BUILD_DIR[$PHASE_1_DIR]}/train_val.prototxt" ]
  then
    echoY "-- Copying CNN to build directory.."
    cp data/nets/train_val.prototxt ${BUILD_DIR[$PHASE_1_DIR]}/
  fi

  # Getting expression mean image used by "bvlc_reference_caffenet"
  $CAFFE_DIR/build/tools/compute_image_mean -backend=lmdb ${BUILD_DIR[$PHASE_1_DIR]}/yalefaces_train_lmdb/ ${BUILD_DIR[$PHASE_1_DIR]}/mean.binaryproto

  # Training model using "Fine-tune" technique through "bvlc_reference_caffenet"
  #cd ..
  ./$CAFFE_DIR/build/tools/caffe train -solver ${BUILD_DIR[$PHASE_1_DIR]}/solver.prototxt -weights $CAFFE_DIR/models/bvlc_reference_caffenet/bvlc_reference_caffenet.caffemodel

  # Erasing files used for training.
  rm -r ${BUILD_DIR[$PHASE_1_DIR]}/yalefaces_train_lmdb ${BUILD_DIR[$PHASE_1_DIR]}/yalefaces_test_lmdb

  cd $APP_DIR
done

echoG "-- Training completed..."



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
