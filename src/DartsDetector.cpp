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
#include "Utils.h"
#include "Labeling.h"

int width = 500;
int height = 500;

Mask mask;
cv::Point2i center;
Labeling labels;

void ObjectInfoCallBack(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cv::Mat_<cv::Vec3b>* src = static_cast<cv::Mat_<cv::Vec3b>*>(param);
		cv::Point2i pixelLoc(x, y);

		std::cout << "\n";

		if (mask.miss(pixelLoc) == 255)
		{
			std::cout << "Miss!";
			return;
		}

		if (mask.innerBull(pixelLoc) == 255)
		{
			std::cout << "2 x 25";
			return;
		}
		if (mask.outerBull(pixelLoc) == 255)
		{
			std::cout << "25";
			return;
		}
		
		if (mask.triple(pixelLoc) == 255)
		{
			std::cout << "3 x ";
		}
		else if (mask.double_(pixelLoc) == 255)
		{
			std::cout << "2 x ";
		}

		int value = labels.fullLabel(pixelLoc);
		
		
		if (value == 0)
			std::cout << "?"; // TODO: approximate value by the closest slice
		else
			std::cout << value;
	}
}

int main()
{
	bool showImages = false;

	system("cls");
	cv::destroyAllWindows();


	// Read images:

	std::cout << "Reading background image.\n";
	cv::Mat backgroundImage = imread("Images/DartHigh.jpg", cv::IMREAD_COLOR);
	
	std::cout << "Reading Dart Image.\n";
	cv::Mat dartImage = imread("Images/DartHigh.jpg", cv::IMREAD_COLOR);

	if (backgroundImage.empty() || dartImage.empty())
	{
		return -1;
	}



	// Blur images to reduce noise:

	cv::GaussianBlur(backgroundImage, backgroundImage, cv::Size(3, 3), 1, 0);
	cv::GaussianBlur(dartImage, dartImage, cv::Size(3, 3), 1, 0);

	if (showImages)
	{
		namedWindow("Background", cv::WINDOW_NORMAL);
		namedWindow("Dart", cv::WINDOW_NORMAL);

		cv::resizeWindow("Background", width, height);
		cv::resizeWindow("Dart", width, height);

		imshow("Background", backgroundImage);
		imshow("Dart", dartImage);
	}



	// Grey level thresholding:

	std::cout << "Thresholding background image.\n";
	cv::Mat grayBackgroundImage;
	cvtColor(backgroundImage, grayBackgroundImage, cv::COLOR_RGB2GRAY);

	cv::Mat BWBackgroundImage;
	auto thresholdValue = 90; // set by trial and error
	threshold(grayBackgroundImage, BWBackgroundImage, thresholdValue, 255, cv::THRESH_BINARY_INV);

	if (showImages)
	{
		namedWindow("Gray background image", cv::WINDOW_NORMAL);
		namedWindow("BW background image", cv::WINDOW_NORMAL);

		cv::resizeWindow("Gray background imaged", width, height);
		cv::resizeWindow("BW background image", width, height);

		imshow("Gray background image", grayBackgroundImage);
		imshow("BW background image", BWBackgroundImage);
	}
	
	cv::Mat maskBackground = imfill_holes(BWBackgroundImage);
	morphologyEx(maskBackground, maskBackground, CV_MOP_CLOSE, getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5)), CvPoint(-1, -1), 1);
	morphologyEx(maskBackground, maskBackground, CV_MOP_DILATE, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 2);

	if (showImages)
	{
		namedWindow("Mask background", cv::WINDOW_NORMAL);

		cv::resizeWindow("Mask background", width, height);

		imshow("Mask background", maskBackground);
	}



	// Crop Images
	// TODO: crop images - only increases performance, not needed now



	// Create Point map:

	std::cout << "Creating point map.\n";
	mask = Mask(backgroundImage);



	// Center:

	center = findCenter(mask.innerBull);

	std::cout << "Center: (" << center.x << ", " << center.y << ").\n";


	// Assign a value to each pixel:

	labels = Labeling(mask.white, mask.black, center);



	// Wait on user input and detect score

	namedWindow("Dart Image", cv::WINDOW_NORMAL);
	cv::resizeWindow("Dart Image", width, height);
	cv::setMouseCallback("Dart Image", ObjectInfoCallBack, &backgroundImage);
	imshow("Dart Image", backgroundImage);

	cv::waitKey(0);

	return 0;
}
