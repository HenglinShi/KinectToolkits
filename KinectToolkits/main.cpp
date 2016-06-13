#include "stdafx.h"
#include <omp.h>
#include <time.h> 
//#include "KinectInstance.h"
//#include "FrameReader.h"

IKinectSensor *kinectSensor = nullptr;
ICoordinateMapper* multisourceCoordinateMapper;

IMultiSourceFrameReader * multiSourceFrameReader = nullptr;



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


BYTE * colorFrameArray;
UINT colorFrameArraySize = 0;
UINT colorFramePointNum = 0;
DepthSpacePoint * colorPointCoordinateInDepthSpace = nullptr;
DepthSpacePoint colorPointCoordinateInDepthSpaceIterator;
Mat colorFrameMat;
Mat colorFrameMatInDepth;
BYTE * colorFrameArrayInDepthSpace = nullptr;

Mat depthFrameMat;
UINT16 * depthFrameArray = nullptr;
UINT16 * depthFrameArrayEnd = nullptr;
UINT  depthFrameArraySize = 0;
RGBQUAD * depthFrameArrayRGBX = nullptr;
RGBQUAD * depthFrameArrayRGBXIterator = nullptr;
UINT depthFrameArrayRGBXSize = 0;


Mat bodyIndexFrameMat;
BYTE * bodyIndexFrameArray = nullptr;
BYTE * bodyIndexArrayEnd = nullptr;
UINT bodyIndexFrameArraySize = 0;
RGBQUAD * bodyIndexFrameArrayRGBX = nullptr;
RGBQUAD * bodyIndexFrameArrayRGBXIterator = nullptr;
UINT bodyIndexFrameArrayRGBXSize = 0;


Mat bodyFrameMat;
IBody* bodies[BODY_COUNT] = { 0 };
IBody * trackedBody;
BOOLEAN isTracked = false;

Joint joints[JointType_Count];
JointOrientation jointsOrientations[JointType_Count];

Joint jointTmp;
JointOrientation jointOrientationTmp;
DepthSpacePoint depthSpacePointTmp[JointType_Count];
CvPoint depthSkeletonPoint[JointType_Count] = { cvPoint(-1.0, -1.0) };

//Skeleton * skeleton = nullptr;
//BodyFramePainter * mBodyFramePainter = nullptr;
//ColorFramePainter * mColorFramePainter = nullptr;
//DepthFramePainter * mDepthFramePainter = nullptr;
//BodyIndexFramePainter * mBodyIndexFramePainter = nullptr;

float skeletonJoints[9 * JointType_Count] = { 0 };
Mat drawAperson(CvPoint *jointsPoints, CvScalar skeletonColor, int skeletonThickness, Mat tmpSkeletonMat);

//HRESULT initializing();

typedef struct BodySkeleton
{
	Mat bodyInfoMat;
	float skeletonInfo[9 * JointType_Count] = { 0 };
	CameraSpacePoint cameraSpacePoint[JointType_Count] = { 0.0, 0.0, 0.0 };
};


#define CHANNEL 4
/*Initializing Kinect Device*/

