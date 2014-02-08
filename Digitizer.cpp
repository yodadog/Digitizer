/*
 * Author: Viking Wizard Anthology
 * This program will read in images, and determine the digit within.
 */

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <opencv/ml.h>

using namespace std;
using namespace cv;
RNG rng(31337);
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
	Mat temp(0,28,CV_8UC1);
	for (int j=0; j < 28; j++) {
	    temp.push_back(x.rowRange(i,i+1).colRange(j*28,((j+1)*28)));
	}

	findContours(temp,v,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
	vector<vector<Point> > contours_poly( v.size() );
	vector<Rect> boundRect(v.size());
	for (unsigned int j=0; j < v.size();j++) {
	    approxPolyDP( Mat(v[j]),contours_poly[j],3,true );
	    boundRect[j] = boundingRect( Mat(contours_poly[j]) );
	}

	/*//Drawing image to a window
	Mat drawing = Mat::zeros(28,28,CV_8UC3);
	for (unsigned int j=0; j < v.size(); j++) {
	    Scalar color = Scalar( rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255) );
	    drawContours(drawing, contours_poly, j , color);
	    rectangle(drawing, boundRect[j].tl(),boundRect[j].br(),color,2,8,0);
	}

	namedWindow("Contours",CV_WINDOW_NORMAL);
	imshow("Contours",drawing);
	*/

    }


    //waitKey(0);

    return 0;
}

//prints specified amount of images
//in 28x28 form
void print_images(int rowstart, int rowend, Mat x){
    if (rowstart == rowend)
	rowend++;
    if (rowstart < 1)
	rowstart = 1;
    if (rowend > x.rows)
	rowend = x.rows;
    for (int i=rowstart; i < rowend; i++)
	for (int j =0; j < 784; j+=28)
	    cout << x(Range(i,i+1),Range(j,j+28)) << endl;	
}



