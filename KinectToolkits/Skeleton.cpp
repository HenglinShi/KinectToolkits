#include "stdafx.h"
#include "Skeleton.h"


Skeleton::Skeleton()
{
}

Skeleton::Skeleton(IBody * body)
{

}

Skeleton::Skeleton(Joint mjoints[JointType_Count], JointOrientation mJointOrientations[JointType_Count])
{
	this->initialization(mjoints, mJointOrientations);
}


Skeleton::~Skeleton()
{

}




void Skeleton::initialization(Joint mjoints[JointType_Count], JointOrientation mJointOrientations[JointType_Count])
{
	this->setJoints(mjoints);
	this->setJointOrientation(mJointOrientations);
	setSpineMid();
	setNeck();
	setHead();
	setShoulderLeft();
	setElbowLeft();
	setWristLeft();
	setHandLeft();
	setShoulderRight();
	setElbowRight();
	setWristRight();
	setHandRight();
	setHipLeft();
	setKneeLeft();
	setAnkleLeft();
	setFootLeft();
	setHipRight();
	setKneeRight();
	setAnkleRight();
	setFootRight();
	setSpineShoulder();
	setHandTipLeft();
	setThumbLeft();
	setHandTipRight();
	setThumbRight();
}

bool Skeleton::initialization(IBody * body)
{
	if (SUCCEEDED(body->GetJoints(JointType_Count, this->mJoints)) && 
		SUCCEEDED(body->GetJointOrientations(JointType_Count, this->mJointOrientations))) {
		
		this->setSpineMid();
		this->setNeck();
		this->setHead();
		this->setShoulderLeft();
		this->setElbowLeft();
		this->setWristLeft();
		this->setHandLeft();
		this->setShoulderRight();
		this->setElbowRight();
		this->setWristRight();
		this->setHandRight();
		this->setHipLeft();
		this->setKneeLeft();
		this->setAnkleLeft();
		this->setFootLeft();
		this->setHipRight();
		this->setKneeRight();
		this->setAnkleRight();
		this->setFootRight();
		this->setSpineShoulder();
		this->setHandTipLeft();
		this->setThumbLeft();
		this->setHandTipRight();
		this->setThumbRight();
	}
}


void Skeleton::setJoints(Joint mJoints[JointType_Count])
{
	this->mJoints[JointType_Count] = mJoints[JointType_Count];
}

void Skeleton::setJointOrientation(JointOrientation mJointOrientations[JointType_Count])
{
	this->mJointOrientations[JointType_Count] = mJointOrientations[JointType_Count];
}




void Skeleton::setShoulderRight()
{
	this->shoulderRight = new SkeletalJoint(this->mJoints[JointType_ShoulderRight], this->mJointOrientations[JointType_ShoulderRight]);
}

void Skeleton::setElbowRight()
{
	this->elbowRight = new SkeletalJoint(this->mJoints[JointType_ElbowRight], this->mJointOrientations[JointType_ElbowRight]);
}

void Skeleton::setWristRight()
{
	this->wristRight = new SkeletalJoint(this->mJoints[JointType_WristRight], this->mJointOrientations[JointType_WristRight]);
}

void Skeleton::setHandRight()
{
	this->handRight = new SkeletalJoint(this->mJoints[JointType_HandRight], this->mJointOrientations[JointType_HandRight]);
}

void Skeleton::setHipLeft()
{
	this->hipLeft = new SkeletalJoint(this->mJoints[JointType_HipLeft], this->mJointOrientations[JointType_HipLeft]);
}

void Skeleton::setKneeLeft()
{
	this->kneeLeft = new SkeletalJoint(this->mJoints[JointType_KneeLeft], this->mJointOrientations[JointType_KneeLeft]);
}

void Skeleton::setAnkleLeft()
{
	this->ankleLeft = new SkeletalJoint(this->mJoints[JointType_AnkleLeft], this->mJointOrientations[JointType_AnkleLeft]);
}

void Skeleton::setFootLeft()
{
	this->footLeft = new SkeletalJoint(this->mJoints[JointType_FootLeft], this->mJointOrientations[JointType_FootLeft]);
}

void Skeleton::setHipRight()
{
	this->hipRight = new SkeletalJoint(this->mJoints[JointType_HipRight], this->mJointOrientations[JointType_HipRight]);
}

void Skeleton::setKneeRight()
{
	this->kneeRight = new SkeletalJoint(this->mJoints[JointType_KneeRight], this->mJointOrientations[JointType_KneeRight]);
}

void Skeleton::setAnkleRight()
{
	this->ankleRight = new SkeletalJoint(this->mJoints[JointType_AnkleRight], this->mJointOrientations[JointType_AnkleRight]);
}

void Skeleton::setFootRight()
{
	this->footRight = new SkeletalJoint(this->mJoints[JointType_FootRight], this->mJointOrientations[JointType_FootRight]);
}

void Skeleton::setSpineShoulder()
{
	this->spineShoulder = new SkeletalJoint(this->mJoints[JointType_SpineShoulder], this->mJointOrientations[JointType_SpineShoulder]);
}

void Skeleton::setHandTipLeft()
{
	this->handTipLeft = new SkeletalJoint(this->mJoints[JointType_HandTipLeft], this->mJointOrientations[JointType_HandTipLeft]);
}

void Skeleton::setThumbLeft()
{
	this->thumbLeft = new SkeletalJoint(this->mJoints[JointType_ThumbLeft], this->mJointOrientations[JointType_ThumbLeft]);
}

void Skeleton::setHandTipRight()
{
	this->handTipRight = new SkeletalJoint(this->mJoints[JointType_HandTipRight], this->mJointOrientations[JointType_HandTipRight]);
}

void Skeleton::setThumbRight()
{
	this->thumbRight = new SkeletalJoint(this->mJoints[JointType_ThumbRight], this->mJointOrientations[JointType_ThumbRight]);
}


void Skeleton::setSpineMid()
{
	this->spineMid = new SkeletalJoint(this->mJoints[JointType_SpineBase], this->mJointOrientations[JointType_SpineMid]);
}

void Skeleton::setNeck()
{
	this->neck = new SkeletalJoint(this->mJoints[JointType_Neck], this->mJointOrientations[JointType_Neck]);
}

void Skeleton::setHead()
{
	this->head = new SkeletalJoint(this->mJoints[JointType_Head], this->mJointOrientations[JointType_Head]);
}

void Skeleton::setShoulderLeft()
{
	this->shoulderLeft = new SkeletalJoint(this->mJoints[JointType_ShoulderLeft], this->mJointOrientations[JointType_ShoulderLeft]);
}

void Skeleton::setElbowLeft()
{
	this->elbowLeft = new SkeletalJoint(this->mJoints[JointType_ElbowLeft], this->mJointOrientations[JointType_ElbowLeft]);
}

void Skeleton::setWristLeft()
{
	this->wristLeft = new SkeletalJoint(this->mJoints[JointType_WristLeft], this->mJointOrientations[JointType_WristLeft]);
}

void Skeleton::setHandLeft()
{
	this->handLeft = new SkeletalJoint(this->mJoints[JointType_HandLeft], this->mJointOrientations[JointType_HandLeft]);
}


