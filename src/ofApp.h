#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxThreadedImageLoader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxJSONElement result; // the json
    vector<ofPoint> pts; // draw locs
    vector<ofPoint> cameraLocs; // lat/lon of cameras
    
    
    // for figuring out the mapping
    // of lat/on to screen
    float spread;
    float avgX;
    float avgY;
    
    int selectedCamera;
    
    string message;
    vector<string> locationNames;
    vector<string> urls;
    
    ofImage cameraImg;
    		ofxThreadedImageLoader loader;
		
};
