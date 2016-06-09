#pragma once
#include "stdafx.h"
#include "MultiSourceFrameReader.h"
using namespace cv;
class KinectInstance
{
	MultiSourceFrameReader * mMultiSourceFrameReader = nullptr;
	IKinectSensor * mKinectSensor = nullptr;
	ICoordinateMapper * mCoordinateMapper = nullptr;
	int state = 0;
	bool isReady = false;

private:


	int initializing();
	void setState(int newKinectState);
	void setStateReady();
	void setStatePending();
	HRESULT setCoordinateMapper();
	HRESULT openSensor();
	HRESULT openReader(vector <DWORD> mFrameSourceTypes);
	HRESULT openReader(int mFrameSourceType);
	
public:
	KinectInstance(vector <DWORD> mFrameSourceTypes);
	
	int getState();


	HRESULT acquireLatestFrames();
	void update();
	Mat getDepthFrame();
	Mat getColorFrame();
	Mat getBodyIndexFrame();
	Mat getSkeletonFrame();
	~KinectInstance();
};

