import caffe
import numpy as np
import sys

if len(sys.argv) != 3:
   print "Usage: python convert_protomean.py binaryproto.mean out.npy"
   sys.exit()

blob = caffe.proto.caffe_pb2.BlobProto()
data = open( sys.argv[1] , 'rb' ).read()
blob.ParseFromString(data)
arr = np.array( caffe.io.blobproto_to_array(blob) )
out = arr[0]
np.save( sys.argv[2] , out )

#python examples/illegal/convert_bi_npy.py examples/illegal/illegal_mean_bhushan.binaryproto examples/illegal/out.npy 
# python path:  export PYTHONPATH=/home/bhushan/caffe/python:$PYTHONPATH
#run this command from caffe root directory.


