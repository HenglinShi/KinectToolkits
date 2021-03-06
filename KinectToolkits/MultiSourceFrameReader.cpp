#include "stdafx.h"
#include "MultiSourceFrameReader.h"


MultiSourceFrameReader::MultiSourceFrameReader()
{
	
}


MultiSourceFrameReader::MultiSourceFrameReader(IKinectSensor *mKinectSensor, vector<DWORD> mFrameSourceTypes)
{

	if (SUCCEEDED(this->openReader(mKinectSensor, mFrameSourceTypes))) {

		isHealthy = true;

		if (SUCCEEDED(this->multiSourceFrameReader->AcquireLatestFrame(&(this->multiSourceFrame)))) {

			cout << "Initializing bodyFramePainter..." << endl;

			this->bodyFramePainter = new BodyFramePainter(this->multiSourceFrame);

			while (!this->bodyFramePainter->isHealthy()) {
				cout << "Initializing bodyFramePainter failed..." << endl;
				cout << "reInitializing bodyFramePainter..." << endl;

				if (multiSourceFrame) multiSourceFrame->Release();
				if (SUCCEEDED(this->multiSourceFrameReader->AcquireLatestFrame(&(this->multiSourceFrame)))) {
					this->bodyFramePainter->initializing(this->multiSourceFrame);
				}
			}

			cout << "Initializing bodyFramePainter succeeded..." << endl<<endl;
			cout << "Initializing colorFramePainter..." << endl;


			this->colorFramePainter = new ColorFramePainter(this->multiSourceFrame);

			while (!this->colorFramePainter->isHealthy()) {
				cout << "Initializing colorFramePainter failed..." << endl;
				cout << "reInitializing colorFramePainter..." << endl;

				if (multiSourceFrame) multiSourceFrame->Release();
				if (SUCCEEDED(this->multiSourceFrameReader->AcquireLatestFrame(&(this->multiSourceFrame)))) {
					this->colorFramePainter->initializing(this->multiSourceFrame);
				}
			}


			cout << "Initializing colorFramePainter succeeded..." << endl << endl;
			cout << "Initializing depthFramePainter..." << endl;


			this->depthFramePainter = new DepthFramePainter(this->multiSourceFrame);

			while (!this->depthFramePainter->getHealth()) {
				cout << "Initializing depthFramePainter failed..." << endl;
				cout << "reInitializing depthFramePainter..." << endl;

				if (multiSourceFrame) multiSourceFrame->Release();
				if (SUCCEEDED(this->multiSourceFrameReader->AcquireLatestFrame(&(this->multiSourceFrame)))) {
					this->depthFramePainter->initializing(this->multiSourceFrame);
				}
			}

			cout << "Initializing depthFramePainter succeeded..." << endl << endl;
			cout << "Initializing bodyIndexFramePainter..." << endl;

			this->bodyIndexFramePainter = new BodyIndexFramePainter(this->multiSourceFrame);

			while (!this->bodyIndexFramePainter->getHealth()) {
				cout << "Initializing bodyIndexFramePainter failed..." << endl;
				cout << "reInitializing bodyIndexFramePainter..." << endl;

				if (multiSourceFrame) multiSourceFrame->Release();
				if (SUCCEEDED(this->multiSourceFrameReader->AcquireLatestFrame(&(this->multiSourceFrame)))) {
					this->bodyIndexFramePainter->initializing(this->multiSourceFrame);
				}
			}

			cout << "Initializing bodyIndexFramePainter succeeded..." << endl << endl;

		}



	}
}

MultiSourceFrameReader::~MultiSourceFrameReader()
{
	this->bodyFramePainter->~BodyFramePainter();
	this->colorFramePainter->~ColorFramePainter();
	this->depthFramePainter->~DepthFramePainter();
	this->bodyIndexFramePainter->~BodyIndexFramePainter();

	if (this->multiSourceFrameReader) this->multiSourceFrameReader->Release();
	if (this->multiSourceFrame) this->multiSourceFrame->Release();
}


HRESULT MultiSourceFrameReader::openReader(IKinectSensor *mKinectSensor, vector<DWORD> mFrameSourceTypes)
{
	DWORD sensoringMode = 0x00;
	for (UINT i = 0; i < mFrameSourceTypes.size(); i++)
		sensoringMode = sensoringMode | mFrameSourceTypes[i];
	if (SUCCEEDED(mKinectSensor->OpenMultiSourceFrameReader(sensoringMode, &(this->multiSourceFrameReader))))
		return S_OK;
	return E_FAIL;
}

HRESULT MultiSourceFrameReader::update()
{
	if (multiSourceFrame) multiSourceFrame->Release();

	if (SUCCEEDED(this->multiSourceFrameReader->AcquireLatestFrame(&(this->multiSourceFrame)))) {

		if (SUCCEEDED(this->colorFramePainter->update(this->multiSourceFrame)) &&
			SUCCEEDED(this->depthFramePainter->update(this->multiSourceFrame)) &&
			SUCCEEDED(this->bodyIndexFramePainter->update(this->multiSourceFrame)) &&
			SUCCEEDED(this->bodyFramePainter->update(this->multiSourceFrame)))

			return S_OK;
	}
	return E_FAIL;

}

HRESULT MultiSourceFrameReader::acquireLatestFrames()
{
	while (1) {
		//if all frames are acquired sycronizely
		if(SUCCEEDED(this->update()))
			return S_OK;
	}
	//TODO:
	//how about out of time

}

Mat MultiSourceFrameReader::getDepthFrame()
{
	return this->bodyFramePainter->getFrame();
}

UINT16 * MultiSourceFrameReader::getDepthFrameArray()
{
	return this->depthFramePainter->getFrameArray();
}

UINT MultiSourceFrameReader::getDepthFrameArraySize()
{
	return this->depthFramePainter->getFrameArraySize();
}

RGBQUAD * MultiSourceFrameReader::getDepthFrameArrayRGBX()
{
	return this->depthFramePainter->getFrameArrayRGBX();
}

UINT MultiSourceFrameReader::getDepthFrameArrayRGBXSize()
{
	return 0;
}

Mat MultiSourceFrameReader::getColorFrame()
{
	return this->colorFramePainter->getFrame();
}

UINT8 * MultiSourceFrameReader::getColorFrameArray()
{
	return nullptr;
}

UINT MultiSourceFrameReader::getColorFrameArraySize()
{
	return 0;
}

Mat MultiSourceFrameReader::getBodyFrame()
{
	return this->bodyFramePainter->getFrame();
}

Mat MultiSourceFrameReader::getBodyIndexFrame()
{
	return this->bodyIndexFramePainter->getFrame();
}

BYTE * MultiSourceFrameReader::getBodyIndexFrameArray()
{
	return nullptr;
}

UINT MultiSourceFrameReader::getBodyIndexFrameArraySize()
{
	return 0;
}

RGBQUAD * MultiSourceFrameReader::getBodyIndexFrameArrayRGBX()
{
	return nullptr;
}

UINT MultiSourceFrameReader::getBodyIndexFrameArrayRGBXSize()
{
	return 0;
}

Mat MultiSourceFrameReader::getSkeletonFrame()
{
	return  this->bodyFramePainter->getFrame();
}


bool MultiSourceFrameReader::getHealth()
{
	return this->isHealthy;
}

