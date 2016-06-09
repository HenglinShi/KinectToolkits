#include "stdafx.h"



Body::Body()
{
	initialization(mJoints, mJointOrientations);
}

Body::Body(Joint mJoints[JointType_Count], JointOrientation mJointOrientations[JointType_Count])
{

	//this->mSkeleton = new Skeleton(mJoints, mJointOrientations);

}

Body::~Body()
{
}


void Body::initialization(Joint mJoints[JointType_Count], JointOrientation mJointOrientations[JointType_Count])
{
	this->setJoints(mJoints);
	this->setJointOrientations(mJointOrientations);
}

void Body::setJoints(Joint mJoints[JointType_Count])
{
	this->mJoints[JointType_Count] = mJoints[JointType_Count];
}

void Body::setJointOrientations(JointOrientation mJointOrientations[JointType_Count])
{
	this->mJointOrientations[JointType_Count] = mJointOrientations[JointType_Count];
}
