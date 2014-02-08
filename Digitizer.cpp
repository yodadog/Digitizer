/*
 * Author: Viking Wizard Anthology
 * This program will read in images, and determine the digit within.
 */

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>
#include <opencv/ml.h>

using namespace std;
using namespace cv;
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
	vector<vector<Point> > v; //DA VECTORZ OF VECTORZ
	int i=1;
	//for (int i=1; i < x.rows; i++)
	//{
		Mat temp(0,28,CV_8UC1);
		Mat image;
		for (int j=0; j < 28; j++) {
		    temp.push_back(x.rowRange(3,4).colRange(j*28,((j+1)*28)-1));
		}
		cout << temp << endl;
		
		findContours(temp,v,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
		unsigned int area =0;
		int idx;
		for (unsigned int j=0; j < v.size();j++) {
			if (area < v[j].size()){
				idx=i;
				area = v[j].size();
			}
		}
		//Calc bounding rect of largest area
		Rect rect = boundingRect(Mat(v[idx]));
		Point p1,p2;
		p1.x=rect.x;
		p1.y=rect.y;
		p2.x=rect.x + rect.width;
		p2.y=rect.y + rect.height;


	//}



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



