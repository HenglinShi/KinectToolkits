#include "stdafx.h"
#include "KinectInstance.h"


int KinectInstance::initializing()
{
	if (SUCCEEDED(GetDefaultKinectSensor(&this->mKinectSensor))) {
		if (this->mKinectSensor) {
			if (SUCCEEDED(this->setCoordinateMapper())) {
				if (SUCCEEDED(this->openSensor())) {
					this->setStateReady();
					return this->getState();
				}
			}
		}
	}
	return this->getState();
}




void KinectInstance::setState(int newKinectState)
{
	this->state = newKinectState;
}

void KinectInstance::setStateReady()
{
	this->setState(KINECT_STATE_READY);
}

void KinectInstance::setStatePending()
{
	this->setState(KINECT_STATE_PENDING);
}

HRESULT KinectInstance::setCoordinateMapper()
{
	return this->mKinectSensor->get_CoordinateMapper(&(this->mCoordinateMapper));
}

HRESULT KinectInstance::openSensor()
{
	return this->mKinectSensor->Open();
}

HRESULT KinectInstance::openReader(vector <DWORD> mFrameSourceTypes)
{
	this->mMultiSourceFrameReader = new MultiSourceFrameReader(this->mKinectSensor, mFrameSourceTypes);
	if (this->mMultiSourceFrameReader->getHealth())
		return S_OK;

	return E_FAIL;
}

HRESULT KinectInstance::openReader(int mFrameSourceType)
{

	return E_NOTIMPL;
}

int KinectInstance::getState()
{
	return this->state;
}

HRESULT KinectInstance::acquireLatestFrames()
{
	if(SUCCEEDED(this->mMultiSourceFrameReader->acquireLatestFrames()))
		return S_OK;
	return E_FAIL;
}

void KinectInstance::update()
{
}

Mat KinectInstance::getDepthFrame()
{
	return this->mMultiSourceFrameReader->getDepthFrame();
}

Mat KinectInstance::getColorFrame()
{
	return this->mMultiSourceFrameReader->getColorFrame();
}

Mat KinectInstance::getBodyIndexFrame()
{
	return this->mMultiSourceFrameReader->getBodyIndexFrame();
}

Mat KinectInstance::getSkeletonFrame()
{
	return this->mMultiSourceFrameReader->getSkeletonFrame();
}

KinectInstance::KinectInstance(vector <DWORD> mFrameSourceTypes)
{
	if (this->initializing() == KINECT_STATE_READY) 
		if (SUCCEEDED(this->openReader(mFrameSourceTypes))) {

		}

		else {
			this->setStatePending();
		}
}


KinectInstance::~KinectInstance()
{

}

Mat KinectInstance::getDepthFrameOnColorSpace()
{
	return this->mMultiSourceFrameReader->getColorFrame();
}
