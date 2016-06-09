#pragma once
#include "stdafx.h"
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

	

	void initializingSpineMid();
	void initializingSpineBase();
	void initializingNeck();
	void initializingHead();
	void initializingShoulderLeft();
	void initializingElbowLeft();
	void initializingWristLeft();
	void initializingHandLeft();
	void initializingShoulderRight();
	void initializingElbowRight();
	void initializingWristRight();
	void initializingHandRight();
	void initializingHipLeft();
	void initializingKneeLeft();
	void initializingAnkleLeft();
	void initializingFootLeft();
	void initializingHipRight();
	void initializingKneeRight();
	void initializingAnkleRight();
	void initializingFootRight();
	void initializingSpineShoulder();
	void initializingHandTipLeft();
	void initializingThumbLeft();
	void initializingHandTipRight();
	void initializingThumbRight();


	void updateSkeletalJoints();

	void updateSpineBase();
	void updateSpineMid();
	void updateNeck();
	void updateHead();
	void updateShoulderLeft();
	void updateElbowLeft();
	void updateWristLeft();
	void updateHandLeft();
	void updateShoulderRight();
	void updateElbowRight();
	void updateWristRight();
	void updateHandRight();
	void updateHipLeft();
	void updateKneeLeft();
	void updateAnkleLeft();
	void updateFootLeft();
	void updateHipRight();
	void updateKneeRight();
	void updateAnkleRight();
	void updateFootRight();
	void updateSpineShoulder();
	void updateHandTipLeft();
	void updateThumbLeft();
	void updateHandTipRight();
	void updateThumbRight();

	HRESULT initializing();

public:
	Skeleton();
	~Skeleton();

	HRESULT update(IBody * body);





};

