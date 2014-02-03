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
	const CvMat* digit_data = data.get_values();
	Mat x = Mat::zeros(28,28,CV_8UC1); // 28x28 Matrix 8bits, single channel
	cout << "Rows: " << digit_data->rows << " Cols: " << digit_data->cols << endl;

	//using row 1 to skip the label row
	for(int i = 1; i < digit_data->rows; i++) {
		for(int j = 0; j < digit_data->cols; j++)
			cout << CV_MAT_ELEM(*digit_data, float, i, j) << " ";
		;;//cout << endl;
	}

	return 0;
}
