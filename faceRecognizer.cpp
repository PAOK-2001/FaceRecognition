#include <bits/stdc++.h>

#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;

Scalar red = Scalar(0,0,255);
int contador = 0;
//face_detect
// Description: given a frame, performes a face detection usign the HaarCascade Clasifier. Of the faces detected uses LBPHRecognizer to predict ID from database
// and determine if person is the desired individual
void face_detect(Mat frame, CascadeClassifier target, vector<Rect>& Instances, double scale, Ptr<FaceRecognizer> model, int modelwidth, int modelheigh){
    Mat grayFrame;
    // Convrt frame to gray scale
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY );
    equalizeHist( grayFrame, grayFrame );
    // Resize according to specified scale, to improve HaarCascade face recognition
    resize(grayFrame, grayFrame,Size(grayFrame.size().width /scale,grayFrame.size().height /scale));
    // Detected the perimiter of a faces in frame as a rectangle and store it in Instances
    target.detectMultiScale(grayFrame, Instances,1.1,3,0,Size(145,145));
    
    // Iterate through detected face perimiter
    for (int i = 0; i < Instances.size(); i++){
        Rect realArea = Rect(cvRound(Instances[i].x*scale),cvRound(Instances[i].y*scale),cvRound(Instances[i].width*scale),cvRound(Instances[i].height*scale));
        //crop the face
        Mat face = grayFrame(Instances[i]);
        // Adjust face contrast by a factor of 1.5
        face = 1.2*face;
        // Apply filtering
        Mat filtered;
        bilateralFilter(face,filtered,2,15,15);
        //Apply histogram equalization
        equalizeHist(filtered, filtered);
        //Resize the image to training images size (necessary when using Eigen or Fisher faces)
        //resize(face, face, Size(modelwidth, modelheigh), 1.0, 1.0, INTER_CUBIC);
        // Get preddicted ID from LBPH Method
        int id = model->predict(face);
        // Contador
        // Check if it is desired individual
        if(id==2||id==0){
            contador++;
            if(contador >=10){
                string prediction = format("Welcome!!");
                putText(frame,prediction,Point(realArea.x -10,realArea.y-20),FONT_HERSHEY_PLAIN, 1.0, Scalar(0,255,0), 3);
                rectangle(frame,realArea, Scalar(0,255,0),6);
                imshow("Detector", frame);
            }else{
                string prediction = format("Determining");
                putText(frame,prediction,Point(realArea.x -10,realArea.y-20),FONT_HERSHEY_PLAIN, 1.0, Scalar(100,100,0), 3);
                rectangle(frame,realArea, Scalar(100,100,0),6);
                imshow("Detector", frame);
            }
            
        }else{
            contador = 0;
            string prediction = format("Not target!");
            putText(frame,prediction,Point(realArea.x -10,realArea.y-20),FONT_HERSHEY_PLAIN, 1.0, Scalar(0,0,255), 3);
            rectangle(frame,realArea, red,6);
            imshow("Detector", frame);
        }   
    }
    // Show frame even if there is no faces to show user camera feed.
    if (Instances.size()==0){
        imshow("Detector",frame);
    }
}

int main(){
    // Define training image dimensions
    int train_width = 200;
    int train_height = 200;
    // Create recognition model
    Ptr<FaceRecognizer> model = LBPHFaceRecognizer::create();
    // Read pretrained model from .XML
    model->read("/home/paok/Documents/FaceRecognition/Trainer_auxfiles/faceModel.xml");
    
    // Load Haar Cacade data for faces
    CascadeClassifier faces_haar;
    faces_haar.load("/home/paok/Documents/FaceRecognition/Trainer_auxfiles/haarcascade_frontalface_alt2.xml");
    // Create OpenCV frame object to store frame information
    Mat frame;
    // Create VideoCapture object, reading video device (USB camera)
    VideoCapture camera(0);
    vector<Rect>facesID;
    // Check if the camera is readable
    if(!camera.isOpened()){
        cout<<"Error reading camera feed";
        return -1;
    }
    for (;;){
        camera.read(frame);
        // Check if selected device is sending information
        if(frame.empty()){
            cout<<"NULL frame ";
            break;
        }
        //Run face recognition function
        face_detect(frame,faces_haar,facesID,1.5,model,train_width,train_height);
        // Read key board input, setting esc as break key
        if(waitKey(5)== 27){
            break;
        }
    }
    return 0;
}