#include "stdafx.h"
#include "KinectInstance.h"
#include "FrameReader.h"

IKinectSensor *kinectSensor = nullptr;
ICoordinateMapper* multisourceCoordinateMapper;

IMultiSourceFrameReader * multiSourceFrameReader = nullptr;

IMultiSourceFrame * multiSourceFrame = nullptr;
IBodyFrameReference * mBodyFrameReference = nullptr;
IColorFrameReference * mColorFrameReference = nullptr;
IDepthFrameReference * mDepthFrameReference = nullptr;
IBodyIndexFrameReference * mBodyIndexFrameReference = nullptr;

IBodyFrame * mBodyFrame = nullptr;
IColorFrame *mColorFrame = nullptr;
IDepthFrame *mDepthFrame = nullptr;
IBodyIndexFrame *mBodyIndexFrame = nullptr;

IFrameDescription * mBodyFrameDescrption = nullptr;
IFrameDescription * mColorFrameDescription = nullptr;
IFrameDescription * mDepthFrameDescription = nullptr;
IFrameDescription * mBodyIndexFrameDescription = nullptr;

int bodyFrameHeight = 0;
int bodyFrameWidth = 0;
int colorFrameHeight = 0;
int colorFrameWidth = 0;
int depthFrameHeight = 0;
int depthFrameWidth = 0;

int bodyIndexFrameHeight = 0;
int bodyIndexFrameWidth = 0;

USHORT depthFrameMinReliableDistance = 0;
USHORT depthFrameMaxReliableDistance = 0;

UINT colorFrameArraySize = 0;
UINT colorFramePointNum = 0;

BYTE * colorFrameArray;
DepthSpacePoint * colorPointCoordinateInDepthSpace = nullptr;
DepthSpacePoint colorPointCoordinateInDepthSpaceIterator;

UINT  depthFrameArraySize = 0;
UINT16  * depthFrameArray = nullptr;

Skeleton * skeleton = nullptr;

BodyFramePainter * mBodyFramePainter = nullptr;
ColorFramePainter * mColorFramePainter = nullptr;
DepthFramePainter * mDepthFramePainter = nullptr;
BodyIndexFramePainter * mBodyIndexFramePainter = nullptr;

#define CHANNEL 4
/*Initializing Kinect Device*/

