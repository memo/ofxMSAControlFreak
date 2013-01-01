#include "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Control::Control(Panel *parent) {
                this->parent = parent;
                if(parent) {
                    this->config = parent->config;
                    width   = config->layout.gridSize.x;
                    height  = config->layout.buttonHeight;
                }
                
//                name = "[COULD NOT READ FROM PARAMETER]";
                z = 0;
                localRect.set(0, 0, 0, 0);
                active = false;
                //                this->controlType = controlType;
                //                setName(name);
                //                setKey(key);
                setPosition(0, 0);
                //                lock	  = false;
                //                focused	  = false;
                newColumn = false;
                setKeyboardShortcut(0);
                
                setup();
                
                disableAllEvents();		// just for safety to make sure nothing is registered twice
                //	enableAppEvents();
                //	enableMouseEvents();
                //	disableKeyEvents();
            }
            
            //--------------------------------------------------------------
            Control &Control::setConfig(Config *config) {
                this->config = config;
                setup();
                return *this;
            }
            
            //--------------------------------------------------------------
            Control &Control::setNewColumn(bool b) {
                newColumn = b;
                return *this;
            }
            
            int Control::getDepth() {
                return parent ? parent->getDepth() + 1 : 0;
            }

            //--------------------------------------------------------------
            int Control::getState() {
                if(parent && parent->getActiveControl() == this) return 2;
                else if(isMouseOver()) return 1;
                else return 0;
            }

            //--------------------------------------------------------------
            ofColor Control::setColor(ofColor *c) {
                ofSetColor(c[getState()]);
                return c[getState()];
            }

            
            //--------------------------------------------------------------
            ofColor Control::setBGColor() {
                return setColor(config->colors.bg);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setTextColor() {
                return setColor(config->colors.text);
            }

            
            //--------------------------------------------------------------
            ofColor Control::setSliderColor(bool b) {
                if(b) return setColor(config->colors.slider.full);
                else return setColor(config->colors.slider.empty);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setToggleColor(bool b) {
                if(b) return setColor(config->colors.toggle.full);
                else return setColor(config->colors.toggle.empty);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setBorderColor() {
                return setColor(config->colors.border);
            }
            
            //--------------------------------------------------------------
            bool Control::doTooltip(int millis) {
                return isMouseOver() && getStateChangeMillis() > (millis < 0 ? 250 : millis);
            }
            
            //--------------------------------------------------------------
            Control &Control::setKeyboardShortcut(char c) {
                keyboardShortcut = c;
                if(c) {
                    //	printf("ofxMSAControlFreak/src/gui/Control::setKeyboardShortcut %s %c\n", name.c_str(), c);
                    //                    name = origName + " (" + c + ")";
                } else {
                    //                    name = origName;
                }
                return *this;
            }
          
        }
    }
}