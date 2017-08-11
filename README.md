ofxMSAControlFreak
=====================================

Introduction
------------
This is a GUI agnostic parameter management system. I.e. It's a system for managing a bunch of parameters (toggles, buttons, ints, floats) with ranges, groups, hierarchies etc. But it doesn't actually draw anything. The idea is you can use this to manage your options or settings (or even, each of your modules can have it's own parameter groups), and then you can use another addon to display on screen as a GUI. E.g. You could display the parameters using a native [Cocoa GUI](https://github.com/memo/ofxMSAParamsCocoa)(unfortunately this is now obselete) or a custom [OpenGL GUI](https://github.com/memo/ofxMSAControlFreakGui), or my current favourite, using [ImGui](https://github.com/ocornut/imgui), with the addon [ofxImGui](https://github.com/jvcleave/ofxImGui). THe bridge that makes that connection is [ofxMSAControlFreakImGui](https://github.com/memo/ofxMSAControlFreakImGui).

The Basic usage is as follows:
```
// Create a ParameterGroup that will host all parameters
msa::controlfreak::ParameterGroup params;

// Add parameters to the group
params.addFloat("myfloat");  // create a float Parameter: can be any real number
params.addInt("myint");      // create an int Parameter: can be any whole number
params.addBool("mybool");    // create a bool (toggle) Parameter: can be true or false
params.addBang("mybang");    // create a bang Parameter: almost identical to Bool, but can only be true for one frame

// set values
params["myfloat"] = 5.3;
params["myint"] = 7;
params["mybool"] = true;

// getting values
float f = params["myfloat"];
int i = params["myint"];
bool b = params["mybool"];

// Set properties on parameters by daisy-chaining methods as desired
params.addInt("myint2").setRange(10, 70).setIncrement(5).setSnap(true).set(30).setTooltip("This is a very important parameter");

// Get mapped to different ranges
params["myfloat"].getMappedTo(0, 127);

// Set mapped from different ranges
params["myfloat"].setMappedFrom(50, 0, 127);

// Manage groups and nest as deep as desired
params.startGroup("vision");
	params.addBool("enabled");  // note that this parameter is called 'enabled'
	params.addFloat("brightness").setRange(0, 100);
	params.addFloat("contrast").setRange(-100, 100);
	params.addBool("flip x");
	params.addBool("flip y");
	params.addBang("reset");

	params.startGroup("preprocessing");
		params.startGroup("blur");
			params.addBool("enabled");  // note we can have another parameter called 'enabled' because it is in a different group
			params.addInt("kernelSize").setRange(3, 11).setIncrement(2);
			params.addInt("iterations").setRange(1, 20);
		params.endGroup();  // blur
	params.endGroup();  // preprocessing
params.endGroup(); // vision

// Access from nested groups via dot notation
params["vision.enabled"] = true;
params["vision.preprocessing.blur.iterations"] = 3;

// or if you have a reference directly to a subgroup, use that
visionPreBlurGroup["enabled"] = true;
visionPreBlurGroup["kernelSize"] = 7;
visionPreBlurGroup["iterations"] = 17;

// if you don't directly have a reference to a subgroup, you can get that too
auto visionPreBlurGroup = params.getGroup("vision.preprocessing.blur");


// Get info the frame that a parameter is changed
if(params["myfloat"].hasChanged()) doSomething();

// or if any value in a group has changed
if(params[vision.preprocessing.blur].hasChanged()) doSomething();


// Save and load presets for all parameters
params.saveXmlValues();
params.loadXmlValues();

params.saveXmlValues("test1");
params.loadXmlValues("test1");

// or any subgroup. Will automatically be saved under a subfolder with the path of the subgroup
// save & load from vision/default.xml
params.getGroup("vision").saveXmlValues();
params.getGroup("vision").loadXmlValues();

// save & load from vision/preprocessing/blur/test1.xml
params.getGroup("vision.preprocessing.blur").saveXmlValues("test1");
params.getGroup("vision.preprocessing.blur").loadXmlValues("test1");


// Or even save and load Schemas at runtime (Which include parameter properties like range, snap or clamp state etc)
params.saveXmlSchema();
params.loadXmlSchema();


// To display, use a bridge of some sort, currently my favourite is ofxMSAControlFreakImGui which uses ofxImGui
gui.begin();
// optionally display other gui stuff

// display all of our params
msa::controlfreak::imgui::draw(params);

// optionally display other gui stuff
gui.end();


```

Motivations
------------
The main motivation is to be able to create, manipulate, save and load parameters / settings as quickly and with as minimal code as possible with maximum flexibility.
1. Separate my data (parameters, options, settings, state etc) from displaying and visualising. So I can display using diferent GUIs, e.g. potentially an opengl renderer, native Cocoa GUI, Qt, Gtk etc.

2. Add a new parameter with as minimal code as possible. E.g. ```params.addInt("my param")``` is enough and is ready to be used (and will automatically be displayed, included in presets saved and loaded, sent and received via Midi/OSC/HTTP etc).

3. Access a parameter with as minimal code as possible. E.g. ```params["my param"]``` is enough.

4. Allow a hierarchy where actions (save / load / display / send / receive etc) can be applied to the entire parameter group, or sub groups. Different modules can have parameters, and they can be joined or treated individually. E.g. 
```

Installation
------------
* Add as a usual openframeworks addon (copy to your <openframeworks>/addons directory and add to your project)
* Make sure your addons folder (e.g. '../../../addons') is in your project's 'header search path' (I believe by default this is set now)


Dependencies
------------
* openFrameworks http://openframeworks.cc/
* ofxXmlSettings (comes with openFrameworks)
* ofxMSAOrderedPointerMap https://github.com/memo/ofxMSAOrderedPointerMap



Licence
-------
The code in this repository is available under the [MIT License](https://secure.wikimedia.org/wikipedia/en/wiki/Mit_license).  
Copyright (c) 2008-2012 Memo Akten, [www.memo.tv](http://www.memo.tv)  
The Mega Super Awesome Visuals Company

