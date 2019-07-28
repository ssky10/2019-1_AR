#include "opencv2/opencv.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace std;

const string centerImgPath = "../data/center.jpg";
const string leftImgPath = "../data/left.jpg";
const string rightImgPath = "../data/right.jpg";

int main(void)
{
	/*1. SIFT 특징 추출 (그림 1) */
	Ptr<Feature2D> siftd = xfeatures2d::SIFT::create();
	Mat centerImg = imread(centerImgPath), centerDesc;
	vector<KeyPoint> centerkps;
	siftd->detect(centerImg, centerkps);
	siftd->compute(centerImg, centerkps, centerDesc);

	Mat leftImg = imread(leftImgPath), leftDesc;
	vector<KeyPoint> leftkps;
	siftd->detect(leftImg, leftkps);
	siftd->compute(leftImg, leftkps, leftDesc);

	Mat rightImg = imread(rightImgPath), rightDesc;
	vector<KeyPoint> rightkps;
	siftd->detect(rightImg, rightkps);
	siftd->compute(rightImg, rightkps, rightDesc);

	Mat result1;
	drawKeypoints(centerImg, centerkps, result1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("그림1", result1);

	/*2. 특징간 매칭 수행 (그림 2) */
	BFMatcher matcher(NORM_L2SQR);
	vector<DMatch> left2centerMatches;
	matcher.match(leftDesc, centerDesc, left2centerMatches); //left → center 로 가는 매칭 수행 

	vector<DMatch> right2centerMatches;
	matcher.match(rightDesc, centerDesc, right2centerMatches); //right → center로 가는 매칭 수행 

	Mat result2;
	drawMatches(leftImg, leftkps, centerImg, centerkps, left2centerMatches, result2);
	imshow("그림2", result2);

	/*3. 이미지간 호모그라피 계산 (그림 3-1/3-2) */
	vector<Point2f> from, to;
	for (int i = 0; i < left2centerMatches.size(); i++) {
		from.push_back(leftkps[left2centerMatches[i].queryIdx].pt);
		to.push_back(centerkps[left2centerMatches[i].trainIdx].pt);
	}
	Mat left2centerH = findHomography(from, to, RANSAC, 3.0);

	from.clear(); to.clear();
	for (int i = 0; i < right2centerMatches.size(); i++) {
		from.push_back(rightkps[right2centerMatches[i].queryIdx].pt);
		to.push_back(centerkps[right2centerMatches[i].trainIdx].pt);
	}
	Mat right2centerH = findHomography(from, to, RANSAC, 3.0);

	Mat leftWarpedImg;
	warpPerspective(leftImg, leftWarpedImg, left2centerH, leftImg.size());
	imshow("그림3-1", leftWarpedImg);

	Mat rightWarpedImg;
	warpPerspective(rightImg, rightWarpedImg, right2centerH, rightImg.size());
	imshow("그림3-2", rightWarpedImg);

	/*4. 파노라마 생성 (그림 4-1/4-2) */
	Mat panorama(centerImg.rows * 3, centerImg.cols * 3, centerImg.type(), Scalar(0));

	from.clear(), to.clear();
	from.push_back(Point2f(0, 0));
	to.push_back(Point2f(centerImg.cols, centerImg.rows));
	from.push_back(Point2f(centerImg.cols - 1, 0));
	to.push_back(Point2f(centerImg.cols * 2, centerImg.rows));
	from.push_back(Point2f(centerImg.cols - 1, centerImg.rows - 1));
	to.push_back(Point2f(centerImg.cols * 2, centerImg.rows*2));
	from.push_back(Point2f(0, centerImg.rows - 1));
	to.push_back(Point2f(centerImg.cols, centerImg.rows * 2));
	Mat moveH = findHomography(from, to); //이미지를 중앙으로 옮기는 호모그라피

	Mat mask, centerWarpedImgP;
	warpPerspective(Mat(centerImg.size(), CV_8UC1, Scalar(255)), mask, moveH, panorama.size());
	warpPerspective(centerImg, centerWarpedImgP, moveH, panorama.size());
	centerWarpedImgP.copyTo(panorama,mask);
	imshow("그림 4-1", panorama);

	Mat leftWarpedImgP;
	warpPerspective(Mat(leftImg.size(), CV_8UC1, Scalar(255)), mask, moveH*left2centerH, panorama.size());
	warpPerspective(leftImg, leftWarpedImgP, moveH*left2centerH, panorama.size());
	leftWarpedImgP.copyTo(panorama, mask);

	Mat rightWarpedImgP;
	warpPerspective(Mat(rightImg.size(), CV_8UC1, Scalar(255)), mask, moveH*right2centerH, panorama.size());
	warpPerspective(rightImg, rightWarpedImgP, moveH*right2centerH, panorama.size());
	rightWarpedImgP.copyTo(panorama, mask);

	imshow("그림 4-2", panorama);
	waitKey();

	return 0;
}