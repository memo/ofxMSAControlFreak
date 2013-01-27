#include "testApp.h"

#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"


/*
 
 ***** THIS EXAMPLE IS MEANT AS A TUTORIAL. *****
 Start reading here, at the very top of the file, and read linearly down the page
 
 
 */


// This is a ParameterGroup, everything is done through this
// Parameters are NOT sliders, tickboxes, buttons etc.
// They are just the data and properties behind all of that.
// And also functionality to sync to various controllers, save/load presets and a whole bunch of other stuff
msa::ControlFreak::ParameterGroup params;


// This is a class which can display and handle the interactivity of Parameters
// There can be many different types of gui's which can display and control Parameters
// This particular one is an opengl gui very similar to ofxSimpleGuiToo. I also have a native Cocoa one etc. 
msa::ControlFreak::gui::Gui gui;


//--------------------------------------------------------------
// CREATING PARAMETERS
void tutorial_1a() {
    
    ofLogNotice() << "TUTORIAL 1";
    
    // All Parameters are created via the 'add' methods of a ParameterGroup
    params.addFloat("float1");  // float: can be any real number
    params.addInt("int1");      // int: can be any whole number
    params.addBool("bool1");    // bool: can be true or false
    
    
    // CHANGING PROPERTIES ON CREATION
    // while you're adding, you can change various properties
    params.addFloat("float2").set(0.7);     // create and set value. default value for float is 0
    params.addFloat("float3").setRange(-1, 1);              // create and set range. default range for float is 0...1
    params.addFloat("float4").setIncrement(0.2);            // create and set increment value (e.g. if you use up/down on keyboard)
    params.addFloat("float5").setIncrement(0.2).setSnap(true);  // create and enable snap, so even if you use mouse or any other means, values always snap
    
    params.addInt("int2").set(17);           // create and set value. default value for int is 0
    params.addInt("int3").setRange(-10, 10);                // create and set range. default range for int is 0...100
    params.addInt("int4").setIncrement(5);                  // create and set increment value (e.g. if you use up/down on keyboard)
    params.addInt("int5").setIncrement(5).setSnap(true);    // create and enable snap, so even if you use mouse or any other means, values always snap
    
    params.addBool("a toggle").set(true);                 // create and set value. default value for bool is 0
    params.addBang("a bang");                       // create and enable momentary bool (i.e. a button, or 'bang')
    params.addBool("another bang").setMode(msa::ControlFreak::ParameterBool::kBang);  // create a bool, and later change it to be a bang
    params.addBool("a push button").setMode(msa::ControlFreak::ParameterBool::kPush);  // create a bool, and later change it to be a push button
    
    
    // NOTE: The Parameter names used must be unique!
    // this will throw an exception and break execution if the try/catch is commented out
    // (initially I made it fail silently and just return the existing Parameter, but I found an exception made it much simpler to debug)
    try {
        params.addInt("int2");  // this will throw an exception because 'int2' already exists
    } catch (invalid_argument e) {
        cout << e.what() << endl;
    }
    
    
    // Daisy chaining methods
    // as you've propbably noticed, all property methods can be daisy chained, and in any order
    params.addFloat("float6").setRange(0, 1000).set(500).setClamp(true).setIncrement(10).setSnap(true);
    
    // ... but are evaluated left to right, so if you try to set a high value before setting the range, it wont work
    // e.g. in this example first clamping is enabled, then the value is set to 500, then the range is set to 0-100, so the value is clamped to 100
    params.addFloat("float7").setClamp(true).set(500).setRange(0, 100).setIncrement(10).setSnap(true);
}


