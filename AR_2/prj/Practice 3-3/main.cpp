#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace std;

const string objPath = "../data/3-1/book.jpg";
const string videoPath = "../data/3-3/greatescape2.mp4";
const string camPath = "../data/3-1/cam.jpg";

int main(int argc, char** argv)
{
	Ptr<Feature2D> siftd = xfeatures2d::SIFT::create();
	VideoCapture vidio;
	Mat videoImg, Hv2o;

	Mat objImg = imread(objPath), objDesc;
	vidio.open(videoPath);
	int width = vidio.get(CAP_PROP_FRAME_WIDTH) - 1;
	int height = vidio.get(CAP_PROP_FRAME_HEIGHT) - 1;

	vector<Point2f> from, to;
	from.push_back(Point2f(0, 0));
	to.push_back(Point2f(0, 0));
	from.push_back(Point2f(width, 0));
	to.push_back(Point2f(objImg.cols - 1, 0));
	from.push_back(Point2f(width, height));
	to.push_back(Point2f(objImg.cols - 1, objImg.rows - 1));
	from.push_back(Point2f(0, height));
	to.push_back(Point2f(0, objImg.rows - 1));
	Hv2o = findHomography(from, to);

	vector<KeyPoint> objkps;
	siftd->detectAndCompute(objImg, Mat(), objkps, objDesc);

	//on-line
	Mat camImg = imread(camPath), camDesc;
	vector<KeyPoint> camkps;
	siftd->detect(camImg, camkps);
	siftd->compute(camImg, camkps, camDesc);

	vector<DMatch> matches;
	BFMatcher matcher(NORM_L2SQR);
	matcher.match(objDesc, camDesc, matches);

	from.clear(), to.clear();
	for (int i = 0; i < matches.size(); i++) {
		from.push_back(objkps[matches[i].queryIdx].pt);
		to.push_back(camkps[matches[i].trainIdx].pt);
	}

	Mat inliner;
	Mat Ho2c = findHomography(from, to, RANSAC, 3.0, inliner);

	if (countNonZero(inliner) > 30) {
		while (true)
		{
			vidio >> videoImg;
			Mat warpedImg, mask;
			Mat Hv2c = Ho2c * Hv2o;
			warpPerspective(videoImg, warpedImg, Hv2c, camImg.size());
			warpPerspective(Mat(videoImg.size(), CV_8UC1, Scalar(255)), mask, Hv2c, camImg.size());
			warpedImg.copyTo(camImg, mask);
			imshow("camImg", camImg);
			waitKey(1);
		}
	}
	return 0;
}
