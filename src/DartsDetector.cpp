/*
 * Project title: Using Image Processing to Identify and Score Darts thrown into a Dartboard
 * Project resource: http://web.stanford.edu/class/ee368/Project_Autumn_1516/Reports/Delaney.pdf
 * Laboratory: Image Processing 2017, Technical University
 * Laboratory assistant: Andra Petrovai
 * 
 * Student: Gergő Papp-Szentannai
 * Group: 30431
 * 
 * GitHub: https://github.com/gergo13/DartsDetector
 * 
 * 
 * Copyright (C) 2017 Gergő Papp-Szentannai
 */

#include "stdafx.h"
#include "Mask.h"
#include "ImFill.h"

int main()
{
	bool showImages = true;

	system("cls");
	cv::destroyAllWindows();


	// Read images:

	std::cout << "Reading background image.\n";
	cv::Mat backgroundImage = imread("Images/background.bmp", cv::IMREAD_COLOR);

	std::cout << "Reading Dart Image.\n";
	cv::Mat dartImage = imread("Images/dart.bmp", cv::IMREAD_COLOR);

	if (showImages)
	{
		imshow("Background", backgroundImage);
		imshow("Dart", dartImage);
	}


	// Grey level thresholding:

	std::cout << "Thresholding background image.\n";
	cv::Mat grayBackgroundImage;
	cvtColor(backgroundImage, grayBackgroundImage, cv::COLOR_RGB2GRAY);

	cv::Mat BWBackgroundImage;
	auto thresholdValue = 75; // set by trial and error
	threshold(grayBackgroundImage, BWBackgroundImage, thresholdValue, 255, cv::THRESH_BINARY_INV);

	if (showImages)
	{
		imshow("Gray background image", grayBackgroundImage);
		imshow("BW background image", BWBackgroundImage);
	}
	

	cv::Mat maskBackground = imfill_holes(BWBackgroundImage);
	morphologyEx(maskBackground, maskBackground, CV_MOP_CLOSE, getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5)), CvPoint(-1, -1), 1);
	morphologyEx(maskBackground, maskBackground, CV_MOP_DILATE, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 2);

	if (showImages)
	{
		imshow("Mask background", maskBackground);
	}


	// Crop Images
	// TODO: crop images - only increases performance, not needed now


	// Create Point map

	std::cout << "Creating point map.\n";
	Mask mask(backgroundImage);

	// Center

	std::vector<cv::Point> points;
	cv::Point center;
	findNonZero(mask.innerBull, points);
	for (auto point : points)
		center += point;
	center.x /= points.size();
	center.y /= points.size();

	std::cout << "Center: (" << center.x << ", " << center.y << ").\n";


	// Finish


	cv::waitKey(0);

	return 0;
}
