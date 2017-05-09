# Energy-efficient-illegal-dumping-learning-system-using-GPU
- Designed model to monitor the illegal waste dumping activity using the Caffe machine learning algorithms on Jetson TX1.  - Implemented TensorRT to enhance memory efficiency

Institution: San Jose State University
-------------------------------------------------------------------------------------
Install Caffe in Right way !!
How to install Caffe on UBUNTU 14.04 CPU version
-------------------------------------------------------------------------------------
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

------------------------- end -----------------
---Errors while installing Caffe:
----------------------------------------------------------------------------------------------
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
how to solve above error:
sudo apt-get install python-numpy
------------------------------------------- end ------------------------------------------------

----- Energy efficiency --------

Memory requirement of CNN: -
The memory requirement of convolutional networks is very different from simple neural networks. If you just want to store a network, then the memory requirement is very low. 
But, if you train the network on the device the memory requirement goes high according to the input dimensions of the image. 
The activations and errors of each convolutional layer are huge compared to simple neural networks and this is the main memory footprint. Just summing up the activations and errors we can determine the approximate memory requirement.  In general, the first few layers can eat up a lot of memory, hence the main memory requirement stems from the input size of your data so it makes good sense to first think about your input data. ImageNet usually takes 224x224x3 as input dimensions, that is 224 by 224 pixel images with 3 colour channels. While 12GB of memory are essential for state-of-the-art results on ImageNet on a similar dataset with 112x112x3 dimensions we might get state-of-the-art results with just 4-6GB of memory. On the other hand, for a video dataset with inputs of size 25x75x75x3 the 12GB of memory might be way short of what you would need for good results. However, another important aspect would be how many samples your dataset has. For example, if you only take 10% of the images of the ImageNet dataset, then your model very quickly overfits (it just does not have enough examples to generalize well) so that you a smaller networks that consume much less memory would be sufficient to do as well as a convolutional net can do, so that about 4GB or less of memory would be good for this task. So, this means that the fewer images you have, the less memory you need.
The same is true for the number of classes you have for your labels. If you would take just two classes from the ImageNet dataset and build a model for them, then the model would consume much less memory than the model for 1000 classes. This is so, because overfitting occurs much faster if you have less classes that need to be distinguished from each other, or in other words words, you just need much less parameter to distinguish two classes from each other compared to 1000.

Memory Reduction Techniques: -
One technique is to use larger strides for the convolutional kernels, that is we apply the patch-wise convolution not for every pixel, but every two or four pixels (stride of 2 or 4) so that we generate less output data. This is usually used for input layers because these use most of the memory.
Another trick to reduce the memory footprint is to introduce a 1×1 convolutional kernel layer, which reduces the channels. For example, 64x64x256 inputs can be reduced to 64x64x96 inputs by 96 1×1 kernels.
One obvious technique is pooling. A 2×2 pooling layer will reduce the amount of data for the layer by four and thus reduces the memory footprint for subsequent layers significantly.
If everything fails, you can always reduce the mini-batch size. The mini-batch size is a very significant factor for memory. Using a batch size of 64 instead of 128 halves memory consumption. However, training may also take longer, especially the last stages of training where it becomes more and more important to have accurate gradients. Most convolution operations are also optimized for mini-batch sizes of 64 or greater so that starting from a batch size of 32 the training speed is greatly reduced. So, shrinking the mini-batch size to or even below 32 should only be used as an option of last resort.
Another often overlooked choice is to change the data type that the convolution net uses. By switching from 32-bit to 16-bit you can easily halve the memory consumption without degrading classification performance. On P100 Tesla cards this will even give you a hefty speedup.


Understanding Temporary memory requirements of CNN: -
There are generally three types of convolutional implementations. One uses Fourier transforms, the others direct computation on the data by realigning it in memory first. This realignment happens in either patch-like structures for pixel-by-pixel calculations or to matrix-like structures to use matrix multiplication to perform convolution.
 Continuous convolution theorem with abuse in notation: The input represents an image or feature map and the subtraction of the argument can be thought of creating image patches with width   with respect to some x, which is then multiplied by the kernel. The integration turns into a multiplication in the Fourier domain; here   denotes a Fourier transformed function. For discrete “dimensions” (x) we have a sum instead of an integral – but the idea is the same.

The mathematical operation of convolution can be described by a simple element-wise matrix multiplication in the Fourier frequency domain. So, one can perform a fast Fourier transform on the inputs and on each kernel and multiply them element-wise to obtain feature maps – the outputs of a convolutional layer. During the backward pass, we do an inverse fast Fourier transform to receive gradients in the standard domain so that we can update the weights. Ideally, we store all these Fourier transforms in memory to save the time of allocating the memory during each pass. This can amount to a lot of extra memory and this is the chunk of memory that is added for the Fourier method for convolutional nets – holding all this memory is just required to make everything run smoothly.


Why GPU are used for Deep learning and GPU to be used:-
It turns out that the most important practical measure for GPU performance is memory bandwidth in GB/s, which measures how much memory can be read and written per second. Memory bandwidth is so important because almost all mathematical operations, such as matrix multiplication, dot product, sum, addition etcetera, are bandwidth bound, that is limited by how much numbers can be fetched from memory rather than how many calculation can be performed on those given numbers.
Another important factor to consider however is that not all architectures are compatible with cuDNN. Since almost all deep learning libraries make use of cuDNN for convolutional operations this restricts the choice of GPUs to Kepler GPUs or better, that is GTX 600 series or above. On top of that, Kepler GPUs are generally quite slow. So this means you should prefer GPUs of the 900 or 1000 series for good performance.

Best GPU overall: Titan X Pascal
Cost efficient but expensive: GTX 1080, GTX 1070
Cost efficient and cheap:  GTX 1060
Cheapest card with no troubles: GTX 1060


