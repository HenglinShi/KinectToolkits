#include "stdafx.h"
#include "MultiSourceFrameReader.h"


MultiSourceFrameReader::MultiSourceFrameReader()
{
	
}

HRESULT MultiSourceFrameReader::openReader(IKinectSensor *mKinectSensor, vector<int> mFrameSourceTypes)
{
	DWORD sensoringMode = 0x00;
	for (int i = 0; i < mFrameSourceTypes.size; i++)
		sensoringMode = sensoringMode | mFrameSourceTypes[i];
	if (SUCCEEDED(mKinectSensor->OpenMultiSourceFrameReader(sensoringMode, &(this->multiSourceFrameReader))))
		return S_OK;
	return E_FAIL;
}

HRESULT MultiSourceFrameReader::update()
{
	if (multiSourceFrame) multiSourceFrame->Release();
	if (SUCCEEDED(this->multiSourceFrameReader->AcquireLatestFrame(&(this->multiSourceFrame)))) {
		this->bodyFramePainter->update();
		this->colorFramePainter->update();
		this->depthFramePainter->update();
	}

}

void MultiSourceFrameReader::getDepthFrame()
{
	this->bodyFramePainter->getFrame();
}

void MultiSourceFrameReader::getColorFrame()
{
	this->colorFramePainter->getFrame();
}

void MultiSourceFrameReader::getBodyFrame()
{
	this->bodyFramePainter->getFrame();
}



MultiSourceFrameReader::MultiSourceFrameReader(IKinectSensor *mKinectSensor, vector<int> mFrameSourceTypes)
{
	if (SUCCEEDED(this->openReader(mKinectSensor, mFrameSourceTypes))) {
		isHealthy = true;

		this->bodyFramePainter = new BodyFramePainter();
		this->colorFramePainter = new ColorFramePainter();
		this->depthFramePainter = new DepthFramePainter();
	}
}

bool MultiSourceFrameReader::getHealth()
{
	return isHealthy;
}

MultiSourceFrameReader::~MultiSourceFrameReader()
{
}
