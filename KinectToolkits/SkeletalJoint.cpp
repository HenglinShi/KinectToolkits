#include "stdafx.h"
#include "SkeletalJoint.h"


void SkeletalJoint::setJointCameraSpacePoint(CameraSpacePoint mJointCameraSpacePoint)
{
	this->mJointCameraSpacePoint = mJointCameraSpacePoint;
}

void SkeletalJoint::setJointCameraSpacePoint(Joint mJoint)
{
	this->mJointCameraSpacePoint = mJoint.Position;
}

void SkeletalJoint::setJointCameraSpacePoint(float x, float y, float z)
{
	this->mJointCameraSpacePoint.X = x;
	this->mJointCameraSpacePoint.Y = y;
	this->mJointCameraSpacePoint.Z = z;
}

void SkeletalJoint::setJointDepthSpacePoint(DepthSpacePoint mJointDepthSpacePoint)
{
	this->mJointDepthSpacePoint = mJointDepthSpacePoint;
}

void SkeletalJoint::setJointDepthSpacePoint(Joint mJoint, ICoordinateMapper *mCoordinateMapper)
{
	mCoordinateMapper->MapCameraPointToDepthSpace(mJoint.Position, &(this->mJointDepthSpacePoint));
}

void SkeletalJoint::setJointDepthSpacePoint(float x, float y)
{
	this->mJointDepthSpacePoint.X = x;
	this->mJointDepthSpacePoint.Y = y;
}

void SkeletalJoint::setJointColorSpacePoint(ColorSpacePoint mJointColorSpacePoint)
{
	this->mJointColorSpacePoint = mJointColorSpacePoint;
}

void SkeletalJoint::setJointColorSpacePoint(Joint mJoint, ICoordinateMapper * mCoordinateMapper)
{
	mCoordinateMapper->MapCameraPointToColorSpace(mJoint.Position, &(this->mJointColorSpacePoint));
}

void SkeletalJoint::setJointColorSpacePoint(float x, float y)
{
	this->mJointColorSpacePoint.X = x;
	this->mJointColorSpacePoint.Y = y;
}

void SkeletalJoint::setJoint(Joint mJoint)
{
	this->mJoint = mJoint;
}

void SkeletalJoint::setJoint(float x, float y, float z)
{
	this->mJoint.Position.X = x;
	this->mJoint.Position.Y = y;
	this->mJoint.Position.Z = z;
}

SkeletalJoint::SkeletalJoint()
{
}

SkeletalJoint::SkeletalJoint(Joint mJoint, JointOrientation mJointOrientation) {
	this->mJoint = mJoint;
	this->mJointOrientation = mJointOrientation;
}



SkeletalJoint::~SkeletalJoint()
{
}

