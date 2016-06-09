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

UINT16 * BodyIndexFramePainter::getFrameArray()
{
	return nullptr;
}

UINT BodyIndexFramePainter::getFrameArraySize()
{
	return 0;
}

RGBQUAD * BodyIndexFramePainter::getFrameArrayRGBX()
{
	return nullptr;
}

UINT BodyIndexFramePainter::getFrameArrayRGBXSize()
{
	return 0;
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

		this->mFrameMat = Mat(this->mFrameHeight, this->mFrameWidth, CV_8UC4, this->mFrameRGBXMat);
	}
}

void BodyIndexFramePainter::copyFrameDataToMat()
{
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
