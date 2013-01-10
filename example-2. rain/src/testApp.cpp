#include "testApp.h"

#include "ofxMSAControlFreakGui/src/Gui.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"


struct Raindrop {
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f size;
    float rot;
    float rotSpeed;
    float dieTime;
    Raindrop() : dieTime(0){}
};

vector<Raindrop> rain;


// this is a ParameterGroup
msa::ControlFreak::ParameterGroup params;

// this is a gui
msa::ControlFreak::gui::Gui gui;


//--------------------------------------------------------------
void testApp::setup(){
    //    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // Set name for our ParameterGroup
	params.setName("Rain");
        params.addInt("count").setRange(1, 1000).setClamp(true).set(400);
        params.startGroup("emitter"); { // should be ofRectangle
            params.addFloat("x").setRange(0, 100).setClamp(true).set(50);
            params.addFloat("y").setRange(0, 100).setClamp(true).set(10);
            params.addFloat("width").setRange(0, 100).setClamp(true).set(50);
            params.addFloat("height").setRange(0, 100).setClamp(true).set(20);
        } params.endGroup();
        params.startGroup("physics"); {
            params.addFloat("initialVel").setRange(0, 100).set(10);
            params.addFloat("initialVelVari").setRange(0, 1).setClamp(true).set(0.5);
            params.addFloat("spread").setRange(0, 180).set(20).setClamp(true);
            params.addFloat("maxRotSpeed").setRange(0, 10).set(5);
            params.addFloat("gravity").setRange(-1, 1).set(0.1);
            params.addFloat("friction").setRange(0, 1).set(0.02).setClamp(true);;
        } params.endGroup();
        params.startGroup("age"); {
            params.addFloat("min age").setRange(1, 10).set(1);
            params.addFloat("max age").setRange(1, 10).set(5);
        } params.endGroup();
        
        params.startGroup("display options"); {
            params.addNamedIndex("shape type").setLabels(3, "circle", "rectangle", "triangle");
            params.addBool("fill").set(true);
            //            params.addColorf32("color");
            params.addFloat("size").setRange(0, 100).set(10);
            params.addFloat("sizeVari").setRange(0, 1).setClamp(true).set(0.5);
            //            {    // should be ofVec2f
            //                params.addFloat("x").setRange(0, 200).set(50);
            //                params.addFloat("y").setRange(0, 200).set(50);
            //            } params.endGroup();
        } params.endGroup();
        
        params.addBang("randomize");
    
    
    
    
    // TESTERS
//    params.startGroup("Testers");
//    {
//        params.startGroup("floats");
//        {
//            params.addFloat("no clamp, no snap").setRange(0, 5).setIncrement(0.1);
//            params.addFloat("yes clamp, no snap").setRange(0, 5).setIncrement(0.1).setClamp(true);
//            params.addFloat("yes clamp, yes snap").setRange(0, 5).setIncrement(0.1).setClamp(true).setSnap(true);
//            params.addFloat("no clamp, yes snap").setRange(0, 5).setIncrement(0.1).setClamp(false).setSnap(true);
//        }
//        params.endGroup();
//        
//        params.startGroup("ints");
//        {
//            params.addInt("no clamp, no snap").setRange(0, 100).setIncrement(5);
//            params.addInt("yes clamp, no snap").setRange(0, 100).setIncrement(5).setClamp(true);
//            params.addInt("yes clamp, yes snap").setRange(0, 100).setIncrement(5).setClamp(true).setSnap(true);
//            params.addInt("no clamp, yes snap").setRange(0, 100).setIncrement(5).setClamp(false).setSnap(true);
//        }
//        params.endGroup();
//    }
//    params.endGroup();
//    
    
    
    // you can create groups and add any parameters to that group
    gui.addPage(&params);
	gui.setDefaultKeys(true);
	gui.show();
    
    
    ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
    
    //	params.loadFromInfo();
}


