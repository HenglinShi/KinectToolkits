#pragma once
#include "stdafx.h"
#define HEALTHY true
#define UNHEALTHY false
class DepthFramePainter :
	public FramePainter
{
private:
	IDepthFrameReference * mFrameReference = nullptr;
	IDepthFrame * mFrame = nullptr;
	IFrameDescription * mFrameDescription = nullptr;

	USHORT depthFrameMaxReliableDistance;
	USHORT depthFrameMinReliableDistance;
	int mFrameHeight;
	int mFrameWidth;

	Mat mFrameMat;
	UINT16 *mFrameArray = NULL;
	UINT mFrameArraySize = 0;
	RGBQUAD * mFrameArrayRGBX = nullptr;
	UINT mFrameArrayRGBXSize = 0;

	bool health = UNHEALTHY;

	void setHealth(bool health);
	HRESULT copyFrameDataToArray();
	void copyFrameDataToMat();

public:

	DepthFramePainter(IMultiSourceFrame * mMultiSourceFrame);
	~DepthFramePainter();

	HRESULT initializing(IMultiSourceFrame * mMultiSourceFrame);
	HRESULT update(IMultiSourceFrame * mMultiSourceFrame);

	bool getHealth();
	bool isHealthy();
	Mat getFrame();
	UINT16 * getFrameArray();
	UINT getFrameArraySize();
	RGBQUAD * getFrameArrayRGBX();
	UINT getFrameArrayRGBXSize();

};

