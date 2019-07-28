#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

const string imgPath = "../data/windows.jpg";

int main(int argc, char** argv)
{
	Mat img = imread(imgPath), gray, small, graysmall;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	resize(img, small, img.size() / 2);
	resize(gray, graysmall, gray.size() / 2);
	imshow("original", img);
	imshow("gray", gray);
	imshow("small", small);
	imshow("graysmall", graysmall);
	waitKey();
	return 0;
}
