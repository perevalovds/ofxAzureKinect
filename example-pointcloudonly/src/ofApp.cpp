#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//ofSetLogLevel(OF_LOG_VERBOSE);

	ofLogNotice(__FUNCTION__) << "Found " << ofxAzureKinect::Device::getInstalledCount() << " installed devices.";

	if (this->kinectDevice.open())
	{
		auto settings = ofxAzureKinect::DeviceSettings();
		settings.depthMode = K4A_DEPTH_MODE_NFOV_UNBINNED;
		settings.cameraFps = K4A_FRAMES_PER_SECOND_30;

		settings.colorResolution = K4A_COLOR_RESOLUTION_2160P;
		settings.colorFormat = K4A_IMAGE_FORMAT_COLOR_BGRA32;
		settings.wiredSyncMode = K4A_WIRED_SYNC_MODE_STANDALONE;
		settings.depthDelayUsec = 0;
		settings.subordinateDelayUsec = 0;
		settings.updateColor = false;
		settings.updateIr = false;
		settings.updateWorld = true;
		settings.updateVbo = true;
		settings.syncImages = false;

		this->kinectDevice.startCameras(settings);
	}
}

//--------------------------------------------------------------
void ofApp::exit()
{
	this->kinectDevice.close();
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(128);

	if (this->kinectDevice.isStreaming())
	{
		this->cam.begin();
		{
			ofScale(0.5f);

			ofDrawAxis(1000.0f);

			//if (this->kinectDevice.getColorInDepthTex().isAllocated())
			//{
			//	this->kinectDevice.getColorInDepthTex().bind();
			//}
			this->kinectDevice.getPointCloudVbo().draw(
				GL_POINTS,
				0, this->kinectDevice.getPointCloudVbo().getNumVertices());
			//if (this->kinectDevice.getColorInDepthTex().isAllocated())
			//{
			//	this->kinectDevice.getColorInDepthTex().unbind();
			//}
		}
		this->cam.end();
	}

	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(), 2) + " FPS", 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
	
}
