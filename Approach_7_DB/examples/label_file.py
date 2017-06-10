import Image
import ImageOps
import os


path1 = "/home/swetha/caffe/examples/illegal/input/Approach_7_DB/images/val"

listing = os.listdir(path1)
i=0
ani_count=0
cart_count=0
vehicle_count=0
trash_bag_count=0
trash_count=0
trees_count=0
mattress_count=0
human_count=0
electronics_count=0
sofa_count=0
furn_count=0
for file in listing:
	
	if "cart" in file:
		print file,"0"
		cart_count+=1
		continue
	if "electr" in file:
		print file,"1"
		electronics_count+=1
	if "furn" in file:
		print file,"2"
		furn_count+=1
	if "mattress" in file:
		print file,"3"
		mattress_count+=1
	if "sofa" in file:
		print file,"4"
		sofa_count+=1
	if "trash_bags" in file:
		print file,"6"
		trash_bag_count+=1
		continue
	if "trash" in file:
		print file,"5"
		trash_count+=1
	if "tree" in file:
		print file,"7"
		trees_count+=1
	if "vehicle" in file:
		print file,"8"
		vehicle_count+=1
	if "human" in file:
		print file,"9"
		human_count+=1
	if "animals" in file:
		print file,"10"
		ani_count+=1
#print " animals: ", ani_count, " cart: ", cart_count, " electr : ", electronics_count," furniture: ", furn_count, " sofa: ", sofa_count, " trash_bags: ", trash_bag_count, " trash: ",trash_count, " tree: ", trees_count, " mattress: ", mattress_count, " human: ", human_count, " vehicle: ", vehicle_count
