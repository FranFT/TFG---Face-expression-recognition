#! /bin/bash

source data/info.sh
################################################################################
# Variables                                                                    #
################################################################################
CAFFE_DIR="caffe-master"
# Basic variables #
# exprs: centerlight, glasses, happy, leftlight, noglasses, normal, rightlight,
# sad, sleepy, surprised, wink.
EXPR=(wink)

# nets: caffeNet_all.prototxt, caffeNet_single.prototxt, ageNet_all.prototxt,
# ageNet_single.prototxt
NET_USED="ageNet_single.prototxt"

#
WEIGHTS_PATH="data/weights/ageNet.caffemodel"
#WEIGHTS_PATH="$CAFFE_DIR/models/bvlc_reference_caffenet/bvlc_reference_caffenet.caffemodel"


# Special Variables #
NUM_EXPR=${#EXPR[@]}

################################################################################
# Directories                                                                  #
################################################################################
# Basic Dirs
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_DIR="apps"
DATA_DIR="data"
LIB_DIR="lib"
RESULT_DIR="../../Escritorio/results/"

# Special Dirs
CAFFE_TOOLS=$CAFFE_DIR/build/tools
WORKING_DIR=${BUILD_DIR["dataPreprocessing"]}
NET_DIR="$DATA_DIR/nets"
TRAIN_LEVELDB="yalefaces_train_lmdb"
TEST_LEVELDB="yalefaces_test_lmdb"

################################################################################
# Scripts                                                                      #
################################################################################
CLEAN="clean.sh"
PREPROCESSING="dataPreprocessing.sh"

################################################################################
# Caffe Apps                                                                   #
################################################################################
COMPUTE_IMAGE_MEAN=$CAFFE_DIR/build/tools/compute_image_mean
CAFFE=$CAFFE_DIR/build/tools/compute_image_mean

################################################################################
# Data base expressions                                                        #
################################################################################
YALEFACES_EXPR=( "centerlight" "glasses" "happy" "leftlight" "noglasses" "normal" "rightlight" "sad" "sleepy" "surprised" "wink" )


################################################################################
# funciones                                                                    #
################################################################################
# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Functions
# 'echoG' echo a green colored message
function echoG {
  if [ $# -ne 1 ]
  then
    echo -e "${RED}warning:${NC} Missing message"
  else
    echo -e "${GREEN}$1${NC}"
  fi
}
# 'echoR' echo a red colored message
function echoR {
  if [ $# -ne 1 ]
  then
    echo -e "${RED}warning:${NC} Missing message"
  else
    echo -e "${RED}$1${NC}"
  fi
}
# 'echoY' echo a yellow colored message
function echoY {
  if [ $# -ne 1 ]
  then
    echo -e "${RED}warning:${NC} Missing message"
  else
    echo -e "${YELLOW}$1${NC}"
  fi
}

function log_msg {
  if [ $# -ne 1 ]
  then
    echo -e "${RED}warning:${NC} Missing message"
  else
    echo "====================================="
    echoY " << $1 >>"
    echo "====================================="
  fi
}
