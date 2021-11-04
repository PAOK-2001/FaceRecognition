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
//haar_detect
//Description: Detection of faces in fram using Haar Cascade classifier and store said images in specified folder-
void haar_detect(Mat frame, CascadeClassifier target, vector<Rect>& Instances, double scale, int& total, string folder){
    Mat grayFrame;
    // Convert frame to grayscale
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY );
    equalizeHist( grayFrame, grayFrame );
    resize(grayFrame, grayFrame,Size(grayFrame.size().width /scale,grayFrame.size().height /scale));
    // Detected the perimiter of a faces in frame as a rectangle ans store it in Instances
    target.detectMultiScale(grayFrame, Instances,1.1,3,0,Size(25,25));
    Scalar color = Scalar(0,0,255);
    // Iterate instances
    for (int i = 0; i < Instances.size(); i++){
        Rect realArea = Rect(cvRound(Instances[i].x*scale),cvRound(Instances[i].y*scale),cvRound(Instances[i].width*scale),cvRound(Instances[i].height*scale));
        //crop the face
        Mat face = grayFrame(Instances[i]);
        // Draw rectagle around face
        rectangle(frame,Point(cvRound(Instances[i].x*scale),cvRound(Instances[i].y*scale)),Point(cvRound((Instances[i].x +Instances[i].width)*scale),cvRound((Instances[i].y +Instances[i].height)*scale)), color,6);
        imshow("Detector", frame);
        // Write detected Face to specified folder as a .jpg
        imwrite("/home/paok/Documents/FaceRecognition/trainImages/"+folder+"/"+to_string(total)+".jpg",face);
    }
    // Show frame even when no faces detected
    if (Instances.size()==0){
        imshow("Detector",frame);
    }
}
int main() {
    // Define values from image path
    string folder;
    int start; // Initial value, usefull for adding pictures to existing folder
    cout<< "ID of subject:  ";
    cin>> folder;
    cout<<"\n" <<"Pictures in folder:  ";
    cin>> start;
    int total = start+1;
    // Load Haar Cacade data for faces
    CascadeClassifier faces_haar;
    faces_haar.load("/home/paok/Documents/OpenCV_Practice/FaceIdentifier/haarcascade_frontalface_alt2.xml");
    // Create OpenCV frame object to store frame information
    Mat frame;
    // Create VideoCapture object, reading video device (USB camera)
    VideoCapture camera(2);
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
        haar_detect(frame,faces_haar,facesID,1.5,total,folder);
        // Read key board input, setting esc as break key
        // Check of the 69 photos have been taken
        if(waitKey(550)== 27 || total>=69+start){
            break;
        }
        cout<<"Faces registered "<<total<<"\n";
        total++;
    }
    return 0;
}