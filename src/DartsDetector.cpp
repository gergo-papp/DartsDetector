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

int main()
{
	bool showImages = true;

	system("cls");
	cv::destroyAllWindows();


	// Read images:

	std::cout << "Reading background image.\n";
	cv::Mat backgroundImage = cv::imread("Images/background.bmp", cv::IMREAD_COLOR);

	std::cout << "Reading Dart Image.\n";
	cv::Mat dartImage = cv::imread("Images/dart.bmp", cv::IMREAD_COLOR);

	if (showImages)
	{
		cv::imshow("Background", backgroundImage);
		cv::imshow("Dart", dartImage);
	}


	// Grey level thresholding:

	std::cout << "Thresholding background image.\n";
	cv::Mat grayBackgroundImage;
	cv::cvtColor(backgroundImage, grayBackgroundImage, cv::COLOR_RGB2GRAY);

	cv::Mat BWBackgroundImage;
	auto thresholdValue = 75; // set by trial and error
	cv::threshold(grayBackgroundImage, BWBackgroundImage, thresholdValue, 255, cv::THRESH_BINARY_INV);

	if (showImages)
	{
		cv::imshow("Gray background image", grayBackgroundImage);
		cv::imshow("BW background image", BWBackgroundImage);
	}
	

	// Implement the matlab 'imfill' function
	// See: https://www.learnopencv.com/filling-holes-in-an-image-using-opencv-python-c/

	// TODO: Keep 'imfill' implementation or close the image

					cv::Mat floodfillImage = BWBackgroundImage.clone();
					floodFill(floodfillImage, cv::Point(0, 0), cv::Scalar(255));

					cv::Mat floodfillImageInverse;
					bitwise_not(floodfillImage, floodfillImageInverse);

					cv::Mat maskBackground = (BWBackgroundImage | floodfillImageInverse);

	cv::morphologyEx(BWBackgroundImage, maskBackground, CV_MOP_CLOSE, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 4);

	if (showImages)
	{
		cv::imshow("Mask background", maskBackground);
	}


	// Crop Images
	// TODO: crop images - only increases performance, not needed now


	// Create Point map

	Mask mask(backgroundImage);

	// Finish

	cv::waitKey(0);

	return 0;
}
