#pragma once

/*
 * The constructor takes a background image as input and provides masks for certain regions in the image that correspond to the dart table regions.
 */
class Mask
{
public:
	cv::Mat red;
	cv::Mat green;
	cv::Mat multipliers;
	cv::Mat multRings;
	cv::Mat board;
	cv::Mat miss;
	cv::Mat single;
	cv::Mat double_;
	cv::Mat triple;
	cv::Mat outerBull;
	cv::Mat innerBull;

	Mask (cv::Mat image);
};
