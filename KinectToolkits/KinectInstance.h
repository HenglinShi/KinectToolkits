#pragma once
#include "stdafx.h"
#include <vector>
#include "MultiSourceFrameReader.h"
#define KINECT_STATE_READY 1
#define KINECT_STATE_PENDING 0
using namespace std;
class KinectInstance
{
	MultiSourceFrameReader *mMultiSourceFrameReader = nullptr;
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
	HRESULT openReader(vector <int> mFrameSourceTypes);
	HRESULT openReader(int mFrameSourceType);
	
public:
	KinectInstance(vector <int> mFrameSourceTypes);
	~KinectInstance();
	int getState();
};

