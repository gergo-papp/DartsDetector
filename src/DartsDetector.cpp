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

int width = 500;
int height = 500;

int dist(const cv::Point& a, const cv::Point& b)
{
	return int(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

/*std::vector<cv::Vec<int, 4>> filterLines(const std::vector<cv::Vec<int, 4>>&  lines, cv::Point center, const Mask& mask)
{
	std::vector<cv::Vec<int, 4>> filteredLines;
	int rectSize = 20;
	cv::Rect_<int> centerRectangle = cv::Rect_<int>(center.x - rectSize / 2, center.y - rectSize / 2, rectSize, rectSize);
	cv::Vec<int, 4> referenceLine;
	int maxDist = -1;

	for (auto line : lines)
	{
		cv::Point a(line[0], line[1]);
		cv::Point b(line[2], line[3]);

		if (dist(a, b) > maxDist)
		{
			maxDist = dist(a, b);
			referenceLine = line;
		}
	}

	filteredLines.push_back(referenceLine);

	return filteredLines;
}*/

int main()
{
	bool showImages = true;

	system("cls");
	cv::destroyAllWindows();


	// Read images:

	std::cout << "Reading background image.\n";
	cv::Mat backgroundImage = imread("Images/DartHigh.jpg", cv::IMREAD_COLOR);
	cv::GaussianBlur(backgroundImage, backgroundImage, cv::Size(3, 3), 1, 0);

	std::cout << "Reading Dart Image.\n";
	cv::Mat dartImage = imread("Images/DartHigh.jpg", cv::IMREAD_COLOR);
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
		namedWindow("Gray background imaged", cv::WINDOW_NORMAL);
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
	Mask mask(backgroundImage);

	// Center:

	std::vector<cv::Point> points;
	cv::Point center;
	findNonZero(mask.innerBull, points);
	for (auto point : points)
		center += point;
	center.x /= int(points.size());
	center.y /= int(points.size());

	std::cout << "Center: (" << center.x << ", " << center.y << ").\n";

/*	// Edge detection:

	cv::Mat edgeImage;
	cv::Canny(grayBackgroundImage & mask.board, edgeImage, 150, 200);
	morphologyEx(edgeImage, edgeImage, CV_MOP_CLOSE, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 3);

	// Straight line detection:

	cv::Mat linesImage = backgroundImage.clone();


	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(edgeImage, lines, 1, CV_PI / 180, 90, 150, 15);
	lines = filterLines(lines, center, mask);
	for (size_t i = 0; i < lines.size(); i++)
	{
		line(linesImage, cv::Point(lines[i][0], lines[i][1]),
		     cv::Point(lines[i][2], lines[i][3]), cv::Scalar(0, 0, 255), 3, 8);
	}
	line(linesImage, cv::Point(center.x, center.y),
		cv::Point(center.x, center.y), cv::Scalar(255, 0, 0), 3, 8);
	

	if (showImages)
	{
		namedWindow("Edges", cv::WINDOW_NORMAL);
		namedWindow("Lines", cv::WINDOW_NORMAL);

		cv::resizeWindow("Edges", width, height);
		cv::resizeWindow("Lines", width, height);

		imshow("Edges", edgeImage);
		imshow("Lines", linesImage);
	}*/
	

	// Finish


	cv::waitKey(0);

	return 0;
}