//--------------------------------------------------------------
// ACCESS PARAMETERS AND VALUES
void tutorial_1b() {
    ofLogNotice() << "TUTORIAL 1b";
    
    
    // CHANGING PROPERTIES AFTER CREATION
    // the addXXXX methods used above create the Parameter and change the properties at the same time
    // If you want to change properties AFTER creating the Parameter you can use get methods of ParameterGroup
    params.get("float1").setRange(0, 100);
    params.get("float1").set(50);
    params.get("float1").setIncrement(5);

    
    // you can also use the [] operator, it's identical to get(...)
    params["float1"].setRange(0, 100);
    params["float1"].set(50);
    params["float1"].setIncrement(5);
    
    
    
    // of course daisy chaining the property methods still work
    params["float1"].setRange(0, 1000).set(50).setIncrement(10).setSnap(false);
    
    
    
    // GETTING VALUES
    // to extract the value, simply use the above methods (both are identical), and use a c-style type-cast if nessecary
    
    float f1 = params.get("float1");
    ofLogNotice() << "value of 'float1': " << f1;
    
    float f2 = params["float2"];
    ofLogNotice() << "value of 'float1': " << f2;
    
    // .get(...) and [] operator actually returns a reference to the whole Parameter
    // sometimes this causes ambiguity, so you may need to use a type-cast
    ofLogNotice() << "value of 'float2': " << (float)params.get("float2");  // this works
    //    ofLogNotice() << "value of 'float2': " << params.get("float2");  // but this will not compile
    
    // or
    float f3 = (float)params.get("float1") * (float)params.get("float2");   // this works
//    float f4 =params.get("float1") * params.get("float2");   // but this will not compile

    
    
    // SETTING VALUES
    
    // you saw previously you can use set method to set the value
    params["float1"].set(12);
    ofLogNotice() << "new float1 value: " << (float)params.get("float1");
    
    // you can actually use the '=' operator instead of set. they are identical
    params["float2"] = 0.5;    // identical to using 'set(0.5)
    ofLogNotice() << "new float2 value " << (float)params["float2"];
    
    params["float3"] = (float)params["float1"] * (float)params["float2"];
    ofLogNotice() << "new float3 value " << (float)params["float3"];
}


//--------------------------------------------------------------
// TRACKING EXTERNAL VARIABLES
void tutorial_1c() {
    ofLogNotice() << "TUTORIAL 1c";
    
    // by default ControlFreak keeps track of all values internally.
    // however you can also assign an external variable, which is kept track of and kept in sync, at (virtually) no performance cost
    // ControlFreak simply points it's internal data pointer to the external variable, so they share the same memory
    
    
    // e.g. params['testvar'] and var1 are internally using the same memory storage, so any modifications to one affect the other
    static float var1 = 0;
    params.addFloat("testvar").trackVariable(&var1);
    
    ofLogNotice() << " var1 : " << var1 << ", params['testvar'] : " << (float)params["testvar"];
    
    // modify variable
    var1 = 15;
    ofLogNotice() << " var1 : " << var1 << ", params['testvar'] : " << (float)params["testvar"];
    
    // modify variable
    params["testvar"] = 25;
    ofLogNotice() << " var1 : " << var1 << ", params['testvar'] : " << (float)params["testvar"];
    
    
    // so all clamping, snapping etc. constrainst apply to var1 as well
    params["testvar"].setRange(0, 50).setClamp(true).setIncrement(5).setSnap(true);
    params["testvar"] = 33;     // will snap to 35, and var1 will also be affected
    ofLogNotice() << " var1 : " << var1 << ", params['testvar'] : " << (float)params["testvar"];
}


//--------------------------------------------------------------
// NAMED INDEXES
void tutorial_1d() {
    ofLogNotice() << "TUTORIAL 1d";

    // NamedIndex's are a list of strings / options. Basically a dropdownbox, listbox, or radio options
    
    // a few different ways of creating them, all giving identical results
    
    // this is one way of adding a named-index parameter (using variable argument lists)
    params.addNamedIndex("animals").setLabels(4, "cow", "camel", "dolphin", "monkey");
    
    // this is one way of adding a named-index parameter (using a traditional C-array of strings)
    string options1[] = {"january", "february", "march", "april", "may"};
    params.addNamedIndex("month").setLabels(5, options1);
    
    // and another (using stl::vector of strings)
    vector<string> options2;
    options2.push_back("monday");
    options2.push_back("tuesday");
    options2.push_back("wednesday");
    options2.push_back("thursday");
    options2.push_back("friday");
    params.addNamedIndex("days").setLabels(options2);
    
    
    // you can change the mode of the NamedIndex
    params.addNamedIndex("size").setLabels(5, "small", "medium", "large", "extra large", "mega").setMode(msa::ControlFreak::ParameterNamedIndex::kDropdown);
    params.addNamedIndex("color").setLabels(3, "red", "green", "blue").setMode(msa::ControlFreak::ParameterNamedIndex::kList);
    params.addNamedIndex("sex").setLabels(3, "male", "female", "other").setMode(msa::ControlFreak::ParameterNamedIndex::kOptions);
}


