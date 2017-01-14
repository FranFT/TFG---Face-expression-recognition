#! /bin/bash
source ../data/info.sh

### Variables ###
# Directories
DATA_DIR="data"
TRAINING_DIR="$DATA_DIR/training"
TEST_DIR="$DATA_DIR/test"

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
### SCRIPT ###
# Cleaning bash screen
clear

# Building
INDICE=`basename "$0"`
INDICE="${INDICE%.*}"

#############################
# building dataPreprocesing #
#############################
echo "." && echo ".." && echo "..."
echo "====================================="
echoY "... BUILDING \"$INDICE\"..."
echo "====================================="

./$BUILD_APP $INDICE TEST

# Creating training and test directories if they doesnt exist
cd ../${BUILD_DIR[$INDICE]} # Switching to build directory

# Checking if build succeeded
if [ ! -f $INDICE ]; then
  echo " " && echo " "
  echoR "Building \"$INDICE\" FAILED"
  echoY "Exiting script..."
  cd .. && ./clean.sh
  exit 1
fi

if [ -d $DATA_DIR ]; # Data dir reset.
then
  rm -vr $DATA_DIR
fi

# Creating empty directories
mkdir -v ./$DATA_DIR ./$TRAINING_DIR ./$TEST_DIR

##############################
# Executing dataPreprocesing #
# ############################
echo "." && echo ".." && echo "..."
echo "====================================="
echoY "... EXECUTING \"$INDICE\"..."
echo "====================================="
./$INDICE
# Checking if 'dataPreprocesing' succeeded
if [ $? -eq 0 ]; then
  echoG "Execution of \"$INDICE\" ended SUCCESSFULLY."
else
  echoR "Execution of \"$INDICE\" ended FAILED."
  echoY "Exiting script..."
  exit 1
fi
