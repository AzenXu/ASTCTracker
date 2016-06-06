#pragma once

#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

//���Ŷȶ���
//ֻ�����㹻���������Ŷ����ڼ���߶ȱ仯
class ConfidenceList
{

private:
	int intervalNumber;//�����ֵ
	int capacity;//����=���+1
	int startIndex;//startָ����ʼ�ĵ�һ�����ݵ�����
	int endIndex;//endָ�򼴽�д���������ڵ�����
	int size;
	double *dataPtr;

public:
	ConfidenceList(int intervalNumber);
	ConfidenceList(const ConfidenceList& r);
	~ConfidenceList();

public:
	ConfidenceList& operator=(const ConfidenceList& r);

public:
	//���һ���µ����Ŷ�
	void addConfidence(double confi);
	//���㵱�εĹ��Ƴ߶�
	double calculateEstimateScale();

};