#pragma once

#include <k4a/k4atypes.h>
#include "ofVectorMath.h"

#include "ofxAzureKinectConfig.h"
#ifdef USE_BODYTRACKER
#include <k4abttypes.h>
#endif

inline const glm::vec2 & toGlm(const k4a_float2_t & v) 
{
	return *reinterpret_cast<const glm::vec2*>(&v);
}

inline const glm::vec3 & toGlm(const k4a_float3_t & v)
{
	return *reinterpret_cast<const glm::vec3*>(&v);
}

#ifdef USE_BODYTRACKER
inline const glm::quat toGlm(const k4a_quaternion_t & q)
{
	return glm::quat(q.v[0], q.v[1], q.v[2], q.v[3]);
}
#endif

namespace ofxAzureKinect
{
	typedef k4a_depth_mode_t DepthMode;
	typedef k4a_color_resolution_t ColorResolution;
	typedef k4a_image_format_t ImageFormat;
	typedef k4a_fps_t FramesPerSecond;
	typedef k4a_wired_sync_mode_t WiredSyncMode;

#ifdef USE_BODYTRACKER
	typedef k4abt_sensor_orientation_t SensorOrientation;
	typedef k4abt_tracker_processing_mode_t ProcessingMode;
#endif
}
