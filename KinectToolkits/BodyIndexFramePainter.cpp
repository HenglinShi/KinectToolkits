#include "stdafx.h"
#include "BodyIndexFramePainter.h"


BodyIndexFramePainter::BodyIndexFramePainter()
{
	mFrameRGBXMat = new RGBQUAD[this->mFrameHeight * this->mFrameWidth];
}


BodyIndexFramePainter::~BodyIndexFramePainter()
{
}

HRESULT BodyIndexFramePainter::update(IMultiSourceFrame * mMultiSourceFrame)
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();

	if (SUCCEEDED(mMultiSourceFrame->get_BodyIndexFrameReference(&(this->mFrameReference)))) {
		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {
			this->setFrame();
			return S_OK;
		}
	}
	return E_FAIL;
}

void BodyIndexFramePainter::setFrame()
{
	if (SUCCEEDED(this->mFrame->AccessUnderlyingBuffer(&(this->mFrameBufferSize), &(this->mFrameBuffer)))) {
		RGBQUAD * mFrameRGBXMatPointer = this->mFrameRGBXMat;

		for (UINT i = 0; i < this->mFrameBufferSize; i++) {
			mFrameRGBXMatPointer->rgbRed = (*(this->mFrameBuffer)) & 0x01 ? 0x00 : 0xFF;
			mFrameRGBXMatPointer->rgbGreen = (*(this->mFrameBuffer)) & 0x02 ? 0x00 : 0xFF;
			mFrameRGBXMatPointer->rgbBlue = (*(this->mFrameBuffer)) & 0x04 ? 0x00 : 0xFF;
			mFrameRGBXMatPointer->rgbReserved = 0XFF;
			mFrameRGBXMatPointer ++;
			(this->mFrameBuffer) ++;
		}

		this->mFrameMat = Mat(this->mFrameHeight, this->mFrameWidth, CV_8UC4, this->mFrameRGBXMat);
	}
}
