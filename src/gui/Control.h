#pragma once

#include "ofxMSAInteractiveObject/src/ofxMSAInteractiveObject.h"
//#include "ofxMSAControlFreak/src/gui/Panel.h"
//#include "ofxMSAControlFreak/src/gui/Includes.h"
//#include "ofxMSAControlFreak/src/gui/Config.h"
//#include "ofxMSAControlFreak/src/ControlFreak.h"

#include "ofxXmlSettings.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Panel;
            class Config;
            
            class Control : public ofxMSAInteractiveObject {
            public:
                int         z;  // draw order (0 draw last, i.e. drawn on top)
                bool		active;
                bool		newColumn;
                char		keyboardShortcut;
                
                // if this is set (i.e. nonzero), override auto-layout and set position and size in relation to parent
                ofRectangle localRect;
                
                Control(Panel *parent);
                Control& setConfig(Config *config);
                Control& setNewColumn(bool b);
                
                // how deep in the heirarchy it is (how many levels deep)
                int getDepth();
                
                // 0: normal, 1:over, 2:active
                virtual int getState();
                ofColor setColor(ofColor *c);
                ofColor setBGColor();
                ofColor setTextColor();
                ofColor setSliderColor(bool b);
                ofColor setToggleColor(bool b);
                ofColor setBorderColor();
                
                bool doTooltip(int millis = -1);
                
                Control& setKeyboardShortcut(char c);
                
                //                virtual void readFromXml(ofxXmlSettings &XML) {}
                //                virtual void writeToXml(ofxXmlSettings &XML) {}
                
                virtual void setup() {}
                
//                virtual void draw(float x, float y) {}
//                virtual void predraw() {}           // first pass during draw, updating position, z-sorting etc.
                virtual void draw() {}
                
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
            
            
            typedef std::tr1::shared_ptr<Control> ControlPtr;

            
              
        }
    }
}