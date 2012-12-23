#include "testApp.h"
#include  "MSAFreakGui.h"
#include "MSAControlFreak.h"

using namespace msa;
using namespace ControlFreak;

// for demonstrating adding any drawable object (that extends ofBaseDraw);
ofVideoGrabber		vidGrabber;
unsigned char * 	videoInverted;
ofTexture			videoTexture;

ParameterGroup      params;
guigl::Gui			gui;

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	
	// ADD variables and controls programmatically like below
	// OR just hand edit XML / JSON / INI file and the schema will be loaded and gui constructed
	params.setName("My Settings");
	
	params.addFloat("float1");
    params.addFloat("float2");
    
	string labels[] = {"first option", "another option", "yet anothing option", "even more", "and last one"};
	params.addNamedIndex("a dropdown", 5, labels);
	params.addInt("int1");
	params.addToggle("bool1");
	params.addBang("trigger");
	
	params.startGroup("vision");		// now this becomes the activeGroup
    {
        params.addToggle("enabled");
        params.addFloat("brightness").setRange(0, 100);
        params.addFloat("contrast").setRange(-100, 100);
        params.addInt("deviceid").setRange(0, 10);
        params.addToggle("flip x");
        params.addToggle("flip y");
        params.addToggle("bang");
        
        params.startGroup("optical flow");
        {
            params.addToggle("enabled");
            params.addFloat("velMult").setRange(0, 10);
            params.addInt("windowSize").setRange(1, 3);
        }
        params.endGroup();	// optical flow
    }
	params.endGroup();	// vision
	
	
	params.startGroup("particles");
    {
        params.addToggle("enabled");
        params.addInt("count").setRange(100, 200);
        params.addFloat("maxSpeed").setRange(0, 100);
	}
    params.endGroup();
    
    
    // set GUI handler for the Parameter params
//    gui.set
	gui.setDefaultKeys(true);
	gui.show();
    
    
	
    //	params.loadFromInfo();
}


//--------------------------------------------------------------
void testApp::update(){
    //	if(myBool1Animate) myFloat1 = ofNoise(ofGetElapsedTimef());
    //
    //	if(gui.control("myBool1 Animate").value()) myFloat1 = ofNoise(ofGetElapsedTimef());
    //
    //	if(randomizeButton) {
    //		randomizeButton = false;
    //		aColor.r = ofRandomuf();
    //		aColor.g = ofRandomuf();
    //		aColor.b = ofRandomuf();
    //	}
	
	
	// from ofVideoGrabber example (
    //	vidGrabber.update();
    //	if(vidGrabber.isFrameNew()){
    //		int totalPixels = vidGrabber.getWidth() * vidGrabber.getHeight() * 3;
    //		unsigned char * pixels = vidGrabber.getPixels();
    //		for(int i = 0; i < totalPixels; i++) videoInverted[i] = 255 - pixels[i];
    //		videoTexture.loadData(videoInverted, vidGrabber.getWidth(), vidGrabber.getHeight(), GL_RGB);
    //	}
	
    //	if(params("vision")["bang"]) printf("BANG");
}

//--------------------------------------------------------------
void testApp::draw(){
    //	ofBackground(color.r * 255, color.g * 255.0f, color.b * 255.0);
	
//	gui.draw();
}

void testApp::exit() {
    //	gui.exit();
}


//--------------------------------------------------------------
void testApp::keyPressed (int key){
    //	gui.keyPressed(key);
	
	switch(key) {
		case 'x':
            params.saveToXML();
            break;
		case 'i':
			params.saveToInfo();
			break;
		case 'j':
            //            params.saveToJSON();
			break;
			
		case 'l':
			params.loadFromInfo();
			break;
			
	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
    //	gui.keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
    //	gui.mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
    //	gui.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    //	gui.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
    //	gui.mouseReleased(x, y, button);
}
