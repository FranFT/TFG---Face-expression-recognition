#! /bin/bash

#############################################
###	Script que lleva la ejecución general	###
#############################################

############################## Includes ########################################
source configuration.sh

# Python Scripts
CONF_MATRIX="Caffe_Convnet_ConfuxionMatrix.py"


############################### Script #########################################
log_msg "Cleaning previous files"
./$CLEAN

if [ ! -d "$CAFFE_DIR/" ]
then
  echoR "No se encontró el directorio raiz de Caffe."
  echoY "Descárgalo y copialo dentro de esta carpeta (TFG---Face---)"
  exit 1
fi

######## Fase - 1 ########
log_msg "Executing Phase_1"
cd $APP_DIR

# ------------------------------------------ #
# --- Preprocesamiento de la información --- #
# ------------------------------------------ #
# If -all option was given we train a single model for all expressions

if [ $NUM_EXPR -eq 0 ]; then
  echoY "-- Preprocessing for ALL expressions..."
  ./$PREPROCESSING

  # Checking if Preprocessing succeeded.
  if [ $? -eq 0 ]; then
    echoG "-- '$1' expression preprocessed SUCCESSFULLY."
  else
    echoR "-- Execution of \"$PREPROCESSING\" for ALL expressions: FAILED."
    echoY "-- Exiting script..."
    exit 1
  fi

  cd $ROOT_DIR

  echoY "-- Copying CNN to build directory.."
  cp $NET_DIR/$NET_USED $WORKING_DIR/train_val.prototxt

  # Getting expression mean image used
  $CAFFE_TOOLS/compute_image_mean \
  -backend=lmdb $WORKING_DIR/$TRAIN_LEVELDB/ \
  $WORKING_DIR/mean.binaryproto

  # Training model using "Fine-tune"
  ./$CAFFE_TOOLS/caffe train \
  -solver $WORKING_DIR/solver.prototxt \
  -weights $WEIGHTS_PATH \
  2>&1 | tee $NET_DIR/output/all-output.txt

else

  for i in "$EXPR"
  do
    echoY "-- Preprocessing '$i' expression..."
    ./$PREPROCESSING $i

    # Checking if Preprocessing succeeded.
    if [ $? -eq 0 ]; then
      echoG "-- '$i' expression preprocessed SUCCESSFULLY."
    else
      echoR "-- Execution of \"$PREPROCESSING\" for '$i': FAILED."
      echoY "-- Exiting script..."
      exit 1
    fi

    cd $ROOT_DIR

    # Copying the CNN once.
    if [ ! -f "$WORKING_DIR/train_val.prototxt" ]
    then
      echoY "-- Copying CNN to build directory.."
      cp $NET_DIR/$NET_USED $WORKING_DIR/train_val.prototxt
    fi

    # Getting expression mean image used
    $CAFFE_TOOLS/compute_image_mean \
    -backend=lmdb $WORKING_DIR/$TRAIN_LEVELDB/ \
    $WORKING_DIR/mean.binaryproto

    # Training model using "Fine-tune"
    ./$CAFFE_TOOLS/caffe train \
    -solver $WORKING_DIR/solver.prototxt \
    -weights $WEIGHTS_PATH \
    2>&1 | tee $NET_DIR/output/$i-output.txt

    # Erasing files used for training.
    rm -r $WORKING_DIR/$TRAIN_LEVELDB $WORKING_DIR/$TEST_LEVELDB

    cd $APP_DIR

  done
fi

echoG "-- Training completed..."
