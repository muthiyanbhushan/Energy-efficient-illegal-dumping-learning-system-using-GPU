#!/usr/bin/env sh
set -e

./build/tools/caffe train --solver=approaches/models/illegal/Approach_7/approach_7_GoogleNet/--log_dir=approach_4$@  

