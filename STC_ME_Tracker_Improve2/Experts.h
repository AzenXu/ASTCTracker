#pragma once

#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "ExpertResult.h"
#include "SnapshootExpert.h"
#include "NormalExpert.h"
#include "Config.h"

using namespace std;
using namespace cv;

//ר������
class Experts
{
private:
	Config *mConfigPtr;

private:
	NormalExpert mNormalExpert;

	//��ʱ����ר��
	SnapshootExpert mTSnapshootExpert;
	vector<SnapshootExpert> mSnapExpertArr;

	vector<ExpertResult> mExpertResultArr;
	double* mExpertsConfiArray;	//0��ר��Ϊ��ͨר�ң�1�����Ժ��Ϊ����ר��
	int mSnapExpertsSize;	//����ר������
	
	
public:
	Experts(const Size& mTCxtSize, const Size& mTFrameSize, Config *mTConfig);
	Experts(const Experts& r);
	~Experts();

public:
	Experts& operator=(const Experts& r);

private:
	//����һ������ר��
	bool eraseASnapExpert();


public:
	//����һ������ר��
	void increaseSnapExpert(int mTFrameIndex);

	
	ExpertResult& calculateExpertResult(const Mat& mFrame, const Mat& mFilterWindowMat, int mTFrameIndex);

	void setCenterPoint(const Point& mTPoint);

	//�����ṩ�ĵ�ǰ֡���ݾ�����˲����ھ�����㵱ǰ֡�����������ݾ���
	void getContext(const Mat& mFrame, const Mat& mFilterWindowMat);

	//���þ���FFT�任��ʱ��������ģ��
	void setSTCModel(const Mat& mTSTCModel);

	void updateSTCModel(double mTLearnRate);

	//���㵱ǰר�ҵľ���FFT�任�Ŀռ�������ģ��
	Mat& calculateSCModel(const Mat& mTCxtPostProMatFFT);

};