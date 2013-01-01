#include "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Control::Control(Panel *parent) {
                this->_parent = parent;
                if(_parent) {
                    this->_config = &_parent->getConfig();
                    width   = getConfig().layout.gridSize.x;
                    height  = getConfig().layout.buttonHeight;
                }
                
                z = 0;
//                active = false;
                newColumn = false;
                localRect.set(0, 0, 0, 0);

                setKeyboardShortcut(0);
                
                setup();

                // we don't want auto events (they will be controlled via the parent panels)
                disableAllEvents();
            }
            
            //--------------------------------------------------------------
            Control &Control::setConfig(Config *config) {
                this->_config = config;
                setup();
                return *this;
            }
            
            //--------------------------------------------------------------
            Control &Control::setNewColumn(bool b) {
                newColumn = b;
                return *this;
            }
            
            
            //--------------------------------------------------------------
            Panel *Control::getParent() {
                return _parent;
            }
            
            //--------------------------------------------------------------
            Panel *Control::getRoot() {
                return _parent ? _parent->getRoot() : (Panel*)this;
            }
            
            //--------------------------------------------------------------
            Config &Control::getConfig() {
                return *_config;
            }

            //--------------------------------------------------------------
            int Control::getDepth() {
                return _parent ? _parent->getDepth() + 1 : 0;
            }

            //--------------------------------------------------------------
//            bool Control::getActive() {
//                return active;
//            }
            
            //--------------------------------------------------------------
            int Control::getState() {
                if(isMousePressed()) return 2;
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
                return setColor(getConfig().colors.bg);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setTextColor() {
                return setColor(getConfig().colors.text);
            }

            
            //--------------------------------------------------------------
            ofColor Control::setSliderColor(bool b) {
                if(b) return setColor(getConfig().colors.slider.full);
                else return setColor(getConfig().colors.slider.empty);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setToggleColor(bool b) {
                if(b) return setColor(getConfig().colors.toggle.full);
                else return setColor(getConfig().colors.toggle.empty);
            }
            
            //--------------------------------------------------------------
            ofColor Control::setBorderColor() {
                return setColor(getConfig().colors.border);
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
            
            //--------------------------------------------------------------
            void Control::drawBorder(ofColor *c) {
                ofNoFill();
                setColor(c ? c : getConfig().colors.border);
                glLineWidth(1.0);
                ofRect(0, 0, width, height);
            }
            
            //--------------------------------------------------------------
            void Control::draw() {
                ofPushStyle();
                ofPushMatrix();
                ofTranslate(x, y);
                ofEnableAlphaBlending();
                
                onDraw();
//                if(!getActive()) {
//                    ofSetColor(0, 128);
//                    ofFill();
//                    ofRect(0, 0, width, height);
//                }
                
                drawBorder();
                
                ofPopMatrix();
                ofPopStyle();
            }

          
        }
    }
}