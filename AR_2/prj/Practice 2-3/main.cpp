#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

Mat src, gray;
int thresh = 200;
const int maxThresh = 255;
const int blockSize = 2;
const int apertureSize = 3;
const double k = 0.04;

const string imgPath = "../data/butterfly.jpg";

void cornerHarris(int, void*) {
	Mat res = Mat::zeros(src.size(), CV_32FC1);
	cornerHarris(gray, res, blockSize, apertureSize, k);
	normalize(res, res, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	Mat resMap;
	res.convertTo(resMap, CV_8UC1);
	Mat result;
	src.copyTo(result);
	for (int i = 0; i < res.rows; i++)
		for (int j = 0; j < res.cols; j++)
			if ((int)res.at<float>(i, j) > thresh)
				circle(result, Point(j, i), 1, Scalar(0, 255, 0), 2, 8, 0);
	imshow("responses", resMap);
	imshow("result", result);
}

int main(int argc, char** argv)
{
	src = imread(imgPath);
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("img", src);
	createTrackbar("Threshold: ", "img", &thresh, maxThresh, cornerHarris);
	cornerHarris(0, 0);
	waitKey(0);
	return 0;
}
