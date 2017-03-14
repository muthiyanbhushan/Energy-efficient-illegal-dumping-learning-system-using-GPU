#!/usr/bin/env sh
set -e

./build/tools/caffe train --solver=models/illegal_approach_3_AlexNet/solver.prototxt --log_dir=examples$@  

