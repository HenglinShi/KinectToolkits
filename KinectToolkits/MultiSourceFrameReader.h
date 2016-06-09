#pragma once
#include "FrameReader.h"
#include "KinectInstance.h"
#include "stdafx.h"
class MultiSourceFrameReader :
	public FrameReader
{
private:

	ColorFramePainter *colorFramePainter = nullptr;
	DepthFramePainter *depthFramePainter = nullptr;
	BodyFramePainter *bodyFramePainter = nullptr;



	bool isHealthy = false;

	IMultiSourceFrameReader * multiSourceFrameReader = nullptr;
	IMultiSourceFrame * multiSourceFrame = nullptr;

	HRESULT openReader(IKinectSensor *mKinectSensor, vector <int> mFrameSourceTypes);
	HRESULT update();
	void getDepthFrame();
	void getColorFrame();
	void getBodyFrame();

public:
	MultiSourceFrameReader();
	MultiSourceFrameReader(IKinectSensor *mKinectSensor, vector<int> mFrameSourceTypes);
	bool getHealth();
	~MultiSourceFrameReader();
};

