#pragma once
#include "stdafx.h"
#include "Body.h"
using namespace cv;

class FramePainter
{
private:
	Body persons[BODY_COUNT];
	Mat frameMat;
	int frameHeight;
	int frameWidth;

public:
	FramePainter();
	FramePainter(IMultiSourceFrame * mMultiSourceFrame);

	FramePainter(IColorFrame * mColorFrame);
	FramePainter(IDepthFrame * mDepthFrame);
	FramePainter(IBodyFrame * mBodyFrame);


	~FramePainter();
};

