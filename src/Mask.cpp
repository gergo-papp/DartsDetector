#include "stdafx.h"
#include "Mask.h"
#include "ImFill.h"

Mask::Mask(cv::Mat image)
{
	bool showImages = true;

	cv::Mat grayImage;
	cvtColor(image, grayImage, cv::COLOR_RGB2GRAY);

	cv::Mat regions[3];
	split(image, regions);

	regions[2] = regions[2] - grayImage;
	regions[1] = regions[1] - grayImage;

	cv::Mat redRegion;
	cv::Mat greenRegion;

	threshold(regions[2], redRegion, 61, 255, cv::THRESH_BINARY);
	threshold(regions[1], greenRegion, 15, 255, cv::THRESH_BINARY);

	morphologyEx(redRegion, red, CV_MOP_CLOSE, getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5)), CvPoint(-1, -1), 3);
	morphologyEx(red, red, CV_MOP_ERODE, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 1);
	//cv::morphologyEx(greenRegion, green, CV_MOP_CLOSE, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 1);
	morphologyEx(greenRegion, green, CV_MOP_ERODE, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 1);

	multipliers = red + green;

	morphologyEx(multipliers, multRings, CV_MOP_DILATE, getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)), CvPoint(-1, -1), 3);
	morphologyEx(multRings, multRings, CV_MOP_CLOSE, getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5)), CvPoint(-1, -1), 3);

	cv::Mat tempBoard= imfill_holes(multRings);
	morphologyEx(tempBoard, board, CV_MOP_CLOSE, getStructuringElement(cv::MORPH_CROSS, cv::Size(15, 15)), CvPoint(-1, -1), 7);
	morphologyEx(board, board, CV_MOP_DILATE, getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5)), CvPoint(-1, -1), 5);
	morphologyEx(board, board, CV_MOP_ERODE, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 11);

	cv::bitwise_not(board, miss);

	single = board - multRings;

	cv::Mat singleFilled = imfill_holes(single); // TODO: Fix!
	double_ = board - singleFilled;

	std::vector<cv::Vec3d> circles;
	cv::HoughCircles(single, circles, CV_HOUGH_GRADIENT, 1, 1);

	if (showImages)
	{
		imshow("Red", red);
		imshow("Green", green);
		imshow("Multipliers", multipliers);
		imshow("Multiplier rings", multRings);
		imshow("Temp Board", tempBoard);
		imshow("Board", board);
		imshow("Miss", miss);
		imshow("Single", single);
		imshow("Single filled", singleFilled);
		imshow("Double", double_);
	}
}
