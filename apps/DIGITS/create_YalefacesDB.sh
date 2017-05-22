#! /bin/bash
source configuration.sh

EXPR=(centerlight glasses happy leftlight noglasses normal rightlight sad sleepy surprised wink)
DB_DIR=yalefaces

if [ -d ~/DIGITS/datasets/$DB_DIR ]; then
  exit 1
fi

# Creating Folder Structure
if [ -d data-preprocessing/build ]; then
  rm -r data-preprocessing/build
fi

mkdir data-preprocessing/build
mkdir data-preprocessing/build/temp
for i in ${EXPR[@]}; do
  mkdir data-preprocessing/build/temp/${i}
  echo ${i} >> data-preprocessing/build/temp/labels.txt
done

cd data-preprocessing/build
cmake .. && make
./DIGITS_yalefaces

mv temp ~/DIGITS/datasets/$DB_DIR
