#pragma once
#include "stdafx.h"


class ColorFramePainter :
	public FramePainter
{
private:
	IColorFrameReference * mFrameReference = nullptr;
	IColorFrame * mFrame = nullptr;
	IFrameDescription * mFrameDescription = nullptr;

	Mat mFrameMat;
	UINT8 * mFrameArray = nullptr;
	UINT mFrameArraySize = 0;

	int mFrameHeight;
	int mFrameWidth;
	int mDesiredFrameHeight;
	int mDesiredFrameWidth;
	bool resizeEnabled = false;
	bool health = UNHEALTHY;


	
	HRESULT copyFrameDataToArray();
	void copyFrameDataToMat();
	void disablingResizing();
	void setDesiredHeight(int desiredHeight);
	void setDesiredWidth(int desiredWidth);
	void setHealth(bool health);
	
public:
	ColorFramePainter();
	ColorFramePainter(IMultiSourceFrame * mMultiSourceFrame);
	ColorFramePainter(IMultiSourceFrame * mMultiSourceFrame, int resizingHeight, int resizingWidth);
	ColorFramePainter(IColorFrame * mColorFrame);
	~ColorFramePainter();

	UINT8 * getFrameArray();
	UINT getFrameArraySize();

	Mat getFrame();
	HRESULT initializing(IMultiSourceFrame * mMultiSourceFrame);
	HRESULT update(IMultiSourceFrame *multiSourceFrame);
	void enablingResizing(int resizingHeight, int resizingWidth);	
	bool getHealth();
	bool isHealthy();
	int getFrameHeight();
	int getFrameWidth();
	
};