//--------------------------------------------------------------
// GROUPS
void tutorial_1e() {
    ofLogNotice() << "TUTORIAL 1e";
    
    // you can create Groups inside ParameterGroups
    // any parameter added after startGroup(....) and before corresponding endGroup() will be created in that group
    params.startGroup("particles"); // now this becomes the active group for following Parameters
    params.addBool("enabled");  // 1st Parameter in this Group
    params.addInt("count");     // 2nd Parameter in this Group
    params.addFloat("size");    // 3rd Parameter in this Group
    params.endGroup();          // any future Parameters will now be outside this group, back in the root

    
    // You can even create Groups inside Groups inside Groups .... (until you run out of memory)
}


//--------------------------------------------------------------
void tutorial_1f() {
    ofLogNotice() << "TUTORIAL 1f";

    
    // this shows some how the clamping and snapping works
    // actually in msa::ControlFreak::gui, you can click on each slider to customize and enable/disable it's snap and clamp properties
    params.startGroup("Snap'n'Clamp");
    {
        params.startGroup("floats");
        {
            params.addFloat("no clamp, no snap").setRange(0, 5).setIncrement(0.1);
            params.addFloat("yes clamp, no snap").setRange(0, 5).setIncrement(0.1).setClamp(true);
            params.addFloat("yes clamp, yes snap").setRange(0, 5).setIncrement(0.1).setClamp(true).setSnap(true);
            params.addFloat("no clamp, yes snap").setRange(0, 5).setIncrement(0.1).setClamp(false).setSnap(true);
        }
        params.endGroup();
        
        params.startGroup("ints");
        {
            params.addInt("no clamp, no snap").setRange(0, 100).setIncrement(5);
            params.addInt("yes clamp, no snap").setRange(0, 100).setIncrement(5).setClamp(true);
            params.addInt("yes clamp, yes snap").setRange(0, 100).setIncrement(5).setClamp(true).setSnap(true);
            params.addInt("no clamp, yes snap").setRange(0, 100).setIncrement(5).setClamp(false).setSnap(true);
        }
        params.endGroup();
    }
    params.endGroup();
}


//--------------------------------------------------------------
void tutorial_1g() {
    ofLogNotice() << "TUTORIAL 1g";
    
    // You can even create Groups inside Groups inside Groups .... (until you run out of memory)
    // Parameter names MUST be unique ONLY within the groups they are in
    // (the { } curly braces are not needed. I'm only using that to help with the code indenting to help visualize the structure in xcode)

    params.startGroup("vision");
    {
        params.addBool("enabled");  // note that this parameter is called 'enabled'
        params.addFloat("brightness").setRange(0, 100);
        params.addFloat("contrast").setRange(-100, 100);
        params.addBool("flip x");
        params.addBool("flip y");
        params.addBang("reset");
        
        params.startGroup("pre-processing");
        {
            params.startGroup("blur");
            {
                params.addBool("enabled");  // note we can have another parameter called 'enabled' because it is in a different group
                params.addInt("kernelSize").setRange(3, 11).setIncrement(2);
                params.addInt("iterations").setRange(1, 20);
            }
            params.endGroup();  // blur
            params.startGroup("median");
            {
                params.addBool("enabled");
                params.addInt("kernelSize").setRange(3, 11).setIncrement(2);
                params.addInt("iterations").setRange(1, 20);
            }
            params.endGroup();  // median
        }
        params.endGroup();  // pre-processing
        
        params.startGroup("optical flow");
        {
            params.addBool("enabled");
            params.addNamedIndex("method").setLabels(3, "Lucas-Kanade", "Horn–Schunck", "Buxton–Buxton");
            params.addFloat("velMult").setRange(0, 10);
            params.addInt("windowSize").setRange(1, 11).setIncrement(2);
        }
        params.endGroup();	// optical flow
    }
    params.endGroup();	// vision
    
    
    
    // ACCESSING PARAMETERS IN A GROUP
    
    // Option1: List full path (my favorite way)
    params["vision.enabled"] = true;
    params["vision.pre-processing.blur.iterations"] = 3;

    
    // Option2: The above is almost identical to the following, the long-winded way, access each parameter from the group it's in
    // I never use this way
    params.getGroup("vision").get("enabled") = true;
    params.getGroup("vision").getGroup("pre-processing").getGroup("blur").get("iterations") = 1;
    
    
    // Option3: Cache groups. if you are going to access lots of the same parameters from the same group, it makes sense to cache it in a variable
    msa::ControlFreak::ParameterGroup &gVisionPreBlur = params.getGroup("vision.pre-processing.blur");
    gVisionPreBlur["enabled"] = true;
    gVisionPreBlur["kernelSize"] = 7;
    gVisionPreBlur["iterations"] = 17;
}


