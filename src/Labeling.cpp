#include "stdafx.h"
#include "Labeling.h"
#include "Utils.h"
#include <queue>
#include <cmath>

cv::Mat_<uchar> label(cv::Mat_<uchar> img)
{
	cv::Mat_<uchar> labels(img.rows, img.cols);
	labels.setTo(255);

	int label = 0;

	for (int row = 1; row < img.rows - 1; row++)
	{
		for (int col = 1; col < img.cols - 1; col++)
		{
			if ((img(row, col) == 255) && (labels(row, col) == 255))
			{
				label++;
				std::queue<cv::Point2i> Q;
				labels(row, col) = label;
				Q.push(cv::Point2i(row, col));

				while (!Q.empty())
				{
					cv::Point2i q = Q.front();
					Q.pop();

					int di[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
					int dj[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
					for (int k = 0; k < 8; k++)
					{
						if ((img(q.x, q.y) == 255) && (labels(q.x + di[k], q.y + dj[k]) == 255))
						{
							labels(q.x + di[k], q.y + dj[k]) = label;
							Q.push(cv::Point2i(q.x + di[k], q.y + dj[k]));
						}
					}
				}
			}
		}
	}

	return labels;
}

void Labeling::SetLabels(cv::Mat_<uchar> whiteLabels, cv::Mat_<uchar> blackLabels, cv::Mat_<uchar> labeledImg, cv::Point2i center)
{
	cv::Mat_<uchar> destImg(whiteLabels.rows, whiteLabels.cols);
	destImg.setTo(0);
	int whiteMax = 0, blackMax = 0;

	// Get number of labels

	for (int row = 1; row < whiteLabels.rows - 1; row++)
	{
		for (int col = 1; col < whiteLabels.cols - 1; col++)
		{
			if (whiteLabels(row, col) != 255)
			{
				if (whiteLabels(row, col) > whiteMax)
					whiteMax = whiteLabels(row, col);
			}

			if (blackLabels(row, col) != 255)
			{
				if (blackLabels(row, col) > blackMax)
					blackMax = blackLabels(row, col);
			}
		}
	}

	// Assign regions

	for (auto iWhite = 0; iWhite < whiteMax; iWhite++)
	{
		int area = objectArea(whiteLabels, iWhite);
		if (area > 1000)
		{
			cv::Point2i regionCenter = centerOfMass(whiteLabels, iWhite, area);
			auto labelVector = regionCenter - center;
			auto length = dist(regionCenter, center);

			float angleRad = atan2(labelVector.y, labelVector.x);
			float angle = (angleRad > 0 ? angleRad : (2 * CV_PI + angleRad)) * 360 / (2 * CV_PI);

			if ((0 <= angle < 10) || (350 <= angle < 360))
			{
				
			}
			else if (0 * (360 / 20) + 10 <= angle < 1 * (360 / 20) + 10)
			{

			}
			else if (1 * (360 / 20) + 10 <= angle < 2 * (360 / 20) + 10)
			{

			}
			else if (2 * (360 / 20) + 10 <= angle < 3 * (360 / 20) + 10)
			{

			}
			else if (3 * (360 / 20) + 10 <= angle < 4 * (360 / 20) + 10)
			{

			}
			else if (4 * (360 / 20) + 10 <= angle < 5 * (360 / 20) + 10)
			{

			}
			else if (5 * (360 / 20) + 10 <= angle < 6 * (360 / 20) + 10)
			{

			}
			else if (6 * (360 / 20) + 10 <= angle < 7 * (360 / 20) + 10)
			{

			}
			else if (7 * (360 / 20) + 10 <= angle < 8 * (360 / 20) + 10)
			{

			}
			else if (8 * (360 / 20) + 10 <= angle < 9 * (360 / 20) + 10)
			{

			}
			else if (10 * (360 / 20) + 10 <= angle < 11 * (360 / 20) + 10)
			{

			}
			else if (11 * (360 / 20) + 10 <= angle < 12 * (360 / 20) + 10)
			{

			}
			else if (12 * (360 / 20) + 10 <= angle < 13 * (360 / 20) + 10)
			{

			}
			else if (13 * (360 / 20) + 10 <= angle < 14 * (360 / 20) + 10)
			{

			}
			else if (14 * (360 / 20) + 10 <= angle < 15 * (360 / 20) + 10)
			{

			}
			else if (15 * (360 / 20) + 10 <= angle < 16 * (360 / 20) + 10)
			{

			}
			else if (16 * (360 / 20) + 10 <= angle < 17 * (360 / 20) + 10)
			{

			}
			else if (17 * (360 / 20) + 10 <= angle < 18 * (360 / 20) + 10)
			{

			}
			else if (18 * (360 / 20) + 10 <= angle < 19 * (360 / 20) + 10)
			{

			}
		}
	}

	for (auto iBlack = 0; iBlack < blackMax; iBlack++)
	{
		int area = objectArea(blackLabels, iBlack);
		if (area > 1000)
		{
			cv::Point2i regionCenter = centerOfMass(whiteLabels, iBlack, area);
			auto labelVector = regionCenter - center;
			auto length = dist(regionCenter, center);

			float angleRad = atan2(labelVector.y, labelVector.x);
			float angle = ((angleRad / CV_PI) * 180.0);


		}
	}

}

Labeling::Labeling()
{
}

Labeling::Labeling(cv::Mat_<uchar> white, cv::Mat_<uchar> black, cv::Point2i center)
{
	cv::Mat_<uchar> whiteLabels(white.rows, white.cols);
	cv::Mat_<uchar> blackLabels(black.rows, black.cols);

	// Assign a label to each slice

	whiteLabels = label(white);
	blackLabels = label(black);

	// Set labels to their actual value (1 - 20):

	cv::Mat_<uchar> labeledImg(black.rows, black.cols);

	SetLabels(whiteLabels, blackLabels, labeledImg, center);

}
