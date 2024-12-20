#pragma once

#include <string>

#include <k4a/k4a.hpp>
#include "ofPixels.h"
#include "ofTexture.h"

#include "Recorder.h"
#include "Stream.h"
#include "Types.h"

namespace ofxAzureKinect
{
	struct DeviceSettings
	{
		DepthMode depthMode = K4A_DEPTH_MODE_NFOV_UNBINNED;
		ColorResolution colorResolution = K4A_COLOR_RESOLUTION_720P;
		ImageFormat colorFormat = K4A_IMAGE_FORMAT_COLOR_BGRA32;
		FramesPerSecond cameraFps = K4A_FRAMES_PER_SECOND_30;

		WiredSyncMode wiredSyncMode = K4A_WIRED_SYNC_MODE_STANDALONE;
		uint32_t depthDelayUsec = 0;
		uint32_t subordinateDelayUsec = 0;

		bool updateColor = false;
		bool updateIr = false;

		bool updateWorld = false;	// Used for point cloud or for body tracking
		bool updatePointCloud = false; // If true,it automatically sets UpdateWorld
		bool updatePointCloudTexCoords = false; // Can't be true without updatePointCloud
		bool updateVbo = false; // If true, it automatically sets updateWorld, updatePointCloud and updatePointCloudTexCoords

		bool syncImages = false;
	};

	class Device
		: public Stream
	{
	public:
		static int getInstalledCount();

		// Call it only when all devices are disconnected
		static std::vector<std::string> getSerials();

	public:
		Device();
		~Device();

		bool open(uint32_t idx = 0);
		bool open(const std::string& serialNumber);
		bool close();

		bool startCameras(DeviceSettings deviceSettings = DeviceSettings());
		bool stopCameras();

		// Is available after camera start
		void getDepthIntrinsics(float& fx, float& fy, float& cx, float& cy);

		bool startRecording(std::string filepath = "");
		bool stopRecording();

		bool isSyncInConnected() const;
		bool isSyncOutConnected() const;

		bool isRecording() const;

		DepthMode getDepthMode() const override;
		ImageFormat getColorFormat() const override;
		ColorResolution getColorResolution() const override;
		FramesPerSecond getCameraFps() const override;

		WiredSyncMode getWiredSyncMode() const override;
		uint32_t getDepthDelayUsec() const override;
		uint32_t getSubordinateDelayUsec() const override;

		bool getSyncImages() const;

		const Recorder& getRecorder() const;
		Recorder& Device::getRecorder();

	protected:
		bool updateCapture() override;

		void updatePixels() override;

	private:
		int index = -1;

		bool bRecording = false;

		k4a_device_configuration_t config;
		k4a::device device;

		Recorder recorder;

		// Intrinsics
		float fx_ = 0;
		float fy_ = 0;
		float cx_ = 0;
		float cy_ = 0;
		void clearDepthIntrinsics() {
			fx_ = 0;
			fy_ = 0;
			cx_ = 0;
			cy_ = 0;
		}

	};
}