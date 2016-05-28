#pragma once
#include "stdafx.h"

#define KINECT_STATE_READY 1
#define KINECT_STATE_PENDING 0
class KinectInstance
{
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
	
public:
	KinectInstance();
	~KinectInstance();
	int getState();
};

