# FisherFaceRecognizer

A proyect that implements the FisherFaceRecognizer class of the OpenCV library to determine if a detected face corresponds to a key individual. The repo contains all the neccesary files to train the FisherFace identifier and implement it.

## Image Filesystem

To train the FisherFaceRecogntion models, we must supply an image database wich contains the faces of different people, each subject will have its own folder and corresponding key, the FisherFaceRecognizer will try to match the detected face with one of the keys in the database. Because of this a varied database improves chances of a unique detection.
To this end, the repo has an imageTrain directory which stores the folders of the different subjects (where the foldername will be the subject key), it is best practice to have the same amount of pictures of each subject. If we are looking to specifically detect a person, we should add more images his/her face to make a unique detection harder and reduce the amount of false positives:

An example of a Training Image folder
![File System](files.png?raw=true "Example of a training image file system")

## Training Utilities

For training the FisherFace model, I created utilities that simply and streamline the process:

- **trainerCapture.cpp:** uses a HaarCascade classifier to detect faces (in general) and stores them in the specified ID folder. This tool is useful for collecting the database, as it takes 69 pictures in less than 2 minutes. The user must create the folder before running the script.
- **imageFormater.py:** FisherFaces requieres that all training images be the same size, this script in python iterates through the training directory resizes and converts the images to grayscale.
- **csv_builder:** to train the FischerFaceRecognizer we must load the images to a vector and the key or label of the corresponing subject to another. To read the images and label conviently we store this information in a CSV file which is built in this python script. This script iterates the training images directory and places the information in the formar "trainFolder/subjectFolder/imageName;subjectID"
- **train.cpp:** reads the images and labels from the CSV files and  trains the FisherFaceRecognizer, saves the trained model as a.XML.

## FaceIdentifier

This is the main script, it reads the trained model from "fisherFace.xml", then it uses HaarCascade classifier to detect the faces in a given shot, it then applies the FisherFaceRecognizer, if it detects the specified key it displays a green box and displays a welcome message.

![Demo image](demo.jpg?raw=true "Demo of face-identifier")

