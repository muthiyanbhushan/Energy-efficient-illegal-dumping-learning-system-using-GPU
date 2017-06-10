#!/usr/bin/env sh
# Compute the mean image from the imagenet training lmdb
# N.B. this is available in data/ilsvrc12

EXAMPLE=/home/swetha/caffe/examples/illegal/input/Approach_7_DB
DATA=/home/swetha/caffe/examples/illegal/input/Approach_7_DB
TOOLS=/home/swetha/caffe/build/tools

$TOOLS/compute_image_mean $EXAMPLE/illegal_train_lmdb \
  $DATA/illegal_approach_7_mean.binaryproto

echo "Done."
