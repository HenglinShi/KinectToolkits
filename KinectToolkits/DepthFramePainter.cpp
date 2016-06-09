#include "stdafx.h"
#include "DepthFramePainter.h"


DepthFramePainter::DepthFramePainter()
{
	this->mFrameRGBXMat = new RGBQUAD[this->mFrameHeight * this->mFrameHeight];
}


DepthFramePainter::~DepthFramePainter()
{
}

HRESULT DepthFramePainter::update(IMultiSourceFrame * mMultiSourceFrame)
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();

	if (SUCCEEDED(mMultiSourceFrame->get_DepthFrameReference(&(this->mFrameReference)))) {
		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {
			this->setFrame();
			return S_OK;
		}
	}
	return E_FAIL;
}

void DepthFramePainter::setFrame()
{
	this->mFrame->AccessUnderlyingBuffer(&(this->mFrameBufferSize), &(this->mFrameBuffer));

	RGBQUAD* depthFrameRGBXPointer = this->mFrameRGBXMat;
	const UINT16* mFrameBufferEnd = this->mFrameBuffer + this->mFrameHeight * this->mFrameWidth;

	while (this->mFrameBuffer < mFrameBufferEnd) {
		USHORT depth = * (this->mFrameBuffer);

		if (depth < 0) {
			depthFrameRGBXPointer->rgbRed = 0xFF;
			depthFrameRGBXPointer->rgbGreen = 0;
			depthFrameRGBXPointer->rgbBlue = 0;
			depthFrameRGBXPointer->rgbReserved = 0xFF;
		}
		else if (depth < depthFrameMinReliableDistance) {
			depthFrameRGBXPointer->rgbRed = 0;
			depthFrameRGBXPointer->rgbGreen = depth & 0x7F + 0x80;
			depthFrameRGBXPointer->rgbBlue = 0;
			depthFrameRGBXPointer->rgbReserved = 0xFF;
		}
		else if (depth < depthFrameMaxReliableDistance) {
			depthFrameRGBXPointer->rgbRed = depth & 0xFF;
			depthFrameRGBXPointer->rgbGreen = depthFrameRGBXPointer->rgbRed;
			depthFrameRGBXPointer->rgbBlue = depthFrameRGBXPointer->rgbRed;
			depthFrameRGBXPointer->rgbReserved = 0xFF;
		}
		else {
			depthFrameRGBXPointer->rgbRed = 0;
			depthFrameRGBXPointer->rgbGreen = 0;
			depthFrameRGBXPointer->rgbBlue = depth & 0x7F + 0x80;
			depthFrameRGBXPointer->rgbReserved = 0xFF;
		}
		++ depthFrameRGBXPointer;
		++ this->mFrameBuffer;
	}
	this->mFrameMat = Mat(this->mFrameHeight, this->mFrameWidth, CV_8UC4, this->mFrameRGBXMat);
}
