#pragma once

//������
class Config
{
private:
	//����ר�Ҹ��¼��
	static const int UPDATE_EXPERT_INTERVAL;
	//���Ŀ���ר������
	static const int MAX_EXPERT_SIZE;
	//ѧϰ����
	static const double LEARN_RATE;

	//������ר�ҷ����˸��ý����ѯ���Ƿ���Ҫ��������ר��ʱ��
	//�ÿ���ר���ṩ�����Ŷ�Ӧ�ó�����ͨר�����Ŷȵ���ֵ
	static const double RESET_THRESHOLD_BY_SNAPEXPERT;

	//�Ƿ�ʹ�����δʹ��ԭ���޳�����ר�ң�trueΪʹ�ã�falseΪ��ʹ��
	static const bool LRU_KICK_SNAPEXPERT;

	static const bool CAPTURE_FIRST_FRAME_SNAP;

public:
	friend class Experts;
	friend class STCTracker;

private:
	const int mUpdateExpertInterval;
	const int mMaxExpertSize;
	const double mResetThresholdBySnapexpert;
	const bool mLRUKickSnapexpert;
	const bool mCaptureFirstFrameSnap;

public:
	Config();
	Config(int mTUpdateExpertInteval, int mTMaxExpertSize, double mTResetThresholdBySnapexpert,
		bool mTLRUKickSnapexpert, bool mCapFirstSnap);
	Config(int mTUpdateExpertInteval, int mTMaxExpertSize, double mTResetThresholdBySnapexpert,
		bool mTLRUKickSnapexpert);
	Config(int mTUpdateExpertInteval, double mTResetThresholdBySnapexpert, bool mTLRUKickSnapexpert);
	Config(const Config& r);
	~Config();

public:
	Config& operator=(const Config& r);


};