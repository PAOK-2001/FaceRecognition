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

int main(){
    // create the vectors to train model
    vector<Mat> images;
    vector<int> labels;
    // Source of training data
    string src = "/home/paok/Documents/FaceRecognition/Trainer_auxfiles/data.csv";
    // Create image and labels vector from data in src
    trainerfromCSV(src,labels,images);
    cout<<"Images used for training: "<<images.size()<<endl;
    Ptr<FaceRecognizer> model = LBPHFaceRecognizer::create();
    // Train and save model
    model->train(images, labels);
    model->save("faceModel.xml");

}