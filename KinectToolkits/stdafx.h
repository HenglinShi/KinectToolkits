// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include <kinect.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/contrib/contrib.hpp>
#include "opencv2/video/video.hpp"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>

#include "KinectInstance.h"
#include "MultiSourceFrameReader.h"
#include "FramePainter.h"
#include "ColorFramePainter.h"
#include "DepthFramePainter.h"
#include "BodyIndexFramePainter.h"
#include "BodyFramePainter.h"

#include "Skeleton.h"
#include "SkeletalJoint.h"
#include "Body.h"


#define KINECT_STATE_READY 1
#define KINECT_STATE_PENDING 0
#define HEALTHY true
#define UNHEALTHY false
#define CHANNEL 4
// TODO: reference additional headers your program requires here
using namespace std;