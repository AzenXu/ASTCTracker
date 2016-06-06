#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;

class CenterPoint
{
private:
	Size mCxtSize;	//�����Ĵ�С
	Size mFrameSize;	//֡��С

	Point mCenterPoint;
	//�ֱ�洢���Ƕ�Ӧ�ľֲ��ռ�������������ͼ��ĺ������������
	int *mCxtX;
	int *mCxtY;

public:
	CenterPoint(const Size& mTCxtSize, const  Size& mTFrameSize);
	CenterPoint(const CenterPoint& r);
	~CenterPoint();

public:
	CenterPoint& operator=(const CenterPoint& r);

public:

	void setCenterPoint(const Point& mTCenterPoint);

	Point& getCenterPoint();

	int* getCxtXPointer();

	int* getCxtYPointer();

};