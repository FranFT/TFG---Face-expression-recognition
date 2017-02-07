#! /bin/bash

#############################################
###	Script que lleva la ejecución general	###
#############################################

############################## Includes ########################################
source apps/funciones.sh

############################## Variables #######################################
# Directorios.
APP_DIR="apps"
DATA_DIR="data"

# Scripts
CLEAN="clean.sh"
PHASE_1="dataPreprocessing.sh"


############################### Script #########################################
clean
log_msg "Cleaning previous files"
./$CLEAN

######## Fase - 1 ########
# ------------------------------------------ #
# --- Preprocesamiento de la información --- #
# ------------------------------------------ #
log_msg "Executing Phase_1"
cd $APP_DIR
./$PHASE_1
if [ $? -eq 0 ]; then
  echoG "-- Phase 1 ended SUCCESSFULLY."
else
  echoR "-- Execution of \"$PHASE_1\" ended FAILED."
  echoY "-- Exiting script..."
  exit 1
fi

######## Fase - 2 ########
# ------------------------------------------ #
# --------- Entrenamiento de la red -------- #
# ------------------------------------------ #
