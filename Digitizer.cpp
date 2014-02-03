/*
 * Author: Viking Wizard Anthology
 * This program will read in images, and determine the digit within.
 */

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>

using namespace std;
using namespace cv;

int main() {
	CvMLData data;
	data.read_csv("../training_data/train.csv");
	Mat x = Mat::zeros(28,28,CV_8UC1); // 28x28 Matrix 8bits, single channel

	cout << x << endl;

	return 0;
}
