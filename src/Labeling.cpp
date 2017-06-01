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

void setValuesFromLabel(const cv::Mat_<unsigned char> labeledImg, cv::Mat_<unsigned char> values, int label, int value)
{
	for (int row = 1; row < labeledImg.rows - 1; row++)
	{
		for (int col = 1; col < labeledImg.cols - 1; col++)
		{
			if (labeledImg(row, col) == label)
			{
				values(row, col) = value;
			}
		}
	}
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

	for (auto i = 0; i < whiteMax; i++)
	{
		int area = objectArea(whiteLabels, i);
		if (area > 1000)
		{
			cv::Point2i regionCenter = centerOfMass(whiteLabels, i, area);
			auto labelVector = regionCenter - center;
			// auto length = dist(regionCenter, center);

			float angleRad = atan2(labelVector.y, labelVector.x);
			float angle = (angleRad > 0 ? angleRad : (2 * CV_PI + angleRad)) * 360 / (2 * CV_PI);

			if ((0 <= angle && angle < 10) || (350 <= angle && angle < 360))
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 1);
			}
			else if (0 * (360 / 20) + 10 <= angle && angle < 1 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 2);
			}
			else if (1 * (360 / 20) + 10 <= angle && angle < 2 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 3);
			}
			else if (2 * (360 / 20) + 10 <= angle && angle < 3 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 4);
			}
			else if (3 * (360 / 20) + 10 <= angle && angle < 4 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 5);
			}
			else if (4 * (360 / 20) + 10 <= angle && angle < 5 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 6);
			}
			else if (5 * (360 / 20) + 10 <= angle && angle < 6 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 7);
			}
			else if (6 * (360 / 20) + 10 <= angle && angle < 7 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 8);
			}
			else if (7 * (360 / 20) + 10 <= angle && angle < 8 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 9);
			}
			else if (8 * (360 / 20) + 10 <= angle && angle < 9 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 10);
			}
			else if (10 * (360 / 20) + 10 <= angle && angle < 11 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 11);
			}
			else if (11 * (360 / 20) + 10 <= angle && angle < 12 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 12);
			}
			else if (12 * (360 / 20) + 10 <= angle && angle < 13 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 13);
			}
			else if (13 * (360 / 20) + 10 <= angle && angle < 14 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 14);
			}
			else if (14 * (360 / 20) + 10 <= angle && angle < 15 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 15);
			}
			else if (15 * (360 / 20) + 10 <= angle && angle < 16 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 16);
			}
			else if (16 * (360 / 20) + 10 <= angle && angle < 17 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 17);
			}
			else if (17 * (360 / 20) + 10 <= angle && angle < 18 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 18);
			}
			else if (18 * (360 / 20) + 10 <= angle && angle < 19 * (360 / 20) + 10)
			{
				setValuesFromLabel(whiteLabels, labeledImg, i, 19);
			}
		}
	}

	for (auto i = 0; i < blackMax; i++)
	{
		int area = objectArea(blackLabels, i);
		if (area > 1000)
		{
			cv::Point2i regionCenter = centerOfMass(blackLabels, i, area);
			auto labelVector = regionCenter - center;
			// auto length = dist(regionCenter, center);

			float angleRad = atan2(labelVector.y, labelVector.x);
			float angle = ((angleRad / CV_PI) * 180.0);

			if ((0 <= angle && angle < 10) || (350 <= angle && angle < 360))
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 1);
			}
			else if (0 * (360 / 20) + 10 <= angle && angle < 1 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 2);
			}
			else if (1 * (360 / 20) + 10 <= angle && angle < 2 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 3);
			}
			else if (2 * (360 / 20) + 10 <= angle && angle < 3 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 4);
			}
			else if (3 * (360 / 20) + 10 <= angle && angle < 4 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 5);
			}
			else if (4 * (360 / 20) + 10 <= angle && angle < 5 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 6);
			}
			else if (5 * (360 / 20) + 10 <= angle && angle < 6 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 7);
			}
			else if (6 * (360 / 20) + 10 <= angle && angle < 7 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 8);
			}
			else if (7 * (360 / 20) + 10 <= angle && angle < 8 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 9);
			}
			else if (8 * (360 / 20) + 10 <= angle && angle < 9 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 10);
			}
			else if (10 * (360 / 20) + 10 <= angle && angle < 11 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 11);
			}
			else if (11 * (360 / 20) + 10 <= angle && angle < 12 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 12);
			}
			else if (12 * (360 / 20) + 10 <= angle && angle < 13 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 13);
			}
			else if (13 * (360 / 20) + 10 <= angle && angle < 14 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 14);
			}
			else if (14 * (360 / 20) + 10 <= angle && angle < 15 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 15);
			}
			else if (15 * (360 / 20) + 10 <= angle && angle < 16 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 16);
			}
			else if (16 * (360 / 20) + 10 <= angle && angle < 17 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 17);
			}
			else if (17 * (360 / 20) + 10 <= angle && angle < 18 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 18);
			}
			else if (18 * (360 / 20) + 10 <= angle && angle < 19 * (360 / 20) + 10)
			{
				setValuesFromLabel(blackLabels, labeledImg, i, 19);
			}
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
	labeledImg.setTo(0);

	SetLabels(whiteLabels, blackLabels, labeledImg, center);

	fullLabel = labeledImg;
}
