/*
 * Author: Viking Wizard Anthology
 * This program will read in images, and determine the digit within.
 * Neural Network Implementation
 */

#include <iostream>
#include <fstream>
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
#define ATTRIBUTES 784
#define HIDDEN_LAYERS 10


void print_images(int rowstart, int rowend, Mat x);
int main() {
    CvMLData data; 					//csv data object
    data.read_csv("./training_data/train.csv");
    data.set_response_idx(0);

    //Matrix to hold all the training data
    /*****************************************************/
    Mat converted=data.get_values();
    Mat x;
    converted.convertTo(x,CV_32FC1);
    Mat training_data(0,ATTRIBUTES,CV_32FC1);
    training_data.push_back(x.rowRange(1,x.rows).colRange(1,x.cols));
    Mat training_class(0,NUMBER_OF_CLASSES,CV_32FC1);

    for(int i=1; i < x.rows;i++)
    {
	Mat tmp = Mat::zeros(1,NUMBER_OF_CLASSES,CV_32FC1);
	tmp.at<float>(0,x.at<float>(i,0))= 1.0;
	training_class.push_back(tmp);
    }
    /*****************************************************/
    CvMLData data2; 					//csv data object
    data2.read_csv("./training_data/test.csv");
    data2.set_response_idx(0);
    //Matrix to hold all the testing data
    /*****************************************************/
    Mat converted2=data2.get_values();
    Mat x2;
    converted2.convertTo(x2,CV_32FC1);
    Mat testing_data(0,ATTRIBUTES,CV_32FC1);
    testing_data.push_back(x2.rowRange(1,x2.rows).colRange(0,x2.cols));
    Mat testing_class(0,NUMBER_OF_CLASSES,CV_32FC1);

    for(int i=1; i < x2.rows;i++)
    {
	Mat tmp = Mat::zeros(1,NUMBER_OF_CLASSES,CV_32FC1);
	tmp.at<float>(0,x2.at<float>(i,0))=1.0;
	testing_class.push_back(tmp);
    }
    /*****************************************************/
    //MAKE NEURAL NETWORK WITH:
    //inputs: 784	 (28x28)
    //hidden layers: 10
    //output classes: 10 (0-9)
    
    Mat layers(1,3,CV_32SC1);
    layers.at<int>(0,0) = ATTRIBUTES;
    layers.at<int>(0,1) = HIDDEN_LAYERS;
    layers.at<int>(0,2) = NUMBER_OF_CLASSES;

    CvANN_MLP NN;
    NN.create(layers,CvANN_MLP::SIGMOID_SYM,0.6,1); //why .6 and 1??
    					//stop training after 10000 iterations
					//or small change
    CvANN_MLP_TrainParams PARAMZ(cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,
						5000,0.000001),
	    			 CvANN_MLP_TrainParams::BACKPROP, 
				 //coefficients for training
				 0.1,0.1);
    /*****************************************************/
    //STORE CLASSIFIED GUESSES
    Mat classified(1,NUMBER_OF_CLASSES,CV_32FC1);
    /*****************************************************/
    cout << "Training...\n";
    long int iterations = NN.train(training_data, training_class ,Mat(),Mat(),PARAMZ);
    cout << "Training took " << iterations << " iterations\n";
    /*****************************************************/


    //ACCURACY
    Mat tester;
    int correct=0,incorrect=0; 
    int false_detection[NUMBER_OF_CLASSES] ={0,0,0,0,0,0,0,0,0,0};
    Point Max;
    cout << "Predicting....\n";
    ofstream fout;
    fout.open("classified.csv");
    fout << "ImageId,Label\n";

    for(int i=0; i < testing_data.rows; i++) {
	tester = testing_data.row(i);
	NN.predict(tester, classified);
	minMaxLoc(classified,0,0,0,&Max);
	//printf("Tested sample %d, -> %d\n",i, Max.x);

	if(!(testing_class.at<float>(i,Max.x)))
	{
	    incorrect++;
	    false_detection[(int)Max.x]++;
	}
	else
	    correct++;
	fout << i+1 <<"," << Max.x << endl;
    }
    fout.close();

    cout << "RESULTS\n";
    cout << "--------------------------------\n";
    cout << "Correct: " << correct << "(%" << (double) correct*100.0/testing_data.rows <<")"<< endl;
    cout << "Incorrect: " << incorrect << "(%" << (double) incorrect*100.0/testing_data.rows <<")"<< endl;

    cout << "Digit False Positive Breakdowns\n";
    cout << "--------------------------------\n";
    for (int i=0; i < NUMBER_OF_CLASSES; i++)
	cout << "DIGIT: " << i << " -> " << false_detection[i] 
	     <<"(%" << (double) false_detection[i]*100.0/testing_data.rows <<")"<< endl;



    //waitKey(0);

    return 0;
}



