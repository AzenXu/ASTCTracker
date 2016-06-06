#pragma once

#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include "ConfidenceList.h"
#include "Experts.h"
#include "ExpertResult.h"
#include "Complex.h"
#include "Config.h"

using namespace cv;
using namespace std;

class STCTracker
{
//��Ա����
private:

	ofstream out;
	int mFrameIndex;				//��ǰ����֡������
	int mIntervalNumber;	//ÿ������֡ͼƬ����һ�γ߶Ȳ���
	double sigma;			//������������ʹ�ʽ�еĳ߶Ȳ���������ʽ5
	double alpha;			//������ʣ�������ͼ����ʽ�еĳ߶����Ų���������ʽ6
	double beta;			//������ʣ�������ͼ����ʽ�еĿ���ͼ�μ���ȵĲ���������ʽ6
	double mLearnRate;		//��ʽ12�е�ѧϰ����

	Point mCenter;			//���ٶ�������ĵ�
	Size2d mRectSize;			//���پ��ο�ĳߴ�
	Size mCxtRegionSize;	//����������ߴ�
	double mScale;			//�߶����ű���
	double mScaleLearnRate;	//�߶�����ѧϰ����

	ConfidenceList *mConfidenceList;//�����ڽ������Ŷ����ڹ��Ƴ߶Ȳ���

	Mat mCxtPostProMat;		//�����ĺ�����ʾ��󣬼���׼����ͼ
	Mat mCxtPostProFFTMat;	//��������Ҷת����ĺ�����ʾ���

	Mat mFilterWindowMat;	//��ǰ֡���˲����ڣ�����ʽ4�л�δ��I(z)ʱ�ľ������ݣ���Ϊһ���˲�����������


	Mat mHammingWinMat;		//����������������ͼ���Ե������Ƶ��Ӱ��
	Mat mEucliDistMat;		//�洢������������ÿһ�����ص㵽���ٶ������ĵ��ŷ����þ���ƽ����������������ʾ���Ҳ���ں�����ʾ���

	double mMinConfiPosi;

	Experts *mExperts;

public:
	STCTracker();
	virtual ~STCTracker();

public:
	//��ʼ������
	void init(const Mat& mFrame, const Rect& mBox, int mFrameCount, Config *mTConfig);
	//����ÿһ֡�ĸ���
	void track(const Mat& mFrame, Rect& mBox, Config& mTConfig);


private:
	//���캺����
	void createHammingWindow();
	//��ʼ��ŷ����þ������ͺ�����ʾ���
	void createEucliDistMatAndCxtPostPro();

	void getFilterWindow();

};