HRESULT initializingKinectDevice()
{
	if (SUCCEEDED(GetDefaultKinectSensor(&kinectSensor))) {

		if (SUCCEEDED(kinectSensor->get_CoordinateMapper(&multisourceCoordinateMapper))) {
			kinectSensor->Open();
			if (SUCCEEDED(kinectSensor->OpenMultiSourceFrameReader(
				FrameSourceTypes::FrameSourceTypes_Depth |
				FrameSourceTypes::FrameSourceTypes_Color |
				FrameSourceTypes::FrameSourceTypes_Body |
				FrameSourceTypes::FrameSourceTypes_BodyIndex,
				&multiSourceFrameReader)))
				return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT initializingBodyFrame(IMultiSourceFrame * multiSourceFrame) {

	IBodyFrameReference * mBodyFrameReference = nullptr;
	IBodyFrame * mBodyFrame = nullptr;
	if (SUCCEEDED(multiSourceFrame->get_BodyFrameReference(&mBodyFrameReference))) {
		if (SUCCEEDED(mBodyFrameReference->AcquireFrame(&mBodyFrame))) {


			//skeleton = new Skeleton();		
			bodyFrameMat = Mat::zeros(depthFrameHeight, depthFrameWidth, CV_8UC4);
			//BodySkeleton *skeleton = new BodySkeleton();
			mBodyFrameReference->Release();
			mBodyFrame->Release();
			return S_OK;
		}
		mBodyFrameReference->Release();
	}

	return E_FAIL;
}


HRESULT initializingColorFrame(IMultiSourceFrame * multiSourceFrame) {
	IColorFrameReference * mColorFrameReference = nullptr;
	IColorFrame *mColorFrame = nullptr;
	IFrameDescription * mColorFrameDescription = nullptr;

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
						//colorFrameMatInDepth = Mat::zeros(depthFrameHeight, depthFrameWidth, CV_8UC4);
					}

					mColorFrameDescription->Release();
					mColorFrame->Release();
					mColorFrameReference->Release();
					return S_OK;
				}

			}

		}

	}
	if (mColorFrameDescription) mColorFrameDescription->Release();
	if (mColorFrame) mColorFrame->Release();
	if (mColorFrameReference) mColorFrameReference->Release();
	return E_FAIL;
}
HRESULT initializingDepthFrame(IMultiSourceFrame * multiSourceFrame) {
	IDepthFrame *mDepthFrame = nullptr;
	IDepthFrameReference * mDepthFrameReference = nullptr;
	IFrameDescription * mDepthFrameDescription = nullptr;

	if (SUCCEEDED(multiSourceFrame->get_DepthFrameReference(&mDepthFrameReference))) {
		if (SUCCEEDED(mDepthFrameReference->AcquireFrame(&mDepthFrame))) {
			if (SUCCEEDED(mDepthFrame->get_FrameDescription(&mDepthFrameDescription))) {

				if (SUCCEEDED(mDepthFrameDescription->get_Height(&depthFrameHeight)) &&
					SUCCEEDED(mDepthFrameDescription->get_Width(&depthFrameWidth))) {

					if (depthFrameHeight * depthFrameWidth != 0) {
						if (SUCCEEDED(mDepthFrame->get_DepthMaxReliableDistance(&depthFrameMaxReliableDistance)) &&
							SUCCEEDED(mDepthFrame->get_DepthMinReliableDistance(&depthFrameMinReliableDistance))) {

							depthFrameArrayRGBXSize = depthFrameWidth * depthFrameHeight;
							depthFrameArrayRGBX = new RGBQUAD[depthFrameArrayRGBXSize];
							colorFrameArrayInDepthSpace = new BYTE[depthFrameHeight * depthFrameWidth * CHANNEL];
							depthFrameArraySize = depthFrameHeight * depthFrameWidth;
							depthFrameArray = new UINT16[depthFrameArraySize];
							mDepthFrameDescription->Release();
							mDepthFrame->Release();
							mDepthFrameReference->Release();
							return S_OK;
						}
					}
				}

			}

		}

	}
	if (mDepthFrameDescription) mDepthFrameDescription->Release();
	if (mDepthFrame) mDepthFrame->Release();
	if (mDepthFrameReference) mDepthFrameReference->Release();

	return E_FAIL;
}
HRESULT initializingBodyIndexFrame(IMultiSourceFrame * multiSourceFrame) {
	IBodyIndexFrameReference * mBodyIndexFrameReference = nullptr;
	IBodyIndexFrame *mBodyIndexFrame = nullptr;
	IFrameDescription * mBodyIndexFrameDescription = nullptr;

	if (SUCCEEDED(multiSourceFrame->get_BodyIndexFrameReference(&mBodyIndexFrameReference))) {
		if (SUCCEEDED(mBodyIndexFrameReference->AcquireFrame(&mBodyIndexFrame))) {
			if (SUCCEEDED(mBodyIndexFrame->get_FrameDescription(&mBodyIndexFrameDescription))) {
				if (SUCCEEDED(mBodyIndexFrameDescription->get_Height(&bodyIndexFrameHeight)) &&
					SUCCEEDED(mBodyIndexFrameDescription->get_Width(&bodyIndexFrameWidth))) {

					if (bodyIndexFrameHeight * bodyIndexFrameWidth != 0) {

						bodyIndexFrameArrayRGBXSize = bodyIndexFrameHeight * bodyIndexFrameWidth;
						bodyIndexFrameArrayRGBX = new RGBQUAD[bodyIndexFrameArrayRGBXSize];

						bodyIndexFrameArraySize = bodyIndexFrameHeight * bodyIndexFrameWidth;
						bodyIndexFrameArray = new BYTE[bodyIndexFrameArraySize];

						mBodyIndexFrameDescription->Release();
						mBodyIndexFrame->Release();
						mBodyIndexFrameReference->Release();
						return S_OK;
					}
				}

			}

		}

	}
	if (mBodyIndexFrameDescription) mBodyIndexFrameDescription->Release();
	if (mBodyIndexFrame) mBodyIndexFrame->Release();
	if (mBodyIndexFrameReference) mBodyIndexFrameReference->Release();
	return E_FAIL;
}

