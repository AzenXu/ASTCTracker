#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;

//�����˷�
void complexMultiply(const Mat& src1, const Mat& src2, Mat& dst);
//��������
void complexDivide(const Mat& src1, const Mat& src2, Mat& dst);