#pragma once

/*
 * The constructor takes a background image as input and provides masks for certain regions in the image that correspond to the dart table regions.
 */
class Mask
{
public:
	cv::Mat_<uchar> red;
	cv::Mat_<uchar> green;
	cv::Mat_<uchar> white;
	cv::Mat_<uchar> black;
	cv::Mat_<uchar> multipliers;
	cv::Mat_<uchar> multRings;
	cv::Mat_<uchar> board;
	cv::Mat_<uchar> miss;
	cv::Mat_<uchar> single;
	cv::Mat_<uchar> double_;
	cv::Mat_<uchar> triple;
	cv::Mat_<uchar> outerBull;
	cv::Mat_<uchar> innerBull;

	Mask ();
	Mask (cv::Mat image);
};