HRESULT initializingKinectDevice()
{
	if (SUCCEEDED(GetDefaultKinectSensor(&kinectSensor))) {

		if (SUCCEEDED(kinectSensor->get_CoordinateMapper(&multisourceCoordinateMapper))) {
			kinectSensor->Open();
			kinectSensor->OpenMultiSourceFrameReader(
				FrameSourceTypes::FrameSourceTypes_Depth |
				FrameSourceTypes::FrameSourceTypes_Color |
				FrameSourceTypes::FrameSourceTypes_Body |
				FrameSourceTypes::FrameSourceTypes_BodyIndex,
				&multiSourceFrameReader);
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT initializingBodyFrame(IMultiSourceFrame * multiSourceFrame) {
	if (mBodyFrameReference) mBodyFrameReference->Release();
	if (mBodyFrame) mBodyFrame->Release();

	if (SUCCEEDED(multiSourceFrame->get_BodyFrameReference(&mBodyFrameReference))) {
		if (SUCCEEDED(mBodyFrameReference->AcquireFrame(&mBodyFrame))) {
			skeleton = new Skeleton();		
			return S_OK;
		}	
	}

	return E_FAIL;
}

HRESULT initializingColorFrame(IMultiSourceFrame * multiSourceFrame) {
	if (mColorFrameReference) mColorFrameReference->Release();
	if (mColorFrame) mColorFrame->Release();
	if (mColorFrameDescription) mColorFrameDescription->Release();

	if (SUCCEEDED(multiSourceFrame->get_ColorFrameReference(&mColorFrameReference))) {
		if (SUCCEEDED(mColorFrameReference->AcquireFrame(&mColorFrame))) {
			if (SUCCEEDED(mColorFrame->get_FrameDescription(&mColorFrameDescription))) {

				if (SUCCEEDED(mColorFrameDescription->get_Height(&colorFrameHeight)) &&
					SUCCEEDED(mColorFrameDescription->get_Width(&colorFrameWidth))) {

					colorFramePointNum = colorFrameHeight * colorFrameWidth;
					colorFrameArraySize = colorFramePointNum * CHANNEL;

					if (colorFrameArraySize > 0) {
						colorFrameArray = new BYTE[colorFrameArraySize];
						colorPointCoordinateInDepthSpace = new DepthSpacePoint[colorFramePointNum];
					}
					
					
					return S_OK;
				}
			}
		}
	}
	return E_FAIL;
}
HRESULT initializingDepthFrame(IMultiSourceFrame * multiSourceFrame) {
	if (mDepthFrameReference) mDepthFrameReference->Release();
	if (mDepthFrame) mDepthFrame->Release();
	if (mDepthFrameDescription) mDepthFrameDescription->Release();

	if (SUCCEEDED(multiSourceFrame->get_DepthFrameReference(&mDepthFrameReference))) {

		if (SUCCEEDED(mDepthFrameReference->AcquireFrame(&mDepthFrame))) {

			if (SUCCEEDED(mDepthFrame->get_FrameDescription(&mDepthFrameDescription))) {

				if (SUCCEEDED(mDepthFrameDescription->get_Height(&depthFrameHeight)) &&
					SUCCEEDED(mDepthFrameDescription->get_Width(&depthFrameWidth))) {

					if (depthFrameHeight * depthFrameWidth != 0) {
						if (SUCCEEDED(mDepthFrame->get_DepthMaxReliableDistance(&depthFrameMaxReliableDistance)) &&
							SUCCEEDED(mDepthFrame->get_DepthMinReliableDistance(&depthFrameMinReliableDistance))) {
							return S_OK;

						}						
					}
				}
			}
		}
	}
	return E_FAIL;
}
HRESULT initializingBodyIndexFrame(IMultiSourceFrame * multiSourceFrame) {
	if (SUCCEEDED(multiSourceFrame->get_BodyIndexFrameReference(&mBodyIndexFrameReference))) {

		if (SUCCEEDED(mBodyIndexFrameReference->AcquireFrame(&mBodyIndexFrame))) {

			if (SUCCEEDED(mBodyIndexFrame->get_FrameDescription(&mBodyIndexFrameDescription))) {

				if (SUCCEEDED(mBodyIndexFrameDescription->get_Height(&bodyIndexFrameHeight)) &&
					SUCCEEDED(mBodyIndexFrameDescription->get_Width(&bodyIndexFrameWidth))) {

					if (bodyIndexFrameHeight * bodyIndexFrameWidth != 0) {
						return S_OK;
					}
				}
			}
		}
	}
	return E_FAIL;
}

HRESULT updateBodyFrame() {
	if (mBodyFrameReference) mBodyFrameReference->Release();
	if (SUCCEEDED(multiSourceFrame->get_BodyFrameReference(&mBodyFrameReference))) {

		if (mBodyFrame) mBodyFrame->Release();
		if (SUCCEEDED(mBodyFrameReference->AcquireFrame(&mBodyFrame))) {
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT updateDepthFrame() {
	if (mDepthFrameReference) mDepthFrameReference->Release();
	if (SUCCEEDED(multiSourceFrame->get_DepthFrameReference(&mDepthFrameReference))) {

		if (mDepthFrame) mDepthFrame->Release();
		if (SUCCEEDED(mDepthFrameReference->AcquireFrame(&mDepthFrame))) {
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT updateColorFrame() {
	if (mColorFrameReference) mColorFrameReference->Release();
	if (SUCCEEDED(multiSourceFrame->get_ColorFrameReference(&mColorFrameReference))) {

		if (mColorFrame) mColorFrame->Release();
		if (SUCCEEDED(mColorFrameReference->AcquireFrame(&mColorFrame))) {

			mColorFrame->

			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT updateBodyIndexFrame() {
	if (mBodyIndexFrameReference) mBodyIndexFrameReference->Release();
	if (SUCCEEDED(multiSourceFrame->get_BodyIndexFrameReference(&mBodyIndexFrameReference))) {

		if (mBodyIndexFrame) mBodyIndexFrame->Release();
		if (SUCCEEDED(mBodyIndexFrameReference->AcquireFrame(&mBodyIndexFrame))) {
			return S_OK;
		}
	}
	return E_FAIL;
}
HRESULT update()
{
	if (multiSourceFrame) multiSourceFrame->Release();

	if (SUCCEEDED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {

		if (SUCCEEDED(updateBodyFrame) &&
			SUCCEEDED(updateColorFrame) &&
			SUCCEEDED(updateDepthFrame) &&
			SUCCEEDED(updateBodyIndexFrame))

			//SUCCEEDED(mColorFrame->AccessRawUnderlyingBuffer(&colorFrameArraySize, &colorFrameArray))

			if (SUCCEEDED(mDepthFrame->AccessUnderlyingBuffer(&depthFrameArraySize, &depthFrameArray))) {

				if (SUCCEEDED(multisourceCoordinateMapper->MapColorFrameToDepthSpace(
									depthFrameArraySize,
									depthFrameArray,
									colorFramePointNum,
									colorPointCoordinateInDepthSpace))) {

					//TRANSFORMING COLOR FRAME POINTS ACCORDING TO THE GIVEN COORDINATE

					for (int i = 0; i < colorFramePointNum; i++) {
						colorPointCoordinateInDepthSpaceIterator = colorPointCoordinateInDepthSpace[i];

						if (colorPointCoordinateInDepthSpaceIterator.X != -numeric_limits<float>::infinity() &&
							colorPointCoordinateInDepthSpaceIterator.Y != -numeric_limits<float>::infinity()) {

							if ((colorPointCoordinateInDepthSpaceIterator.X >= 0 && colorPointCoordinateInDepthSpaceIterator.X < depthFrameWidth) &&
								(colorPointCoordinateInDepthSpaceIterator.Y >= 0 && colorPointCoordinateInDepthSpaceIterator.Y < depthFrameHeight)) {

							}

						}


					}


				}






				if (SUCCEEDED(mColorFrame->CopyConvertedFrameDataToArray(
					colorFrameArraySize,
					colorFrameArray,
					ColorImageFormat::ColorImageFormat_Bgra))) {

				}
			}
 

			if (SUCCEEDED(mColorFrame->CopyConvertedFrameDataToArray(
							colorFrameArraySize,
							colorFrameArray,
							ColorImageFormat::ColorImageFormat_Bgra))) {

			}



		mDepthFrame->AccessUnderlyingBuffer(&depthFrameArraySize, &depthFrameArray);
		multisourceCoordinateMapper->MapColorFrameToDepthSpace(
			depthFrameArraySize,
			depthFrameArray,
			colorFrameArraySize,
			colorPointCoordinateInDepthSpace);







			return S_OK;
	}

	return E_FAIL;
}


int main() {


	while (FAILED(initializingKinectDevice())) {}

	while (FAILED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
		if (multiSourceFrame) multiSourceFrame->Release();
	}

	cout << "Initializing painters ---- First try" << endl;
	
	while (FAILED(initializingBodyFrame(multiSourceFrame))) {
		cout << "BodyFramePainter initializing failed" << endl;
		cout << "fixing" << endl;

		if (multiSourceFrame) multiSourceFrame->Release();
		while (FAILED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
			if (multiSourceFrame) multiSourceFrame->Release();
		}
	}

	while (FAILED(initializingDepthFrame(multiSourceFrame))) {
		cout << "DepthFramePainter initializing failed" << endl;
		cout << "fixing" << endl;

		if (multiSourceFrame) multiSourceFrame->Release();
		while (FAILED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
			if (multiSourceFrame) multiSourceFrame->Release();
		}
	}

	while (FAILED(initializingColorFrame(multiSourceFrame))) {
		cout << "ColorFramePainter initializing failed" << endl;
		cout << "fixing" << endl;

		if (multiSourceFrame) multiSourceFrame->Release();
		while (FAILED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
			if (multiSourceFrame) multiSourceFrame->Release();
		}
	}

	while (FAILED(initializingBodyIndexFrame(multiSourceFrame))) {
		cout << "initializingBodyIndexFrame initializing failed" << endl;
		cout << "fixing" << endl;

		if (multiSourceFrame) multiSourceFrame->Release();
		while (FAILED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
			if (multiSourceFrame) multiSourceFrame->Release();
		}
	}

	if (multiSourceFrame) multiSourceFrame->Release();


	namedWindow("DEPTH", CV_WINDOW_AUTOSIZE);
	namedWindow("COLOR", CV_WINDOW_AUTOSIZE);
	namedWindow("BODY INDEX", CV_WINDOW_AUTOSIZE);
	namedWindow("SKELETON", CV_WINDOW_AUTOSIZE);



	while (1)
	{
		while (1) {
			if (FAILED(update()))
				break;
		}

		//mDepthFrame->CopyFrameDataToArray(mDepthFrameArraySize, mDepthFrameArray);
		//GET COLOR FRAME

		multisourceCoordinateMapper->MapColorFrameToDepthSpace()
			mColorFramePainter->getFrameArraySize(),
			mColorFramePainter->getFrameArray(),
			mColorFramePainter->getFrameArrayInDepthSpace(),
			mColorFramePainter->getFrameArrayInDepthSpaceSize())



			(;




		mDepthFramePainter->getFrameArraySize,


			)




			imshow("DEPTH", mKinect->getDepthFrame());
		imshow("COLOR", mKinect->getColorFrame());
		imshow("BODY INDEX", mKinect->getBodyIndexFrame());
		//imshow("SKELETON", mKinect->getSkeletonFrame());
		waitKey(1);
	}
}

HRESULT initializing()
{
	while (FAILED(initializingKinectDevice())) {}

	/*Initializing painters, first try*/

	if (multiSourceFrame) multiSourceFrame->Release();

	while (FAILED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
		if (multiSourceFrame) multiSourceFrame->Release();
	}

	cout << "Initializing painters ---- First try" << endl;

	BodyFramePainter * mBodyFramePainter = new BodyFramePainter(multiSourceFrame);
	ColorFramePainter * mColorFramePainter = new ColorFramePainter(multiSourceFrame);
	DepthFramePainter * mDepthFramePainter = new DepthFramePainter(multiSourceFrame);
	BodyIndexFramePainter * mBodyIndexFramePainter = new BodyIndexFramePainter(multiSourceFrame);

	if (multiSourceFrame) multiSourceFrame->Release();


	/*Handling exceptions of failed painter initialization*/

	while (!mBodyFramePainter->isHealthy()) {
		cout << "BodyFramePainter initializing failed" << endl;
		cout << "fixing" << endl;
		if (SUCCEEDED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
			mBodyFramePainter->initializing(multiSourceFrame);
		}
		if (multiSourceFrame) multiSourceFrame->Release();
	}
	cout << "BodyFramePainter initializing succeeded" << endl;

	while (!mColorFramePainter->isHealthy()) {
		cout << "ColorFramePainter initializing failed" << endl;
		cout << "fixing" << endl;
		if (SUCCEEDED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
			mColorFramePainter->initializing(multiSourceFrame);
		}
		if (multiSourceFrame) multiSourceFrame->Release();
	}
	cout << "ColorFramePainter initializing succeeded" << endl;


	while (!mDepthFramePainter->isHealthy()) {
		cout << "DepthFramePainter initializing failed" << endl;
		cout << "fixing" << endl;
		if (SUCCEEDED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
			mDepthFramePainter->initializing(multiSourceFrame);
		}
		if (multiSourceFrame) multiSourceFrame->Release();
	}
	cout << "DepthFramePainter initializing succeeded" << endl;


	while (!mBodyIndexFramePainter->isHealthy()) {
		cout << "BodyIndexFramePainter initializing failed" << endl;
		cout << "fixing" << endl;
		if (SUCCEEDED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
			mBodyIndexFramePainter->initializing(multiSourceFrame);
		}
		if (multiSourceFrame) multiSourceFrame->Release();
	}
	cout << "BodyIndexFramePainter initializing succeeded" << endl;

	return S_OK;
}



