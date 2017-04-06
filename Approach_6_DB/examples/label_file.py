import Image
import ImageOps
import os


path1 = "/home/bhushan/Approach_6_DB/val"

listing = os.listdir(path1)
i=0  
for file in listing:
	
	if "cart" in file:
		print file,"0"
		continue
	if "electronics" in file:
		print file,"1"
	if "furniture" in file:
		print file,"2"
	if "Mattress" in file:
		print file,"3"
	if "Sofa" in file:
		print file,"4"
	if "Trash_bags" in file:
		print file,"6"
		continue
	if "Trash" in file:
		print file,"5"
	if "tree" in file:
		print file,"7"
	if "vehicle" in file:
		print file,"8"
	if "human" in file:
		print file,"9"
	if "cat" in file:
		print file,"10"
	if "dog" in file:
		print file,"11"

