#pragma once

int dist(const cv::Point& a, const cv::Point& b);
cv::Point findCenter(const cv::Mat& mat);
int objectArea(cv::Mat_<uchar> img, uchar label);
cv::Point2i centerOfMass(cv::Mat_<uchar> img, uchar color, int area);