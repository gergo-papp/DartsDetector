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

int objectArea(cv::Mat_<uchar> img, uchar label)
{
	int area = 0;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img(i, j) == label)
			{
				area++;
			}
		}
	}

	return area;
}

cv::Point2i centerOfMass(cv::Mat_<uchar> img, uchar color, int area)
{
	int centerRow = 0;
	int centerCol = 0;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img(i, j) == color)
			{
				centerRow += i;
				centerCol += j;
			}
		}
	}

	centerRow /= area;
	centerCol /= area;

	return cv::Point2i(centerRow, centerCol);
}
