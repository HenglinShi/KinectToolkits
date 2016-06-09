#pragma once
#include "SkeletalJoint.h"
class Skeleton
{
private:
	Joint mJoints[JointType_Count];
	JointOrientation mJointOrientations[JointType_Count];
	int jointCount;
	SkeletalJoint * spineMid = nullptr;
	SkeletalJoint * neck = nullptr;
	SkeletalJoint * head = nullptr;
	SkeletalJoint * shoulderLeft = nullptr;
	SkeletalJoint * elbowLeft = nullptr;
	SkeletalJoint * wristLeft = nullptr;
	SkeletalJoint * handLeft = nullptr;
	SkeletalJoint * shoulderRight = nullptr;
	SkeletalJoint * elbowRight = nullptr;
	SkeletalJoint * wristRight = nullptr;
	SkeletalJoint * handRight = nullptr;
	SkeletalJoint * hipLeft = nullptr;
	SkeletalJoint * kneeLeft = nullptr;
	SkeletalJoint * ankleLeft = nullptr;
	SkeletalJoint * footLeft = nullptr;
	SkeletalJoint * hipRight = nullptr;
	SkeletalJoint * kneeRight = nullptr;
	SkeletalJoint * ankleRight = nullptr;
	SkeletalJoint * footRight = nullptr;
	SkeletalJoint * spineShoulder = nullptr;
	SkeletalJoint * handTipLeft = nullptr;
	SkeletalJoint * thumbLeft = nullptr;
	SkeletalJoint * handTipRight = nullptr;
	SkeletalJoint * thumbRight = nullptr;

	void setJoints(Joint mJoints[JointType_Count]);
	void setJointOrientation(JointOrientation mJointOrientation[JointType_Count]);

	void setSpineMid();
	void setNeck();
	void setHead();
	void setShoulderLeft();
	void setElbowLeft();
	void setWristLeft();
	void setHandLeft();
	void setShoulderRight();
	void setElbowRight();
	void setWristRight();
	void setHandRight();
	void setHipLeft();
	void setKneeLeft();
	void setAnkleLeft();
	void setFootLeft();
	void setHipRight();
	void setKneeRight();
	void setAnkleRight();
	void setFootRight();
	void setSpineShoulder();
	void setHandTipLeft();
	void setThumbLeft();
	void setHandTipRight();
	void setThumbRight();
	void initialization(Joint mjoints[JointType_Count], JointOrientation mJointOrientations[JointType_Count]);
	bool initialization(IBody *body);

public:
	Skeleton();
	Skeleton(IBody * body);
	Skeleton(Joint mjoints[JointType_Count], JointOrientation mJointOrientations[JointType_Count]);
	~Skeleton();







};

