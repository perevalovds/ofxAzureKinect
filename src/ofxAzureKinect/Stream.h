#pragma once

#include "ofxAzureKinectConfig.h"

#include <mutex>
#include <string>

#include <k4a/k4a.hpp>

#include <turbojpeg.h>

#include "ofEvents.h"
#include "ofPixels.h"
#include "ofTexture.h"
#include "ofThread.h"
#include "ofVbo.h"
#include "ofVectorMath.h"

#include "BodyTracker.h"
#include "Types.h"

namespace ofxAzureKinect
{
	class Stream
		: public ofThread
	{
	public:
		Stream();
		virtual ~Stream();

#ifdef USE_BODYTRACKER
		virtual bool startBodyTracker(BodyTrackerSettings trackerSettings = BodyTrackerSettings());
		virtual bool stopBodyTracker();
#endif
		bool isOpen() const;
		bool isStreaming() const;
		bool isFrameNew() const;

		const std::string& getSerialNumber() const;

		virtual DepthMode getDepthMode() const = 0;
		virtual ImageFormat getColorFormat() const = 0;
		virtual ColorResolution getColorResolution() const = 0;
		virtual FramesPerSecond getCameraFps() const = 0;
		virtual uint32_t getFramerate() const;

		virtual WiredSyncMode getWiredSyncMode() const = 0;
		virtual uint32_t getDepthDelayUsec() const = 0;
		virtual uint32_t getSubordinateDelayUsec() const = 0;

		const std::vector<glm::vec3> getPointCloud() const;
		const std::vector<glm::vec2> getPointCloudTexCoords() const;
		bool GetPointCloudMirrored(std::vector<glm::vec3>& pc, int mirrorx = 0, int mirrory = 0, int mirrorz = 0) const;
		const ofVbo& getPointCloudVbo() const;

		const ofShortPixels& getDepthPix() const;
		const ofTexture& getDepthTex16();	// Updates texture once if it'sdirty
	
		// Use it to create 8bit texture to visualize depth image with given cropping distances
		bool getDepthPixels8(float min_dist, float max_dist, int& w, int& h, std::vector<unsigned char>& data);


		const ofPixels& getColorPix() const;
		const ofTexture& getColorTex() const;

		const ofShortPixels& getIrPix() const;
		const ofTexture& getIrTex() const;

		const ofFloatPixels& getDepthToWorldPix() const;
		const ofTexture& getDepthToWorldTex() const;

		const ofFloatPixels& getColorToWorldPix() const;
		const ofTexture& getColorToWorldTex() const;

		const ofShortPixels& getDepthInColorPix() const;
		const ofTexture& getDepthInColorTex() const;

		const ofPixels& getColorInDepthPix() const;
		const ofTexture& getColorInDepthTex() const;

#ifdef USE_BODYTRACKER
		const BodyTracker& getBodyTracker() const;
		BodyTracker& getBodyTracker();

		const ofPixels& getBodyIndexPix() const;
		const ofTexture& getBodyIndexTex() const;

		size_t getNumBodies() const;
		const std::vector<k4abt_skeleton_t>& getBodySkeletons() const;
		const std::vector<uint32_t>& getBodyIDs() const;
#endif

	protected:
		virtual bool setupDepthToWorldTable();
		virtual bool setupColorToWorldTable();
		virtual bool setupImageToWorldTable(k4a_calibration_type_t type, k4a::image& img);

		virtual bool startStreaming();
		virtual bool stopStreaming();

		virtual void threadedFunction() override;

		virtual void update(ofEventArgs& args);

		virtual bool updateCapture() = 0;
		virtual void releaseCapture();

		virtual void updatePixels();
		virtual void updateTextures();

		virtual bool updatePointsCache(k4a::image& frameImg, k4a::image& tableImg);

		virtual bool updateDepthInColorFrame(const k4a::image& depthImg, const k4a::image& colorImg);
		virtual bool updateColorInDepthFrame(const k4a::image& depthImg, const k4a::image& colorImg);

	protected:
		bool bOpen = false;
		bool bStreaming = false;
		bool bNewFrame = false;

		bool bUpdateColor = false;
		bool bUpdateIr = false;

		bool bUpdateWorld = false;	// Used for point cloud or for body tracking
		bool bUpdatePointCloud = false;	// If true, it automatically sets UpdateWorld
		bool bUpdatePointCloudTexCoords = false; // Can't be true without updatePointCloud
		bool bUpdateVbo = false;		// If true,it automatically sets UpdateWorld, bUpdatePointCloud and bUpdatePointCloudTexCoords

		std::condition_variable condition;
		uint64_t pixFrameNum = 0;
		uint64_t texFrameNum = 0;

		std::string serialNumber;

		k4a::calibration calibration;
		k4a::transformation transformation;
		k4a::capture capture;

		tjhandle jpegDecompressor;

#ifdef USE_BODYTRACKER
		BodyTracker bodyTracker;
#endif

		ofShortPixels depthPix;
		ofTexture depthTex;
		bool depthTexIsDirty = false;

		ofPixels colorPix;
		ofTexture colorTex;

		ofShortPixels irPix;
		ofTexture irTex;

		k4a::image depthToWorldImg;
		ofFloatPixels depthToWorldPix;
		ofTexture depthToWorldTex;

		k4a::image colorToWorldImg;
		ofFloatPixels colorToWorldPix;
		ofTexture colorToWorldTex;

		ofShortPixels depthInColorPix;
		ofTexture depthInColorTex;

		ofPixels colorInDepthPix;
		ofTexture colorInDepthTex;

		std::vector<glm::vec3> positionCache;
		std::vector<glm::vec2> uvCache;
		size_t numPoints= 0;
			
		ofVbo pointCloudVbo;
	};
}
