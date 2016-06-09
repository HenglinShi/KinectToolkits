#include "stdafx.h"
#include "KinectInstance.h"
#include "FrameReader.h"

int main() {
	

	vector <DWORD> frameSourceTypes { FrameSourceTypes::FrameSourceTypes_Depth, 
									  FrameSourceTypes::FrameSourceTypes_Color, 
									  FrameSourceTypes::FrameSourceTypes_Body, 
									  FrameSourceTypes::FrameSourceTypes_BodyIndex };

	KinectInstance * mKinect = new KinectInstance(frameSourceTypes);

	if (mKinect->getState() == KINECT_STATE_READY) {

		namedWindow("DEPTH", CV_WINDOW_AUTOSIZE);
		namedWindow("COLOR", CV_WINDOW_AUTOSIZE);
		namedWindow("BODY INDEX", CV_WINDOW_AUTOSIZE);
		namedWindow("SKELETON", CV_WINDOW_AUTOSIZE);


		while (1)
		{
			mKinect->acquireLatestFrames();
			imshow("DEPTH", mKinect->getDepthFrame());
			imshow("COLOR", mKinect->getColorFrame());
			imshow("BODY INDEX", mKinect->getBodyIndexFrame());
			imshow("SKELETON", mKinect->getSkeletonFrame());
			waitKey(1);
		}


		

	}



}