//--------------------------------------------------------------
void testApp::update() {
    params.update();
    
    // resize vector if nessecary
    int count = params["count"];
    if(rain.size() != count) {
        ofLogNotice() << "INIT RAIN " << count;
        rain.clear();
        rain.resize(count);
    }
    
    
    if((bool)params["randomize"]) {
        params["emitter.x"].setRandom();
        params["emitter.y"].setRandom();
        params["emitter.width"].setRandom();
        params["emitter.height"].setRandom();
        params["physics.initialVel"].setRandom();
        params["physics.initialVelVari"].setRandom();
        params["physics.spread"].setRandom();
        params["physics.maxRotSpeed"].setRandom();
        params["physics.gravity"].setRandom();
        params["physics.friction"].setRandom();
        params["age.min age"].setRandom();
        params["age.max age"].setRandom();
        params["display options.fill"].setRandom();
        params["display options.size"].setRandom();
        params["display options.sizeVari"].setRandom();
        //        params["display options.size.y"].setRandom();
        params["display options.shape type"].setRandom();
    }
    
    // cache relevant values
    ofVec2f emitterPos = ofVec2f(
                                 params["emitter.x"].getMappedTo(0, ofGetWidth()),  // a fancy method to map the output to this range
                                 params["emitter.y"].getMappedTo(0, ofGetHeight())
                                 );
    float emitterWidth = params["emitter.width"].getMappedTo(0, ofGetWidth());
    float emitterHeight = params["emitter.height"].getMappedTo(0, ofGetHeight());
    float initialVel = params["physics.initialVel"];
    float initialVelVari = params["physics.initialVelVari"];
    float spread = params["physics.spread"];
    float maxRotSpeed = params["physics.maxRotSpeed"];
    float gravity = params["physics.gravity"];
    float friction = params["physics.friction"];
    float minAge = params["age.min age"];
    float maxAge = params["age.max age"];
    float sizeVari = params["display options.sizeVari"];
    
    
    // iterate all rain. update position, rotation and speed
    for(int i=0; i<rain.size(); i++) {
        Raindrop &b = rain[i];
        b.pos += b.vel;
        b.vel.y += gravity;
        b.vel -= b.vel * friction;
        b.rot += b.rotSpeed;
        
        // if offscreen, reset
        if(ofGetElapsedTimef() > b.dieTime || !ofInRange(b.pos.x, 1, ofGetWidth()) || !ofInRange(b.pos.y, 1, ofGetHeight())) {
            b.dieTime = ofGetElapsedTimef() + ofRandom(minAge, maxAge);
            b.pos = emitterPos + ofVec2f(ofRandom(-emitterWidth/2, emitterWidth/2), ofRandom(-emitterHeight/2, emitterHeight/2));
            b.vel = ofVec2f(0, initialVel * ofRandom(1 - initialVelVari));
            b.vel.rotate(ofRandom(-spread/2, spread/2));
            b.rot = ofRandom(360);
            b.rotSpeed = ofRandom(0, maxRotSpeed) * ofSign(ofRandomf());
            b.size = ofVec2f(ofRandom(1 - sizeVari, 1), ofRandom(1 - sizeVari, 1));
        }
    }
    
    
    // read from the bool parameters, and update the float parameters if they are true
    // note that parameter 'animated2' had had it's 'clamp' set to true, so it will never go outside of -1...1
    //    if(params.getBool("Testers.doAnimate1"]) params["Testers.animated1"] = sin(ofGetElapsedTimef()) * 2;
    //    if(params.getBool("Testers.doAnimate2"]) params["Testers.animated2"] = sin(ofGetElapsedTimef()) * 2;
    
    // 'trackTester' is a normal variable, which we had set to sync to the parameter 'trackTester'
    // if we write to this variable, the gui updates
    //    fvar1 = sin(ofGetElapsedTimef());
    
    //	if(myBool1Animate) myFloat1 = ofNoise(ofGetElapsedTimef());
    //
    //	if(gui.control("myBool1 Animate"].value()) myFloat1 = ofNoise(ofGetElapsedTimef());
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
	
    //	if(params("vision"]["bang"]) printf("BANG"];
}

//--------------------------------------------------------------
void testApp::draw(){
    //	ofBackground(color.r * 255, color.g * 255.0f, color.b * 255.0);
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    // draw emitter
    ofNoFill();
    ofRect(params["emitter.x"].getMappedTo(0, ofGetWidth()), params["emitter.y"].getMappedTo(0, ofGetHeight()),
           params["emitter.width"].getMappedTo(0, ofGetWidth()), params["emitter.height"].getMappedTo(0, ofGetHeight()));
    
    // set fill options
    if(params["display options.fill"]) ofFill();
    else ofNoFill();
    
    // cache size value
    float size = params["display options.size"];
    
    int shapeType = params["display options.shape type"];
    for(int i=0; i<rain.size(); i++) {
        Raindrop &b = rain[i];
        
        ofPushMatrix();
        ofTranslate(b.pos);
        ofRotate(b.rot);
        ofScale(b.size.x * size, b.size.y * size, 1);
        
        switch(shapeType) {
            case 0:
                ofCircle(0, 0, 0.5);
                break;
                
            case 1:
                ofRect(0, 0, 1, 1);
                break;
                
            case 2:
                ofTriangle(-0.5, 0.33, 0, -0.67, 0.5, 0.33);
                break;
        }
        ofPopMatrix();
    }
    
    ofPopStyle();
}

void testApp::exit() {
    //	gui.exit();
}


//--------------------------------------------------------------
void testApp::keyPressed (int key){
    //	gui.keyPressed(key);
	
	switch(key) {
		case 's':
            params.saveXmlValues();
            break;
            
		case 'S':
            params.saveXmlSchema();
            break;
            
            
		case 'l':
			params.loadXmlValues();
			break;
			
		case 'L':
			params.loadXmlSchema();
			break;
            
            
        case 'f':
            ofToggleFullscreen();
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
