#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

const string imgPath = "../data/windows.jpg";

int main(int argc, char** argv)
{
	Mat img = imread(imgPath);
	imshow("result", img);
	waitKey();
	return 0;
}
