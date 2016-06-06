#pragma once

#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "ExpertResult.h"
#include "Complex.h"
#include "SnapshootExpert.h"

using namespace std;
using namespace cv;

//��ͨר����
class NormalExpert
{
public:
	friend class SnapshootExpert;

private:
	Size mCxtSize;	//�����Ĵ�С
	Size mFrameSize;	//֡��С

	Point mCenterPoint;	//���ٶ�������ĵ�
	//�ֱ�洢���Ƕ�Ӧ�ľֲ��ռ�������������ͼ��ĺ������������
	int *mCxtX;
	int *mCxtY;

	Mat mCxtMat;	//���������ݾ���
	Mat mCxtPriProMat;	//���������õ���������������ʾ���
	Mat mCxtPriProMatFFT;	//����FFT�任���������������ʾ���

	Mat mSCModelFFT;	//����FFT�任�Ŀռ�������ģ�;���
	Mat mSTCModelFFT;	//����FFT�任��ʱ��������ģ�;���
	
	ExpertResult mExpertResult;

	Mat mPredictionConfidenceMap;	//���ڴ洢��ǰ֡��Ԥ���õ�����ͼ

public:
	NormalExpert(const Size& mTCxtSize, const Size& mTFrameSize);
	NormalExpert(const NormalExpert& r);
	~NormalExpert();

public:
	NormalExpert& operator=(const NormalExpert& r);

public:
	void setCenterPoint(const Point& mTPoint);

	//�����ṩ�ĵ�ǰ֡���ݾ�����˲����ھ�����㵱ǰ֡�����������ݾ���
	void getContext(const Mat& mFrame, const Mat& mFilterWindowMat);

	//���þ���FFT�任��ʱ��������ģ��
	void setSTCModel(const Mat& mTSTCModel);

	void updateSTCModel(double mTLearnRate);

	//���㵱ǰר�ҵľ���FFT�任�Ŀռ�������ģ��
	Mat& calculateSCModel(const Mat& mTCxtPostProMatFFT);

	ExpertResult& calculateExpertResult(const Mat& mFrame, const Mat& mFilterWindowMat);

	//ʹ��ר�����еõ������ר��������ͨר���ࡣ�β���ר�Ҽ���õ�������Ϊ������ɿ������ݣ���ֱ���������и���
	void resetBySnapshootExpert(SnapshootExpert& mTSnapExpert);

};
