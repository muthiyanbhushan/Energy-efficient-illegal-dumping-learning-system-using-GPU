#!/usr/bin/env sh
# Compute the mean image from the imagenet training lmdb
# N.B. this is available in data/ilsvrc12

EXAMPLE=/home/bhushan/caffe/examples/illegal/Approach_6_DB
DATA=/home/bhushan/caffe/examples/illegal/Approach_6_DB
TOOLS=/home/bhushan/caffe/build/tools

$TOOLS/compute_image_mean $EXAMPLE/illegal_train_lmdb_googlenet \
  $DATA/illegal_mean_googlenet_6.binaryproto

echo "Done."
