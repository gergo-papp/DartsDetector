#include "stdafx.h"
#include "Mask.h"

Mask::Mask(cv::Mat image)
{
	cv::Mat grayImage;
	cv::cvtColor(image, grayImage, cv::COLOR_RGB2GRAY);

	cv::Mat regions[3];
	cv::split(image, regions);

	regions[2] = regions[2] - grayImage;
	regions[1] = regions[1] - grayImage;

	cv::Mat redRegion;
	cv::Mat greenRegion;

	cv::threshold(regions[2], redRegion, 61, 255, cv::THRESH_BINARY);
	cv::threshold(regions[1], greenRegion, 15, 255, cv::THRESH_BINARY);

	cv::morphologyEx(redRegion, red, CV_MOP_CLOSE, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5)), CvPoint(-1, -1), 3);
	cv::morphologyEx(red, red, CV_MOP_ERODE, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 1);
	//cv::morphologyEx(greenRegion, green, CV_MOP_CLOSE, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 1);
	cv::morphologyEx(greenRegion, green, CV_MOP_ERODE, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 1);

	multipliers = red + green;

	cv::imshow("Red", red);
	cv::imshow("Green", green);
	cv::imshow("Multipliers", multipliers);
}
