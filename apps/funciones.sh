#! /bin/bash

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
