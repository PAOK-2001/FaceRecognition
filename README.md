# FisherFaceRecognizer

A proyect that impements the FisherFace class of the openCV library to determine if a detected face corresponds to a key individual. The repo contains all the neccesary files to train the FisherFace identifier an implement it.

## Image Filesystem

To train the FisherFace models, we must supply an image database wich contains the faces of different people, each subject will have it own folder and corresponding key, the FisherFaceRecognizer will try to match the detected face with one of the keys in the database, because of this a varied database improves chances of a unique detection.
Because of this, the repo has a imageTrain directory which stores the folders of the different subjects (where the foldername will be the subject key), it is best practice to have the same amount of picture of each subject, giving priority to the key subjects to detect.

## Training Utilities

For training the FisherFace model, I created training utilities that simply and streamline the process:

- **trainerCapture.cpp:** uses HaarCascade classifier to detect faces (in general) and stores them in the specified ID folder. This tool is useful for collecting the database, as it takes 69 pictures in less than 2 minutes. The user must create the folder before running the script.
- **imageFormater.py:** FisherFaces requieres that all training images be the same size, this script in python iterates through the training directory resizes and converts the images to grayscale.
- **csv_builder:** to train the FischerFaceRecognizer we must load the images to a vector and the key or label of the corresponing subject to another. To read the iamges and label conviently we store this information in a CSV file which is built in this python script.
- **train.cpp:** reads the images and labels from the CSV files and calls trains the FisherFaceRecognizer, saves the train model as a.XML.

## FaceIdentifier

This is the main script, it reads the trained model from "fisherFace.xml", then it uses HaarCascade classifier to detect the faces in a given shot, it then applies the FisherFaceRecognizer, if it detects the specified key it displays a green box and displays a welcome message.

![Demo image](demo.jpg?raw=true "Demo of face-identifier")

