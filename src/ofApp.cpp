#include "ofApp.h"

float spread;
float avgX;
float avgY;

//--------------------------------------------------------------
void ofApp::setup(){
    
    std::string file = "traffic-cameras.json";
    
    // Now parse the JSON
    bool parsingSuccessful = result.open(file);
    
    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << result.getRawString();
        
        // now write pretty print
        if (!result.save("example_output_pretty.json", true))
        {
            ofLogNotice("ofApp::setup") << "example_output_pretty.json written unsuccessfully.";
        }
        else
        {
            ofLogNotice("ofApp::setup") << "example_output_pretty.json written successfully.";
        }
        
        // now write without pretty print
        if (!result.save("example_output_fast.json", false))
        {
            ofLogNotice("ofApp::setup") << "example_output_pretty.json written unsuccessfully.";
        }
        else
        {
            ofLogNotice("ofApp::setup") << "example_output_pretty.json written successfully.";
        }
        
    }
    else
    {
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
            
            pts.push_back(ofPoint(lat, lon));
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
    

    



}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);

    for(int i=0;i<pts.size();i++){
        
        
        float lat = (pts[i].x - avgX)*ofGetWidth();
        float lon = (pts[i].y - avgY)*ofGetWidth();
        
        
        
        ofDrawCircle(ofGetWidth()/2+lon, ofGetHeight()/2-lat, 2);
    };

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
