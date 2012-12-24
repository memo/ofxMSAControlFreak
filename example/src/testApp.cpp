#include "testApp.h"

//using namespace msa;
//using namespace ControlFreak;

// for demonstrating adding any drawable object (that extends ofBaseDraw);
ofVideoGrabber		vidGrabber;
unsigned char * 	videoInverted;
ofTexture			videoTexture;

msa::ControlFreak::gui::Gui             gui;

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
	
	// ADD variables and controls programmatically like below
	// OR just hand edit XML / JSON / INI file and the schema will be loaded and gui constructed
	params.setName("Test Settings");
	
    // ADD 'FLOAT' PARAMETERS. CAN BE ANY REAL NUMBER
	params.addFloat("varf1");
    params.addFloat("varf2").setValue(0.7f);
    params.addFloat("varf3").setRange(-1, 1);
    params.addFloat("varf5").setRange(0, 1000).setValue(ofRandom(200)).setIncrement(0.5);
    
    // add 'integer' parameters. can be any whole number
	params.addInt("vari1");
	params.addInt("vari2").setValue(ofRandom(30));
	params.addInt("vari3").setRange(-10, 10);
	params.addInt("vari4").setRange(50, 1000).setValue(7).setIncrement(10);
    
    // add 'toggle' parameters (can be only true or false)
	params.addToggle("vartoggle1");                            // default value for for toggle is false
	params.addToggle("vartoggle2").setValue(true);             // set value
    params.addFloat("varsin1").setRange(-1, 1).setClamp(true);
    params.addFloat("varsin2").setRange(-1, 1).setClamp(false);
    
    // add a 'bang' parameter (i.e. like a button, sends a trigger value of 'true' for one frame)
	params.addBang("trigger");
    

    // this is one way of adding a named-index parameter (i.e. dropbox box or option list)
    string labels[] = {"first option", "another option", "yet another option", "even more", "and last one"};
	params.addNamedIndex("a dropdown").setLabels(5, labels);
    
    // this is another way of adding a named-index parameter
    params.addNamedIndex("animals").setLabels(4, "cow", "camel", "dolphin", "monkey");
    
    // you can add complex types
    params.addVec3f("pos1");
    params.addVec3f("pos2").setValue( ofVec3f(0.1, 0.2, 0.3) );
    params.addVec3f("pos3").setValue( ofVec3f(1.5, 2.5, 3.5) ).setRange( ofVec3f(-10, -20, -20), ofVec3f(100, 200, 300) );
    
    
    // you can create groups and add any parameters to that group
	params.startGroup("vision");		// now this becomes the activeGroup
        params.addToggle("enabled");
        params.addFloat("brightness").setRange(0, 100);
        params.addFloat("contrast").setRange(-100, 100);
        params.addInt("deviceid").setRange(0, 10);
        params.addToggle("flip x");
        params.addToggle("flip y");
        params.addToggle("bang");
    
        // you can even add groups inside of groups (you can go infinitely deep, as long as you have enough memory)
        params.startGroup("optical flow");
            params.addToggle("enabled");
            params.addFloat("velMult").setRange(0, 10);
            params.addInt("windowSize").setRange(1, 3);
            params.addNamedIndex("method").setLabels(3, "Lucas-Kanade", "Horn–Schunck", "Buxton–Buxton");
        params.endGroup();	// optical flow
	params.endGroup();	// vision
	
	
	params.startGroup("particles");
        params.addToggle("enabled");
        params.addInt("count").setRange(100, 200);
        params.addFloat("maxSpeed").setRange(0, 100);
    params.endGroup();
    
    
    // set GUI handler for the Parameter params
    gui.addParameters(params);
	gui.setDefaultKeys(true);
	gui.show();
    
    
	
    //	params.loadFromInfo();
}


//--------------------------------------------------------------
void testApp::update() {
//    if(params["vartoggle1"]) params["varsin1"] = sin(ofGetElapsedTimef()) * 2;
//    if(params["vartoggle2"]) params["varsin2"] = sin(ofGetElapsedTimef()) * 2;
    //	if(myBool1Animate) myFloat1 = ofNoise(ofGetElapsedTimef());
    //
    //	if(gui.control("myBool1 Animate").getValue()) myFloat1 = ofNoise(ofGetElapsedTimef());
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
		case 's':
            params.saveXml(false);
            break;
            
		case 'S':
            params.saveXml(true);
            break;
            

		case 'l':
			params.loadXml(false);
			break;
			
		case 'L':
			params.loadXml(true);
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
