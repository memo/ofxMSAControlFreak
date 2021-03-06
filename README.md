ofxMSAControlFreak
=====================================

Introduction
------------
A GUI agnostic parameter management system for openFrameworks. I.e. For managing a bunch of parameters (toggles, buttons, ints, floats, dropdowns etc.) with ranges, groups, hierarchies etc. But it doesn't actually draw anything. The idea is that you can use this to manage your options or settings (or even, each of your modules can have its own parameter groups or hierarchies of options), and then you can save / load / manage presets for different groups of options, and use another lightweight wrapper addon to display on screen as a GUI (which could be on another computer as you could send the XML schema over the network). 

Currently I have a custom opengl gui for this ([ofxMSAControlFreakGui](https://github.com/memo/ofxMSAControlFreakGui)), but I now prefer to use [ofxMSAControlFreakImGui](https://github.com/memo/ofxMSAControlFreakImGui) which is a very lightweight wrapper for [ImGui](https://github.com/ocornut/imgui) (using [ofxImGui](https://github.com/jvcleave/ofxImGui)). I also used to have a native [Cocoa GUI](https://github.com/memo/ofxMSAParamsCocoa), but that is currently very out of date. One could easily write Cocoa, GTK, Qt, HTML5 etc. wrappers. 

Motivations
------------
The main motivation is to be able to create, manipulate, save and load parameters (options / settings) as quickly and with as minimal code as possible with maximum flexibility. Goals are:
1. Separate my data (i.e. parameters, options, settings, state etc) from displaying / visualising. So I can display using different GUIs, or send the schema to another computer for display.

2. Add a new parameter with as minimal code as possible. E.g. ```params.addInt("my param")``` is enough and is ready to be used (will automatically be displayed, included in presets for save / load / send / receive etc).

3. Access a parameter with as minimal code as possible. E.g. ```params["my param"]```.

4. Allow a hierarchy where actions (save / load / display / send / receive etc) can be applied to the entire parameter group, or sub groups. Different modules can have parameters, and they can be joined or treated individually.

See the [tutorial](https://github.com/memo/ofxMSAControlFreak/blob/master/src/ofxMSAControlFreakTutorial.h) for details.


Installation
------------
* Add as a usual openframeworks addon (copy to your openframeworks/addons directory and add to your project)
* Make sure addons folder (e.g. '../../../addons') is in your project's 'header search path' (I believe by default this is set)


Dependencies
------------
* [openFrameworks](http://openframeworks.cc/)
* ofxXmlSettings (comes with openFrameworks)
* [ofxMSAOrderedPointerMap](https://github.com/memo/ofxMSAOrderedPointerMap)



Licence
-------
The code in this repository is available under the [MIT License](https://secure.wikimedia.org/wikipedia/en/wiki/Mit_license).  
Copyright (c) 2008-2017 Memo Akten, [www.memo.tv](http://www.memo.tv)  
The Mega Super Awesome Visuals Company