//--------------------------------------------------------------
// A PRACTICAL EXAMPLE
void tutorial_2() {
    ofLogNotice() << "TUTORIAL 2";
    
    
    // tabs are just like groups. In fact they are groups, with a flag indicating that it should be considered a new tab
    params.startPage("boxes");
    
    // the above is the same as doing this
    //    params.startGroup("boxes").setMode(msa::ControlFreak::ParameterGroup::kTab);
    
    
    params.addInt("count").setRange(0, 100).setClamp(true);
    
    params.addFloat("speed").setRange(0, 2).setClamp(true);
    
    params.addFloat("a slider");
    
    params.startGroup("max size");
    {
        params.addFloat("width").setClamp(true);
        params.addFloat("height").setClamp(true);
    } params.endGroup();
    
    params.startGroup("spread");
    {
        params.addFloat("width").setClamp(true);
        params.addFloat("height").setClamp(true);
    } params.endGroup();


    params.startGroup("background color");
    {
        params.addInt("r").setRange(0, 255).setClamp(true);
        params.addInt("g").setRange(0, 255).setClamp(true);
        params.addInt("b").setRange(0, 255).setClamp(true);
        params.addBang("randomize");
    } params.endGroup();
}

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
    
    // optionally, set the display name for your parameter group
    // this is also the default folder for the xml files
    params.setName("tutorial");
    

    // fill our parameters
    tutorial_1a();
    tutorial_1b();
    tutorial_1c();
    tutorial_1d();
    tutorial_1e();
    tutorial_1f();
    
    tutorial_2();

    
    // load default values for all parameters
    params.loadXmlValues();

    
    // link the parameters to the gui. The GUI will constuct all the nessecary controls and link each one to the relevant parameters
//    gui.addParameter(params);
    gui.addPage(params);
    
    // default keys are: space (toggle show/hide), numbers (jump to that page in the gui), '[]' (next page / prev page)
	gui.setDefaultKeys(true);
    
//    gui.enableAllEvents();
  
    // if you don't like all the automatic update/draw/mouse/keyboard events being called, you can disableAutoEvents for the gui
    // but if you do, you need to make sure you call the gui update/draw/mouse/keyboard events manually
    // automatic events are enabled by default
//    gui.disableAllEvents();
    
    gui.setPage(2);
}


//--------------------------------------------------------------
void testApp::update() {
    
    // this needs to be called for some things to work such as syncing to external controllers (midi etc), checking for changes, snapping / clamping etc.
    msa::ControlFreak::update();
    
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
//     gui.update();
}

//--------------------------------------------------------------
void testApp::draw() {
    
    // draw something random and colorful
    ofSetRectMode(OF_RECTMODE_CENTER);
    static float t = 0;
    
    t += (float)params["boxes.speed"] * 0.1;
    if(params["boxes.background color.randomize"]) {
        params["boxes.background color.r"].setRandom(); // sets a random number between it's min and max
        params["boxes.background color.g"].setRandom(); // sets a random number between it's min and max
        params["boxes.background color.b"].setRandom(); // sets a random number between it's min and max
    }
    
    ofBackground(params["boxes.background color.r"], params["boxes.background color.g"], params["boxes.background color.b"]);
    
    float maxsizew = (float)params["boxes.max size.width"] * ofGetWidth();
    float maxsizeh = (float)params["boxes.max size.height"] * ofGetHeight();
    
    float spreadw = (float)params["boxes.spread.width"] * ofGetWidth();
    float spreadh = (float)params["boxes.spread.height"] * ofGetHeight();
    
    if(params["boxes.a slider"].hasChanged()) {
        ofLogNotice() << "'boxes.a slider' has changed";
    }


    int numBoxes = params["boxes.count"];
    for(int i=0; i<numBoxes; i++) {
        float f = t*0.4 + 34.7324 + i * 258.60293;
        ofSetColor(ofNoise(f+92.8274)*255, ofNoise(f+8723.34576)*255, ofNoise(f+4768.976)*255);
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofTranslate(ofSignedNoise(f+7682.28476)*spreadw, ofSignedNoise(f+283.525)*spreadh);
        ofRotate(ofSignedNoise(f*0.3+193.56259)*360);
        ofRect(0, 0, ofSignedNoise(f*0.4+9273.442)*maxsizew, ofSignedNoise(f*0.4+18363.5652)*maxsizeh);
        ofPopMatrix();
    }
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()-100, 30);

    
    // if you've disabled events for the gui, then you need to manually call this
    // if you have gui events enabled (default), then it's unnessecary
//     gui.draw();
}

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
