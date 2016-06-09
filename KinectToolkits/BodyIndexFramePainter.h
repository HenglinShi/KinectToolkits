#pragma once
#include "FramePainter.h"
#define HEALTHY true
#define UNHEALTHY false
#define CHANNEL 4

class BodyIndexFramePainter :
	public FramePainter
{
private:
	IBodyIndexFrame * mFrame = nullptr;
	IBodyIndexFrameReference *mFrameReference = nullptr;
	IFrameDescription * mFrameDescription = nullptr;
	int mFrameHeight;
	int mFrameWidth;

	Mat mFrameMat;
	BYTE *mFrameArray = NULL;
	UINT mFrameArraySize = 0;
	RGBQUAD * mFrameArrayRGBX = nullptr;
	UINT mFrameArrayRGBXSize = 0;

	bool health = UNHEALTHY;

	void setHealth(bool health);
	HRESULT copyFrameDataToArray();
	void copyFrameDataToMat();

	

public:
	BodyIndexFramePainter(IMultiSourceFrame *mMultiSourceFrame);
	~BodyIndexFramePainter();
	HRESULT update(IMultiSourceFrame *mMultiSourceFrame);
	HRESULT initializing(IMultiSourceFrame * mMultiSourceFrame);


	Mat getFrame();
	UINT16 * getFrameArray();
	UINT getFrameArraySize();
	RGBQUAD * getFrameArrayRGBX();
	UINT getFrameArrayRGBXSize();



	bool getHealth();
	bool isHealthy();

};

