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
	
	params.createFloat("varf1");                                  // default value for float is 0, default range for float is 0...1
    params.createFloat("varf2").setValue(0.7f);                   // init with value 0.7, and default range
    params.createFloat("varf3").setRange(-1, 1);                  // set range
    params.createFloat("varf4").setRange(0, 1000).setValue(ofRandom(200));  // set range to 0..1000 and set a random value
    
	params.createInt("vari1");                                    // default value for int is 0, default range is 0...100
	params.createInt("vari2").setValue(ofRandom(30));             // init with random value, and default range
	params.createInt("vari3").setRange(-10, 10);                  // set range
	params.createInt("vari4").setRange(5, 10).setValue(7);        // set range and value
    
	params.createToggle("vartoggle1");                            // default value for for toggle is false
	params.createToggle("vartoggle2").setValue(true);             // set value
    
	params.createBang("trigger");
    
    string labels[] = {"first option", "another option", "yet another option", "even more", "and last one"};
	params.createNamedIndex("a dropdown").setLabels(5, labels);
    params.createNamedIndex("animals").setLabels(4, "cow", "camel", "dolphin", "monkey");
    
	params.startGroup("vision");		// now this becomes the activeGroup
        params.createToggle("enabled");
        params.createFloat("brightness").setRange(0, 100);
        params.createFloat("contrast").setRange(-100, 100);
        params.createInt("deviceid").setRange(0, 10);
        params.createToggle("flip x");
        params.createToggle("flip y");
        params.createToggle("bang");
        
        params.startGroup("optical flow");
            params.createToggle("enabled");
            params.createFloat("velMult").setRange(0, 10);
            params.createInt("windowSize").setRange(1, 3);
            params.createNamedIndex("method").setLabels(3, "Lucas-Kanade", "Horn–Schunck", "Buxton–Buxton");
        params.endGroup();	// optical flow
	params.endGroup();	// vision
	
	
	params.startGroup("particles");
        params.createToggle("enabled");
        params.createInt("count").setRange(100, 200);
        params.createFloat("maxSpeed").setRange(0, 100);
    params.endGroup();
    
    
    // set GUI handler for the Parameter params
    gui.addParameters(params);
	gui.setDefaultKeys(true);
	gui.show();
    
    
	
    //	params.loadFromInfo();
}


//--------------------------------------------------------------
void testApp::update(){
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
