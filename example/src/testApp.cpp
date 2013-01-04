#include "testApp.h"
#include "AnyValue.h"

//using namespace msa;
//using namespace ControlFreak;

// for demonstrating adding any drawable object (that extends ofBaseDraw);
ofVideoGrabber		vidGrabber;
unsigned char * 	videoInverted;
ofTexture			videoTexture;



struct Ball {
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f size;
    float rot;
    float rotSpeed;
    float dieTime;
};

vector<Ball> balls;


// this is a (smart) Pointer to a ParameterGroup
msa::ControlFreak::ParameterGroupPtr   params;

msa::ControlFreak::gui::Gui            gui;


// CREATING PARAMETERS
void tutorial1() {
    
    ofLogNotice() << "TUTORIAL 1";
    
    // All Parameters are created via the addXXXX methods of a ParameterGroup
    // Adding basic value Parameters
    params->addFloat("float1");  // float: can be any real number
    params->addInt("int1");      // int: can be any whole number
    params->addBool("bool1");    // bool: can be true or false
    
    
    
    // CHANGING PROPERTIES ON CREATION
    // while you're adding, you can change various properties
    params->addFloat("float2").setValue(0.7);     // create and set value. default value for float is 0
    params->addFloat("float3").setRange(-1, 1);              // create and set range. default range for float is 0...1
    params->addFloat("float4").setIncrement(0.2);            // create and set increment value (e.g. if you use up/down on keyboard)
    params->addFloat("float5").setIncrement(0.2).setSnap(true);  // create and enable snap, so even if you use mouse or any other means, values always snap
    
    params->addInt("int2").setValue(17);           // create and set value. default value for int is 0
    params->addInt("int3").setRange(-10, 10);                // create and set range. default range for int is 0...100
    params->addInt("int4").setIncrement(5);                  // create and set increment value (e.g. if you use up/down on keyboard)
    params->addInt("int5").setIncrement(5).setSnap(true);    // create and enable snap, so even if you use mouse or any other means, values always snap
    
    params->addBool("bool2").setValue(true);                 // create and set value. default value for bool is 0
    params->addBool("bool3").setMode(msa::ControlFreak::ParameterBool::kBang);                  // create and enable momentary bool (i.e. a button, or 'bang')
    
    // NOTE: The Parameter names used must be unique!
    
    
    // DAISY CHAINING
    // all property methods can be daisy chained in any order
    params->addFloat("float6").setRange(0, 1000).setValue(500).setClamp(true).setIncrement(10).setSnap(true);
    
    // ... but are evaluated left to right, so if you try to set a high value before setting the range, it wont work
    params->addFloat("float7").setClamp(true).setValue(500).setRange(0, 1000).setIncrement(10).setSnap(true);
}


// ACCESS PARAMETERS AND VALUES
void tutorial2() {
    ofLogNotice() << "TUTORIAL 2";
    
    // CHANGING PROPERTIES AFTER CREATION
    // the addXXXX methods used above create the Parameter and change the properties at the same time
    // If you want to change properties AFTER creating the Parameter you should use get methods of ParameterGroup instead of addXXXXX
    params->get("float1").setRange(0, 100);
    params->get("float1").setValue(50);
    params->get("float1").setIncrement(5);
    
    // of course daisy chaining the property methods still work
    params->get("float1").setRange(0, 1000).setValue(50).setIncrement(10).setSnap(false);
    
    
    // GETTING VALUES
    // to extract the value, simply use the get method
    
    float a = params->get("float1");
    ofLogNotice() << "value of 'float1': " << a;
    
    // the .get() method actually returns a reference to the whole Parameter, which has a cast operator
    // if this causes ambiguity, just cast it
    ofLogNotice() << "value of 'float2': " << (float)params->get("float2");  // e.g. this works
    //    ofLogNotice() << "value of 'float2': " << params->get("float2");  // e.g. but this will not compile
}


// SETTING VALUES
void tutorial3() {
    ofLogNotice() << "TUTORIAL 3";
    
    // you saw above you can use setValue method
    params->get("float1").setValue(12);
    ofLogNotice() << "new float1 value: " << (float)params->get("float1");
    
    // you can actually use the '=' operator instead of setValue
    params->get("float2") = 0.2;    // identical to using 'setValue(0.5)
    ofLogNotice() << "new float2 value " << (float)params->get("float2");
    
    // remember to cast as nessecary
    params->get("float3") = (float)params->get("float1") * (float)params->get("float2");
    ofLogNotice() << "new float3 value " << (float)params->get("float3");
}


