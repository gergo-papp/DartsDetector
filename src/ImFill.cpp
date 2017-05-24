#include "stdafx.h"
#include "ImFill.h"

// Implement the matlab 'imfill' function
// See: https://www.learnopencv.com/filling-holes-in-an-image-using-opencv-python-c/
cv::Mat imfill_holes(cv::Mat sourceImage)
{
	cv::Mat floodfillImage = sourceImage.clone();
	floodFill(floodfillImage, cv::Point(0, 0), cv::Scalar(255));

	cv::Mat floodfillImageInverse;
	bitwise_not(floodfillImage, floodfillImageInverse);

	cv::Mat filledImage = (sourceImage | floodfillImageInverse);

	return filledImage;
}
