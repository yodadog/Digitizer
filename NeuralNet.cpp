/*
 * Author: Viking Wizard Anthology
 * This program will read in images, and determine the digit within.
 * Neural Network Implementation
 */

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <opencv/ml.h>
#include <cstdlib>
#include <vector>

using namespace std;
using namespace cv;
RNG rng(31337); // RNG seed set

/* Magic Constant DEFINES */
#define PIX_DIM 28		//image pixel size= 28x28
#define NUMBER_OF_CLASSES 10 	//classes=0-9


void print_images(int rowstart, int rowend, Mat x);
int main() {
    CvMLData data; 					//csv data object
    data.read_csv("./training_data/train.csv");
    data.set_response_idx(0);

    //Matrix to hold all the digit data
    Mat converted=data.get_values();
    Mat x;
    converted.convertTo(x,CV_8UC1);
    cout << "Rows: " << x.rows << " Cols: " << x.cols << endl;

    //print_images(1,100,x);	
    /*----------------------------------------------*/
    /*Bounding boxes of each image*/
    //for (int i=1; i < x.rows; i++)
    int i=1;
    {
	vector<vector<Point> > v; //DA VECTORZ OF VECTORZ
	Mat temp(0,PIX_DIM,CV_8UC1);
	for (int j=0; j < PIX_DIM; j++) {
	    temp.push_back(x.rowRange(i,i+1).colRange(j*PIX_DIM,((j+1)*PIX_DIM)));
	}

	//findContours changes temp so save actual number here
	int trainer = temp.at<int>(0,0);
	//cout <<temp << endl;
	//cout << trainer << endl;
    }


    //waitKey(0);

    return 0;
}



