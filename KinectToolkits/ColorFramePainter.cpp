#include "stdafx.h"
#include "ColorFramePainter.h"

#define CHANNEL 4

using namespace cv;
ColorFramePainter::ColorFramePainter()
{
}


ColorFramePainter::ColorFramePainter(IMultiSourceFrame * mMultiSourceFrame)
{
	if (SUCCEEDED(this->initializing(mMultiSourceFrame))) {

	}


		
}

ColorFramePainter::ColorFramePainter(IMultiSourceFrame * mMultiSourceFrame, int resizingHeight, int resizingWidth)
{
	if (SUCCEEDED(this->initializing(mMultiSourceFrame))) {
		this->enablingResizing(resizingHeight, resizingWidth);
		this->mFrameMat = Mat::zeros(this->mDesiredFrameHeight, this->mDesiredFrameWidth, CV_8UC4);
		this->setHealth(true);
	}

	else
		this->setHealth(false);
}

ColorFramePainter::ColorFramePainter(IColorFrame * mColorFrame)
{
}

ColorFramePainter::~ColorFramePainter()
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();
	if (this->mFrameDescription) this->mFrameDescription->Release();
}

void ColorFramePainter::setHealth(bool health)
{
	this->health = health;
}

bool ColorFramePainter::getHealth()
{
	return this->health;
}

bool ColorFramePainter::isHealthy()
{
	return this->health;
}



int ColorFramePainter::getFrameHeight()
{
	return this->mFrameHeight;
}

int ColorFramePainter::getFrameWidth()
{
	return this->mFrameWidth;
}

UINT8 * ColorFramePainter::getFrameArray()
{
	this->copyFrameDataToArray();
	return this->mFrameArray;
}

UINT ColorFramePainter::getFrameArraySize()
{
	return this->mFrameArraySize;
}



HRESULT ColorFramePainter::initializing(IMultiSourceFrame * mMultiSourceFrame)
{
	if (SUCCEEDED(mMultiSourceFrame->get_ColorFrameReference(&(this->mFrameReference)))) {

		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {

			if (SUCCEEDED(this->mFrame->get_FrameDescription(&(this->mFrameDescription)))) {

				if (SUCCEEDED(this->mFrameDescription->get_Height(&(this->mFrameHeight))) &&
					SUCCEEDED(this->mFrameDescription->get_Width(&(this->mFrameWidth)))) {

					if (this->mFrameHeight * this->mFrameWidth != 0) {

						this->mFrameMat = Mat::zeros(this->mFrameHeight, this->mFrameWidth, CV_8UC4);
						this->setHealth(HEALTHY);

						this->mFrameArraySize = (this->mFrameHeight) * (this->mFrameWidth) * CHANNEL;
						this->mFrameArray = new UINT8[this->mFrameArraySize];
						return S_OK;
					}
						
				}
			}
		}
	}
	this->setHealth(UNHEALTHY);
	return E_FAIL;
}

HRESULT ColorFramePainter::update(IMultiSourceFrame *multiSourceFrame)
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();

	if (SUCCEEDED(multiSourceFrame->get_ColorFrameReference(&(this->mFrameReference)))) {
		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {
			return S_OK;
		}
	}
	return E_FAIL;
}

void ColorFramePainter::enablingResizing(int resizingHeight, int resizingWidth) {
	this->resizeEnabled = true;
	this->setDesiredHeight(resizingHeight);
	this->setDesiredWidth(resizingWidth);
}

void ColorFramePainter::disablingResizing() {
	this->resizeEnabled = false;
}

void ColorFramePainter::setDesiredHeight(int desiredHeight) {
	this->mDesiredFrameHeight = desiredHeight;
}

void ColorFramePainter::setDesiredWidth(int desiredWidth) {
	this->mDesiredFrameWidth = desiredWidth;
}

Mat ColorFramePainter::getFrame()
{
	this->copyFrameDataToMat();
	return this->mFrameMat;
}

void ColorFramePainter::copyFrameDataToMat() {

	if (SUCCEEDED(this->copyFrameDataToArray())) {

		if (resizeEnabled) {
			resize(Mat(this->mFrameHeight, this->mFrameWidth, CV_8UC4, this->mFrameArray),
				   this->mFrameMat, 
				   (this->mFrameMat).size(), 
				   0, 
				   0, 
				   INTER_LINEAR);
		}
		else {
			this->mFrameMat = Mat(this->mFrameHeight, this->mFrameWidth, CV_8UC4, this->mFrameArray);
		}
	}
}

HRESULT ColorFramePainter::copyFrameDataToArray() {

	return this->mFrame->CopyConvertedFrameDataToArray(this->mFrameArraySize,
													   this->mFrameArray,
													   ColorImageFormat::ColorImageFormat_Bgra);
}


