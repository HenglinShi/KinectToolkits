#pragma once
#include "FramePainter.h"
class DepthFramePainter :
	public FramePainter
{
private:

public:
	DepthFramePainter();
	DepthFramePainter(IMultiSourceFrame * mMultiSourceFrame);
	DepthFramePainter(IDepthFrameReader * mDepthFrameReader);
	~DepthFramePainter();
};

