#include "stdafx.h"
#include "BodyFramePainter.h"


void BodyFramePainter::setHealth(bool health)
{
	this->health = health;
}

BodyFramePainter::BodyFramePainter()
{
}

BodyFramePainter::BodyFramePainter(IMultiSourceFrame * multiSourceFrame)
{
}


BodyFramePainter::BodyFramePainter(IBodyFrameReader * mBodyFrameReader) {

}

Mat BodyFramePainter::getFrame()
{
	return Mat();
}


HRESULT BodyFramePainter::update(IMultiSourceFrame * multiSourceFrame)
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();


	if (SUCCEEDED(multiSourceFrame->get_BodyFrameReference(&(this->mFrameReference)))) {
		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {
			if (SUCCEEDED(this->setFrame()))
				return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT BodyFramePainter::setFrame()
{
	if (SUCCEEDED(this->mFrame->GetAndRefreshBodyData(BODY_COUNT, bodies))) {
		for (int i = 0; i < BODY_COUNT; i++) {

			this->isTracked = false;
			if (bodies[i]) {
				if (SUCCEEDED(bodies[i]->get_IsTracked(&isTracked)) && isTracked) {
					this->skeleton = new Skeleton(bodies[i]);
					
					for (int j = i; j < BODY_COUNT; j++) {
						bodies[j]->Release();
					}
					return S_OK;
				}

				bodies[i]->Release();
			}
		}
	}
	return E_FAIL;
}

BodyFramePainter::~BodyFramePainter()
{
}

HRESULT BodyFramePainter::initializing(IMultiSourceFrame * mMultiSourceFrame)
{
	if (SUCCEEDED(mMultiSourceFrame->get_BodyFrameReference(&(this->mFrameReference)))) {
		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {
			this->skeleton = new Skeleton();
			this->setHealth(HEALTHY);
			return S_OK;
		}
	}
	return E_FAIL;
}

bool BodyFramePainter::getHealth()
{
	return this->health;
}

bool BodyFramePainter::isHealthy()
{
	return this->health;
}
