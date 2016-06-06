#include "SnapshootExpert.h"
#include "NormalExpert.h"

SnapshootExpert::SnapshootExpert(const Size& mTCxtSize, const Size& mTFrameSize)
	:mInnateCenterPoint(mTCxtSize, mTFrameSize), mNewCenterPoint(mTCxtSize, mTFrameSize)
{
	mFrameIndex = -1;
	mUpdateCount = 0;
	mCxtSize = mTCxtSize;
	mFrameSize = mTFrameSize;

	mCxtMat = Mat::zeros(mCxtSize, CV_64FC1);
	mCxtPriProMat = Mat::zeros(mCxtSize, CV_64FC1);
	mCxtPriProMatFFT = Mat::zeros(mCxtSize, CV_64FC2);

	mSTCModelFFT = Mat::zeros(mCxtSize, CV_64FC2);
}

SnapshootExpert::SnapshootExpert(const SnapshootExpert& r)
	:mInnateCenterPoint(r.mCxtSize, r.mFrameSize), mNewCenterPoint(r.mCxtSize, r.mFrameSize)
{
	mFrameIndex = r.mFrameIndex;
	mUpdateCount = r.mUpdateCount;

	mCxtSize = r.mCxtSize;
	mFrameSize = r.mFrameSize;

	mInnatePoint = r.mInnatePoint;
	mInnateCenterPoint = r.mInnateCenterPoint;
	mNewCenterPoint = r.mNewCenterPoint;

	mCxtMat = Mat::zeros(mCxtSize, CV_64FC1);
	r.mCxtMat.copyTo(mCxtMat);
	mCxtPriProMat = Mat::zeros(mCxtSize, CV_64FC1);
	r.mCxtPriProMat.copyTo(mCxtPriProMat);
	mCxtPriProMatFFT = Mat::zeros(mCxtSize, CV_64FC2);
	r.mCxtPriProMatFFT.copyTo(mCxtPriProMatFFT);

	mSTCModelFFT = Mat::zeros(mCxtSize, CV_64FC2);
	r.mSTCModelFFT.copyTo(mSTCModelFFT);

	mExpertResult = r.mExpertResult;

	r.mPredictionConfidenceMap.copyTo(mPredictionConfidenceMap);
}

SnapshootExpert::~SnapshootExpert()
{

}

SnapshootExpert& SnapshootExpert::operator=(const SnapshootExpert& r)
{
	if (this == &r)
	{
		return *this;
	}

	mFrameIndex = r.mFrameIndex;
	mUpdateCount = r.mUpdateCount;

	if (mCxtSize.width != r.mCxtSize.width || mCxtSize.height != r.mCxtSize.height)
	{
		mCxtSize = r.mCxtSize;

		mInnateCenterPoint = CenterPoint(r.mCxtSize, r.mFrameSize);
		mNewCenterPoint = CenterPoint(r.mCxtSize, r.mFrameSize);

		mCxtMat = Mat::zeros(mCxtSize, CV_64FC1);
		mCxtPriProMat = Mat::zeros(mCxtSize, CV_64FC1);
		mCxtPriProMatFFT = Mat::zeros(mCxtSize, CV_64FC2);

		mSTCModelFFT = Mat::zeros(mCxtSize, CV_64FC2);
	}

	mFrameSize = r.mFrameSize;

	mInnatePoint = r.mInnatePoint;
	mInnateCenterPoint = r.mInnateCenterPoint;
	mNewCenterPoint = r.mNewCenterPoint;

	r.mCxtMat.copyTo(mCxtMat);
	r.mCxtPriProMat.copyTo(mCxtPriProMat);
	r.mCxtPriProMatFFT.copyTo(mCxtPriProMatFFT);

	r.mSTCModelFFT.copyTo(mSTCModelFFT);

	mExpertResult = r.mExpertResult;

	r.mPredictionConfidenceMap.copyTo(mPredictionConfidenceMap);
	return *this;
}

int SnapshootExpert::getFrameIndex()
{
	return mFrameIndex;
}

