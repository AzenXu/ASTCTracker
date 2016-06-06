#pragma once

#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "ExpertResult.h"
#include "Complex.h"
#include "CenterPoint.h"

using namespace std;
using namespace cv;

class NormalExpert;

//����ר����
class SnapshootExpert
{
public:
	friend class NormalExpert;

private:
	int mFrameIndex;
	//���¼���
	int mUpdateCount;

	Size mCxtSize;	//�����Ĵ�С
	Size mFrameSize;	//֡��С

	Point mInnatePoint;	//��Ϊ����ר�ҵĹ̶����ĵ�����
	CenterPoint mInnateCenterPoint;	//��Ϊ����ר�Ҷ�Ӧ�Ĺ̶����ĵ����������װ��
	CenterPoint mNewCenterPoint;	//��ʱ�������õ����µ����ĵ������Լ������װ��

	Mat mCxtMat;	//���������ݾ���
	Mat mCxtPriProMat;	//���������õ���������������ʾ���
	Mat mCxtPriProMatFFT;	//����FFT�任���������������ʾ���

	Mat mSTCModelFFT;	//����FFT�任��ʱ��������ģ�;���

	ExpertResult mExpertResult;

	Mat mPredictionConfidenceMap;	//���ڴ洢��ǰ֡��Ԥ���õ�����ͼ

public:
	SnapshootExpert(const Size& mTCxtSize, const Size& mTFrameSize);
	SnapshootExpert(const SnapshootExpert& r);
	~SnapshootExpert();

public:
	SnapshootExpert& operator=(const SnapshootExpert& r);

public:
	int getFrameIndex();

	void init(int mTFrameIndex, const NormalExpert& mTNormalExpert);

	//�����ṩ�ĵ�ǰ֡���ݾ�����˲����ھ�����㵱ǰ֡�����������ݾ���
	void getContext(const Mat& mFrame, const Mat& mFilterWindowMat, CenterPoint& mTCenterPoint);

	ExpertResult& calculateExpertResult(const Mat& mFrame, const Mat& mFilterWindowMat);

	//�ۼӸ��¼���
	void accumulateUpdateCount();

	int getUpdateCount();

};