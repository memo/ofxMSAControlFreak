#pragma once

#include "ofxMSAInteractiveObject/src/ofxMSAInteractiveObject.h"
//#include "ofxMSAControlFreak/src/gui/Config.h"

#include "ofxXmlSettings.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Panel;
            class Config;
            
            class Control : public ofxMSAInteractiveObject {
            public:
                string		name;		// Human readable name this is what is displayed on screen (includes keyboard shortcut)
                string		origName;	// the original name (excluding keyboard shortcut)
                string		key;		// Machine readable name (don't change this after creating control, used for saving/loading)
                string		controlType;
                bool		lock;
                bool		focused;
                bool		newColumn;
                bool		hasTitle;
                char		keyboardShortcut;
                
                Control(Panel* parent, string name);
                Control& setName(string newName);
                Control& setKey(string newKey);
                Control& setConfig(Config *config);
                Control& setNewColumn(bool b);
                
                Control& setTextColor(bool clickable = true);
                Control& setTextBGColor(bool clickable = true);
                Control& setFullColor(bool forceActive = false);
                Control& setEmptyColor();
                Control& setKeyboardShortcut(char c);
                
                virtual void readFromXml(ofxXmlSettings &XML) {}
                virtual void writeToXml(ofxXmlSettings &XML) {}
                
                virtual void setup() {}
                
                virtual void draw(float x, float y) {}
                virtual void draw() { draw(x, y); }
                
                virtual void onKeyUp() {}			// up key is pressed
                virtual void onKeyDown() {}			// down key is pressed
                virtual void onKeyLeft() {}			// left key is pressed
                virtual void onKeyRight() {}		// right key is pressed
                virtual void onKeyEnter() {}		// enter key is pressed
                
                
                // from ofxMSAInteractiveObject
                virtual void onRollOver(int x, int y)					{}		// called when mouse enters object x, y, width, height
                virtual void onRollOut()								{}		// called when mouse leaves object x, y, width, height
                virtual void onMouseMove(int x, int y)					{}		// called when mouse moves while over object x, y, width, height
                virtual void onDragOver(int x, int y, int button)		{}		// called when mouse moves while over object and button is down
                virtual void onDragOutside(int x, int y, int button)	{}		// called when mouse moves while outside the object after being clicked on it
                virtual void onPress(int x, int y, int button)			{}		// called when mouse presses while over object
                virtual void onPressOutside(int x, int y, int button)	{}		// called when mouse presses while outside object
                virtual void onRelease(int x, int y, int button)		{}		// called when mouse releases while over object
                virtual void onReleaseOutside(int x, int y, int button)	{}		// called when mouse releases outside of object after being pressed on object
                
                virtual void keyPressed( int key ){}
                virtual void keyReleased( int key ){}
                
                
            protected:
                Config	*config;
                Panel    *parent;
            };
            
        }
    }
}