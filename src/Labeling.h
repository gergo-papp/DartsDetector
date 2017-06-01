#pragma once

/*
* The constructor takes a background image as input and slices for each value in the dart board.
*/
class Labeling
{
public:
	cv::Mat_<uchar> fullLabel;

	Labeling();
	Labeling(cv::Mat_<uchar> white, cv::Mat_<uchar> black, cv::Point2i center);

	void Labeling::SetLabels(cv::Mat_<uchar> whiteLabels, cv::Mat_<uchar> blackLabels, cv::Mat_<uchar> labeledImg, cv::Point2i center);
};