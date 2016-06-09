#include "stdafx.h"



Skeleton::Skeleton()
{
	for (int i = 0; i < JointType_Count; i++) {
		mJoints[i].Position.X = 0.0;
		mJoints[i].Position.Y = 0.0;
		mJoints[i].Position.Z = 0.0;

		mJointOrientations[i].Orientation.w = 0.0;
		mJointOrientations[i].Orientation.x = 0.0;
		mJointOrientations[i].Orientation.y = 0.0;
		mJointOrientations[i].Orientation.z = 0.0;
	}

	this->initializing();
}

Skeleton::~Skeleton()
{

}

HRESULT Skeleton::update(IBody * body)
{
	if (SUCCEEDED(body->GetJoints(JointType_Count, this->mJoints) &&
		SUCCEEDED(body->GetJointOrientations(JointType_Count, this->mJointOrientations)))) {
		return S_OK;
	}
	return E_NOTIMPL;
}


HRESULT Skeleton::initializing()
{
	this->initializingSpineMid();
	this->initializingNeck();
	this->initializingHead();
	this->initializingShoulderLeft();
	this->initializingElbowLeft();
	this->initializingWristLeft();
	this->initializingHandLeft();
	this->initializingShoulderRight();
	this->initializingElbowRight();
	this->initializingWristRight();
	this->initializingHandRight();
	this->initializingHipLeft();
	this->initializingKneeLeft();
	this->initializingAnkleLeft();
	this->initializingFootLeft();
	this->initializingHipRight();
	this->initializingKneeRight();
	this->initializingAnkleRight();
	this->initializingFootRight();
	this->initializingSpineShoulder();
	this->initializingHandTipLeft();
	this->initializingThumbLeft();
	this->initializingHandTipRight();
	this->initializingThumbRight();
	return S_OK;
}

void Skeleton::setJoints(Joint mJoints[JointType_Count])
{
	this->mJoints[JointType_Count] = mJoints[JointType_Count];
}
void Skeleton::setJointOrientation(JointOrientation mJointOrientations[JointType_Count])
{
	this->mJointOrientations[JointType_Count] = mJointOrientations[JointType_Count];
}









void Skeleton::updateSkeletalJoints()
{
	this->updateSpineMid();
	this->updateNeck();
	this->updateHead();
	this->updateShoulderLeft();
	this->updateElbowLeft();
	this->updateWristLeft();
	this->updateHandLeft();
	this->updateShoulderRight();
	this->updateElbowRight();
	this->updateWristRight();
	this->updateHandRight();
	this->updateHipLeft();
	this->updateKneeLeft();
	this->updateAnkleLeft();
	this->updateFootLeft();
	this->updateHipRight();
	this->updateKneeRight();
	this->updateAnkleRight();
	this->updateFootRight();
	this->updateSpineShoulder();
	this->updateHandTipLeft();
	this->updateThumbLeft();
	this->updateHandTipRight();
	this->updateThumbRight();
	
}

































