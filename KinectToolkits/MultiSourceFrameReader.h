#pragma once
#include "stdafx.h"
#include "BodyIndexFramePainter.h"
#include "BodyFramePainter.h"
#include "ColorFramePainter.h"
#include "DepthFramePainter.h"
#include "FrameReader.h"
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
	UINT16 * getDepthFrameArray();
	UINT getDepthFrameArraySize();
	RGBQUAD * getDepthFrameArrayRGBX();
	UINT getDepthFrameArrayRGBXSize();

	Mat getColorFrame();
	UINT8 * getColorFrameArray();
	UINT getColorFrameArraySize();

	Mat getBodyFrame();

	Mat getBodyIndexFrame();
	BYTE * getBodyIndexFrameArray();
	UINT getBodyIndexFrameArraySize();
	RGBQUAD * getBodyIndexFrameArrayRGBX();
	UINT getBodyIndexFrameArrayRGBXSize();
	Mat getSkeletonFrame();


};

