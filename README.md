# Local Binary Patterns Histogram Recognizer

A proyect that implements the LBPHRecognizer class of the OpenCV library to determine if a detected face corresponds to a key individual. The repo contains all the neccesary files to train the a FaceRecognizer and implement it.

## Why LBPH ?

A quick foreword on the different FaceRecognizer models included in the opencv_contib repo. The models available in OpenCV are EigenFaces, FisherFaces and Local Binary Patterns Histograms. Without going into the mathematical theory (which you can find the recommended reading) I will give some consideration for choosing the best model:
- **EigenFaces** and **FisherFaces** are both based on Principal Component Analysis (PCA), with the difference being that FisherFaces also incorporates The Linear Discriminant Analysis. Because fo this, these two models have a similar performance -with Fisher being the most accurate-; although they are practical to implemente as they do not have a big computational strain, they are suceptible to changes in the circustances of detection, be it light, position, camera used, etc. Because of this Eigen and Fisher model need a great deal of processing on the dectected face to normalize the conditions, and also requiere a large and diverse training set.
- As is name suggests, **Local Binary Patterns Histograms** analize of the values of the pixels in picture matrix and constructs an histogram with said information. This is a less sophiscticated approach as it needs to analyze the enterity of the picture, because of this it has a higher computational strain. However, it is less suceptible to changes in conditions and thus it was choosen for a real-time application.

## Image Filesystem

To train the LBPHRecogntion models, we must supply an image database wich contains the faces of different people, each subject will have its own folder and corresponding key, the LBPHRecognizer will try to match the detected face with one of the keys in the database. Because of this a varied database improves chances of a unique detection.
To this end, the repo has an imageTrain directory which stores the folders of the different subjects (where the foldername will be the subject key), it is best practice to have the same amount of pictures of each subject. If we are looking to specifically detect a person, we should add more images his/her face to make a unique detection harder and reduce the amount of false positives:

An example of a Training Image folder
![File System](files.png?raw=true "Example of a training image file system")

## Training Utilities

For training the Local Binary Patterns Histogram model, I created utilities that simply and streamline the process:

- **trainerCapture.cpp:** uses a HaarCascade classifier to detect faces (in general) and stores them in the specified ID folder. This tool is useful for collecting the database, as it takes 69 pictures in less than 2 minutes. The user must create the folder before running the script.
- **imageFormater.py:** Local Binary Patterns Histograms requieres that all training images be the same size, this script in python iterates through the training directory resizes and converts the images to grayscale.
- **csv_builder:** to train the FischerFaceRecognizer we must load the images to a vector and the key or label of the corresponing subject to another. To read the images and label conviently we store this information in a CSV file which is built in this python script. This script iterates the training images directory and places the information in the formar "trainFolder/subjectFolder/imageName;subjectID"
- **train.cpp:** reads the images and labels from the CSV files and  trains the LBPHRecognizer, saves the trained model as a.XML.

## FaceIdentifier

The face identifier script uses Haar Cascade Classifiers to detect the face in a given shot, it then crops said face and applies a pre-processing saturation, bilateral filtering and a histogram equalization to make the subjects features more prominent and also eliminate noise. With that done, the face is feed to a LBPH Recognizer to make a prediction on the ID of the subject, in order for a successfull message to be displayed the detected ID must be mainted for 10 frames, this is done to avoid false detection while the subject is entering or leaving the frame (this also helps avoid false detections due to face masks).

### Demo
![Demo image](demo.gif?raw=true "Demo of face-identifier")


## Recommended reading
For more information on classifiers, check out the following links:

- [OpenCV FaceRecognizer Documentation](https://docs.opencv.org/2.4/modules/contrib/doc/facerec/facerec_tutorial.html) 
- [FaceRecognizer Methods Comparison](https://www.baseapp.com/computer-vision/a-comprehensive-guide-to-facial-recognition-algorithms/)
- [Paper on image processing for succesfull LBPH detection](https://www.sciencedirect.com/science/article/pii/S2590005619300141)


