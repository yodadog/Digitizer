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

int main() {
	CvMLData data; 					//csv data object
	data.read_csv("./training_data/train.csv");
	data.set_response_idx(0);
	
	//Matrix to hold all the digit data
	Mat x; 						
	x=data.get_values();
	cout << "Rows: " << x.rows << " Cols: " << x.cols << endl;

	IplImage * img = cvCreateImage(Size(28,28),IPL_DEPTH_32F, 1);

	for (int i=0; i< 784; i+=28)
		cout << x(Range(4,5),Range(i,i+28)) << endl;//.colRange(i, i*28) << endl; 
	/* //show csv data
	cout << x;
	cout << endl;
	*/
	return 0;
}