// tracking external variables
void tutorial4() {
    ofLogNotice() << "TUTORIAL 4";
    
    // you can also assign an external variable, which is kept track of and kept in sync, at no performance cost
    
    // assigning the tracked variable upon Parameter creation (i.e. using addXXXX method)

    float var1 = 0;
    
    params->addFloat("param1").trackVariable(&var1);
    
    ofLogNotice() << " var1 : " << var1 << ", param1 : " << (float)params->get("param1");
    
    // modify variable
    var1 = 15;
    ofLogNotice() << " var1 : " << var1 << ", param1 : " << (float)params->get("param1");
    
    // modify variable
    params->get("param1") = 25;
    ofLogNotice() << " var1 : " << var1 << ", param1 : " << (float)params->get("param1");
    
}


// NAMED INDEXES
void tutorial5() {
    ofLogNotice() << "TUTORIAL 5";
    
    // this is one way of adding a named-index parameter (i.e. dropbox box or option list)
    string labels[] = {"first option", "another option", "yet another option", "even more", "and last one"};
    params->addNamedIndex("a dropdown").setLabels(5, labels);
    
    // this is another way of adding a named-index parameter
    params->addNamedIndex("animals").setLabels(4, "cow", "camel", "dolphin", "monkey");
}


//--------------------------------------------------------------
void testApp::setup(){
    //    ofSetLogLevel(OF_LOG_VERBOSE);
 
    
    // create and get a new instance of a ParameterGroup (returned as a ParameterGroupPtr)
    params = msa::ControlFreak::ParameterGroup::create("ControlFreak Demo");
    
    // Set name for our ParameterGroup
    //	params->setName("ControlFreak Demo");
    
    
    tutorial1();
    tutorial2();
    tutorial3();
    tutorial4();
    tutorial5();


    
    
    
    // GROUPS
    // you can create Groups inside ParameterGroups
    // any parameter added after startGroup(....) and before corresponding endGroup() will be created in that group
    params->startGroup("particles"); // now this becomes the active group for following Parameters
    params->addBool("enabled");  // 1st Parameter in this Group
    params->addInt("count");     // 2nd Parameter in this Group
    params->addFloat("size");    // 3rd Parameter in this Group
    params->endGroup();          // any future Parameters will now be outside this group
    
    
    
    
    // You can even create Groups inside Groups inside Groups .... (until you run out of memory)
    // Parameter names MUST be unique ONLY within the groups they are in
    // (the { } curly braces are not needed. I'm only using that to help with the indenting to help visualize the structure)
    params->startGroup("vision");
    {
        params->addBool("enabled");
        params->addFloat("brightness").setRange(0, 100);
        params->addFloat("contrast").setRange(-100, 100);
        params->addBool("flip x");
        params->addBool("flip y");
        params->addBang("reset");
        
        params->startGroup("pre-processing");
        {
            params->startGroup("blur");
            {
                params->addBool("enabled");
                params->addInt("kernelSize").setRange(3, 11).setIncrement(2);
                params->addInt("iterations").setRange(1, 20);
            }
            params->endGroup();  // blur
            params->startGroup("median");
            {
                params->addBool("enabled");
                params->addInt("kernelSize").setRange(3, 11).setIncrement(2);
                params->addInt("iterations").setRange(1, 20);
            }
            params->endGroup();  // median
        }
        params->endGroup();  // pre-processing
        
        params->startGroup("optical flow");
        {
            params->addBool("enabled");
            params->addNamedIndex("method").setLabels(3, "Lucas-Kanade", "Horn–Schunck", "Buxton–Buxton");
            params->addFloat("velMult").setRange(0, 10);
            params->addInt("windowSize").setRange(1, 11).setIncrement(2);
        }
        params->endGroup();	// optical flow
    }
    params->endGroup();	// vision
    
    
    
    // ACCESSING PARAMETERS IN A GROUP
    // Option1: The simple, but long-winded way, access each parameter from the group it's in
    params->getGroup("vision").get("enabled") = true;
    params->getGroup("vision").getGroup("pre-processing").getGroup("blur").get("iterations") = 1;
    
    
    // Option2: Cache groups, slightly more optimum
    msa::ControlFreak::ParameterGroup &gVision = params->getGroup("vision");
    msa::ControlFreak::ParameterGroup &gVisionPre = gVision.getGroup("pre-processing");
    msa::ControlFreak::ParameterGroup &gVisionPreBlur = gVisionPre.getGroup("blur");
    gVision.get("enabled") = true;
    gVisionPreBlur.get("iterations") = 2;
    
    
    // Option3: List full path (my favorite)
    params->get("vision.enabled") = true;
    params->get("vision.pre-processing.blur.iterations") = 3;
    
    
    // TESTERS
    params->startGroup("Testers");
    {
        params->startGroup("floats");
        {
            params->addFloat("no clamp, no snap").setRange(0, 5).setIncrement(0.1);
            params->addFloat("yes clamp, no snap").setRange(0, 5).setIncrement(0.1).setClamp(true);
            params->addFloat("yes clamp, yes snap").setRange(0, 5).setIncrement(0.1).setClamp(true).setSnap(true);
            params->addFloat("no clamp, yes snap").setRange(0, 5).setIncrement(0.1).setClamp(false).setSnap(true);
        }
        params->endGroup();
        
        params->startGroup("ints");
        {
            params->addInt("no clamp, no snap").setRange(0, 100).setIncrement(5);
            params->addInt("yes clamp, no snap").setRange(0, 100).setIncrement(5).setClamp(true);
            params->addInt("yes clamp, yes snap").setRange(0, 100).setIncrement(5).setClamp(true).setSnap(true);
            params->addInt("no clamp, yes snap").setRange(0, 100).setIncrement(5).setClamp(false).setSnap(true);
        }
        params->endGroup();
    }
    params->endGroup();
    
    
    
    
    //--------------------------------------------------------------
    // clear all parameters (so we have a clean slate to carry on)
    params->clear();
    
    
    
    
    params->startGroup("particle system"); {
        params->addInt("count").setRange(1, 20).setValue(5);
        params->startGroup("emitter"); {
            params->addFloat("x").setRange(0, ofGetWidth()).setValue(ofGetWidth()/2);
            params->addFloat("y").setRange(0, ofGetHeight()).setValue(ofGetHeight()/2);
            params->addFloat("radius").setRange(0, 100).setValue(20);
        } params->endGroup();
        params->startGroup("physics"); {
            params->addFloat("maxEmitVelocity").setRange(0, 100).setValue(30);
            params->addFloat("maxRotSpeed").setRange(0, 10).setValue(5);
            params->addFloat("gravity").setRange(-1, 1).setValue(0.03);
            params->addFloat("friction").setRange(0, 1).setValue(0.05);
        } params->endGroup();
        params->startGroup("age"); {
            params->addFloat("min age").setRange(1, 10).setValue(1);
            params->addFloat("max age").setRange(1, 10).setValue(5);
        } params->endGroup();
        
        params->startGroup("display options"); {
            params->addNamedIndex("shape type").setLabels(3, "circle", "rectangle", "triangle");
            params->addBool("fill").setValue(true);
            params->startGroup("size"); {
                params->addFloat("x").setRange(0, 200).setValue(50);
                params->addFloat("y").setRange(0, 200).setValue(50);
            } params->endGroup();
        } params->endGroup();
        
        params->addBang("randomize");
    }
    params->endGroup();
    
    
    // you can add complex types
    //    params->addVec3f("pos1");
    //    params->addVec3f("pos2").setValue( ofVec3f(0.1, 0.2, 0.3) );
    //    params->addVec3f("pos3").setValue( ofVec3f(1.5, 2.5, 3.5) ).setRange( ofVec3f(-10, -20, -20), ofVec3f(100, 200, 300) );
    
    
    
    
    // you can create groups and add any parameters to that group
    
   gui.addPage(params);
	gui.setDefaultKeys(true);
	gui.show();
    
    
    ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
    
    //	params->loadFromInfo();
}