void SnapshootExpert::init(int mTFrameIndex, const NormalExpert& mTNormalExpert)
{
	mFrameIndex = mTFrameIndex;
	mUpdateCount = 0;

	mInnatePoint = mTNormalExpert.mCenterPoint;
	mInnateCenterPoint.setCenterPoint(mInnatePoint);

	mTNormalExpert.mSTCModelFFT.copyTo(mSTCModelFFT);
	mExpertResult = mTNormalExpert.mExpertResult;
}

void SnapshootExpert::getContext(const Mat& mFrame, const Mat& mFilterWindowMat, CenterPoint& mTCenterPoint)
{
	double *mData = NULL;
	uchar *mFrameData = NULL;
	double mPxSum = 0, mPxAverage = 0;

	int* mCxtX = mTCenterPoint.getCxtXPointer();
	int* mCxtY = mTCenterPoint.getCxtYPointer();

	for (int i = 0; i < mCxtSize.height; i++)
	{

		mData = (double *)(mCxtMat.data + mCxtMat.step * i);
		mFrameData = (uchar *)(mFrame.data + mFrame.step * mCxtY[i]);
		for (int j = 0; j < mCxtSize.width; j++)
		{
			mData[j] = mFrameData[mCxtX[j]];
			mPxSum += mData[j];
		}

	}
	mPxAverage = mPxSum / (mCxtSize.width * mCxtSize.height);

	mCxtMat.convertTo(mCxtMat, -1, 1, -mPxAverage);

	mCxtPriProMat = mFilterWindowMat.mul(mCxtMat);

	Mat priorFourier;
	Mat planes[] = { mCxtPriProMat, Mat::zeros(mCxtPriProMat.size(), CV_64FC1) };
	merge(planes, 2, priorFourier);
	dft(priorFourier, mCxtPriProMatFFT);
}

ExpertResult& SnapshootExpert::calculateExpertResult(const Mat& mFrame, const Mat& mFilterWindowMat)
{
	getContext(mFrame, mFilterWindowMat, mInnateCenterPoint);

	Mat mConditionalFourier;
	complexMultiply(mSTCModelFFT, mCxtPriProMatFFT, mConditionalFourier);
	dft(mConditionalFourier, mPredictionConfidenceMap, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

	Point point;
	minMaxLoc(mPredictionConfidenceMap, 0, 0, 0, &point);
	if (point.x == -1 || point.y == -1)
	{
		cout << "�Ҳ���������Ŷȵĵ㣬�����Ѿ��޷�����ִ�У����ڽ���Ԥ��" << endl;
		mExpertResult.setConfidence(0.001);
		return mExpertResult;
	}

	Point mNewPoint;
	//����Ҫ��һ�����ص�ƫ����������Ϊpoint�õ����Ǿ�����Ԫ�ص����꣬�߶ȷ�ΧΪ0��(size-1)����mCxtRegionSize�Ŀ�߳����õ�����������ĳ߶ȷ�ΧΪ1��size
	//���������һ�����ص�ƫ������ʹ���������䵽һ���߶ȷ�Χ�ڣ���ɵõ����������ƶ���ƫ����
	mNewPoint.x = mInnatePoint.x + point.x + 1 - mCxtSize.width / 2;
	mNewPoint.y = mInnatePoint.y + point.y + 1 - mCxtSize.height / 2;

	mNewCenterPoint.setCenterPoint(mNewPoint);
	getContext(mFrame, mFilterWindowMat, mNewCenterPoint);

	complexMultiply(mSTCModelFFT, mCxtPriProMatFFT, mConditionalFourier);
	dft(mConditionalFourier, mPredictionConfidenceMap, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
	minMaxLoc(mPredictionConfidenceMap, 0, 0, 0, &point);

	mExpertResult.setData(mNewPoint, *(((double *)(mPredictionConfidenceMap.data + point.y * mPredictionConfidenceMap.step)) + point.x));

	return mExpertResult;
}

void SnapshootExpert::accumulateUpdateCount()
{
	mUpdateCount++;
}

int SnapshootExpert::getUpdateCount()
{
	return mUpdateCount;
}