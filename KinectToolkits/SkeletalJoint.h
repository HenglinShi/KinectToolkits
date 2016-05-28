#pragma once
class SkeletalJoint
{
private:
	JointOrientation mJointOrientation;
	Joint mJoint;
	CameraSpacePoint mJointCameraSpacePoint;
	DepthSpacePoint mJointDepthSpacePoint;
	ColorSpacePoint mJointColorSpacePoint;
	void setJointCameraSpacePoint(CameraSpacePoint mJointCameraSpacePoint);
	void setJointCameraSpacePoint(Joint mJoint);
	void setJointCameraSpacePoint(float x, float y, float z);

	void setJointDepthSpacePoint(DepthSpacePoint mJointDepthSpacePoint);
	void setJointDepthSpacePoint(Joint mJoint, ICoordinateMapper *mCoordinateMapper);
	void setJointDepthSpacePoint(float x, float y);

	void setJointColorSpacePoint(ColorSpacePoint mJointColorSpacePoint);
	void setJointColorSpacePoint(Joint mJoint, ICoordinateMapper *mCoordinateMapper);
	void setJointColorSpacePoint(float x, float y);

	void setJoint(Joint mJoint);
	void setJoint(float x, float y, float z);


public:
	SkeletalJoint();
	SkeletalJoint(Joint mJoint, JointOrientation mJointOrientation);
	~SkeletalJoint();
};

