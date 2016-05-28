#include "stdafx.h"
#include "KinectInstance.h"
#include "FrameReader.h"

int main() {
	
	KinectInstance *mKinect = new KinectInstance();
	if (mKinect->getState = KINECT_STATE_READY) {
		FrameReader * mFrameReader = new FrameReader(mKinect);

	}



}