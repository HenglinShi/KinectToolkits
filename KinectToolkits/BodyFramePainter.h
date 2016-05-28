#pragma once
#include "FramePainter.h"
class BodyFramePainter :
	public FramePainter
{
private:
	IBodyFrame * mBodyFrame = nullptr;
	IBodyFrameReference * mBodyFrameReference = nullptr;


public:
	BodyFramePainter(IMultiSourceFrame * multiSourceFrame);
	BodyFramePainter(IBodyFrameReader * mBodyFrameReader);
	~BodyFramePainter();
};

