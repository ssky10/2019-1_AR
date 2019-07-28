#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace std;

const string imgPath = "../data/butterfly.jpg";

int main(int argc, char** argv)
{
	Mat img = imread(imgPath), result;
	Ptr<Feature2D> siftd = xfeatures2d::SIFT::create();
	vector<KeyPoint> kps;
	siftd->detect(img, kps);
	drawKeypoints(img, kps, result,Scalar::all(-1),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("result", result);
	waitKey(0);
	return 0;
}
