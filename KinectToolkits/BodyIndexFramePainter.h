#pragma once
#include "FramePainter.h"
class BodyIndexFramePainter :
	public FramePainter
{
private:
	IBodyIndexFrame * mFrame = nullptr;
	IBodyIndexFrameReference *mFrameReference = nullptr;
	IFrameDescription * mFrameDescription = nullptr;
	int mFrameHeight;
	int mFrameWidth;

	BYTE * mFrameBuffer = nullptr;
	UINT mFrameBufferSize = 0;

	RGBQUAD * mFrameRGBXMat = nullptr;

	Mat mFrameMat;

public:
	BodyIndexFramePainter();
	~BodyIndexFramePainter();
	HRESULT update(IMultiSourceFrame *mMultiSourceFrame);
	Mat getFrame();
	void setFrame();
};

