############################## Includes ########################################
source configuration.sh

TRAINING_DB_NAME="kdef_training_lmdb"
TEST_DB_NAME="kdef_test_lmdb"

############################### Script #########################################
if [ "$1" == "-f" ] || [ "$1" == "--force" ];then
  log_msg "Cleaning"
  rm -r data-preprocessing/build/*
  rmdir data-preprocessing/build
  rm -r data/kdef/*
fi

log_msg "Preprocessing images"
cd $PREPROC_DIR && ./run.sh $1

if [ ! -d "../data/kdef/$TRAINING_DB_NAME" ] || [ ! -d "../data/kdef/$TEST_DB_NAME" ];then
  log_msg "Creating data base"
  rm -r ../data/kdef/*
  cd build
  ../../$CAFFE_TOOLS/convert_imageset training/ trainingListFile.txt ../../data/kdef/$TRAINING_DB_NAME
  ../../$CAFFE_TOOLS/convert_imageset test/ testListFile.txt ../../data/kdef/$TEST_DB_NAME
  mv solver.prototxt ../../data/kdef/solver.prototxt
  cd ../../
  $CAFFE_TOOLS/compute_image_mean -backend=lmdb data/kdef/$TRAINING_DB_NAME data/kdef/mean.binaryproto
else
  echoG "Data Base being used:"
  echoG "------ '../data/kdef/$TRAINING_DB_NAME'"
  echoG "------ '../data/kdef/$TEST_DB_NAME'"
  cd ..
fi

log_msg "Training"
./$CAFFE_TOOLS/caffe train -solver data/kdef/solver.prototxt \
2>&1 | tee data/kdef/output.txt
