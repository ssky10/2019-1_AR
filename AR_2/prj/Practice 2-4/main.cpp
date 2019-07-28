#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

Mat gray;
int std_dev = 10;
const int maxThresh = 100;

const string imgPath = "../data/butterfly.jpg";

void gaussianBlur(int, void*) {
	if (std_dev == 0) return;
	Mat res = Mat(gray.size(), CV_32FC1);
	GaussianBlur(gray, res, Size(0,0), std_dev/10.0);
	imshow("result", res);
}

int main(int argc, char** argv)
{
	gray = imread(imgPath, IMREAD_GRAYSCALE);
	imshow("img", gray);
	createTrackbar("10*std_dev: ", "img", &std_dev, maxThresh, gaussianBlur);
	gaussianBlur(0, 0);
	waitKey(0);
	return 0;
}
