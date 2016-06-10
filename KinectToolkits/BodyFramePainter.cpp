#include "stdafx.h"
#include "BodyFramePainter.h"





BodyFramePainter::BodyFramePainter(IMultiSourceFrame * multiSourceFrame)
{
	if (SUCCEEDED(this->initializing(multiSourceFrame))) {

	}
	else {
		
	}
}

BodyFramePainter::~BodyFramePainter()
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();

	for (int i = 0; i < BODY_COUNT; i++) {
		if (this->bodies[i]) 
			bodies[i]->Release();
	}
}


Mat BodyFramePainter::getFrame()
{
	return this->mFrameMat;
}


HRESULT BodyFramePainter::update(IMultiSourceFrame * multiSourceFrame)
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();


	if (SUCCEEDED(multiSourceFrame->get_BodyFrameReference(&(this->mFrameReference)))) {
		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {

			if (SUCCEEDED(this->mFrame->GetAndRefreshBodyData(BODY_COUNT, this->bodies))) {

				for (int i = 0; i < BODY_COUNT; i++) {

					this->isTracked = false;
					if (this->bodies[i]) {

						if (SUCCEEDED(bodies[i]->get_IsTracked(&isTracked)) && isTracked) {

							this->skeleton->update(bodies[i]);

							for (int j = i; j < BODY_COUNT; j++) {
								bodies[j]->Release();
							}
							return S_OK;
						}

						bodies[i]->Release();
					}
				}
			}
		}
	}
	return E_FAIL;
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
	this->setHealth(UNHEALTHY);
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
void BodyFramePainter::setHealth(bool health)
{
	this->health = health;
}
