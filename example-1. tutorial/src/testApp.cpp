#include "testApp.h"

#include "ofxMSAControlFreakGui/src/Gui.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"


// this is a ParameterGroup
msa::ControlFreak::ParameterGroup   params;

// this is a GUI
msa::ControlFreak::gui::Gui            gui;


// CREATING PARAMETERS
void tutorial1() {
    
    ofLogNotice() << "TUTORIAL 1";
    
    // All Parameters are created via the addXXXX methods of a ParameterGroup
    // Adding basic value Parameters
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
    
    params.addBool("bool2").set(true);                 // create and set value. default value for bool is 0
    params.addBool("bool3").setMode(msa::ControlFreak::ParameterBool::kBang);                  // create and enable momentary bool (i.e. a button, or 'bang')
    
    // NOTE: The Parameter names used must be unique!
    
    
    // Daisy chaining methods
    // all property methods can be daisy chained in any order
    params.addFloat("float6").setRange(0, 1000).set(500).setClamp(true).setIncrement(10).setSnap(true);
    
    // ... but are evaluated left to right, so if you try to set a high value before setting the range, it wont work
    params.addFloat("float7").setClamp(true).set(500).setRange(0, 1000).setIncrement(10).setSnap(true);
}


// ACCESS PARAMETERS AND VALUES
void tutorial2() {
    ofLogNotice() << "TUTORIAL 2";
    
    // CHANGING PROPERTIES AFTER CREATION
    // the addXXXX methods used above create the Parameter and change the properties at the same time
    // If you want to change properties AFTER creating the Parameter you can use get methods of ParameterGroup instead of addXXXXX
    params.get("float1").setRange(0, 100);
    params.get("float1").set(50);
    params.get("float1").setIncrement(5);
    
    // of course daisy chaining the property methods still work
    params.get("float1").setRange(0, 1000).set(50).setIncrement(10).setSnap(false);
    
    
    
    // you can also use the [...] operator, it's identical to get(...)
    params["float1"].setRange(0, 100);
    params["float1"].set(50);
    params["float1"].setIncrement(5);
    
    
    
    // GETTING VALUES
    // to extract the value, simply use the get method (or [] operator)
    
    float f1 = params.get("float1");
    ofLogNotice() << "value of 'float1': " << f1;
    
    float f2 = params["float2"];
    ofLogNotice() << "value of 'float1': " << f2;
    
    // .get(...) and [] operator actually returns a reference to the whole Parameter
    // sometimes this causes ambiguity, so you need to use a type-cast
    ofLogNotice() << "value of 'float2': " << (float)params.get("float2");  // e.g. this works
    //    ofLogNotice() << "value of 'float2': " << params.get("float2");  // e.g. but this will not compile
}


// SETTING VALUES
void tutorial3() {
    ofLogNotice() << "TUTORIAL 3";
    
    // you saw above you can use set method
    params.get("float1").set(12);
    ofLogNotice() << "new float1 value: " << (float)params.get("float1");
    
    // you can actually use the '=' operator instead of set
    params.get("float1") = 12;    // identical to using 'set(0.5)
    params["float2"] = 5;
    ofLogNotice() << "new float1 value " << (float)params.get("float2");
    ofLogNotice() << "new float2 value " << (float)params["float2"];
    
    
    params["float3"] = (float)params["float1"] * (float)params["float2"];
    ofLogNotice() << "new float3 value " << (float)params["float3"];
}


// tracking external variables
void tutorial4() {
    ofLogNotice() << "TUTORIAL 4";
    
    // you can also assign an external variable, which is kept track of and kept in sync, at no performance cost
    
    // assigning the tracked variable upon Parameter creation (i.e. using addXXXX method)
    
    float var1 = 0;
    
    params.addFloat("param1").trackVariable(&var1);
    
    ofLogNotice() << " var1 : " << var1 << ", param1 : " << (float)params["param1"];
    
    // modify variable
    var1 = 15;
    ofLogNotice() << " var1 : " << var1 << ", param1 : " << (float)params["param1"];
    
    // modify variable
    params["param1"] = 25;
    ofLogNotice() << " var1 : " << var1 << ", param1 : " << (float)params["param1"];
    
}


// NAMED INDEXES
void tutorial5() {
    ofLogNotice() << "TUTORIAL 5";
    
    // this is one way of adding a named-index parameter (i.e. dropbox box or option list)
    string labels[] = {"first option", "another option", "yet another option", "even more", "and last one"};
    params.addNamedIndex("a dropdown").setLabels(5, labels);
    
    // this is another way of adding a named-index parameter
    params.addNamedIndex("animals").setLabels(4, "cow", "camel", "dolphin", "monkey");
}



// GROUPS
void tutorial6() {
    // you can create Groups inside ParameterGroups
    // any parameter added after startGroup(....) and before corresponding endGroup() will be created in that group
    params.startGroup("particles"); // now this becomes the active group for following Parameters
    params.addBool("enabled");  // 1st Parameter in this Group
    params.addInt("count");     // 2nd Parameter in this Group
    params.addFloat("size");    // 3rd Parameter in this Group
    params.endGroup();          // any future Parameters will now be outside this group
    params.addBool("enabled");
    params.startGroup("g2"); // now this becomes the active group for following Parameters
    params.addBool("b1");  // 1st Parameter in this Group
    params.endGroup();          // any future Parameters will now be outside this group
}


void tutorial7() {
    
    // You can even create Groups inside Groups inside Groups .... (until you run out of memory)
    // Parameter names MUST be unique ONLY within the groups they are in
    // (the { } curly braces are not needed. I'm only using that to help with the indenting to help visualize the structure)
    params.startGroup("vision");
    {
        params.addBool("enabled");
        params.addFloat("brightness").setRange(0, 100);
        params.addFloat("contrast").setRange(-100, 100);
        params.addBool("flip x");
        params.addBool("flip y");
        params.addBang("reset");
        
        params.startGroup("pre-processing");
        {
            params.startGroup("blur");
            {
                params.addBool("enabled");
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
    // Option1: The simple, but long-winded way, access each parameter from the group it's in
    params.getGroup("vision").get("enabled") = true;
    params.getGroup("vision").getGroup("pre-processing").getGroup("blur").get("iterations") = 1;
    
    
    // Option2: Cache groups, slightly more optimum
    msa::ControlFreak::ParameterGroup &gVision = params.getGroup("vision");
    msa::ControlFreak::ParameterGroup &gVisionPre = gVision.getGroup("pre-processing");
    msa::ControlFreak::ParameterGroup &gVisionPreBlur = gVisionPre.getGroup("blur");
    gVision.get("enabled") = true;
    gVisionPreBlur.get("iterations") = 2;
    
    
    // Option3: List full path (my favorite)
    params["vision.enabled"] = true;
    params["vision.pre-processing.blur.iterations"] = 3;
}


//--------------------------------------------------------------
void testApp::setup(){
    //    ofSetLogLevel(OF_LOG_VERBOSE);

    // OPTIONAL
    // Set name for our ParameterGroup
	params.setName("ControlFreak Demo");
    
    
    tutorial1();
    tutorial2();
    tutorial3();
    tutorial4();
    tutorial5();
//    tutorial6();
//    tutorial7();
    
    
//    params.startGroup("Snap'n'Clamp");
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

    gui.addPage(&params);
	gui.setDefaultKeys(true);
	gui.show();
    
    
    ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
    //	params.loadFromInfo();
}


//--------------------------------------------------------------
void testApp::update() {
//    params.update();
    // gui.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    // gui.draw();
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
