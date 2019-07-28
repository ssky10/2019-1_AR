#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace std;

const string imgPath = "../data/butterfly.jpg";

int main(int argc, char** argv)
{
	Mat img = imread(imgPath), result, desc;
	Ptr<Feature2D> siftd = xfeatures2d::SIFT::create();
	vector<KeyPoint> kps;
	siftd->detect(img, kps);
	siftd->compute(img, kps, desc);
	for (int i = 0; i < kps.size(); i++)
	{
		vector<KeyPoint> kp;
		kp.push_back(kps[i]);
		drawKeypoints(img, kp, result, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		for (int j = 0; j < desc.cols; j++)
			cout << desc.at<float>(i, j) << " ";
		cout << endl;
		imshow("result", result);
		waitKey(0);
	}	
	return 0;
}
