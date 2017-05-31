#pragma once

/*
* The constructor takes a background image as input and slices for each value in the dart board.
*/
class Labeling
{
public:
	cv::Mat_<uchar> slice_1;
	cv::Mat_<uchar> slice_2;
	cv::Mat_<uchar> slice_3;
	cv::Mat_<uchar> slice_4;
	cv::Mat_<uchar> slice_5;
	cv::Mat_<uchar> slice_6;
	cv::Mat_<uchar> slice_7;
	cv::Mat_<uchar> slice_8;
	cv::Mat_<uchar> slice_9;
	cv::Mat_<uchar> slice_10;
	cv::Mat_<uchar> slice_11;
	cv::Mat_<uchar> slice_12;
	cv::Mat_<uchar> slice_13;
	cv::Mat_<uchar> slice_14;
	cv::Mat_<uchar> slice_15;
	cv::Mat_<uchar> slice_16;
	cv::Mat_<uchar> slice_17;
	cv::Mat_<uchar> slice_18;
	cv::Mat_<uchar> slice_19;
	cv::Mat_<uchar> slice_20;

	Labeling();
	Labeling(cv::Mat_<uchar> white, cv::Mat_<uchar> black, cv::Point2i center);

	void Labeling::SetLabels(cv::Mat_<uchar> whiteLabels, cv::Mat_<uchar> blackLabels, cv::Mat_<uchar> labeledImg, cv::Point2i center);
};