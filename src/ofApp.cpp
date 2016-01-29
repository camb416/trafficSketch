#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    
    std::string file = "traffic-cameras.json";
    
    // Now parse the JSON
    bool parsingSuccessful = result.open(file);
    
    if (parsingSuccessful) {
        ofLogNotice("ofApp::setup") << "JSON loaded successfully";
    } else  {
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << endl;
    }
    
    
    
    ofBackground(255);
    
    // See this page for all of the ways to access data in a Json::Value
    // http://open-source-parsers.github.io/jsoncpp-docs/doxygen/class_json_1_1_value.html
    
 //  ofSetHexColor(0x00FF00);
    
    //if (result.isMember("errors"))
    //{
    //    ofDrawBitmapString(result.getRawString(), 10, 14);
    // }
    //else
    if (result.isArray())
    {
        //const Json::Value& name = result[0]["name"];
        //const Json::Value& camera = result[0]["camera"];
        
        
        float leastLat = 999999;
        float mostLat = -999999;
        
        float leastLon = 999999;
        float mostLon = -999999;
        avgX = avgY = 0;
        
        for (Json::ArrayIndex i = 0; i < result.size(); ++i)
        {
            std::string message = result[i]["name"].asString();
            ofDrawBitmapString(message, 10, 40*i+40);
            
            string lat_str = result[i]["lat"].asString();
            string lon_str = result[i]["lng"].asString();
            
            float lat = ofToFloat(lat_str);
            float lon = ofToFloat(lon_str);
            
            if(lat<leastLat) leastLat = lat;
            if(lat>mostLat) mostLat = lat;
            
            if(lon<leastLon) leastLon = lon;
            if(lon>mostLon) mostLon = lon;
            
            avgX += lat;
            avgY += lon;
            
            ofLog() << lon;
            cameraLocs.push_back(ofPoint(lat, lon));
            locationNames.push_back(result[i]["name"].asString());
        }
        
        avgX /= result.size();
        avgY /= result.size();
        
        float spreadX = mostLat - leastLat;
        float spreadY = mostLon - leastLon;
        ofLog() << spreadX;
        ofLog() << spreadY;
        ofLog() << mostLat << ", " << leastLat;
        
        spread = MAX(spreadX, spreadY);
    }
    
    for(int i=0;i<cameraLocs.size();i++){
        
        float lat = (cameraLocs[i].x - avgX)*ofGetWidth()*1.2;
        float lon = (cameraLocs[i].y - avgY)*ofGetWidth()*1.2;
        
        ofSetColor(212);
        pts.push_back(ofPoint(ofGetWidth()/2+lon, ofGetHeight()/2-lat));
    }

    
    selectedCamera = -1;
    



}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(212);
    ofSetColor(0);
    
    if(selectedCamera>-1){
    ofNoFill();
    ofSetColor(255,0,0);
    ofDrawLine(mouseX,mouseY,pts[selectedCamera].x,pts[selectedCamera].y);
        
        ofDrawBitmapString(locationNames[selectedCamera],20,20);
        
    }
    
    ofFill();
    
    // render smaller white circles
    for(int i=0;i<pts.size();i++){
        i == selectedCamera ? ofSetColor(255,0,0) : ofSetColor(128);
        ofDrawCircle(pts[i].x,pts[i].y, 6);
    }
    
    // render smaller white circles
    for(int i=0;i<pts.size();i++){
        ofSetColor(255);
        ofDrawCircle(pts[i].x,pts[i].y, 4);
    }
    
    // render black dots
    for(int i=0;i<pts.size();i++){
        i == selectedCamera ? ofSetColor(255,0,0) : ofSetColor(0);
        ofDrawCircle(pts[i].x,pts[i].y, 1.5f);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    int nearestID = -1;
    int nearestDist = 9999;
    
    for(int i=0;i<pts.size();i++){
        float thisDist = ofDist(x,y,pts[i].x,pts[i].y);
        if(thisDist<nearestDist){
            nearestID = i;
            nearestDist = thisDist;
        }
    }
    selectedCamera = nearestID;
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