HRESULT updateBodyFrame(IMultiSourceFrame * multiSourceFrame) {

	IBodyFrameReference * mBodyFrameReference = nullptr;
	IBodyFrame * mBodyFrame = nullptr;

	if (SUCCEEDED(multiSourceFrame->get_BodyFrameReference(&mBodyFrameReference))) {
		if (SUCCEEDED(mBodyFrameReference->AcquireFrame(&mBodyFrame))) {


			if (SUCCEEDED(mBodyFrame->GetAndRefreshBodyData(BODY_COUNT, bodies))) {
				for (int i = 0; i < BODY_COUNT; i++) {
					if (bodies[i]) {
						if (SUCCEEDED(bodies[i]->get_IsTracked(&isTracked)) && isTracked) {
							//isTracked = false;		
							trackedBody = bodies[i];


							if (SUCCEEDED(trackedBody->GetJoints(JointType_Count, joints) &&
								SUCCEEDED(trackedBody->GetJointOrientations(JointType_Count, jointsOrientations)))) {

								for (int jointIte = 0; jointIte < JointType_Count; jointIte++) {

									jointTmp = joints[jointIte];
									jointOrientationTmp = jointsOrientations[jointIte];

									if (jointTmp.TrackingState > 0) {
										skeletonJoints[0 + jointIte * 9] = jointTmp.Position.X;
										skeletonJoints[1 + jointIte * 9] = jointTmp.Position.Y;
										skeletonJoints[2 + jointIte * 9] = jointTmp.Position.Z;

										//Get space point;

										skeletonJoints[3 + jointIte * 9] = jointOrientationTmp.Orientation.w;
										skeletonJoints[4 + jointIte * 9] = jointOrientationTmp.Orientation.x;
										skeletonJoints[5 + jointIte * 9] = jointOrientationTmp.Orientation.y;
										skeletonJoints[6 + jointIte * 9] = jointOrientationTmp.Orientation.z;

										if (SUCCEEDED(multisourceCoordinateMapper->MapCameraPointToDepthSpace(jointTmp.Position, &depthSpacePointTmp[jointIte]))) {
											skeletonJoints[7 + jointIte * 9] = depthSkeletonPoint[jointIte].x = depthSpacePointTmp[jointIte].X;
											skeletonJoints[8 + jointIte * 9] = depthSkeletonPoint[jointIte].y = depthSpacePointTmp[jointIte].Y;

										}
									}
								}
							}

							mBodyFrame->Release();
							mBodyFrameReference->Release();
							return S_OK;
						}
						//bodies[i]->Release();
					}
				}
			}
		}
	}
	if (mBodyFrame) mBodyFrame->Release();
	if (mBodyFrameReference) mBodyFrameReference->Release();

	return E_FAIL;
}

