#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace std;

const string objPath = "../data/3-1/book.jpg";
const string camPath = "../data/3-1/cam.jpg";

int main(int argc, char** argv)
{
	Ptr<Feature2D> siftd = xfeatures2d::SIFT::create();

	Mat objImg = imread(objPath), objDesc;
	vector<KeyPoint> objkps;
	siftd->detect(objImg, objkps);
	siftd->compute(objImg, objkps, objDesc);

	Mat camImg = imread(camPath), camDesc;
	vector<KeyPoint> camkps;
	siftd->detect(camImg, camkps);
	siftd->compute(camImg, camkps, camDesc);

	vector<DMatch> matches;
	BFMatcher matcher(NORM_L2SQR);
	matcher.match(objDesc, camDesc, matches);

	Mat result;
	drawMatches(objImg, objkps, camImg, camkps, matches, result,
		Scalar::all(-1), Scalar::all(-1),vector<char>(),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("match", result);
	waitKey();
	return 0;
}
