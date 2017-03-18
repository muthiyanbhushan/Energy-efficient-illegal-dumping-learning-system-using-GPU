# Energy-efficient-illegal-dumping-learning-system-using-GPU
- Designed model to monitor the illegal waste dumping activity using the Caffe machine learning algorithms on Jetson TX1.  - Implemented TensorRT to enhance memory efficiency

Institution: San Jose State University

Install Caffe in Right way !!
Follow following commands to install Caffe on CPU.

How to install Caffe on UBUNTU 14.04 CPU version

Update your system:
sudo apt-get update
sudo apt-get upgrade

Run following dependencies from command line:

General dependencies

sudo apt-get install libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler

sudo apt-get install --no-install-recommends libboost-all-dev

sudo apt-get install libgflags-dev libgoogle-glog-dev liblmdb-dev

sudo apt-get install python-numpy python-matplotlib python-setuptools

Install Git on your system.

Sudo apt-get install git

Clone the caffe github repository on your desired folder

git clone https://github.com/BVLC/caffe.git

cd caffe

cp Makefile.config.example Makefile.config

open makefile.config

uncomment CPU_ONLY := 1

save the file

goto your home directory

run:

sudo apt-get install python-pip python-dev build-essential 
sudo pip install --upgrade pip 
sudo apt-get install python-setuptools python-dev build-essential

If above commands gives some errors then follow below commands:
 
sudo apt-get install python-pip
sudo pip install --upgrade pip 

Again run: 

sudo apt-get update
sudo apt-get upgrade

Caffe’s Python interface works with Python 2.7. For protobuf support please install protobuf 3.0 alpha

 sudo apt-get install python-protobuf
sudo apt-get update

Go in caffe root directory

cd python

sudo pip install Cython
sudo pip install numpy
sudo pip install scipy
sudo pip install scikit-image
sudo pip install matplotlib
sudo pip install ipython
sudo pip install h5py
sudo pip install leveldb
sudo pip install networkx
sudo pip install nose
sudo pip install pandas
sudo pip install python-dateutil
sudo pip install protobuf
sudo pip install python-gflags
sudo pip install pyyaml
sudo pip install Pillow
sudo pip install six

Check for individual errors

Do not use following command 

for req in $(cat requirements.txt); do pip install $req; done

If there are some errors you need to individually figure out the errors.
Its better if you try and install dependencies one by one.


After all the dependencies are installed go to caffe root directory and RUN

export PYTHONPATH=/path/to/caffe/python:$PYTHONPATH

once you are set with the environment in caffe root directory RUN 

make pycaffe
make distribute


Caffe can be compiled with either Make or CMake. Make is officially supported while CMake is supported by the community.

Compilation with Make
Configure the build by copying and modifying the example Makefile.config for your setup. The defaults should work, but uncomment the relevant lines if using Anaconda Python.

make all
make test
make runtest
To test if caffe is installed or not
In caffe root directory run
python
import caffe

If no error comes then your caffe iss installed.


If still caffe dose not work then follow the caffe cmake commands

mkdir build
cd build
cmake ..
make all
make install
make runtest


error after running “make all”:
LD -o .build_release/lib/libcaffe.so.1.0.0-rc3
/usr/bin/ld: cannot find -lcblas
/usr/bin/ld: cannot find -latlas
collect2: error: ld returned 1 exit status
make: *** [.build_release/lib/libcaffe.so.1.0.0-rc3] Error 1
how to resolve:
 sudo apt-get install libatlas-base-dev

error after make pycaffe:
python/caffe/_caffe.cpp:10:31: fatal error: numpy/arrayobject.h: No such file or directory
 #include <numpy/arrayobject.h>
                               ^
how to solve:
sudo apt-get install python-numpy