void Skeleton::updateSpineBase()
{
	this->spineMid->update(this->mJoints[JointType_SpineBase], this->mJointOrientations[JointType_SpineMid]);
}
void Skeleton::updateSpineMid()
{
	this->spineMid->update(this->mJoints[JointType_SpineMid], this->mJointOrientations[JointType_SpineMid]);
}
void Skeleton::updateNeck()
{
	this->neck->update(this->mJoints[JointType_Neck], this->mJointOrientations[JointType_Neck]);
}
void Skeleton::updateHead()
{
	this->head->update(this->mJoints[JointType_Head], this->mJointOrientations[JointType_Head]);
}
void Skeleton::updateShoulderLeft()
{
	this->shoulderLeft->update(this->mJoints[JointType_ShoulderLeft], this->mJointOrientations[JointType_ShoulderLeft]);
}
void Skeleton::updateElbowLeft()
{
	this->elbowLeft->update(this->mJoints[JointType_ElbowLeft], this->mJointOrientations[JointType_ElbowLeft]);
}
void Skeleton::updateWristLeft()
{
	this->wristLeft->update(this->mJoints[JointType_WristLeft], this->mJointOrientations[JointType_WristLeft]);
}
void Skeleton::updateHandLeft()
{
	this->handLeft->update(this->mJoints[JointType_HandLeft], this->mJointOrientations[JointType_HandLeft]);
}
void Skeleton::updateShoulderRight()
{
	this->shoulderRight->update(this->mJoints[JointType_ShoulderRight], this->mJointOrientations[JointType_ShoulderRight]);
}
void Skeleton::updateElbowRight()
{
	this->elbowRight->update(this->mJoints[JointType_ElbowRight], this->mJointOrientations[JointType_ElbowRight]);
}
void Skeleton::updateWristRight()
{
	this->wristRight->update(this->mJoints[JointType_WristRight], this->mJointOrientations[JointType_WristRight]);
}
void Skeleton::updateHandRight()
{
	this->handRight->update(this->mJoints[JointType_HandRight], this->mJointOrientations[JointType_HandRight]);
}
void Skeleton::updateHipLeft()
{
	this->hipLeft->update(this->mJoints[JointType_HipLeft], this->mJointOrientations[JointType_HipLeft]);
}
void Skeleton::updateKneeLeft()
{
	this->kneeLeft->update(this->mJoints[JointType_KneeLeft], this->mJointOrientations[JointType_KneeLeft]);
}
void Skeleton::updateAnkleLeft()
{
	this->ankleLeft->update(this->mJoints[JointType_AnkleLeft], this->mJointOrientations[JointType_AnkleLeft]);
}
void Skeleton::updateFootLeft()
{
	this->footLeft->update(this->mJoints[JointType_FootLeft], this->mJointOrientations[JointType_FootLeft]);
}
void Skeleton::updateHipRight()
{
	this->hipRight->update(this->mJoints[JointType_HipRight], this->mJointOrientations[JointType_HipRight]);
}
void Skeleton::updateKneeRight()
{
	this->kneeRight->update(this->mJoints[JointType_KneeRight], this->mJointOrientations[JointType_KneeRight]);
}
void Skeleton::updateAnkleRight()
{
	this->ankleRight->update(this->mJoints[JointType_AnkleRight], this->mJointOrientations[JointType_AnkleRight]);
}
void Skeleton::updateFootRight()
{
	this->footRight->update(this->mJoints[JointType_FootRight], this->mJointOrientations[JointType_FootRight]);
}
void Skeleton::updateSpineShoulder()
{
	this->spineShoulder->update(this->mJoints[JointType_SpineShoulder], this->mJointOrientations[JointType_SpineShoulder]);
}
void Skeleton::updateHandTipLeft()
{
	this->handTipLeft->update(this->mJoints[JointType_HandTipLeft], this->mJointOrientations[JointType_HandTipLeft]);
}
void Skeleton::updateThumbLeft()
{
	this->thumbLeft->update(this->mJoints[JointType_ThumbLeft], this->mJointOrientations[JointType_ThumbLeft]);
}
void Skeleton::updateHandTipRight()
{
	this->handTipRight->update(this->mJoints[JointType_HandTipRight], this->mJointOrientations[JointType_HandTipRight]);
}
void Skeleton::updateThumbRight()
{
	this->thumbRight->update(this->mJoints[JointType_ThumbRight], this->mJointOrientations[JointType_ThumbRight]);
}


