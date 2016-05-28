#pragma once
#include "Skeleton.h"
class Body
{

private:
	Joint mJoints[JointType_Count];
	JointOrientation mJointOrientations[JointType_Count];

	Skeleton * mSkeleton;
	void initialization(Joint mJoints[JointType_Count], JointOrientation mJointOrientations[JointType_Count]);
	void setJoints(Joint mJoints[JointType_Count]);
	void setJointOrientations(JointOrientation mJointOrientations[JointType_Count]);

public:
	Body();
	Body(Joint mJoints[JointType_Count], JointOrientation mJointOrientations[JointType_Count]);
	~Body();
};

