#include "stdafx.h"
#include "BodyFramePainter.h"


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
			this->setFrame();
			return S_OK;
		}
	}
	return E_FAIL;
}

void BodyFramePainter::setFrame()
{
	if (SUCCEEDED(this->mFrame->GetAndRefreshBodyData(BODY_COUNT, bodies))) {
		for (int i = 0; i < BODY_COUNT; i++) {
			body = bodies[i];

			this->isTracked = false;

			if (body) {
				if (SUCCEEDED(body->get_IsTracked(&isTracked)) && isTracked) {
					skeleton = new Skeleton();

					if (SUCCEEDED(body->GetJoints(JointType_Count, skeleton)))
				}
			}
		}
		
	}
}

BodyFramePainter::~BodyFramePainter()
{
}