HRESULT updateDepthFrame(IMultiSourceFrame * multiSourceFrame) {
	IDepthFrame *mDepthFrame = nullptr;
	IDepthFrameReference * mDepthFrameReference = nullptr;
	//IFrameDescription * mDepthFrameDescription = nullptr;

	if (SUCCEEDED(multiSourceFrame->get_DepthFrameReference(&mDepthFrameReference))) {
		if (SUCCEEDED(mDepthFrameReference->AcquireFrame(&mDepthFrame))) {

			//Put depth frame data to buffer
			if (SUCCEEDED(mDepthFrame->CopyFrameDataToArray(depthFrameArraySize, depthFrameArray))) {
				//cout << "accessing depth frame buffer failed" << endl;

				if (FAILED(multisourceCoordinateMapper->MapColorFrameToDepthSpace(
					depthFrameArraySize,
					depthFrameArray,
					colorFramePointNum,
					colorPointCoordinateInDepthSpace))) {
					cout << "mapping pixels failed" << endl;
					//releaseAllFrames();

					mDepthFrame->Release();
					mDepthFrameReference->Release();

					return E_FAIL;
				}


				depthFrameArrayRGBXIterator = depthFrameArrayRGBX;
				depthFrameArrayEnd = depthFrameArray + depthFrameArraySize;


				for (UINT16 *i = depthFrameArray; i < depthFrameArrayEnd; i++) {

					USHORT depth = *i;

					if (depth < 0) {
						depthFrameArrayRGBXIterator->rgbRed = 0xFF;
						depthFrameArrayRGBXIterator->rgbGreen = 0;
						depthFrameArrayRGBXIterator->rgbBlue = 0;
						depthFrameArrayRGBXIterator->rgbReserved = 0xFF;
					}
					else if (depth < depthFrameMinReliableDistance) {
						depthFrameArrayRGBXIterator->rgbRed = 0;
						depthFrameArrayRGBXIterator->rgbGreen = depth & 0x7F + 0x80;
						depthFrameArrayRGBXIterator->rgbBlue = 0;
						depthFrameArrayRGBXIterator->rgbReserved = 0xFF;
					}
					else if (depth < depthFrameMaxReliableDistance) {
						depthFrameArrayRGBXIterator->rgbRed = depth & 0xFF;
						depthFrameArrayRGBXIterator->rgbGreen = depthFrameArrayRGBXIterator->rgbRed;
						depthFrameArrayRGBXIterator->rgbBlue = depthFrameArrayRGBXIterator->rgbRed;
						depthFrameArrayRGBXIterator->rgbReserved = 0xFF;
					}
					else {
						depthFrameArrayRGBXIterator->rgbRed = 0;
						depthFrameArrayRGBXIterator->rgbGreen = 0;
						depthFrameArrayRGBXIterator->rgbBlue = depth & 0x7F + 0x80;
						depthFrameArrayRGBXIterator->rgbReserved = 0xFF;
					}
					++depthFrameArrayRGBXIterator;
					
				}

				depthFrameMat = Mat(depthFrameHeight, depthFrameWidth, CV_8UC4, depthFrameArrayRGBX);

				mDepthFrame->Release();
				mDepthFrameReference->Release();
				return S_OK;
			}
		}
	}
	if (mDepthFrame) mDepthFrame->Release();
	if (mDepthFrameReference) mDepthFrameReference->Release();
	return E_FAIL;
}

