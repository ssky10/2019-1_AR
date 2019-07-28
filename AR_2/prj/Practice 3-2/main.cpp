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

	vector<Point2f> from, to;
	for (int i = 0; i < matches.size(); i++) {
		from.push_back(objkps[matches[i].queryIdx].pt);
		to.push_back(camkps[matches[i].trainIdx].pt);
	}

	Mat inliner;
	Mat H = findHomography(from, to, RANSAC, 3.0,inliner);
	cout << countNonZero(inliner);
	if (countNonZero(inliner) > 30) {
		Mat warpedImg;
		warpPerspective(objImg, warpedImg, H, camImg.size());
		imshow("warpedImg", warpedImg);
	}

	waitKey();
	return 0;
}
