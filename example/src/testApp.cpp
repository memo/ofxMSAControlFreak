#include "testApp.h"
#include "AnyValue.h"

//using namespace msa;
//using namespace ControlFreak;

// for demonstrating adding any drawable object (that extends ofBaseDraw);
ofVideoGrabber		vidGrabber;
unsigned char * 	videoInverted;
ofTexture			videoTexture;


msa::ControlFreak::ParameterGroup      params;
msa::ControlFreak::gui::Gui            gui;

float fvar1;
float fvar2;

bool doDebug = true;

//--------------------------------------------------------------
void testApp::setup(){
    //    ofSetLogLevel(OF_LOG_VERBOSE);
    
    
    
    // Set name for our ParameterGroup
	params.setName("ControlFreak Demo");
    
    if(!doDebug) {
    
	// CREATING PARAMETERS
    // All Parameters are created via the addXXXX methods of a ParameterGroup
    // Adding basic value Parameters
	params.addFloat("float1");  // float: can be any real number
	params.addInt("int1");      // int: can be any whole number
	params.addBool("bool1");    // bool: can be true or false
    
    
    
    
    // CHANGING PROPERTIES ON CREATION
    // while you're adding, you can change various properties
    params.addFloat("float2").setValue(ofRandom(0, 1));     // create and set value. default value for float is 0
    params.addFloat("float3").setRange(-1, 1);              // create and set range. default range for float is 0...1
    params.addFloat("float4").setIncrement(0.2);            // create and set increment value (e.g. if you use up/down on keyboard)
    params.addFloat("float5").setIncrement(0.2).setSnap(true);  // create and enable snap, so even if you use mouse or any other means, values always snap
    
	params.addInt("int2").setValue(ofRandom(30));           // create and set value. default value for int is 0
	params.addInt("int3").setRange(-10, 10);                // create and set range. default range for int is 0...100
	params.addInt("int4").setIncrement(5);                  // create and set increment value (e.g. if you use up/down on keyboard)
	params.addInt("int5").setIncrement(5).setSnap(true);    // create and enable snap, so even if you use mouse or any other means, values always snap
    
    params.addBool("bool2").setValue(true);                 // create and set value. default value for bool is 0
    params.addBool("bool3").setBang(true);                  // create and enable momentary bool (i.e. a button, or 'bang')
    
    // NOTE: The Parameter names used must be unique!
    
    
    
    // DAISY CHAINING
    // all property methods can be daisy chained in any order
    params.addFloat("float6").setRange(0, 1000).setValue(500).setClamp(true).setIncrement(10).setSnap(true);
    
    // ... but are evaluated left to right, so if you try to set a high value before setting the range, it wont work
    params.addFloat("float7").setClamp(true).setValue(500).setRange(0, 1000).setIncrement(10).setSnap(true);
    
    
    
    
    // CHANGING PROPERTIES AFTER CREATION
    // the addXXXX methods used above create the Parameter and change the properties at the same time
    // If you want to change properties AFTER creating the Parameter you should use getXXXX methods of ParameterGroup instead of addXXXXX
    params.getFloat("float1").setRange(0, 100);
    params.getFloat("float1").setValue(50);
    params.getFloat("float1").setIncrement(5);
    
    // of course daisy chaining the property methods still work
    params.getFloat("float1").setRange(0, 1000).setValue(ofRandom(1000)).setIncrement(10).setSnap(true);
    
    
    
    
    // GETTING VALUES
    // to extract the value, simply use the getXXXX methods and (possibly) type-cast it if need be
    ofLogNotice() << "Sending straight to ofLogVerbose needs an explicit type-cast to avoid ambiguity: " << (float)params.getFloat("float1");
    
    // or
    float f = params.getFloat("float1");
    ofLogNotice() << "Saving to a variable doesn't need a type-cast. type-cast is done implicitly: " << f;
    
    
    
    
    // SETTING VALUES
    // you saw above you can use setValue method
    params.getFloat("float1").setValue(0.5);
    
    // you can actually use the '=' operator instead of setValue
    params.getFloat("float1") = 0.5;    // identical to using '.setValue(0.5)
    
    // or use arithmetic operators
    params.getFloat("float2") = params.getFloat("float1") * 2.0;
    
    // explicit type-cast needed to avoid ambiguity on * operator
    params.getFloat("float3") = params.getFloat("float1") * (float)params.getFloat("float2");
    
    
    
    
    // EXTERNAL
    // you can also assign an external variable, which is kept track of and kept in sync, at no performance cost
    
    // assigning the tracked variable upon Parameter creation (i.e. using addXXXX method)
    params.addFloat("float8").trackVariable(&fvar1);
    
    // assigning the tracked variable after Parameter creation (i.e. using getXXXX method)
    params.getFloat("float1").trackVariable(&fvar2);
    
    
    
    // NAMED INDEXES
    // this is one way of adding a named-index parameter (i.e. dropbox box or option list)
    string labels[] = {"first option", "another option", "yet another option", "even more", "and last one"};
	params.addNamedIndex("a dropdown").setLabels(5, labels);
    
    // this is another way of adding a named-index parameter
    params.addNamedIndex("animals").setLabels(4, "cow", "camel", "dolphin", "monkey");
    
    
    
    // GROUPS
    // you can create Groups inside ParameterGroups
    // any parameter added after startGroup(....) and before corresponding endGroup() will be created in that group
    params.startGroup("particles"); // now this becomes the active group for following Parameters
    params.addBool("enabled");  // 1st Parameter in this Group
    params.addInt("count");     // 2nd Parameter in this Group
    params.addFloat("size");    // 3rd Parameter in this Group
    params.endGroup();          // any future Parameters will now be outside this group
    
    
    
    // clear all parameters (so we have a clean slate to carry on)
    params.clear();
    
    
    
    // You can even create Groups inside Groups inside Groups .... (until you run out of memory)
    // Parameter names MUST be unique ONLY within the groups they are in
    // (the { } curly braces are not needed. I'm only using that to help with the indenting to help visualize the structure)
	params.startGroup("vision"); {
        params.addBool("enabled");
        params.addFloat("brightness").setRange(0, 100);
        params.addFloat("contrast").setRange(-100, 100);
        params.addBool("flip x");
        params.addBool("flip y");
        params.addBang("reset");
        
        params.startGroup("pre-processing"); {
            params.startGroup("blur"); {
                params.addBool("enabled");
                params.addInt("kernelSize").setRange(3, 11).setIncrement(2);
                params.addInt("iterations").setRange(1, 20);
            } params.endGroup();  // blur
            params.startGroup("median"); {
                params.addBool("enabled");
                params.addInt("kernelSize").setRange(3, 11).setIncrement(2);
                params.addInt("iterations").setRange(1, 20);
            } params.endGroup();  // median
        } params.endGroup();  // pre-processing
        
        params.startGroup("optical flow"); {
            params.addBool("enabled");
            params.addFloat("velMult").setRange(0, 10);
            params.addInt("windowSize").setRange(1, 11).setIncrement(2);
            params.addNamedIndex("method").setLabels(3, "Lucas-Kanade", "Horn–Schunck", "Buxton–Buxton");
        } params.endGroup();	// optical flow
	} params.endGroup();	// vision
	
    
    
    // ACCESSING PARAMETERS IN A GROUP
    // Option1: The simple, but long-winded way
    params.getGroup("vision").getBool("enabled") = true;
    params.getGroup("vision").getGroup("pre-processing").getGroup("blur").getInt("iterations") = 1;
    
    
    // Option2: Cache groups, slightly more optimum
    msa::ControlFreak::ParameterGroup &gVision = params.getGroup("vision");
    msa::ControlFreak::ParameterGroup &gVisionPre = gVision.getGroup("pre-processing");
    msa::ControlFreak::ParameterGroup &gVisionPreBlur = gVisionPre.getGroup("blur");
    gVision.getBool("enabled") = true;
    gVisionPreBlur.getInt("iterations") = 2;
    
    
    // Option3: List full path (my favorite)
    params.getBool("vision.enabled") = true;
    params.getInt("vision.pre-processing.blur.iterations") = 3;
    
    
    
    // TESTERS
    params.startGroup("Testers");
	params.addBool("doAnimate1");
    params.addFloat("animated1").setRange(-1, 1).setClamp(true);
	params.addBool("doAnimate2").setValue(true);
    params.addFloat("animated2").setRange(-1, 1).setClamp(false);
    params.addFloat("float snap").setRange(0.25, 2).setIncrement(0.5).setSnap(true);
    params.addInt("int snap").setRange(1, 15).setIncrement(2).setSnap(true);
    params.endGroup();
    
    
    
    
    // you can add complex types
    //    params.addVec3f("pos1");
    //    params.addVec3f("pos2").setValue( ofVec3f(0.1, 0.2, 0.3) );
    //    params.addVec3f("pos3").setValue( ofVec3f(1.5, 2.5, 3.5) ).setRange( ofVec3f(-10, -20, -20), ofVec3f(100, 200, 300) );
    
    
    
    // AN EXAMPLE
    params.startGroup("shape"); {
        params.startGroup("transform");{
            params.addInt("posx").setRange(0, ofGetWidth()).setValue(ofGetWidth()/2);
            params.addInt("posy").setRange(0, ofGetHeight()).setValue(ofGetHeight()/2);
            params.addFloat("sizex").setRange(0, ofGetWidth()).setValue(ofGetHeight()/2);
            params.addFloat("sizey").setRange(0, ofGetHeight()).setValue(ofGetHeight()/2);
            params.addInt("rotation").setRange(0, 360);
        } params.endGroup();
        params.startGroup("display options"); {
            params.addBool("fill").setValue(true);
            params.addNamedIndex("shape type").setLabels(3, "circle", "rectangle", "triangle");
        } params.endGroup();
        params.addBang("randomize");
        params.addBang("reset");
    } params.endGroup();
    
    }
    
    params.startGroup("floats");
    params.addFloat("no clamp, no snap").setRange(0, 5).setIncrement(0.1);
    params.addFloat("yes clamp, no snap").setRange(0, 5).setIncrement(0.1).setClamp(true);
    params.addFloat("yes clamp, yes snap").setRange(0, 5).setIncrement(0.1).setClamp(true).setSnap(true);
    params.addFloat("no clamp, yes snap").setRange(0, 5).setIncrement(0.1).setClamp(false).setSnap(true);
    params.endGroup();
    
    params.startGroup("ints");
    params.addInt("no clamp, no snap").setRange(0, 100).setIncrement(5);
    params.addInt("yes clamp, no snap").setRange(0, 100).setIncrement(5).setClamp(true);
    params.addInt("yes clamp, yes snap").setRange(0, 100).setIncrement(5).setClamp(true).setSnap(true);
    params.addInt("no clamp, yes snap").setRange(0, 100).setIncrement(5).setClamp(false).setSnap(true);
    params.endGroup();
    
    // you can create groups and add any parameters to that group
    
    gui.addParameters(params);
	gui.setDefaultKeys(true);
	gui.show();
    
    
    ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
    
    //	params.loadFromInfo();
}


