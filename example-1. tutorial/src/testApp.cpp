#include "testApp.h"

#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"
#include "ofxMSAControlFreakGui/src/ofxMSAControlFreakGui.h"


/*
 
 ***** THIS EXAMPLE IS MEANT AS A TUTORIAL. *****
 Start reading here, at the very top of the file, and read linearly down the page

 Look at the #pragma marks for a rough Table Of Contents
 
 
 */


#pragma mark START TUTORIAL

// Create a ParameterGroup
msa::controlfreak::ParameterGroup params;

// this is one of the main Classes of controlfreak and probably the only one you'll ever need to explicitly instantiate
// i.e. almost everything is done through this
// Parameters are NOT sliders, tickshapes, buttons etc.
// They are just the data and properties behind all of that.
// And also functionality to sync to various controllers, save/load presets and a whole bunch of other stuff





// Create a GUI
msa::controlfreak::gui::Gui gui;

// This is a class which can display and interact with Parameters
// There can be many different types of gui's which can display and control Parameters
// This particular one is an opengl gui very similar to ofxSimpleGuiToo. I also have a native Cocoa one etc.
// The Gui class reads all of the (nested) Parameters in a ParameterGroup, and builds a Gui
// it may sound complicated, but it's really really simple






void testApp::setup() {
    //--------------------------------------------------------------
#pragma mark BASIC USAGE
    
    // set the display name for your parameter group
    // this is also the default folder for preset xml files (SO REMEMBER IT FOR WHEN WE COME TO PRESETS)
    params.setName("tutorial");

    
    // creating basic parameters
    params.addFloat("myfloat");  // create a float Parameter: can be any real number
    params.addInt("myint");      // create an int Parameter: can be any whole number
    params.addBool("mybool");    // create a bool (toggle) Parameter: can be true or false
    params.addBang("mybang");    // create a bang Parameter: almost identical to Bool, but can only be true for one frame

    
    
    // setting values
    params["myfloat"] = 5.3;
    params["myint"] = 7;
    params["mybool"] = true;
    
    
    
    // getting values
    float f = params["myfloat"];
    int i = params["myint"];
    bool b = params["mybool"];
    
    
    
    // params["parameter name"] actually returns a reference to a msa::controlfreak::Parameter, not a simple number
    // so sometimes when using parameters in expressions ambiguity can occur, to avoid this use a c-style type-cast. e.g.
//    float answer1 = params["myfloat"] * params["myint"];   // compiler is confused so this may not compile, be explicit with types:
    float answer2 = (float)params["myfloat"] *(int)params["myint"]; // this works, compiler knows exactly what to do

    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark SETTING PARAMETER PROPERTIES (WHILE CREATING THE PARAMETER)
    
    // I'm not a big fan of long lists of arguments to functions or methods.
    // e.g. params.addFloat("myfloat", 0, 100, 50, 5, true, false);
    // It's difficult to read, you have no idea what is what, adding more options in the future gets quite confusing and generally it's quite error prone
    // My personal preference is daisy chaining small methods with descriptive names, each of which do very specific things.
    // with auto-complete in most modern IDEs it's very quick to write, and it aids readibility and future expansion
    
    // creating and adding a Parameter actually returns a reference to msa::controlfreak::Parameter
    // so you can call further methods on it to change properties of that Parameter
    params.addFloat("myfloat2").set(0.7);               // set value (this is equivalent to using =)
    params.addFloat("myfloat3").setRange(-1, 1);        // set min/max values
    params.addFloat("myfloat4").setIncrement(0.2);      // set increment value (when you use keyboard, or +/- buttons on the slider, how much to increment the value by)
    params.addFloat("myfloat5").setSnap(true);          // if snap is enabled, values always snap to the increment value (even if you excplicitly assign values to it)
    params.addFloat("myfloat6").setClamp(true);         // if clamp is enabled, values cannot be outside the set range
    
    
    
    // you can daisy chain these methods, in any order, and use as little or as many of them as you need.
    params.addFloat("myfloat7").setRange(0, 50).setClamp(true);
    params.addInt("myint2").setIncrement(5).setSnap(true).set(30);
    
    
    
    // the defaults are (i.e. if you don't explicitly call any of these methods, this is what will be assumed):
    params.addFloat("myfloat8").setRange(0, 1).set(0).setClamp(false).setIncrement(0.01).setSnap(false);
    params.addInt("myint3").setRange(0, 100).set(0).setClamp(false).setIncrement(1).setSnap(false);

    
    
    

    
    //--------------------------------------------------------------
#pragma mark CHANGING PARAMETER PROPERTIES (FOR EXISTING PARAMETERS)
    // remember that params["parameter name"] actually returns a reference to a msa::controlfreak::Parameter, not a simple number
    // so you can call all msa::controlfreak::Parameter methods on it
    // i.e. you can also change properties for existing parameters
    // (the following code assumes parameter 'myfloat' already exists)
    params["myfloat"].setRange(0, 100);
    params["myfloat"].set(50);
    params["myfloat"].setIncrement(5);
    params["myfloat"].setClamp(true);
    
    
    
    // of course daisy chaining the methods still work
    params["myfloat"].setRange(0, 1000).set(50).setIncrement(10).setSnap(false).setClamp(true);
    
    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark SETTING AND GETTING PARAMETER VALUES IN DIFFERENT RANGE
    // sometimes you want to set or get the value in a different range,

    // e.g. if we want the value of Parameter 'myfloat' mapped to 0...127 (so we can send it as a midi controller value)
    // we can use ofMap to map from the Parameters min/max value range to the desired range
    
    int mappedValue1 = ofMap(params["myfloat"], params["myfloat"].getMin(), params["myfloat"].getMax(), 0, 127);
    
    // there is a much simpler way of doing that:
    int mappedValue2 = params["myfloat"].getMappedTo(0, 127);   // much easier to read, quicker, and less likely for typos / errors
    
    
    
    
    
    
    // similarly, if we have a value in a specific range, and we want to assign it to the Parameter mapping it to the Parameters range in the process.
    // e.g. assume we have the value '50', which is in the range 0...127 (e.g. a midi controller value)
    // we want to assign this to Parameter 'myfloat', which is in a different range
    params["myfloat"] = ofMap(50, 0, 127, params["myfloat"].getMin(), params["myfloat"].getMax());
    
    // there is a much simpler way of doing that:
    params["myfloat"].setMappedFrom(50, 0, 127);    // much easier to read, quicker, and less likely for typos / errors
    
    
    
    
    
    
    // similarly, normalized versions of this exist, if you know the other range to be 0...1
    
    // gets the value of Parameter 'myfloat' as normalized between 0...1
    float normalizedValue = params["myfloat"].getNormalized();
    
    // sets the value of Parameter 'myfloat' from a normalized value and maps it to it's own range
    params["myfloat"].setNormalized(0.3);
    
    
    
    
    // NOTE:
    // Since the parameter may have clamping disabled, it's value may be outside it's own range
    // so when getting the value using getMappedTo, or getNormalized, you may get a value which is outside of the target range too
    // you can provide an optional (bool) parameter to these to clamp the return value.
    
    // e.g.
    params.addFloat("unclamped float").setRange(0, 100).setClamp(false);

    params["unclamped float"] = 150;    // this is fine, the Parameter is unclamped

    float fret;
    fret = params["unclamped float"].getNormalized();   // this will return 1.5
    fret = params["unclamped float"].getMappedTo(2000, 3000);   // this will return 3500
    fret = params["unclamped float"].getNormalized(true);   // this will return 1 (clamped)
    fret = params["unclamped float"].getMappedTo(2000, 3000);   // this will return 3000 (clamped)
    
    // the original Parameter is still unclamped
    fret = params["unclamped float"];  // this will return 150;
    
    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark NAMED INDEXES
    // NamedIndex's are a list of strings / options. Basically the data for a dropdownbox, listbox, or radio options
    // There are a few different ways of creating them, all giving identical results
    
    // Option 1: this is one way of adding a named-index parameter (using variable argument lists)
    params.addNamedIndex("animals").setLabels(4, "cow", "camel", "dolphin", "monkey");
    
    
    
    // Option 2: this is one way of adding a named-index parameter (using a traditional C-array of strings)
    string options2[] = {"january", "february", "march", "april", "may"};
    params.addNamedIndex("month").setLabels(5, options2);
    
    
    
    // and another (using stl::vector of strings)
    vector<string> options3;
    options3.push_back("monday");
    options3.push_back("tuesday");
    options3.push_back("wednesday");
    options3.push_back("thursday");
    options3.push_back("friday");
    params.addNamedIndex("days").setLabels(options3);
    
    
    
    // you can change the mode of the NamedIndex
    params.addNamedIndex("size").setLabels(5, "small", "medium", "large", "extra large", "mega").setMode(msa::controlfreak::ParameterNamedIndex::kDropdown);
    params.addNamedIndex("color").setLabels(3, "red", "green", "blue").setMode(msa::controlfreak::ParameterNamedIndex::kList);
    params.addNamedIndex("sex").setLabels(3, "male", "female", "other").setMode(msa::controlfreak::ParameterNamedIndex::kOptions);
    // this doesn't actually affect how the Parameter works at all, it's just info for when you add it to a GUI

    
    
    
    
    
    // access data from named index
    // to get the selected index, use the [] operator as you would to get the value out of an int, bool or float Parameter:
    int selectedIndex = params["animals"];  // returns 0-based index of selected item
    
    
    
    // to get the selected item label involves a tiny bit more work:
    // params["animals"] returns a normal msa::controlfreak::Parameter, not a msa::controlfreak::ParameterNamedIndex
    // so to access msa::controlfreak::ParameterNamedIndex specific methods, you need to type-cast it
    msa::controlfreak::ParameterNamedIndex &p = (msa::controlfreak::ParameterNamedIndex&)params["animals"];
    string selectedLabel1 = p.getSelectedLabel();
    
    
    
    // actually the ParameterGroup has a get<>() template method to return a correctly type-cast Parameter
    string selectedLabel2 = params.get<msa::controlfreak::ParameterNamedIndex>("animals");
    
    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark GROUPS
    // you can nest ParameterGroups inside ParameterGroups
    // any parameter added after startGroup(....) and before the corresponding endGroup() will be created in that group
    params.addFloat("rootvar");       // this goes in the root of params
    params.startGroup("particles"); // create a group called 'particles', now this becomes the active group for following Parameters
        params.addBool("enabled");  // 1st Parameter in the ParameterGroup 'particles'
        params.addInt("count");     // 2nd Parameter in the ParameterGroup 'particles'
        params.addFloat("size");    // 3rd Parameter in the ParameterGroup 'particles'
    params.endGroup();          // finish the group
    params.addFloat("rootvar2");  // this goes back in the root of params

    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark NESTED GROUPS
    // You can even create Groups inside Groups inside Groups ....
    // Parameter names MUST be unique ONLY within the groups they are in
    // (the { } curly braces are not needed. I'm only using that to automate the code indenting to help visualize the structure in xcode)
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

    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark ACCESSING PARAMETERS IN A GROUP
    // Option 1: List full path (my favorite way)
    params["vision.enabled"] = true;
    params["vision.pre-processing.blur.iterations"] = 3;
    
    
    
    // Option 2: The above is almost identical to the following, the long-winded way, access each parameter from the group it's in
    // I never use this way
    params.getGroup("vision").get("enabled") = true;
    params.getGroup("vision").getGroup("pre-processing").getGroup("blur").get("iterations") = 1;
    
    
    
    // Option 3: Cache groups. if you are going to access lots of the same parameters from the same group, it makes sense to cache it in a variable
    msa::controlfreak::ParameterGroup &visionPreBlurGroup = params.getGroup("vision.pre-processing.blur");
    visionPreBlurGroup["enabled"] = true;
    visionPreBlurGroup["kernelSize"] = 7;
    visionPreBlurGroup["iterations"] = 17;

    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark CHECKING IF A PARAMETER HAS CHANGED
    // A very easy way to see if a value of a Parameter has changed is to use the hasChanged method
    
    // e.g.
    // in App::setup() let's create an integer Parameter for number of particles
    params.addInt("particle count").setRange(0, 1000000);
    
    // in App::update() check to see if this value has changed, if it has, reallocate particle array
    if(params["particle count"].hasChanged()) {
        // code to reallocate particle array with the new particle count
    }
    
    // NOTE:
    // for the above to work, you need to call msa::controlfreak::update() in your app's update() function
    // I may remove this requirement and register the msa::controlfreak::update() method to be called automatically every frame, I haven't decided yet
    
    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark CHECKING IF ANY PARAMETER IN A GROUP HAS CHANGED
    // Sometimes you need to check if ANY Parameter in a group has changed
    // then you can just use the hasChanged() method on the group
    
    // e.g.
    // in App::setup() let's create a bunch of initialization parameters
    params.startGroup("fbo init parameters");
    {
        params.addInt("width").setRange(0, 4096);
        params.addInt("height").setRange(0, 4096);
        params.addNamedIndex("type").setLabels(4, "RGB", "RGBA","RGBA16F", "RGBA32F");
        params.addInt("numSamples").setRange(0, 8);
    } params.endGroup();
    
    if(params["fbo init parameters"].hasChanged()) {
        // code to reallocate fbo with the new init parameters
    }
    
    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark TRACKING VARIABLES
    // by default controlfreak keeps track of all values internally, i.e. you don't need to pass it a variable (as you did in ofxSimpleGuiToo)
    // however if you like that functionality, you can also assign an external variable, which is kept track of and kept in sync, at no performance cost
    // controlfreak simply points it's internal data pointer to the external variable (instead of an internal one), so they share the same memory
    // (the following code assumes parameter 'myfloat' already exists)
    
    float var1 = 0;
    params["myfloat"].trackVariable(&var1); // params['myfloat'] and var1 are now internally using the same memory storage
    
    
    
    // modify variable 'var1' and 'mytestvar' will also be instantly updated
    var1 = 15;
    ofLogNotice() << (float)params["myfloat"];  // this will print 15
    
    
    
    // or modify parameter 'myfloat' and the variable 'var1' will be instantly updated
    params["myfloat"] = 25;
    ofLogNotice() << var1;  // this will print 25
    
    
    
    // so all clamping, snapping etc. constraints apply to var1 as well
    params["myfloat"].setRange(0, 50).setClamp(true).setIncrement(5).setSnap(true);
    params["myfloat"] = 33;     // will snap to 35, and var1 will also be affected
    ofLogNotice() << " var1 : " << var1 << ", params['myfloat'] : " << (float)params["myfloat"];

    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark ADDING SENDERS AND RECEIVERS
    // a 'Sender' is a controller which is sent when the parameter is changed.
    // e.g.
//    params["myfloat"].addSender(new msa::controlfreak::MidiController); 
    
    
    //--------------------------------------------------------------
#pragma mark PRESETS: SAVING AND LOADING ALL VALUES IN A GROUP
    // you can save and load values in a parameter group
    
    // this will save / load the values to the default file in the default folder: data/ofxMSAControlFreak/[name of group]/default.xml
    // i.e. data/ofxMSAControlFreak/tutorial/default.xml    (remember we gave 'params' a name of 'tutorial' at the very start of this tutorial)
    // any folders will be created as nessecary
    params.saveXmlValues();
    params.loadXmlValues();
    
    
    
    // this will save / load the values to the specified filename in the default folder: data/ofxMSAControlFreak/[name of group]/[name of file].xml
    // i.e. data/ofxMSAControlFreak/tutorial/bestsettings.xml    (remember we gave 'params' a name of 'tutorial' at the very start of this tutorial)
    // any folders will be created as nessecary
    params.saveXmlValues("bestsettings");
    params.loadXmlValues("bestsettings");
    
    
    
    // this will save / load the values to the specified filename at the specified relative path (relative to the data folder)
    // i.e. data/mypath/bestsettings.xml
    params.saveXmlValues("mypath/bestsettings");
    params.loadXmlValues("mypath/bestsettings");
    
    
    
    // this will save / load the values to the specified filename at the specified absolute path
    // i.e. /mypath/bestsettings.xml
    params.saveXmlValues("/mypath/bestsettings");
    params.loadXmlValues("/mypath/bestsettings");

    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark PRESETS: SAVING AND LOADING ALL VALUES IN A SUB-GROUP
    // remember that any Group you create with startGroup()/endGroup(), is a ParameterGroup just like your root (i.e. params)
    // so the same methods will apply
    // i.e. you can save and load values for any sub-group, or even a sub-group of a sub-group etc.
    
    // this will save / load the values to the default file in the default folder: data/ofxMSAControlFreak/[full path of group]/default.xml
    // the full path of the group is analagous to a file path, just list all of the parents starting at the root
    // ie. data/ofxMSAControlFreak/tutorial/vision/default.xml
    // any folders will be created as nessecary
    params.getGroup("vision").saveXmlValues();
    params.getGroup("vision").loadXmlValues();
    
    
    
    // data/ofxMSAControlFreak/tutorial/vision/pre-processing/blur/default.xml
    // any folders will be created as nessecary
    params.getGroup("vision.pre-processing.blur").saveXmlValues();
    params.getGroup("vision.pre-processing.blur").loadXmlValues();

    
    
    // the rest of the rules of default filenames and paths are identical to saving / loading the root

    // this will save / load the values to the specified filename in the default folder
    // i.e. data/ofxMSAControlFreak/tutorial/vision/bestsettings.xml
    // any folders will be created as nessecary
    params.getGroup("vision").saveXmlValues("bestsettings");
    params.getGroup("vision").loadXmlValues("bestsettings");
    
    
    
    // this will save / load the values to the specified filename at the specified (relative) path
    // i.e. data/mypath/bestsettings.xml
    params.getGroup("vision").saveXmlValues("mypath/bestsettings");
    params.getGroup("vision").loadXmlValues("mypath/bestsettings");
    
    
    
    // this will save / load the values to the specified filename at the specified (absolute) path
    // i.e. /mypath/bestsettings.xml
    params.getGroup("vision").saveXmlValues("/mypath/bestsettings");
    params.getGroup("vision").loadXmlValues("/mypath/bestsettings");
    
    
    
    
    
    
    //--------------------------------------------------------------
#pragma mark SCHEMA: SAVING AND LOADING SCHEMA
    // you can also save and load the schema of parameters, this is the whole structure and properties of the ParameterGroup, including
    // what parameters there are, what are their types, what are their ranges, snap/clamp enable states,
    // what are the labels for any NamedIndices, what groups are there etc.
    // basically everything you wrote with code in creating and setting up the ParameterGroup, stored in an XML
    // this can be used to re-construct the ParameterGroup (and related GUI) by simply loading this XML, perhaps even on a different computer
    // or modify the XML by hand (or by other means), and load in runtime to rebuild your ParameterGroup (and related GUI)

    
    
    // the rules of default paths and filenames is identical to saveXmlValues() and loadXmlValues() except for schemas, '-schema' is added to the default filename
    // i.e. this will save / load schema from data/ofxMSAControlFreak/[name of group]/default-schema.xml
    params.saveXmlSchema();
    params.loadXmlSchema();
    
    

    
    
    
    //--------------------------------------------------------------
#pragma mark (ADVANCED) ERROR HANDLING
    
    // Parameter names used must be unique!
    // trying to add a Parameter with a name that already exists will throw an exception
    // (initially I made it fail silently and just return the existing Parameter, but I found an exception made it much simpler to debug)
    params.addFloat("a test var");
//    params.addInt("a test var");    // if this is uncommented, it will throw an exception
    
    
    
    
    
    
    // to avoid the exception and manage this at runtime, you can use try / catch
    try {
//        params.addInt("a test var");
    } catch (invalid_argument e) {
        cout << e.what() << endl;
    }
    
    
    
    // Accessing a parameter which doesn't excist will throw an exception
    float fspeed;
//    fspeed = params["speed"];      // if this is uncommented, it will throw an exception
    
    
    
    // to avoid the exception and manage this at runtime, you have two options
    // Option 1: use try / catch
    try {
        fspeed = params["speed"];
    } catch (invalid_argument e) {
        cout << e.what() << endl;
    }
    
    
    
    // Option 2: use the getPtr() method to get a pointer to the Parameter (instead of a reference), and check against null
    if(params.getPtr("speed") != NULL) {    // if 'speed' doesn't exist, this will be NULL
        fspeed = params["speed"];       // ... and this code won't run
    } else {
        fspeed = 0;
    }
    
    
    
    // a slightly more efficient way of doing the above is to look for the 'speed' parameter only once:
    msa::controlfreak::Parameter *pspeed = params.getPtr("speed");
    if(pspeed != NULL) {
        fspeed = pspeed->value();
    } else {
        fspeed = 0;
    }

    
    
    

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
