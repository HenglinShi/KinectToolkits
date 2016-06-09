#pragma once
#include "FramePainter.h"
class DepthFramePainter :
	public FramePainter
{
private:
	Mat mFrameMat;

	UINT16 *mFrameBuffer = NULL;
	UINT mFrameBufferSize;

	USHORT depthFrameMaxReliableDistance;
	USHORT depthFrameMinReliableDistance;

	int mFrameHeight;
	int mFrameWidth;

	RGBQUAD * mFrameRGBXMat = nullptr;
	

	IDepthFrameReference * mFrameReference = nullptr;
	IDepthFrame * mFrame = nullptr;
public:
	DepthFramePainter();
	DepthFramePainter(IMultiSourceFrame * mMultiSourceFrame);
	DepthFramePainter(IDepthFrameReader * mDepthFrameReader);
	~DepthFramePainter();
	Mat getFrame();
	HRESULT update(IMultiSourceFrame * mMultiSourceFrame);
	void setFrame();
};

