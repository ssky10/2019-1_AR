#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img = imread("../data/ryan.png",IMREAD_UNCHANGED);
	Mat img2 = imread("../data/windows.jpg");
	Mat roi = img2(Rect(100, 100, img.cols, img.rows));
	Mat channels[4]; //vector<Mat> channels;

	split(img, channels);
	cvtColor(img, img, COLOR_BGRA2BGR); // channels.pop_back(); merge(channels, img);

	img.copyTo(roi, channels[3]);
	imshow("ryan", img);
	imshow("windows", img2);
	waitKey();
	return 0;
}
