#pragma once

// ***** THIS EXAMPLE IS MEANT AS A TUTORIAL. *****
// 
// Start reading here, at the very top of the file, and read linearly down the page
//
// Look at the #pragma marks for a rough Table Of Contents
//
// Note that this file in itself will not display anything. In order to display a GUI or something, you will need another addon.
// E.g. https://github.com/memo/ofxMSAControlFreakImGui to display using ImGui https://github.com/ocornut/imgui
// or https://github.com/memo/ofxMSAControlFreakGui to display using my own Gui (I prefer the ImGui version now)
// or I used to have https://github.com/memo/ofxMSAParamsCocoa based on Native Cocoa GUI (but is now very out of date)


//--------------------------------------------------------------
#pragma mark START TUTORIAL

// include the header
#include "ofxMSAControlFreak.h"


//=================================================================================================
//=================================================================================================
//=================================================================================================
class TutorialModule {
public:

    // Declare a ParameterGroup
    // This is the main Class of MSAControlFreak and the only one you'll ever need to explicitly instantiate
    // It will contain a bunch of Parameters (and other ParameterGroups) and almost everything is done through this.
    // Parameters are NOT sliders, tickboxes, buttons etc. They are just the data and properties behind all of that.
    // To display them, you need a GUI wrapper. Any GUI could work with such a minimal wrapper
    msa::controlfreak::ParameterGroup params;

    // just some vars
    vector<ofVec2f> particle_pos;
    vector<ofVec2f> particle_vel;
    vector<ofColor> particle_col;



