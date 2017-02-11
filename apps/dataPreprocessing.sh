#! /bin/bash
source ../data/info.sh
source funciones.sh

### Variables ###
# Directories
DATA_DIR="data"
LMDB_YALEFACES="yalefaces"
TRAINING_DIR="$DATA_DIR/training"
TEST_DIR="$DATA_DIR/test"

### SCRIPT ###

# Building
INDICE=`basename "$0"`
INDICE="${INDICE%.*}"

#############################
# building dataPreprocesing #
#############################
echoY "-- BUILDING \"$INDICE\"..."
echo " "

./$BUILD_APP $INDICE TEST

# Creating training and test directories if they doesnt exist
cd ../${BUILD_DIR[$INDICE]} # Switching to build directory

# Checking if build succeeded
if [ ! -f $INDICE ]; then
  echo " " && echo " "
  echoR "-- Building \"$INDICE\" FAILED"
  echoY "-- Exiting script..."
  cd .. && ./clean.sh
  exit 1
fi

# Cleaning previous data.
if [ -d $DATA_DIR ]; # Data dir reset.
then
  rm -r $DATA_DIR
fi

if [ -d $LMDB_YALEFACES ]; # Data dir reset.
then
  rm -r $LMDB_YALEFACES
fi

# Creating empty directories
mkdir -v ./$DATA_DIR ./$TRAINING_DIR ./$TEST_DIR

##############################
# Executing dataPreprocesing #
# ############################
echoY "-- EXECUTING \"$INDICE\"..."
echo " "
./$INDICE $1
# Checking if 'dataPreprocesing' succeeded
if [ $? -eq 0 ]; then
  echoG "-- Execution of \"$INDICE\" ended SUCCESSFULLY."
else
  echoR "-- Execution of \"$INDICE\" ended FAILED."
  echoY "-- Exiting script..."
  exit 1
fi

##############################
# Getting lmdb format images #
# ############################
echoY "... EXECUTING \"convert_imageset\"..."
echo " "
./../caffe-master/build/tools/convert_imageset.bin data/ trainingListFile.txt yalefaces_train_lmdb
./../caffe-master/build/tools/convert_imageset.bin data/ testListFile_$1.txt yalefaces_test_lmdb

if [ $? -eq 0 ]; then
  echoG "-- Execution of \"convert_imageset\" ended SUCCESSFULLY."
else
  echoR "-- Execution of \"convert_imageset\": FAILED."
  echoY "-- Exiting script..."
  exit 1
fi

rm -r yalefaces_train_lmdb yalefaces_test_lmdb
