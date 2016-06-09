#pragma once
#include "FrameReader.h"
#include "KinectInstance.h"
#include "stdafx.h"
#include "BodyIndexFramePainter.h"
class MultiSourceFrameReader :
	public FrameReader
{
private:

	ColorFramePainter *colorFramePainter = nullptr;
	DepthFramePainter *depthFramePainter = nullptr;
	BodyFramePainter *bodyFramePainter = nullptr;
	BodyIndexFramePainter *bodyIndexFramePainter = nullptr;


	bool isHealthy = false;

	IMultiSourceFrameReader * multiSourceFrameReader = nullptr;
	IMultiSourceFrame * multiSourceFrame = nullptr;

	HRESULT openReader(IKinectSensor *mKinectSensor, vector <DWORD> mFrameSourceTypes);
	HRESULT update();


public:
	MultiSourceFrameReader();
	MultiSourceFrameReader(IKinectSensor *mKinectSensor, vector<DWORD> mFrameSourceTypes);
	bool getHealth();
	~MultiSourceFrameReader();

	HRESULT acquireLatestFrames();
	Mat getDepthFrame();
	Mat getColorFrame();
	Mat getBodyFrame();
	Mat getBodyIndexFrame();
	Mat getSkeletonFrame();


};

