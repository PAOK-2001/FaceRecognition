#This script will format all images in a given directory to the same size and to gray scale using OpenCV
from scipy import ndimage, misc
import numpy as np
import cv2 as cv
from os import listdir
#Iterate throuh the training image directory and sub folders
img_directory= "/home/paok/Documents/FaceRecognition/trainImages"
#create a list with file names in image directory
#Iterate through folder in img_directory
subjects= listdir(img_directory)
#Iterate through file name list and add to csv file
for i in range(len(subjects)):
    pictures = listdir("/home/paok/Documents/FaceRecognition/trainImages/"+subjects[i])
    for pic in pictures:
        filtered = np.zeros((256, 256, 1), dtype = "uint8")
        path = "/home/paok/Documents/FaceRecognition/trainImages/"+subjects[i]+"/"+pic
        #print(path)
        #Open image in direcotry
        image = cv.imread(path)
        #Convert it to gray scale
        image = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
        #Saturate image
        image = 1.2*image
        #Format as float32
        img = np.array(image, dtype=np.float32)
        #Filter
        filtered = cv.bilateralFilter(img,2,15,15)
        #Resize to 200x200 pixels
        filtered = cv.resize(filtered,(200,200))
        wrt = np.array(filtered, dtype="uint8")
        write = cv.equalizeHist(wrt)
        cv.imwrite(path, write)



