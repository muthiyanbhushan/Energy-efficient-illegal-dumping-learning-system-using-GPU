#!/usr/bin/env sh
# Compute the mean image from the imagenet training lmdb
# N.B. this is available in data/ilsvrc12

EXAMPLE=/home/swetha/caffe/examples/illegal
DATA=/home/swetha/caffe/examples/illegal
TOOLS=/home/swetha/caffe/build/tools

$TOOLS/compute_image_mean $EXAMPLE/illegal_train_lmdb \
  $DATA/illegal_approach_2_mean.binaryproto

echo "Done."
