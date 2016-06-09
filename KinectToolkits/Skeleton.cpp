#include "stdafx.h"
#include "Skeleton.h"


Skeleton::Skeleton()
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
	this->shoulderRight = new SkeletalJoint(mJoints[JointType_ShoulderRight], mJointOrientations[JointType_ShoulderRight]);
}

void Skeleton::setElbowRight()
{
	this->elbowRight = new SkeletalJoint(mJoints[JointType_ElbowRight], mJointOrientations[JointType_ElbowRight]);
}

void Skeleton::setWristRight()
{
	this->wristRight = new SkeletalJoint(mJoints[JointType_WristRight], mJointOrientations[JointType_WristRight]);
}

void Skeleton::setHandRight()
{
	this->handRight = new SkeletalJoint(mJoints[JointType_HandRight], mJointOrientations[JointType_HandRight]);
}

void Skeleton::setHipLeft()
{
	this->hipLeft = new SkeletalJoint(mJoints[JointType_HipLeft], mJointOrientations[JointType_HipLeft]);
}

void Skeleton::setKneeLeft()
{
	this->kneeLeft = new SkeletalJoint(mJoints[JointType_KneeLeft], mJointOrientations[JointType_KneeLeft]);
}

void Skeleton::setAnkleLeft()
{
	this->ankleLeft = new SkeletalJoint(mJoints[JointType_AnkleLeft], mJointOrientations[JointType_AnkleLeft]);
}

void Skeleton::setFootLeft()
{
	this->footLeft = new SkeletalJoint(mJoints[JointType_FootLeft], mJointOrientations[JointType_FootLeft]);
}

void Skeleton::setHipRight()
{
	this->hipRight = new SkeletalJoint(mJoints[JointType_HipRight], mJointOrientations[JointType_HipRight]);
}

void Skeleton::setKneeRight()
{
	this->kneeRight = new SkeletalJoint(mJoints[JointType_KneeRight], mJointOrientations[JointType_KneeRight]);
}

void Skeleton::setAnkleRight()
{
	this->ankleRight = new SkeletalJoint(mJoints[JointType_AnkleRight], mJointOrientations[JointType_AnkleRight]);
}

void Skeleton::setFootRight()
{
	this->footRight = new SkeletalJoint(mJoints[JointType_FootRight], mJointOrientations[JointType_FootRight]);
}

void Skeleton::setSpineShoulder()
{
	this->spineShoulder = new SkeletalJoint(mJoints[JointType_SpineShoulder], mJointOrientations[JointType_SpineShoulder]);
}

void Skeleton::setHandTipLeft()
{
	this->handTipLeft = new SkeletalJoint(mJoints[JointType_HandTipLeft], mJointOrientations[JointType_HandTipLeft]);
}

void Skeleton::setThumbLeft()
{
	this->thumbLeft = new SkeletalJoint(mJoints[JointType_ThumbLeft], mJointOrientations[JointType_ThumbLeft]);
}

void Skeleton::setHandTipRight()
{
	this->handTipRight = new SkeletalJoint(mJoints[JointType_HandTipRight], mJointOrientations[JointType_HandTipRight]);
}

void Skeleton::setThumbRight()
{
	this->thumbRight = new SkeletalJoint(mJoints[JointType_ThumbRight], mJointOrientations[JointType_ThumbRight]);
}


void Skeleton::setSpineMid()
{
	this->spineMid = new SkeletalJoint(mJoints[JointType_SpineBase], mJointOrientations[JointType_SpineMid]);
}

void Skeleton::setNeck()
{
	this->neck = new SkeletalJoint(mJoints[JointType_Neck], mJointOrientations[JointType_Neck]);
}

void Skeleton::setHead()
{
	this->head = new SkeletalJoint(mJoints[JointType_Head], mJointOrientations[JointType_Head]);
}

void Skeleton::setShoulderLeft()
{
	this->shoulderLeft = new SkeletalJoint(mJoints[JointType_ShoulderLeft], mJointOrientations[JointType_ShoulderLeft]);
}

void Skeleton::setElbowLeft()
{
	this->elbowLeft = new SkeletalJoint(mJoints[JointType_ElbowLeft], mJointOrientations[JointType_ElbowLeft]);
}

void Skeleton::setWristLeft()
{
	this->wristLeft = new SkeletalJoint(mJoints[JointType_WristLeft], mJointOrientations[JointType_WristLeft]);
}

void Skeleton::setHandLeft()
{
	this->handLeft = new SkeletalJoint(mJoints[JointType_HandLeft], mJointOrientations[JointType_HandLeft]);
}


