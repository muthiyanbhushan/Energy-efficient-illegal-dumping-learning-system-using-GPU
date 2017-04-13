import Image
import ImageOps
import os


path1 = "/home/swetha/caffe/examples/illegal/input/images_real_time"

listing = os.listdir(path1)
i=0  
for file in listing:
	print file.split("_")[0]
	name = file.split("_")[0]
	if(file.split("_")[1]=="bags"):
		name = file.split("_")[0]+"_"+file.split("_")[1]
	img = Image.open(path1+"/"+file)
	grayscale = ImageOps.grayscale(img) 
	grayscale.save(name+"_"+str(i)+".JPG")
	i=i+1
'''	img.save(name+"_"+str(i)+".JPG")
	i=i+1
	mirror_img = ImageOps.mirror(img) 
	mirror_img.save(name+"_"+str(i)+".JPG")
	i=i+1
	mirror_grayscale = ImageOps.grayscale(mirror_img) 
	mirror_grayscale.save(name+"_"+str(i)+".JPG")
	i=i+1

	if not ("human" in name or "vehicle" in name):
		#flip = ImageOps.flip(img) 
		#flip.save(name+"_"+str(i)+".JPG")
		i=i+1
		grayscale_flip = ImageOps.grayscale(grayscale) 
		grayscale_flip.save(name+"_"+str(i)+".JPG")
		i=i+1
		mirror_grayscale_flip = ImageOps.grayscale(mirror_grayscale) 
		mirror_grayscale_flip.save(name+"_"+str(i)+".JPG")
		i=i+1'''
