#pragma once
#include "FramePainter.h"
class ColorFramePainter :
	public FramePainter
{
private:
	IColorFrameReference * mFrameReference = nullptr;
	IColorFrame * mFrame = nullptr;
	IFrameDescription * mFrameDescription = nullptr;
	Mat mFrameMat;
	int mFrameHeight;
	int mFrameWidth;
	int mDesiredFrameHeight;
	int mDesiredFrameWidth;
	void setFrame();
	void enablingResizing(int resizingHeight, int resizingWidth);
	void disablingResizing();
	void initialization();
	bool resizeEnabled = false;

	void setDesiredHeight(int desiredHeight);
	void setDesiredWidth(int desiredWidth);

public:
	ColorFramePainter();
	ColorFramePainter(IMultiSourceFrame * mMultiSourceFrame);
	ColorFramePainter(IMultiSourceFrame * mMultiSourceFrame, int resizingHeight, int resizingWidth);
	ColorFramePainter(IMultiSourceFrame * mMultiSourceFrame, Size resizingSize);
	ColorFramePainter(IColorFrame * mColorFrame);
	Mat getFrame();
	HRESULT update(IMultiSourceFrame *multiSourceFrame);
	~ColorFramePainter();
};

