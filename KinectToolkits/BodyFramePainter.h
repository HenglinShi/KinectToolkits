#pragma once
#include "stdafx.h"
#include "Skeleton.h"
#define HEALTHY true
#define UNHEALTHY false
class BodyFramePainter :
	public FramePainter
{

private:
	IBodyFrame * mFrame = nullptr;
	IBodyFrameReference * mFrameReference = nullptr;
	IFrameDescription *mFrameDescription = nullptr;

	bool health = UNHEALTHY;

	BOOLEAN isTracked = false;

	int mFrameHeight;
	int mFrameWidth;

	IBody* bodies[BODY_COUNT] = { 0 };
	Mat mFrameMat;

	Skeleton * skeletons[BODY_COUNT] = { 0 };
	Skeleton * skeleton;

	void setHealth(bool health);

public:

	BodyFramePainter(IMultiSourceFrame * multiSourceFrame);

	Mat getFrame();
	HRESULT update(IMultiSourceFrame * multiSourceFrame);

	~BodyFramePainter();

	HRESULT initializing(IMultiSourceFrame * mMultiSourceFrame);

	bool getHealth();
	bool isHealthy();

};

