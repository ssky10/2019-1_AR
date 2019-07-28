#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img = imread("../data/ryan.jpg");
	Mat img2 = imread("../data/windows.jpg");
	Mat roi = img2(Rect(100, 100, img.cols, img.rows));
	Mat mask, gray;

	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat white(img.size(), CV_8UC1, Scalar(255));
	//imshow("gray", gray); imshow("white", white);
	bitwise_xor(gray, white, mask);
	//imshow("white", mask);
	img.copyTo(roi, mask);
	imshow("windows", img2);
	waitKey();
}