//--------------------------------------------------------------
void testApp::update() {
    params->update();
    
    // resize vector if nessecary
    int count = params->get("particle system.count");
    if(balls.size() != count) {
        ofLogNotice() << "INIT BALLS " << count;
        balls.resize(count);
    }
    
    
    if((bool)params->get("particle system.randomize")) {
        params->get("particle system.emitter.x").setRandom();
        params->get("particle system.emitter.y").setRandom();
        params->get("particle system.emitter.radius").setRandom();
        params->get("particle system.physics.maxEmitVelocity").setRandom();
        params->get("particle system.physics.maxRotSpeed").setRandom();
        params->get("particle system.physics.gravity").setRandom();
        params->get("particle system.physics.friction").setRandom();
        params->get("particle system.age.min age").setRandom();
        params->get("particle system.age.max age").setRandom();
        params->get("particle system.display options.fill").setRandom();
        params->get("particle system.display options.size.x").setRandom();
        params->get("particle system.display options.size.y").setRandom();
        params->get("particle system.display options.shape type").setRandom();
    }
    
    // cache relevant values
    ofVec2f emitterPos = ofVec2f(params->get("particle system.emitter.x"), params->get("particle system.emitter.y"));
    float emitterRadius = params->get("particle system.emitter.radius");
    float maxEmitVelocity = params->get("particle system.physics.maxEmitVelocity");
    float maxRotSpeed = params->get("particle system.physics.maxRotSpeed");
    float gravity = params->get("particle system.physics.gravity");
    float friction = params->get("particle system.physics.friction");
    float minAge = params->get("particle system.age.min age");
    float maxAge = params->get("particle system.age.max age");
    
    
    // iterate all balls. update position, rotation and speed
    for(int i=0; i<balls.size(); i++) {
        Ball &b = balls[i];
        b.pos += b.vel;
        b.vel.y += gravity;
        b.vel -= b.vel * friction;
        b.rot += b.rotSpeed;
        
        // if offscreen, reset
        if(ofGetElapsedTimef() > b.dieTime || !ofInRange(b.pos.x, 1, ofGetWidth()) || !ofInRange(b.pos.y, 1, ofGetHeight())) {
            b.dieTime = ofGetElapsedTimef() + ofRandom(minAge, maxAge);
            b.pos = emitterPos + ofVec2f(ofRandom(-emitterRadius, emitterRadius), ofRandom(-emitterRadius, emitterRadius));
            b.vel = ofVec2f(ofRandom(-maxEmitVelocity, maxEmitVelocity), 0);
            b.vel.rotate(ofRandom(0, 1080));
            b.rot = ofRandom(360);
            b.rotSpeed = ofRandom(0, maxRotSpeed) * ofSign(ofRandomf());
            b.size = ofVec2f(ofRandomuf(), ofRandomuf());
        }
    }
    
    
    // read from the bool parameters, and update the float parameters if they are true
    // note that parameter 'animated2' had had it's 'clamp' set to true, so it will never go outside of -1...1
    //    if(params->getBool("Testers.doAnimate1")) params->get("Testers.animated1") = sin(ofGetElapsedTimef()) * 2;
    //    if(params->getBool("Testers.doAnimate2")) params->get("Testers.animated2") = sin(ofGetElapsedTimef()) * 2;
    
    // 'trackTester' is a normal variable, which we had set to sync to the parameter 'trackTester'
    // if we write to this variable, the gui updates
    //    fvar1 = sin(ofGetElapsedTimef());
    
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
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    // draw emitter
    ofVec2f emitterPos = ofVec2f(params->get("particle system.emitter.x"), params->get("particle system.emitter.y"));
    ofNoFill();
    ofCircle(emitterPos, params->get("particle system.emitter.radius"));
    
    // set fill options
    if(params->get("particle system.display options.fill")) ofFill();
    else ofNoFill();
    
    // cache size value
    ofVec2f size = ofVec2f(params->get("particle system.display options.size.x"), params->get("particle system.display options.size.y"));
    
    int shapeType = params->get("particle system.display options.shape type");
    for(int i=0; i<balls.size(); i++) {
        Ball &b = balls[i];
        
        ofPushMatrix();
        ofTranslate(b.pos);
        ofRotate(b.rot);
        ofScale(b.size.x * size.x, b.size.y * size.y, 1);
        
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
            params->saveXmlValues();
            break;
            
		case 'S':
            params->saveXmlSchema();
            break;
            
            
		case 'l':
			params->loadXmlValues();
			break;
			
		case 'L':
			params->loadXmlSchema();
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
