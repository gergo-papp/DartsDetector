#include "stdafx.h"
#include "Utils.h"

int dist(const cv::Point& a, const cv::Point& b)
{
	return int(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

cv::Point findCenter(const cv::Mat& mat)
{
	std::vector<cv::Point> points;
	findNonZero(mat, points);
	cv::Point center;

	for (auto point : points)
		center += point;

	center.x /= int(points.size());
	center.y /= int(points.size());

	return center;
}