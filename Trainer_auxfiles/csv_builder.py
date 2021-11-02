# Script that creates CSV file from images in folder
from os import listdir
# Open CSV file where to store output data
csv_file= open("data.csv", "w")
# Specify directory where images used for training are stored
img_directory= "/home/paok/Documents/FaceRecognition/trainImages"
#create a list with file names in image directory
#Iterate through folder in img_directory
subjects= listdir(img_directory)
#Iterate through file name list and add to csv file
for i in range(len(subjects)):
    pictures = listdir("/home/paok/Documents/FaceRecognition/trainImages/"+subjects[i])
    for pic in pictures:
        # Format text for CSV file: directory/target/file_name/#number
        # sample: /home/paok/Documents/FaceRecognition/trainImages/target/IMG2.jpg;0
        out_put = img_directory+"/"+subjects[i]+"/"+pic+";"+subjects[i]
        csv_file.write(out_put)
        csv_file.write("\n")