HRESULT updateColorFrame(IMultiSourceFrame * multiSourceFrame) {
	IColorFrameReference * mColorFrameReference = nullptr;
	IColorFrame *mColorFrame = nullptr;
	//mColorFrameReference = nullptr;
	if (SUCCEEDED(multiSourceFrame->get_ColorFrameReference(&mColorFrameReference))) {
		//mColorFrame = nullptr;
		//if (mColorFrame) mColorFrame->Release();
		if (SUCCEEDED(mColorFrameReference->AcquireFrame(&mColorFrame))) {

			//Acquire color framea
			if (SUCCEEDED(mColorFrame->CopyConvertedFrameDataToArray(
				colorFrameArraySize,
				colorFrameArray,
				ColorImageFormat::ColorImageFormat_Bgra))) {

				//#pragma omp parallel for
				for (int i = 0; i < colorFramePointNum; i++) {
					colorPointCoordinateInDepthSpaceIterator = colorPointCoordinateInDepthSpace[i];

					int depthX = static_cast<int>(colorPointCoordinateInDepthSpaceIterator.X + 0.5f);
					int depthY = static_cast<int>(colorPointCoordinateInDepthSpaceIterator.Y + 0.5f);


					if (colorPointCoordinateInDepthSpaceIterator.X >= 0 && colorPointCoordinateInDepthSpaceIterator.X < depthFrameWidth) {
						if (colorPointCoordinateInDepthSpaceIterator.Y >= 0 && colorPointCoordinateInDepthSpaceIterator.Y < depthFrameHeight) {
							colorFrameArrayInDepthSpace[(depthY * depthFrameWidth + depthX) * 4] = colorFrameArray[i * 4];
							colorFrameArrayInDepthSpace[(depthY * depthFrameWidth + depthX) * 4 + 1] = colorFrameArray[i * 4 + 1];
							colorFrameArrayInDepthSpace[(depthY * depthFrameWidth + depthX) * 4 + 2] = colorFrameArray[i * 4 + 2];
							colorFrameArrayInDepthSpace[(depthY * depthFrameWidth + depthX) * 4 + 3] = colorFrameArray[i * 4 + 3];

						}
					}
				}

				colorFrameMat = Mat(depthFrameHeight, depthFrameWidth, CV_8UC4, colorFrameArrayInDepthSpace);
				mColorFrame->Release();
				mColorFrameReference->Release();
				return S_OK;
			}
			//How about updating a exisiting mat, rather than newing one?
		}

	}
	if (mColorFrame) mColorFrame->Release();
	if (mColorFrameReference) {
		mColorFrameReference->Release();
	}

	return E_FAIL;
}

HRESULT updateBodyIndexFrame(IMultiSourceFrame * multiSourceFrame) {
	IBodyIndexFrameReference * mBodyIndexFrameReference = nullptr;
	IBodyIndexFrame *mBodyIndexFrame = nullptr;
	if (SUCCEEDED(multiSourceFrame->get_BodyIndexFrameReference(&mBodyIndexFrameReference))) {


		if (SUCCEEDED(mBodyIndexFrameReference->AcquireFrame(&mBodyIndexFrame))) {

			if (SUCCEEDED(mBodyIndexFrame->CopyFrameDataToArray(bodyIndexFrameArraySize, bodyIndexFrameArray))) {

				bodyIndexFrameArrayRGBXIterator = bodyIndexFrameArrayRGBX;
				BYTE * bodyIndexFrameArrayIterator = bodyIndexFrameArray;

				for (UINT i = 0; i < bodyIndexFrameArraySize; i++) {
					bodyIndexFrameArrayRGBXIterator->rgbRed = (*bodyIndexFrameArrayIterator) & 0x01 ? 0x00 : 0xFF;
					bodyIndexFrameArrayRGBXIterator->rgbGreen = (*bodyIndexFrameArrayIterator) & 0x02 ? 0x00 : 0xFF;
					bodyIndexFrameArrayRGBXIterator->rgbBlue = (*bodyIndexFrameArrayIterator) & 0x04 ? 0x00 : 0xFF;
					bodyIndexFrameArrayRGBXIterator->rgbReserved = 0XFF;
					bodyIndexFrameArrayRGBXIterator++;
					bodyIndexFrameArrayIterator++;
				}

				bodyIndexFrameMat = Mat(bodyIndexFrameHeight, bodyIndexFrameWidth, CV_8UC4, bodyIndexFrameArrayRGBX);


				mBodyIndexFrame->Release();
				mBodyIndexFrameReference->Release();
				return S_OK;
			}
		}

	}
	if (mBodyIndexFrame) mBodyIndexFrame->Release();
	if (mBodyIndexFrameReference) mBodyIndexFrameReference->Release();
	return E_FAIL;
}


