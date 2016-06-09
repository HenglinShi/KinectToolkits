#pragma once
#include "FramePainter.h"
class BodyFramePainter :
	public FramePainter
{
private:
	IBodyFrame * mFrame = nullptr;
	IBodyFrameReference * mFrameReference = nullptr;

	BOOLEAN isTracked = false;

	int mFrameHeight;
	int mFrameWidth;

	IBody* bodies[BODY_COUNT] = { 0 };
	IBody* body;

	Skeleton * skeletons[BODY_COUNT] = { 0 };
	Skeleton * skeleton;

public:
	BodyFramePainter();
	BodyFramePainter(IMultiSourceFrame * multiSourceFrame);
	BodyFramePainter(IBodyFrameReader * mBodyFrameReader);
	Mat getFrame();
	HRESULT update(IMultiSourceFrame * multiSourceFrame);
	void setFrame();
	~BodyFramePainter();
};

