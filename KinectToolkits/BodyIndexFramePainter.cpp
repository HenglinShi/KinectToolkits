#include "stdafx.h"
#include "BodyIndexFramePainter.h"

BodyIndexFramePainter::BodyIndexFramePainter(IMultiSourceFrame * mMultiSourceFrame)
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


BodyIndexFramePainter::~BodyIndexFramePainter()
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();
	if (this->mFrameDescription) this->mFrameDescription->Release();
}


HRESULT BodyIndexFramePainter::initializing(IMultiSourceFrame * mMultiSourceFrame)
{
	if (SUCCEEDED(mMultiSourceFrame->get_BodyIndexFrameReference(&(this->mFrameReference)))) {

		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {

			if (SUCCEEDED(this->mFrame->get_FrameDescription(&(this->mFrameDescription)))) {

				if (SUCCEEDED(this->mFrameDescription->get_Height(&(this->mFrameHeight))) &&
					SUCCEEDED(this->mFrameDescription->get_Width(&(this->mFrameWidth)))) {

					if (this->mFrameHeight * this->mFrameWidth != 0) {

						return S_OK;

					}

				}
			}
		}
	}
	return E_FAIL;
}

HRESULT BodyIndexFramePainter::update(IMultiSourceFrame * mMultiSourceFrame)
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();

	if (SUCCEEDED(mMultiSourceFrame->get_BodyIndexFrameReference(&(this->mFrameReference)))) {
		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {

			return S_OK;
		}
	}
	return E_FAIL;
}

void BodyIndexFramePainter::setHealth(bool health)
{
	this->health = health;
}


bool BodyIndexFramePainter::getHealth()
{
	return this->health;
}

bool BodyIndexFramePainter::isHealthy()
{
	return this->health;
}



Mat BodyIndexFramePainter::getFrame()
{
	return this->mFrameMat;
}

BYTE * BodyIndexFramePainter::getFrameArray()
{
	return this->mFrameArray;
}

UINT BodyIndexFramePainter::getFrameArraySize()
{
	return this->mFrameArraySize;
}

RGBQUAD * BodyIndexFramePainter::getFrameArrayRGBX()
{
	return this->mFrameArrayRGBX;
}

UINT BodyIndexFramePainter::getFrameArrayRGBXSize()
{
	return this->mFrameArrayRGBXSize;
}


HRESULT BodyIndexFramePainter::copyFrameDataToArray()
{
	if (SUCCEEDED(this->mFrame->AccessUnderlyingBuffer(&(this->mFrameArraySize), &(this->mFrameArray)))) {

		RGBQUAD * mFrameArrayRGBXIterator = this->mFrameArrayRGBX;

		for (UINT i = 0; i < this->mFrameArraySize; i++) {
			mFrameArrayRGBXIterator->rgbRed = (*(this->mFrameArray)) & 0x01 ? 0x00 : 0xFF;
			mFrameArrayRGBXIterator->rgbGreen = (*(this->mFrameArray)) & 0x02 ? 0x00 : 0xFF;
			mFrameArrayRGBXIterator->rgbBlue = (*(this->mFrameArray)) & 0x04 ? 0x00 : 0xFF;
			mFrameArrayRGBXIterator->rgbReserved = 0XFF;
			mFrameArrayRGBXIterator++;
			(this->mFrameArray)++;
		}
		return S_OK;
		
	}
	return E_FAIL;
}

void BodyIndexFramePainter::copyFrameDataToMat()
{
	if (SUCCEEDED(this->copyFrameDataToArray()))
		this->mFrameMat = Mat(this->mFrameHeight, this->mFrameWidth, CV_8UC4, this->mFrameArrayRGBX);
}

