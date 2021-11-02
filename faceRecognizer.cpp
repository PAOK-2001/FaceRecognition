#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <bits/stdc++.h>
#include <sys/timeb.h>
using namespace std;
using namespace cv;

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
            stringstream liness;
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