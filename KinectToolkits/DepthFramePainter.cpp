#include "stdafx.h"
#include "DepthFramePainter.h"

DepthFramePainter::DepthFramePainter(IMultiSourceFrame * mMultiSourceFrame)
{
	if (SUCCEEDED(this->initializing(mMultiSourceFrame))) {

		this->mFrameMat = Mat::zeros(this->mFrameHeight, this->mFrameWidth, CV_8UC4);
		this->mFrameArrayRGBXSize = mFrameHeight * mFrameWidth;
		this->mFrameArrayRGBX = new RGBQUAD[this->mFrameArrayRGBXSize];

		this->setHealth(HEALTHY);
	}
	else 
		this->setHealth(UNHEALTHY);
}


DepthFramePainter::~DepthFramePainter()
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();
	if (this->mFrameDescription) this->mFrameDescription;
}

HRESULT DepthFramePainter::initializing(IMultiSourceFrame * mMultiSourceFrame)
{
	if (SUCCEEDED(mMultiSourceFrame->get_DepthFrameReference(&(this->mFrameReference)))) {

		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {

			if (SUCCEEDED(this->mFrame->get_FrameDescription(&(this->mFrameDescription)))) {

				if (SUCCEEDED(this->mFrameDescription->get_Height(&(this->mFrameHeight))) &&
					SUCCEEDED(this->mFrameDescription->get_Width(&(this->mFrameWidth)))) {

					if (this->mFrameHeight * this->mFrameWidth != 0) {
						if (SUCCEEDED(this->mFrame->get_DepthMaxReliableDistance(&(this->depthFrameMaxReliableDistance))) &&
							SUCCEEDED(this->mFrame->get_DepthMinReliableDistance(&(this->depthFrameMinReliableDistance))))

							return S_OK;
					}

				}
			}
		}
	}
	return E_FAIL;
}

HRESULT DepthFramePainter::update(IMultiSourceFrame * mMultiSourceFrame)
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();

	if (SUCCEEDED(mMultiSourceFrame->get_DepthFrameReference(&(this->mFrameReference)))) {
		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {

			return S_OK;
		}
	}
	return E_FAIL;
}

void DepthFramePainter::setHealth(bool health)
{
	this->health = health;
}


bool DepthFramePainter::getHealth()
{
	return this->health;
}

bool DepthFramePainter::isHealthy()
{
	return this->health;
}

UINT16 * DepthFramePainter::getFrameArray()
{
	return this->mFrameArray;
}

UINT DepthFramePainter::getFrameArraySize()
{
	return this->mFrameArraySize;
}

RGBQUAD * DepthFramePainter::getFrameArrayRGBX()
{
	this->copyFrameDataToArray();
	return this->getFrameArrayRGBX();
}

UINT DepthFramePainter::getFrameArrayRGBXSize()
{
	return this->getFrameArrayRGBXSize();
}

Mat DepthFramePainter::getFrame()
{
	this->copyFrameDataToMat();
	return this->mFrameMat;
}


HRESULT DepthFramePainter::copyFrameDataToArray()
{
	if (SUCCEEDED())
	this->mFrame->AccessUnderlyingBuffer(&(this->mFrameArraySize), &(this->mFrameArray));

	RGBQUAD* mFrameArrayRGBXIterator = this->mFrameArrayRGBX;

	const UINT16* mFrameArrayEnd = this->mFrameArray + this->mFrameHeight * this->mFrameWidth;

	while (this->mFrameArray < mFrameArrayEnd) {

		USHORT depth = *(this->mFrameArray);

		if (depth < 0) {
			mFrameArrayRGBXIterator->rgbRed = 0xFF;
			mFrameArrayRGBXIterator->rgbGreen = 0;
			mFrameArrayRGBXIterator->rgbBlue = 0;
			mFrameArrayRGBXIterator->rgbReserved = 0xFF;
		}
		else if (depth < depthFrameMinReliableDistance) {
			mFrameArrayRGBXIterator->rgbRed = 0;
			mFrameArrayRGBXIterator->rgbGreen = depth & 0x7F + 0x80;
			mFrameArrayRGBXIterator->rgbBlue = 0;
			mFrameArrayRGBXIterator->rgbReserved = 0xFF;
		}
		else if (depth < depthFrameMaxReliableDistance) {
			mFrameArrayRGBXIterator->rgbRed = depth & 0xFF;
			mFrameArrayRGBXIterator->rgbGreen = mFrameArrayRGBXIterator->rgbRed;
			mFrameArrayRGBXIterator->rgbBlue = mFrameArrayRGBXIterator->rgbRed;
			mFrameArrayRGBXIterator->rgbReserved = 0xFF;
		}
		else {
			mFrameArrayRGBXIterator->rgbRed = 0;
			mFrameArrayRGBXIterator->rgbGreen = 0;
			mFrameArrayRGBXIterator->rgbBlue = depth & 0x7F + 0x80;
			mFrameArrayRGBXIterator->rgbReserved = 0xFF;
		}
		++mFrameArrayRGBXIterator;
		++ this->mFrameArray;
	}
}


void DepthFramePainter::copyFrameDataToMat()
{
	this->copyFrameDataToArray();
	this->mFrameMat = Mat(this->mFrameHeight, this->mFrameWidth, CV_8UC4, this->mFrameArrayRGBX);
}