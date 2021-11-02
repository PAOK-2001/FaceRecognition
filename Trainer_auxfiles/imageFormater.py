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
        path = "/home/paok/Documents/FaceRecognition/trainImages/"+subjects[i]+"/"+pic
        #Open image in direcotry
        image = cv.imread(path)
        #Convert it to gray scale
        image = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
        #Resize to 168x192 like Yale library
        image = cv.resize(image,(168,192))
        cv.imwrite(path, image)