HRESULT update(IMultiSourceFrame * multiSourceFrame)
{



	if (FAILED(updateBodyFrame(multiSourceFrame))) {
		//cout << "update body frame failed" << endl;
		return E_FAIL;
	}
	if (FAILED(updateBodyIndexFrame(multiSourceFrame))) {
		cout << "update body index frame failed" << endl;
		return E_FAIL;
	}
	if (FAILED(updateDepthFrame(multiSourceFrame))) {
		cout << "update depth frame failed" << endl;
		return E_FAIL;
	}
	if (FAILED(updateColorFrame(multiSourceFrame))) {
		//cout << "update color frame failed" << endl;
		return E_FAIL;
	}
	return S_OK;
}


int main() {

	IMultiSourceFrame * multiSourceFrame = nullptr;
	while (FAILED(initializingKinectDevice())) {}

	while (FAILED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
		if (multiSourceFrame) multiSourceFrame->Release();
	}

	cout << "Initializing painters ---- First try" << endl;

	while (FAILED(initializingBodyFrame(multiSourceFrame))) {
		cout << "BodyFramePainter initializing failed" << endl;
		cout << "fixing" << endl;

		multiSourceFrame->Release();

		while (FAILED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
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

	CvScalar skeletonColor = cvScalar(0.0, 0.0, 255.0);


	time_t startTimer;
	time_t endTimer;
	double seconds;
	time(&startTimer);
	int frameNum = 0;


	while (1)
	{
		if (SUCCEEDED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {


			if (SUCCEEDED(update(multiSourceFrame))) {


				frameNum++;
				time(&endTimer);
				seconds = difftime(endTimer, startTimer);

				if (seconds >= 1) {
					cout << frameNum << endl;
					time(&startTimer);
					frameNum = 0;
				}
				



				imshow("DEPTH", depthFrameMat);
				imshow("COLOR", colorFrameMat);
				imshow("BODY INDEX", bodyIndexFrameMat);
				imshow("SKELETON", (bodyIndexFrameMat + drawAperson(depthSkeletonPoint, skeletonColor, 10, bodyIndexFrameMat)));
				waitKey(1);
			}
		}

		if (multiSourceFrame)
			multiSourceFrame->Release();


	}






}

//HRESULT initializing()
//{
//	while (FAILED(initializingKinectDevice())) {}
//
//	/*Initializing painters, first try*/
//
//	if (multiSourceFrame) multiSourceFrame->Release();
//
//	while (FAILED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
//		if (multiSourceFrame) multiSourceFrame->Release();
//	}
//
//	cout << "Initializing painters ---- First try" << endl;
//
//	BodyFramePainter * mBodyFramePainter = new BodyFramePainter(multiSourceFrame);
//	ColorFramePainter * mColorFramePainter = new ColorFramePainter(multiSourceFrame);
//	DepthFramePainter * mDepthFramePainter = new DepthFramePainter(multiSourceFrame);
//	BodyIndexFramePainter * mBodyIndexFramePainter = new BodyIndexFramePainter(multiSourceFrame);
//
//	if (multiSourceFrame) multiSourceFrame->Release();
//
//
//	/*Handling exceptions of failed painter initialization*/
//
//	while (!mBodyFramePainter->isHealthy()) {
//		cout << "BodyFramePainter initializing failed" << endl;
//		cout << "fixing" << endl;
//		if (SUCCEEDED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
//			mBodyFramePainter->initializing(multiSourceFrame);
//		}
//		if (multiSourceFrame) multiSourceFrame->Release();
//	}
//	cout << "BodyFramePainter initializing succeeded" << endl;
//
//	while (!mColorFramePainter->isHealthy()) {
//		cout << "ColorFramePainter initializing failed" << endl;
//		cout << "fixing" << endl;
//		if (SUCCEEDED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
//			mColorFramePainter->initializing(multiSourceFrame);
//		}
//		if (multiSourceFrame) multiSourceFrame->Release();
//	}
//	cout << "ColorFramePainter initializing succeeded" << endl;
//
//
//	while (!mDepthFramePainter->isHealthy()) {
//		cout << "DepthFramePainter initializing failed" << endl;
//		cout << "fixing" << endl;
//		if (SUCCEEDED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
//			mDepthFramePainter->initializing(multiSourceFrame);
//		}
//		if (multiSourceFrame) multiSourceFrame->Release();
//	}
//	cout << "DepthFramePainter initializing succeeded" << endl;
//
//
//	while (!mBodyIndexFramePainter->isHealthy()) {
//		cout << "BodyIndexFramePainter initializing failed" << endl;
//		cout << "fixing" << endl;
//		if (SUCCEEDED(multiSourceFrameReader->AcquireLatestFrame(&multiSourceFrame))) {
//			mBodyIndexFramePainter->initializing(multiSourceFrame);
//		}
//		if (multiSourceFrame) multiSourceFrame->Release();
//	}
//	cout << "BodyIndexFramePainter initializing succeeded" << endl;
//
//	return S_OK;
//}





Mat drawAperson(CvPoint *jointsPoints, CvScalar skeletonColor, int skeletonThickness, Mat tmpSkeletonMat) {


	//HEAD + NECK
	if ((jointsPoints[JointType_Head].x >= 0) && (jointsPoints[JointType_Neck].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_Head], jointsPoints[JointType_Neck], skeletonColor, skeletonThickness);

	//NECK + SPINE SHOULDER;
	if ((jointsPoints[JointType_Neck].x >= 0) && (jointsPoints[JointType_SpineShoulder].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_Neck], jointsPoints[JointType_SpineShoulder], skeletonColor, skeletonThickness);

	//SPINE SHOULDER + RIGHT SHOULDER
	if ((jointsPoints[JointType_SpineShoulder].x >= 0) && (jointsPoints[JointType_ShoulderRight].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_SpineShoulder], jointsPoints[JointType_ShoulderRight], skeletonColor, skeletonThickness);

	//SPINE SHOULDER + LEFT SHOULDER
	if ((jointsPoints[JointType_SpineShoulder].x >= 0) && (jointsPoints[JointType_ShoulderLeft].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_SpineShoulder], jointsPoints[JointType_ShoulderLeft], skeletonColor, skeletonThickness);
	//RIGHT SHOULDER + RIGHT ELBOW

	if ((jointsPoints[JointType_ShoulderRight].x >= 0) && (jointsPoints[JointType_ElbowRight].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_ShoulderRight], jointsPoints[JointType_ElbowRight], skeletonColor, skeletonThickness);

	//LEFT SHOULDER + LEFT ELBOW
	if ((jointsPoints[JointType_ShoulderLeft].x >= 0) && (jointsPoints[JointType_ElbowLeft].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_ShoulderLeft], jointsPoints[JointType_ElbowLeft], skeletonColor, skeletonThickness);

	// RIGHT ELBOW + RIGHT WRIST
	if ((jointsPoints[JointType_ElbowRight].x >= 0) && (jointsPoints[JointType_WristRight].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_ElbowRight], jointsPoints[JointType_WristRight], skeletonColor, skeletonThickness);

	//LEFT ELBOW + LEFT WRIST
	if ((jointsPoints[JointType_ElbowLeft].x >= 0) && (jointsPoints[JointType_WristLeft].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_ElbowLeft], jointsPoints[JointType_WristLeft], skeletonColor, skeletonThickness);

	//RIGHT WRIST + RIGHT HAND
	if ((jointsPoints[JointType_WristRight].x >= 0) && (jointsPoints[JointType_HandRight].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_WristRight], jointsPoints[JointType_HandRight], skeletonColor, skeletonThickness);

	//LEFT WRIST + LEFT HAND
	if ((jointsPoints[JointType_WristLeft].x >= 0) && (jointsPoints[JointType_HandLeft].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_WristLeft], jointsPoints[JointType_HandLeft], skeletonColor, skeletonThickness);

	//RIGHT HAND + RIGHT THUMB
	if ((jointsPoints[JointType_HandRight].x >= 0) && (jointsPoints[JointType_ThumbRight].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_HandRight], jointsPoints[JointType_ThumbRight], skeletonColor, skeletonThickness);

	//LEFT HAND + LEFT THUMB
	if ((jointsPoints[JointType_HandLeft].x >= 0) && (jointsPoints[JointType_ThumbLeft].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_HandLeft], jointsPoints[JointType_ThumbLeft], skeletonColor, skeletonThickness);

	//RIGHT HAND + RIGHT HANDTIP
	if ((jointsPoints[JointType_HandRight].x >= 0) && (jointsPoints[JointType_HandTipRight].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_HandRight], jointsPoints[JointType_HandTipRight], skeletonColor, skeletonThickness);

	//LEFT HAND + LEFT HANDTIP
	if ((jointsPoints[JointType_HandLeft].x >= 0) && (jointsPoints[JointType_HandTipLeft].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_HandLeft], jointsPoints[JointType_HandTipLeft], skeletonColor, skeletonThickness);

	//SPINE SHOULDER + SPINE MID
	if ((jointsPoints[JointType_SpineShoulder].x >= 0) && (jointsPoints[JointType_SpineMid].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_SpineShoulder], jointsPoints[JointType_SpineMid], skeletonColor, skeletonThickness);

	//SPINE MID + SPINE BASE
	if ((jointsPoints[JointType_SpineMid].x >= 0) && (jointsPoints[JointType_SpineBase].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_SpineMid], jointsPoints[JointType_SpineBase], skeletonColor, skeletonThickness);

	//SPINE BASE + RIGHT HIP
	if ((jointsPoints[JointType_SpineBase].x >= 0) && (jointsPoints[JointType_HipRight].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_SpineBase], jointsPoints[JointType_HipRight], skeletonColor, skeletonThickness);

	//SPINE BASE + LEFT HIP
	if ((jointsPoints[JointType_SpineBase].x >= 0) && (jointsPoints[JointType_HipLeft].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_SpineBase], jointsPoints[JointType_HipLeft], skeletonColor, skeletonThickness);

	//RIGHT HIP + RIGHT KNEE
	if ((jointsPoints[JointType_HipRight].x >= 0) && (jointsPoints[JointType_KneeRight].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_HipRight], jointsPoints[JointType_KneeRight], skeletonColor, skeletonThickness);

	//LEFT HIP + LEFT KNEE
	if ((jointsPoints[JointType_HipLeft].x >= 0) && (jointsPoints[JointType_KneeLeft].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_HipLeft], jointsPoints[JointType_KneeLeft], skeletonColor, skeletonThickness);

	//RIGHT KNEE + RIGHT ANKLE
	if ((jointsPoints[JointType_KneeRight].x >= 0) && (jointsPoints[JointType_AnkleRight].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_KneeRight], jointsPoints[JointType_AnkleRight], skeletonColor, skeletonThickness);

	//LEFT KNEE + LEFT ANKLE
	if ((jointsPoints[JointType_KneeLeft].x >= 0) && (jointsPoints[JointType_AnkleLeft].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_KneeLeft], jointsPoints[JointType_AnkleLeft], skeletonColor, skeletonThickness);

	//RIGHT ANKLE + RIGHT FOOT
	if ((jointsPoints[JointType_AnkleRight].x >= 0) && (jointsPoints[JointType_FootRight].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_AnkleRight], jointsPoints[JointType_FootRight], skeletonColor, skeletonThickness);

	//LEFT ANKLE + LEFT FOOT
	if ((jointsPoints[JointType_AnkleLeft].x >= 0) && (jointsPoints[JointType_FootLeft].x >= 0))
		line(tmpSkeletonMat, jointsPoints[JointType_AnkleLeft], jointsPoints[JointType_FootLeft], skeletonColor, skeletonThickness);

	return tmpSkeletonMat;

}
