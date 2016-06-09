#include "stdafx.h"
#include "ColorFramePainter.h"

#define CHANNEL 4

using namespace cv;
ColorFramePainter::ColorFramePainter()
{
}


ColorFramePainter::ColorFramePainter(IMultiSourceFrame * mMultiSourceFrame)
{
	if (SUCCEEDED(mMultiSourceFrame->get_ColorFrameReference(&(this->mFrameReference)))) {

		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {

			if (SUCCEEDED(this->mFrame->get_FrameDescription(&(this->mFrameDescription)))) {

				if (SUCCEEDED(this->mFrameDescription->get_Height(&(this->mFrameHeight))) &&
					SUCCEEDED(this->mFrameDescription->get_Width(&(this->mFrameWidth)))) {

					mFrameMat = Mat::zeros(this->mFrameHeight, this->mFrameWidth, CV_8UC4);
					setFrame();
				}
			}
		}
	}
}

ColorFramePainter::ColorFramePainter(IMultiSourceFrame * mMultiSourceFrame, int resizingHeight, int resizingWidth)
{
	if (SUCCEEDED(mMultiSourceFrame->get_ColorFrameReference(&(this->mFrameReference)))) {

		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {

			if (SUCCEEDED(this->mFrame->get_FrameDescription(&(this->mFrameDescription)))) {

				if (SUCCEEDED(this->mFrameDescription->get_Height(&(this->mFrameHeight))) &&
					SUCCEEDED(this->mFrameDescription->get_Width(&(this->mFrameWidth)))) {

					this->enablingResizing(resizingHeight, resizingWidth);

					mFrameMat = Mat::zeros(this->mDesiredFrameHeight, this->mDesiredFrameWidth, CV_8UC4);
					setFrame();
				}
			}
		}
	}
}

ColorFramePainter::ColorFramePainter(IColorFrame * mColorFrame)
{
}

Mat ColorFramePainter::getFrame()
{
	return this->mFrameMat;
}

HRESULT ColorFramePainter::update(IMultiSourceFrame *multiSourceFrame)
{
	if (this->mFrameReference) this->mFrameReference->Release();
	if (this->mFrame) this->mFrame->Release();

	if (SUCCEEDED(multiSourceFrame->get_ColorFrameReference(&(this->mFrameReference)))) {
		if (SUCCEEDED(this->mFrameReference->AcquireFrame(&(this->mFrame)))) {
			this->setFrame();
			return S_OK;
		}
	}
	return E_FAIL;
}

ColorFramePainter::~ColorFramePainter()
{
}





void ColorFramePainter::initialization()
{

}


void ColorFramePainter::setFrame() {

	UINT8 *frameBuffer = new UINT8[(this->mFrameHeight) * (this->mFrameWidth) * CHANNEL];
	if (SUCCEEDED(this->mFrame->CopyConvertedFrameDataToArray((this->mFrameHeight) * (this->mFrameWidth) * CHANNEL,
		frameBuffer,
		ColorImageFormat::ColorImageFormat_Bgra))) {
		Mat tmpFrameMat = Mat(this->mFrameHeight, this->mFrameWidth, CV_8UC4, frameBuffer);
		if (resizeEnabled)
			resize(tmpFrameMat, this->mFrameMat, (this->mFrameMat).size(), 0, 0, INTER_LINEAR);
		else
			this->mFrameMat = tmpFrameMat;
	}
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