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


void haar_detect(Mat frame, CascadeClassifier target, vector<Rect>& Instances, double scale, int& total, string folder){
    Mat grayFrame;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY );
    equalizeHist( grayFrame, grayFrame );
    resize(grayFrame, grayFrame,Size(grayFrame.size().width /scale,grayFrame.size().height /scale));
    target.detectMultiScale(grayFrame, Instances,1.1,3,0,Size(25,25));
    Scalar color = Scalar(0,0,255);
    for (int i = 0; i < Instances.size(); i++){
        Rect realArea = Rect(cvRound(Instances[i].x*scale),cvRound(Instances[i].y*scale),cvRound(Instances[i].width*scale),cvRound(Instances[i].height*scale));
        //crop the face
        Mat face = grayFrame(Instances[i]);
        rectangle(frame,Point(cvRound(Instances[i].x*scale),cvRound(Instances[i].y*scale)),Point(cvRound((Instances[i].x +Instances[i].width)*scale),cvRound((Instances[i].y +Instances[i].height)*scale)), color,6);
        imshow("Detector", frame);
        imwrite("/home/paok/Documents/FaceRecognition/trainImages/"+folder+"/"+to_string(total)+".jpg",face);
    }

    if (Instances.size()==0){
        imshow("Detector",frame);
    }
}
int main() {
    // Load Haar Cacade data for faces
    string folder;
    cout<< "ID de sujeto:  ";
    cin>> folder;
    int total = 0;
    CascadeClassifier faces_haar;
    faces_haar.load("/home/paok/Documents/OpenCV_Practice/FaceIdentifier/haarcascade_frontalface_alt2.xml");
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
        haar_detect(frame,faces_haar,facesID,1.5,total,folder);
        // Read key board input, setting esc as break key
        if(waitKey(550)== 27 || total>=68){
            break;
        }
        cout<<"Faces registered "<<total<<"\n";
        total++;
    }
    return 0;
}