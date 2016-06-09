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

			this->bodyIndexFramePainter = new BodyIndexFramePainter();

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
	this->bodyFramePainter->getFrame();
}

Mat MultiSourceFrameReader::getColorFrame()
{
	this->colorFramePainter->getFrame();
}

Mat MultiSourceFrameReader::getBodyFrame()
{
	this->bodyFramePainter->getFrame();
}

Mat MultiSourceFrameReader::getBodyIndexFrame()
{
	this->bodyIndexFramePainter->getFrame();
}

Mat MultiSourceFrameReader::getSkeletonFrame()
{
	return this->bodyFramePainter->getFrame();
}


bool MultiSourceFrameReader::getHealth()
{
	return isHealthy;
}

