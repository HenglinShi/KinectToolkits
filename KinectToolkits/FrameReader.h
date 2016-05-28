#pragma once
#include <vector>
#include "stdafx.h"
#include "KinectInstance.h"
using namespace std;

class FrameReader
{
private:
	KinectInstance * mKinect = nullptr;
public:
	FrameReader();
	FrameReader(KinectInstance *mKinect, vector <int> mFrameSourceTypes);
	~FrameReader();
};