//--------------------------------------------------------------
void testApp::update() {
    params.update();
    
    if(!doDebug) {
    // read from the bool parameters, and update the float parameters if they are true
    // note that parameter 'animated2' had had it's 'clamp' set to true, so it will never go outside of -1...1
    if(params.getBool("Testers.doAnimate1")) params.getFloat("Testers.animated1") = sin(ofGetElapsedTimef()) * 2;
    if(params.getBool("Testers.doAnimate2")) params.getFloat("Testers.animated2") = sin(ofGetElapsedTimef()) * 2;
    }
    
    // 'trackTester' is a normal variable, which we had set to sync to the parameter 'trackTester'
    // if we write to this variable, the gui updates
    //    fvar1 = sin(ofGetElapsedTimef());
    
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
    if(!doDebug) {
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    // draw shape
    if(params.getBool("shape.randomize") && params.getBool("shape.randomize").hasChanged()) {
        params.getInt("shape.transform.posx") = ofRandom(params.getInt("shape.transform.posx").getMin(), params.getInt("shape.transform.posx").getMax());
        params.getInt("shape.transform.posy") = ofRandom(params.getInt("shape.transform.posy").getMin(), params.getInt("shape.transform.posy").getMax());
        params.getInt("shape.transform.rotation") = ofRandom(params.getInt("shape.transform.rotation").getMin(), params.getInt("shape.transform.rotation").getMax());
        params.getFloat("shape.transform.sizex") = ofRandom(params.getFloat("shape.transform.sizex").getMin(), params.getFloat("shape.transform.sizex").getMax());
        params.getFloat("shape.transform.sizey") = ofRandom(params.getFloat("shape.transform.sizey").getMin(), params.getFloat("shape.transform.sizey").getMax());
        params.getNamedIndex("shape.display options.shape type") = ofRandom(0, params.getNamedIndex("shape.display options.shape type").getMax());
    }
    
    if(params.getBool("shape.reset")) {
        params.getInt("shape.transform.posx") = ofGetWidth()/2;
        params.getInt("shape.transform.posy") = ofGetHeight()/2;
        params.getInt("shape.transform.rotation") = 0;
        params.getFloat("shape.transform.sizex") = ofGetHeight()/2;
        params.getFloat("shape.transform.sizey") = ofGetHeight()/2;
        params.getNamedIndex("shape.display options.shape type") = 0;
    }
    
    if(params.getBool("shape.display options.fill")) ofFill();
    else ofNoFill();
    ofPushMatrix();
    ofTranslate(params.getInt("shape.transform.posx"), params.getInt("shape.transform.posy"));
    ofRotate(params.getInt("shape.transform.rotation"));
    ofScale(params.getFloat("shape.transform.sizex"), params.getFloat("shape.transform.sizey"));
    
    switch(params.getNamedIndex("shape.display options.shape type")) {
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
    ofPopStyle();
    }
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
