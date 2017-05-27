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
	threshold(regions[1], greenRegion, 30, 255, cv::THRESH_BINARY);

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

	cv::Mat singleFilled = imfill_holes(single);
	double_ = board - singleFilled;


	cv::Mat innerRing = board - double_ - single;
	cv::Mat floodfillImage = innerRing.clone();
	floodFill(floodfillImage, cv::Point(0, 0), cv::Scalar(255));
	cv::Mat floodfillImageInverse;
	bitwise_not(floodfillImage, floodfillImageInverse);
	cv::floodFill(floodfillImageInverse, cv::Point(1, 1), cv::Scalar(255));
	bitwise_not(floodfillImageInverse, innerRing);

	triple = board - double_ - single;
	triple -= innerRing;

	outerBull = (multRings - double_ - triple) & green;
	innerBull = (multRings - double_ - triple) & red;

	cv::Mat BWImage;
	cv::threshold(grayImage, BWImage, 100, 255, CV_THRESH_BINARY);
	BWImage -= miss;
	BWImage += green;

	morphologyEx(BWImage, BWImage, CV_MOP_ERODE, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 3);
	morphologyEx(BWImage, BWImage, CV_MOP_DILATE, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 5);
	morphologyEx(BWImage, BWImage, CV_MOP_OPEN, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 2);
	morphologyEx(BWImage, BWImage, CV_MOP_CLOSE, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 2);


	morphologyEx(innerRing, innerRing, CV_MOP_DILATE, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 8);
	white = BWImage - innerRing;
	morphologyEx(white, white, CV_MOP_OPEN, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 1);

	black = board - BWImage - innerRing;
	morphologyEx(black, black, CV_MOP_OPEN, getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)), CvPoint(-1, -1), 1);


	if (showImages)
	{
		namedWindow("Red", cv::WINDOW_NORMAL);
		namedWindow("Green", cv::WINDOW_NORMAL);
		namedWindow("Multipliers", cv::WINDOW_NORMAL);
		namedWindow("Multiplier rings", cv::WINDOW_NORMAL);
		namedWindow("Temp Board", cv::WINDOW_NORMAL);
		namedWindow("Board", cv::WINDOW_NORMAL);
		namedWindow("Miss", cv::WINDOW_NORMAL);
		namedWindow("Single", cv::WINDOW_NORMAL);
		namedWindow("Single filled", cv::WINDOW_NORMAL);
		namedWindow("Double", cv::WINDOW_NORMAL);
		namedWindow("Triple", cv::WINDOW_NORMAL);
		namedWindow("Outer Bull", cv::WINDOW_NORMAL);
		namedWindow("Inner Bull", cv::WINDOW_NORMAL);
		namedWindow("Black", cv::WINDOW_NORMAL);
		namedWindow("White", cv::WINDOW_NORMAL);

		int width = 400;
		int height = 400;

		cv::resizeWindow("Red", width, height);
		cv::resizeWindow("Green", width, height);
		cv::resizeWindow("Multipliers", width, height);
		cv::resizeWindow("Multiplier rings", width, height);
		cv::resizeWindow("Temp Board", width, height);
		cv::resizeWindow("Board", width, height);
		cv::resizeWindow("Miss", width, height);
		cv::resizeWindow("Single", width, height);
		cv::resizeWindow("Single filled", width, height);
		cv::resizeWindow("Double", width, height);
		cv::resizeWindow("Triple", width, height);
		cv::resizeWindow("Outer Bull", width, height);
		cv::resizeWindow("Background", width, height);
		cv::resizeWindow("Black", width, height);
		cv::resizeWindow("White", width, height);

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
		imshow("Triple", triple);
		imshow("Outer Bull", outerBull);
		imshow("Inner Bull", innerBull);
		imshow("Black", black);
		imshow("White", white);
	}
}
