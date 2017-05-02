############################## Includes ########################################
source configuration.sh

############################### Script #########################################
log_msg "Preprocessing images"
cd $PREPROC_DIR && ./run.sh $1 && cd build

log_msg "Creating data base"
../../$CAFFE_TOOLS/convert_imageset training/ trainingListFile.txt kdef_training_lmdb
../../$CAFFE_TOOLS/convert_imageset training/ testListFile.txt kdef_test_lmdb
