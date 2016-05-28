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
	this->setState = newKinectState;
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

int KinectInstance::getState()
{
	return this->state;
}

KinectInstance::KinectInstance()
{
	this->initializing();
}


KinectInstance::~KinectInstance()
{
}
