#pragma once

#include <chrono>
#include <string>

#include <k4arecord/playback.hpp>

#include "Stream.h"
#include "Types.h"

namespace ofxAzureKinect
{
	struct PlaybackSettings
	{
		bool updateColor = false;
		bool updateIr = false;

		bool updateWorld = false;	// Used for point cloud or for body tracking
		bool updatePointCloud = false; // If true,it automatically sets UpdateWorld
		bool updatePointCloudTexCoords = false; // Can't be true without updatePointCloud
		bool updateVbo = false; // If true,it automatically sets updateWorld, updatePointCloud and updatePointCloudTexCoords

		bool autoloop = true;
	};

	class Playback 
		: public Stream
	{
	public:
		Playback();
		~Playback();

		bool open(std::string filepath);
		bool close();

		bool startPlayback(PlaybackSettings playbackSettings = PlaybackSettings());
		bool stopPlayback();

		bool seekPct(float pct);
		bool seekSecs(float seconds);
		bool seekUsecs(long long usecs);

		std::string readTag(const std::string& name);

		DepthMode getDepthMode() const override;
		ImageFormat getColorFormat() const override;
		ColorResolution getColorResolution() const override;
		FramesPerSecond getCameraFps() const override;

		WiredSyncMode getWiredSyncMode() const override;
		uint32_t getDepthDelayUsec() const override;
		uint32_t getSubordinateDelayUsec() const override;

		float getDurationSecs() const;
		long long getDurationUsecs() const;

	protected:
		bool updateCapture() override;

	private:
		bool bUpdateDepth;
		bool bLoops;

		float lastFrameSecs;
		std::chrono::microseconds duration;

		k4a_record_configuration_t config;
		k4a::playback playback;
	};
}
