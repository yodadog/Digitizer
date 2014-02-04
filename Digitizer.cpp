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
	CvMLData data; //csv data object
	data.read_csv("./training_data/train.csv");
	data.set_response_idx(0);
	Mat x; //Matrix to hold all the digit data
	x=data.get_values();
	cout << "Rows: " << x.rows << " Cols: " << x.cols << endl;

	/* //show csv data
	cout << x;
	cout << endl;
	*/
	return 0;
}
