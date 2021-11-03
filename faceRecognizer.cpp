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
//trainerfromCSV
//input: src (string with direction of CSV file), labels, images (vectors passed by reference)
// A function that reads the paths stored in a CSV file and stores said images in a Mat vector.
void trainerfromCSV(string src, vector<int>&labels, vector<Mat>&images){
    ifstream CSV(src);
    if(!CSV){
        cout<<"Not a valid CSV file!"<<endl;
    }else{
        string line, path, label;
        while (getline(CSV,line)){
            stringstream liness(line);
            //get image path from CSV
            getline(liness,path,';');
            // get ID of face
            getline(liness,label);
            // If information read, right to vector
            if(!path.empty()&& !label.empty()){
                // read image from path and store in vector
                images.push_back(imread(path,0));
                // store image ID as int
                labels.push_back(atoi(label.c_str()));
            }   
        }
    }
}

void face_detect(Mat frame, CascadeClassifier target, vector<Rect>& Instances, double scale, Ptr<FaceRecognizer> model, int modelwidth, int modelheigh){
    Mat grayFrame;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY );
    equalizeHist( grayFrame, grayFrame );
    resize(grayFrame, grayFrame,Size(grayFrame.size().width /scale,grayFrame.size().height /scale));
    target.detectMultiScale(grayFrame, Instances,1.1,3,0,Size(25,25));
    

    for (int i = 0; i < Instances.size(); i++){
        Rect realArea = Rect(cvRound(Instances[i].x*scale),cvRound(Instances[i].y*scale),cvRound(Instances[i].width*scale),cvRound(Instances[i].height*scale));
        //crop the face
        Mat face = grayFrame(Instances[i]);
        //Resize the image to training images size (necessaty when using Eigen or Fisher faces)
        Mat predict;
        resize(face, predict, Size(modelwidth, modelheigh), 1.0, 1.0, INTER_CUBIC);
        int id = model->predict(predict);
        if(id!=0){
            string prediction = format("Not target!");
            putText(frame,prediction,Point(realArea.x -10,realArea.y-20),FONT_HERSHEY_PLAIN, 1.0, Scalar(0,0,255), 4);
            rectangle(frame,realArea, red,6);
            imshow("Detector", frame);
        }else{
            string prediction = format("Hello Pablo!!!");
            putText(frame,prediction,Point(realArea.x -10,realArea.y-20),FONT_HERSHEY_PLAIN, 1.0, Scalar(0,255,0), 4);
            rectangle(frame,realArea, Scalar(0,255,0),6);
            imshow("Detector", frame);
        }
        
    }

    if (Instances.size()==0){
        imshow("Detector",frame);
    }
}
int main(){
    int train_width = 200;
    int train_height = 200;
    Ptr<FaceRecognizer> model = FisherFaceRecognizer::create();
    model->read("/home/paok/Documents/FaceRecognition/Trainer_auxfiles/fisherFace.xml");
    
    // Load Haar Cacade data for faces
    CascadeClassifier faces_haar;
    faces_haar.load("/home/paok/Documents/FaceRecognition/Trainer_auxfiles/haarcascade_frontalface_alt2.xml");
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
        face_detect(frame,faces_haar,facesID,3.8,model,train_width,train_height);
        // Read key board input, setting esc as break key
        if(waitKey(5)== 27){
            break;
        }
    }
    return 0;
}