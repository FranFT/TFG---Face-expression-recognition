#! /bin/bash
source configuration.sh

EXPR=( neutral happy angry afraid disgusted sad surprised )
DB_DIR=KDEF_front_faces

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
./DIGITS_KDEF

mv temp ~/DIGITS/datasets/$DB_DIR
