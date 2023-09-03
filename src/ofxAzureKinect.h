#pragma once
#include "ofxAzureKinectConfig.h"

#include "ofxAzureKinect/BodyTracker.h"
#include "ofxAzureKinect/Device.h"
#include "ofxAzureKinect/Playback.h"
#include "ofxAzureKinect/Recorder.h"
#include "ofxAzureKinect/Types.h"


// Link body tracker lib
#ifdef USE_BODYTRACKER
#pragma comment(lib, "k4abt.lib")
#endif