    //=================================================================================================
    //=================================================================================================
    //=================================================================================================
    void setup() {
        
//--------------------------------------------------------------
#pragma mark BASIC USAGE

        // set the display name for your parameter group
        // this is also the default folder for preset xml files (REMEMBER THIS FOR LATER WHEN WE COME TO PRESETS)
        params.setName("tutorial"); // THIS IS OPTIONAL

        // create some simple parameters
        params.addFloat("myfloat");  // create a float Parameter: can be any real number
        params.addInt("myint");      // create an int Parameter: can be any whole number
        params.addBool("mybool");    // create a bool (toggle) Parameter: can be true or false
        params.addBang("mybang");    // create a bang Parameter: almost identical to Bool, but can only be true for a single frame (like a momentary button)

        // assign values
        params["myfloat"] = 5.3;
        params["myint"] = 7;
        params["mybool"] = true;

        // read back values
        float f = params["myfloat"];
        int i = params["myint"];
        bool b = params["mybool"];

        // NOTE: params["parameter name"] actually returns a reference to a msa::controlfreak::Parameter, not a simple number
        // So when using parameters in expressions, ambiguity may occur, e.g. 
        // float answer1 = params["myfloat"] * params["myint"]; // compiler will get confused and give an error on this
        
        // So explicitly use the value() method
        float answer3 = params["myfloat"].value() * params["myint"].value();

        // or use a cast.
        float answer2 = (float)params["myfloat"] * (int)params["myint"];
        


//--------------------------------------------------------------
#pragma mark SETTING PARAMETER PROPERTIES (WHILE CREATING THE PARAMETER)

        // I'm not a big fan of long lists of arguments to functions or methods. e.g. params.addFloat("myfloat", 0, 100, 50, 5, true, false);
        // i) It's difficult to read, ii) you have no idea what is what, iii) adding more options in the future gets confusing and iv) generally it's quite error prone
        // My personal preference is daisy chaining small methods with descriptive names, each of which do specific things.
        // with auto-complete in most modern IDEs it's very quick to write, and it aids readability and future expansion

        // creating and adding a Parameter actually returns a reference to msa::controlfreak::Parameter
        // so you can call further methods on it to change properties of that Parameter
        params.addFloat("myfloat2").set(0.7);               // set value (this is equivalent to creating the Parameter, and then assigning 0.7 with =)
        params.addFloat("myfloat3").setRange(-1, 1);        // set min and max values (will be used when creating the GUI)
        params.addFloat("myfloat4").setIncrement(0.2);      // set increment value (when you use keyboard, or +/- buttons on the slider, how much to increment the value by)
        params.addFloat("myfloat5").setSnap(true);          // if snap is enabled, values always snap to the increment value (even if you explicitly assign values to it)
        params.addFloat("myfloat6").setClamp(true);         // if clamp is enabled, values cannot be outside the set range
        params.addFloat("myfloat7").setTooltip("I am an important parameter. I do things"); // Tooltip for when mouse hovers over

        // you can also daisy chain these methods, in any order, and use as little or as many of them as you need.
        params.addFloat("myfloat8").setTooltip("I am also important! I also do things").setRange(0, 50).setClamp(false).setSnap(true).setIncrement(0.01);



//--------------------------------------------------------------
#pragma mark CHANGING PARAMETER PROPERTIES (FOR EXISTING PARAMETERS)
        // remember that params["parameter name"] actually returns a reference to a msa::controlfreak::Parameter, not a simple number
        // so you can call all msa::controlfreak::Parameter methods on it. i.e. you can also change properties for existing parameters
        params["myfloat"].setRange(0, 100);
        params["myfloat"].set(50);
        params["myfloat"].setIncrement(5);
        params["myfloat"].setClamp(true);
        params["myfloat"].setTooltip("I was the first Parameter to be created!");

        // of course daisy chaining the methods still work
        params["myfloat"].setRange(0, 1000).set(10).setIncrement(3).setSnap(true).setClamp(false);



//--------------------------------------------------------------
#pragma mark GROUPS
        // You can nest ParameterGroups inside other ParameterGroups
        // any parameter added after startGroup(....) and before the next endGroup() will be created in that group
        params.startGroup("particles");                         // create a group called 'particles', now this becomes the active group for following Parameters
        params.addBool("enabled").set(true);                    // 1st Parameter in the ParameterGroup 'particles'
        params.addInt("count").setRange(10, 500).set(200);     // 2nd Parameter in the ParameterGroup 'particles'
        params.addFloat("radius").setRange(1, 30).set(10);      // 3rd Parameter in the ParameterGroup 'particles'
        params.endGroup();                                      // close the group

        params.startGroup("bgcolor");                           // create a group called 'bgcolor', now this becomes the active group for following Parameters
        params.addInt("red").setRange(0, 255).setRandom();      // initialise with random value in the parameter's range
        params.addInt("green").setRange(0, 255).setRandom();    // initialise with random value in the parameter's range
        params.addInt("blue").setRange(0, 255).setRandom();     // initialise with random value in the parameter's range
        params.endGroup();                                      // close the group



//--------------------------------------------------------------
#pragma mark NESTED GROUPS
        // You can even create Groups inside Groups inside Groups ....
        // Parameter names MUST be unique ONLY within the groups they are in
        // the { } curly braces are not needed. I'm only using that to automate the code indenting to help visualize the structure in my IDE
        params.startGroup("vision");
        {
            params.addBool("enabled");  // note that this parameter is called 'enabled'
            params.addFloat("brightness").setRange(0, 100);
            params.addFloat("contrast").setRange(-100, 100);
            params.addBool("flip x");
            params.addBool("flip y");
            params.addBang("reset");

            params.startGroup("preprocessing");
            {
                params.startGroup("blur");
                {
                    params.addBool("enabled");  // we can have another parameter called 'enabled' because it is in a different group
                    params.addInt("kernelSize").setRange(3, 11).setIncrement(2);
                    params.addInt("iterations").setRange(1, 20);
                }
                params.endGroup();  // ending group blur
                params.startGroup("median");
                {
                    params.addBool("enabled");
                    params.addInt("kernelSize").setRange(3, 11).setIncrement(2);
                    params.addInt("iterations").setRange(1, 20);
                }
                params.endGroup();  // ending group median
            }
            params.endGroup();  // ending group preprocessing

            params.startGroup("optical flow");
            {
                params.addBool("enabled");
                params.addNamedIndex("method").setLabels(3, "Lucas-Kanade", "Horn–Schunck", "Buxton–Buxton"); // more on this later
                params.addFloat("velMult").setRange(0, 10);
                params.addInt("windowSize").setRange(1, 11).setIncrement(2);
            }
            params.endGroup();    // ending group optical flow
        }
        params.endGroup();    // ending group vision



//--------------------------------------------------------------
#pragma mark ACCESSING PARAMETERS IN A GROUP
        // Method 1: List full path using dot notation (my favorite way)
        params["vision.enabled"] = true;
        params["vision.preprocessing.blur.iterations"] = 3;

        // Method 2: The above is almost identical to the following, which is more long-winded to write, and I never use this
        params.getGroup("vision").get("enabled") = true;
        params.getGroup("vision").getGroup("preprocessing").getGroup("blur").get("iterations") = 1;

        // Method 3: Cache groups.
        // if you are going to access lots of parameters from the same group, it might be easier to save a reference to the group
        auto blurParams = params.getGroup("vision.preprocessing.blur");
        blurParams["enabled"] = true;
        blurParams["kernelSize"] = 7;
        blurParams["iterations"] = 17;

        // You can do this from any depth of the hierarchy
        auto prepParams = params.getGroup("vision.preprocessing");
        prepParams["blur.enabled"] = false;
        prepParams["blur.kernelSize"] = 5;
        prepParams["blur.iterations"] = 9;



//--------------------------------------------------------------
#pragma mark SETTING AND GETTING PARAMETER VALUES IN A DIFFERENT RANGE
        // Sometimes you want to set or get the Parameter in a different range,

        // e.g. if you want the value of Parameter 'myfloat' mapped to 0...127 (so you can send it as a midi controller value)
        // you could use ofMap to map from the Parameter's min-max value range to the desired range, but that's long winded:
        int mappedValue1 = ofMap(params["myfloat"], params["myfloat"].getMin(), params["myfloat"].getMax(), 0, 127);

        // instead, there is a convenience method for this:
        int mappedValue2 = params["myfloat"].getMappedTo(0, 127); 


        // Similarly, we can do this the other way, assigning a value from a specific range, mapped to the Parameter's range
        // e.g. assume the value '50' is in the range 0...127 (i.e. a midi controller value)
        // we could assign this to Parameter 'myfloat', which is in a different range using ofMap:
        params["myfloat"] = ofMap(50, 0, 127, params["myfloat"].getMin(), params["myfloat"].getMax());

        // again there is a convenience method for this:
        params["myfloat"].setMappedFrom(50, 0, 127);


        // Normalized versions of this exist, if the source or destination range is 0...1
        // for getting normalised values
        float normValue = params["myfloat"].getNormalized(); 

        // or setting from normalised values
        params["myfloat"].setNormalized(0.3); // maps 0.3 to myfloats own range



        // NOTE:
        // Since the parameter may have clamping disabled, its value may be outside it's own range
        // so when getting the value using getMappedTo, or getNormalized, you may get a value which is outside of the target range
        // you can provide an optional (bool) parameter to clamp the return value.
        // e.g.
        params.addFloat("unclamped float").setRange(0, 100).setClamp(false);

        params["unclamped float"] = 150;    // this is fine, the Parameter is unclamped

        float fret;
        fret = params["unclamped float"].getNormalized();   // this will return 1.5
        fret = params["unclamped float"].getMappedTo(2000, 3000);   // this will return 3500
        fret = params["unclamped float"].getNormalized(true);   // this will return 1 (clamped)
        fret = params["unclamped float"].getMappedTo(2000, 3000, true);   // this will return 3000 (clamped)

        // the original Parameter is still unclamped
        fret = params["unclamped float"];  // this will return 150;



//--------------------------------------------------------------
#pragma mark NAMED INDEXES
        // NamedIndex's are a list of strings or options. Basically the data for a dropdownbox, listbox, or radio options
        // There are a few different methods of creating them, all giving identical results

        // Method 1: Using variable argument lists
        params.addNamedIndex("animals").setLabels(4, "cow", "camel", "dolphin", "monkey");

        // Option 2: Using a traditional C-array of strings
        string options2[] = { "january", "february", "march", "april", "may" };
        params.addNamedIndex("month").setLabels(5, options2);

        // using stl::vector of strings
        vector<string> options3 = { "monday", "tuesday", "wednesday", "thursday", "friday" };
        params.addNamedIndex("days").setLabels(options3);

        // to retrieve the selected *index*, use the [] operator as you normally would
        int selectedIndex = params["animals"];  // returns 0-based index of selected item

        // to retrieve the selected *label* involves a tiny bit more work
        // because params["animals"] returns a Parameter reference, not a ParameterNamedIndex
        // so we can't access ParameterNamedIndex specific methods. 
        // Instead we should use ParameterGroup's get<>() template method
        string selectedLabel1 = params.get<msa::controlfreak::ParameterNamedIndex>("animals").getSelectedLabel();

        // or we can type-cast it manually, but that looks a bit more ugly
        string selectedLabel2 = ((msa::controlfreak::ParameterNamedIndex&)params["animals"]).getSelectedLabel();

        // you can change the (interaction / display) mode of the NamedIndex
        // this doesn't actually affect how the Parameter works, it's just info for when you add it to a GUI
        params.addNamedIndex("color").setLabels(3, "red", "green", "blue").setMode(msa::controlfreak::ParameterNamedIndex::kList);

        // as usual you can use the same method on an already existing NamedIndex
        params.get<msa::controlfreak::ParameterNamedIndex>("animals").setMode(msa::controlfreak::ParameterNamedIndex::kDropdown);
        params.get<msa::controlfreak::ParameterNamedIndex>("month").setMode(msa::controlfreak::ParameterNamedIndex::kOptions);



//--------------------------------------------------------------
#pragma mark PRESETS: SAVING AND LOADING ALL VALUES IN A GROUP
        // you can save & load values in a parameter group
        // any folders will always be created as nessecary

        // save to & load from the default file in default folder: data/ofxMSAControlFreak/[name of group]/default.xml
        // i.e. data/ofxMSAControlFreak/tutorial/default.xml (remember we gave 'params' a name of 'tutorial' at the very start of this tutorial)
        params.saveXmlValues();
        params.loadXmlValues();

        //save to & load from the specified filename in default folder: data/ofxMSAControlFreak/[name of group]/[name of file].xml
        // i.e. data/ofxMSAControlFreak/tutorial/bestsettings.xml <--- This is great for managing multiple presets
        params.saveXmlValues("bestsettings");
        params.loadXmlValues("bestsettings");

        // save to & load from the specified filename at the specified relative path (relative to the data folder)
        // i.e. data/mypath/bestsettings.xml
        params.saveXmlValues("mypath/bestsettings");
        params.loadXmlValues("mypath/bestsettings");

        // save to & load from the specified filename at the specified absolute path
        // i.e. /mypath/bestsettings.xml
        params.saveXmlValues("/mypath/bestsettings");
        params.loadXmlValues("/mypath/bestsettings");



//--------------------------------------------------------------
#pragma mark PRESETS: SAVING AND LOADING ALL VALUES IN A SUB-GROUP
        // remember that any ParameterGroup you create with startGroup() & endGroup(), is a ParameterGroup just like your root (i.e. params)
        // so the same methods will apply
        // i.e. you can save & load values for any sub-group, or even a sub-group of a sub-group etc.
        // again, any folders will always be created as nessecary

        // save to & load from the default file in default folder: data/ofxMSAControlFreak/[full path of group]/default.xml
        // the full path of the group is analagous to a file path, just lists all of the parents starting at the root
        // ie. data/ofxMSAControlFreak/tutorial/vision/default.xml
        params.getGroup("vision").saveXmlValues();
        params.getGroup("vision").loadXmlValues();

        //save to & load from data/ofxMSAControlFreak/tutorial/vision/preprocessing/blur/default.xml
        params.getGroup("vision.preprocessing.blur").saveXmlValues();
        params.getGroup("vision.preprocessing.blur").loadXmlValues();

        // save to & load from data/ofxMSAControlFreak/tutorial/vision/bestsettings.xml
        // this is great for managing multiple presets for different groups and subgroups
        params.getGroup("vision").saveXmlValues("bestsettings");
        params.getGroup("vision").loadXmlValues("bestsettings");



//--------------------------------------------------------------
#pragma mark SCHEMA: SAVING AND LOADING SCHEMA
        // you can also save & load the schema of parameters, this is the whole structure and properties of the ParameterGroup,
        // including what parameters there are, what are their types, what are their ranges, snap & clamp enable states,
        // what are the labels for any NamedIndices, what groups are there etc.
        // basically everything you wrote with code in creating and setting up the ParameterGroup, stored in an XML
        // this can be used to re-construct the ParameterGroup (and related GUI) by simply loading this XML, perhaps even on a different computer
        // or modify the XML by hand (or by other means), and load in runtime to rebuild your ParameterGroup (and related GUI)

        // the rules of paths and filenames is identical to saveXmlValues() and loadXmlValues() except that '-schema' is added to the default filename
        // i.e. this will save & load schema from data/ofxMSAControlFreak/[name of group]/default-schema.xml
        params.saveXmlSchema();
        params.loadXmlSchema();



//--------------------------------------------------------------
#pragma mark (ADVANCED) TRACKING VARIABLES
        // by default, controlfreak keeps track of all values internally, i.e. you don't need to pass it a variable (as you did in ofxSimpleGuiToo)
        // however if you do need to do that for any reason, you can assign an external variable, which is kept track of and kept in sync, at no performance cost
        // controlfreak simply points it's internal data pointer to the external variable (instead of an internal one), so they share the same memory

        static float var1 = 0;
        params["myfloat"].trackVariable(&var1); // params['myfloat'] and var1 are now internally using the same memory storage



//--------------------------------------------------------------
#pragma mark (ADVANCED) ERROR HANDLING
        // Parameter names used must be unique within a ParameterGroup
        // Trying to add a Parameter with a name that already exists will throw an exception
        //    params.addInt("myfloat");    // if this is uncommented, it will throw an exception


        // Accessing a parameter which doesn't excist will also throw an exception
        //float t = params["new var"];      // if this is uncommented, it will throw an exception

        // This will always be logged on the console, so if your program is crashing (i.e. exception), check the console.
        // To avoid the exception and manage this at runtime, you have two methods
        // Method 1: use try / catch
        try {
            float t = params["new var"];
        }
        catch (invalid_argument e) {
            cout << e.what() << endl;
        }

        // Methd 2: use the getPtr() method to get a pointer to the Parameter (instead of a reference), and check against null
        if (params.getPtr("new var") != NULL) {
            float t = params["new var"];
        }
        else {
            // do something else, throw a warning or whatever
        }

    }


    
    //=================================================================================================
    //=================================================================================================
    //=================================================================================================
    void draw() {

//--------------------------------------------------------------
#pragma mark CHECKING IF A PARAMETER HAS CHANGED
        // To see if a value of a Parameter has changed, use the hasChanged method.
        // This will remain true until you call the method to check it. Then it will be cleared, until the value changes again
        // e.g. If number of particles has changed, reinitialise the particle arrays with new particle count
        if (params["particles.count"].hasChanged()) {
            int count = params["particles.count"];
            ofLogNotice() << "Reinitialising particles with " << count;
            particle_pos.resize(count);
            particle_vel.resize(count);
            particle_col.resize(count);

            for (int i = 0; i < count; i++) {
                particle_pos[i].set(ofRandomuf()*ofGetWidth(), ofRandomuf()*ofGetHeight());
                particle_vel[i].set(ofRandomf(), ofRandomf());
                particle_col[i].set(ofRandomuf()*255, ofRandomuf()*255, ofRandomuf()*255);
            }
        }



//--------------------------------------------------------------
#pragma mark CHECKING IF ANY PARAMETER IN A GROUP HAS CHANGED
        // Sometimes you need to check if ANY Parameter in a whole group has changed
        // then you can just use the hasChanged() method on the entire group
        // e.g. if any of the background colors have changed, change the background color
        if (params["bgcolor"].hasChanged()) {
            ofLogNotice() << "Changing background color";
            ofBackground(params["bgcolor.red"], params["bgcolor.green"], params["bgcolor.blue"]);
        }



//--------------------------------------------------------------
        // update and draw particles if enabled
        if (params["particles.enabled"]) {

            // cache radius so we don't have to look it up loads of times in the loop
            float radius = params["particles.radius"];

            for (int i = 0; i < particle_pos.size(); i++) {
                auto& p = particle_pos[i]; // reference to position
                auto& v = particle_vel[i]; // reference to velocity
                auto& c = particle_col[i]; // reference to color

                // move particle
                p += v;

                // bounce off edges
                if (p.x > ofGetWidth()) { p.x = ofGetWidth(); v.x *= -1; } else if (p.x < 0) { p.x = 0; v.x *= -1; }
                if (p.y > ofGetHeight()) { p.y = ofGetHeight(); v.y *= -1; } else if (p.y < 0) { p.y = 0; v.y *= -1; }

                // draw
                ofSetColor(c);
                ofCircle(p.x, p.y, radius);
            }
        }
    }
};