void Skeleton::initializingSpineMid()
{
	this->spineMid = new SkeletalJoint(this->mJoints[JointType_SpineMid], this->mJointOrientations[JointType_SpineMid]);
}
void Skeleton::initializingSpineBase()
{
	this->spineShoulder = new SkeletalJoint(this->mJoints[JointType_SpineBase], this->mJointOrientations[JointType_SpineBase]);
}
void Skeleton::initializingNeck()
{
	this->neck = new SkeletalJoint(this->mJoints[JointType_Neck], this->mJointOrientations[JointType_Neck]);
}
void Skeleton::initializingHead()
{
	this->head = new SkeletalJoint(this->mJoints[JointType_Head], this->mJointOrientations[JointType_Head]);
}
void Skeleton::initializingShoulderLeft()
{
	this->shoulderLeft = new SkeletalJoint(this->mJoints[JointType_ShoulderLeft], this->mJointOrientations[JointType_ShoulderLeft]);
}
void Skeleton::initializingElbowLeft()
{
	this->elbowLeft = new SkeletalJoint(this->mJoints[JointType_ElbowLeft], this->mJointOrientations[JointType_ElbowLeft]);
}
void Skeleton::initializingWristLeft()
{
	this->wristLeft = new SkeletalJoint(this->mJoints[JointType_WristLeft], this->mJointOrientations[JointType_WristLeft]);
}
void Skeleton::initializingHandLeft()
{
	this->handLeft = new SkeletalJoint(this->mJoints[JointType_HandLeft], this->mJointOrientations[JointType_HandLeft]);
}
void Skeleton::initializingShoulderRight()
{
	this->shoulderRight = new SkeletalJoint(this->mJoints[JointType_ShoulderRight], this->mJointOrientations[JointType_ShoulderRight]);
}
void Skeleton::initializingElbowRight()
{
	this->elbowRight = new SkeletalJoint(this->mJoints[JointType_ElbowRight], this->mJointOrientations[JointType_ElbowRight]);
}
void Skeleton::initializingWristRight()
{
	this->wristRight = new SkeletalJoint(this->mJoints[JointType_WristRight], this->mJointOrientations[JointType_WristRight]);
}
void Skeleton::initializingHandRight()
{
	this->handRight = new SkeletalJoint(this->mJoints[JointType_HandRight], this->mJointOrientations[JointType_HandRight]);
}
void Skeleton::initializingHipLeft()
{
	this->hipLeft = new SkeletalJoint(this->mJoints[JointType_HipLeft], this->mJointOrientations[JointType_HipLeft]);
}
void Skeleton::initializingKneeLeft()
{
	this->kneeLeft = new SkeletalJoint(this->mJoints[JointType_KneeLeft], this->mJointOrientations[JointType_KneeLeft]);
}
void Skeleton::initializingAnkleLeft()
{
	this->ankleLeft = new SkeletalJoint(this->mJoints[JointType_AnkleLeft], this->mJointOrientations[JointType_AnkleLeft]);
}
void Skeleton::initializingFootLeft()
{
	this->footLeft = new SkeletalJoint(this->mJoints[JointType_FootLeft], this->mJointOrientations[JointType_FootLeft]);
}
void Skeleton::initializingHipRight()
{
	this->hipRight = new SkeletalJoint(this->mJoints[JointType_HipRight], this->mJointOrientations[JointType_HipRight]);
}
void Skeleton::initializingKneeRight()
{
	this->kneeRight = new SkeletalJoint(this->mJoints[JointType_KneeRight], this->mJointOrientations[JointType_KneeRight]);
}
void Skeleton::initializingAnkleRight()
{
	this->ankleRight = new SkeletalJoint(this->mJoints[JointType_AnkleRight], this->mJointOrientations[JointType_AnkleRight]);
}
void Skeleton::initializingFootRight()
{
	this->footRight = new SkeletalJoint(this->mJoints[JointType_FootRight], this->mJointOrientations[JointType_FootRight]);
}
void Skeleton::initializingSpineShoulder()
{
	this->spineShoulder = new SkeletalJoint(this->mJoints[JointType_SpineShoulder], this->mJointOrientations[JointType_SpineShoulder]);
}
void Skeleton::initializingHandTipLeft()
{
	this->handTipLeft = new SkeletalJoint(this->mJoints[JointType_HandTipLeft], this->mJointOrientations[JointType_HandTipLeft]);
}
void Skeleton::initializingThumbLeft()
{
	this->thumbLeft = new SkeletalJoint(this->mJoints[JointType_ThumbLeft], this->mJointOrientations[JointType_ThumbLeft]);
}
void Skeleton::initializingHandTipRight()
{
	this->handTipRight = new SkeletalJoint(this->mJoints[JointType_HandTipRight], this->mJointOrientations[JointType_HandTipRight]);
}
void Skeleton::initializingThumbRight()
{
	this->thumbRight = new SkeletalJoint(this->mJoints[JointType_ThumbRight], this->mJointOrientations[JointType_ThumbRight]);
}



