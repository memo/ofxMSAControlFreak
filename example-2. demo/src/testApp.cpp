#include "testApp.h"

#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"

#include "Particle.h"


msa::controlfreak::ParameterGroup params;
msa::controlfreak::gui::Gui gui;


vector<Particle> particles;


//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
    
    
    // lets create a group for everything,
    // we dont have to, but incase we decide to expand the app later and add more parameters it keeps things tidy from the start
    params.startGroup("particles");
    {
        params.addInt("count").setRange(0, 100).setClamp(true);
        params.addFloat("speed").setRange(0, 2).setClamp(true);
        params.addNamedIndex("shape").setLabels(3, "rectangle", "triangle", "circle");
        
        params.startGroup("max size");
        {
            params.addInt("width").setRange(0, 100).setClamp(true);  // this will be in % of total window width, we can use the handy Parameter::getMappedTo(...) method to map to the correct range
            params.addInt("height").setRange(0, 100).setClamp(true); // this will be in % of total window height, we can use the handy Parameter::getMappedTo(...) method to map to the correct range

        } params.endGroup();
        
        params.startGroup("spread");
        {
            params.addInt("width").setRange(0, 100).setClamp(true);  // this will be in % of total window width, we can use the handy Parameter::getMappedTo(...) method to map to the correct range

            params.addInt("height").setRange(0, 100).setClamp(true); // this will be in % of total window height, we can use the handy Parameter::getMappedTo(...) method to map to the correct range

        } params.endGroup();
        
        
        params.startGroup("background color");
        {
            params.addInt("r").setRange(0, 255).setClamp(true);
            params.addInt("g").setRange(0, 255).setClamp(true);
            params.addInt("b").setRange(0, 255).setClamp(true);
            params.addBang("randomize");
        } params.endGroup();
        
    }
    params.endGroup();
    
    // load default values for all parameters
    params.loadXmlValues();
    
    // link the parameters to the gui. The GUI will constuct all the nessecary controls and link each one to the relevant parameters
    gui.addPage(params);
    
    // default keys are: space (toggle show/hide), numbers (jump to that page in the gui), '[]' (next page / prev page)
	gui.setDefaultKeys(true);
    
        
    // by default all events (update, draw, mouse events, keyboard events etc) are sent to the GUI automatically
    // if you don't like this, you can disableAutoEvents for the gui
    // but if you do, you need to make sure you call the gui update/draw/mouse/keyboard events manually
    //    gui.enableAllEvents();    // this is the default
    //    gui.disableAllEvents();
}


//--------------------------------------------------------------
void testApp::update() {
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
    //     gui.update();
}



//--------------------------------------------------------------
void testApp::draw() {

    // if user clicked on 'randomize' button (bang), choose a new color
    // we don't need to check for hasChanged() because a bang will only be true for one frame anyway
    if(params["particles.background color.randomize"]) {
        params["particles.background color.r"].setRandom(); // sets a random number between the Parameter's min and max
        params["particles.background color.g"].setRandom(); // sets a random number between the Parameter's min and max
        params["particles.background color.b"].setRandom(); // sets a random number between the Parameter's min and max
    }

    // if any of the background color parameters have changed, set the background color
    if(params["particles.background color"].hasChanged()) {
        ofBackground(params["particles.background color.r"], params["particles.background color.g"], params["particles.background color.b"]);
    }
    
    
    // since we will be doing a for-loop with possibly many thousands of iterations per frame,
    // it makes sense to cache the value of these parameters
    ofVec2f maxSpread;
    maxSpread.x = params["particles.spread.width"].getMappedTo(0, ofGetWidth());
    maxSpread.y = params["particles.spread.height"].getMappedTo(0, ofGetHeight());

    ofVec2f maxSize;
    maxSize.x = params["particles.max size.width"].getMappedTo(0, ofGetWidth());
    maxSize.y = params["particles.max size.height"].getMappedTo(0, ofGetHeight());

    int shapeType = params["particles.shape"];
    

    // this is our timer, which controls the speed of everything
    static float myTimer = 0;
    myTimer += (float)params["particles.speed"] * 0.01;
    
    // if particle count has changed, reallocate array
    if(params["particles.count"].hasChanged()) {
        int numParticleCount = params["particles.count"];

        particles.clear();
        for(int i=0; i<numParticleCount; i++) {
            particles.push_back(Particle());
            particles[i].setup(i);
        }
    }
    

    for(int i=0; i<particles.size(); i++) {
        Particle &particle = particles[i];
        particle.update(myTimer, maxSpread, maxSize);
        particle.draw(shapeType);
     }
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()-100, 30);
    
    
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
    //     gui.draw();
}


//--------------------------------------------------------------
void testApp::exit() {
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
    //    gui.exit();
}


//--------------------------------------------------------------
void testApp::keyPressed (int key){
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
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
void testApp::keyReleased(int key){
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
    //	gui.keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
    //	gui.mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
    //	gui.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
    //	gui.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
    //	gui.mouseReleased(x, y, button);
}
