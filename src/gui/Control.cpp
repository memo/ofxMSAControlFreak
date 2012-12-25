#include  "ofxMSAControlFreak/src/gui/Control.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Control::Control(string name) {
                controlType = "";
                this->config = &defaultSimpleGuiConfig;
                setName(name);
                setKey(key);
                setPos(0, 0);
                lock	  = false;
                focused	  = false;
                newColumn = false;
                setKeyboardShortcut(0);
                
                setup();
                
                disableAllEvents();		// just for safety to make sure nothing is registered twice
                //	enableAppEvents();
                //	enableMouseEvents();
                //	disableKeyEvents();
            }
            
            Control &Control::setConfig(Config *config) {
                this->config = config;
                setup();
                return *this;
            }
            
            Control &Control::setNewColumn(bool b) {
                newColumn = b;
                return *this;
            }
            
            
            
            Control &Control::setName(string newName) {
                name = newName;
                origName = name;
                if(key.compare("") == 0) setKey("");	// if key has not been set yet, set name as key too
                
                hasTitle = (name.compare("") != 0);
                return *this;
            }
            
            
            Control &Control::setKey(string newKey) {
                if(newKey.compare("") == 0) key = name;
                else key = newKey;
                for(int i=0; i<key.size(); i++) {
                    if(key[i] == ' ') key[i] = '_';
                }
                return *this;
            }
            
            Control &Control::setTextColor(bool clickable) {
                if(isMouseOver() && clickable) ofSetHexColor(config->textOverColor);
                else ofSetHexColor(config->textColor);
                return *this;
            }
            
            Control &Control::setTextBGColor(bool clickable) {
                if(isMouseOver() && clickable) ofSetHexColor(config->textBGOverColor);
                else ofSetHexColor(config->textBGColor);
                return *this;
            }
            
            Control &Control::setFullColor(bool forceActive) {
                if(isMouseDown() || forceActive) ofSetHexColor(config->fullActiveColor);
                else if(isMouseOver()) ofSetHexColor(config->fullOverColor);
                else ofSetHexColor(config->fullColor);
                return *this;
            }
            
            Control &Control::setEmptyColor() {
                ofSetHexColor(config->emptyColor);
                //		if(isMouseOver()) ofSetHexColor(config->overColor.r, config->overColor.g, config->overColor.b);
                //		if(focused && !isMouseOver()) ofSetHexColor(config->focusColor.r, config->focusColor.g, config->focusColor.b);
                return *this;
            }
            
            Control &Control::setKeyboardShortcut(char c) {
                keyboardShortcut = c;
                if(c) {
                    //	printf( "ofxMSAControlFreak/src/gui/Control::setKeyboardShortcut %s %c\n", name.c_str(), c);
                    name = origName + " (" + c + ")";
                } else {
                    name = origName;
                }
                return *this;
            }
            
        }
    }
}