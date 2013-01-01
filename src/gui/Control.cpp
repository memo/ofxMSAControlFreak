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
                
                z = 0;
                active = false;
                newColumn = false;
                localRect.set(0, 0, 0, 0);

                setKeyboardShortcut(0);
                
                setup();

                // we don't want auto events (they will be controlled via the parent panels)
                disableAllEvents();
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
            
            //--------------------------------------------------------------
            int Control::getDepth() {
                return parent ? parent->getDepth() + 1 : 0;
            }

            //--------------------------------------------------------------
            bool Control::getActive() {
                return active;
            }
            
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
            
            //--------------------------------------------------------------
            void Control::drawBorder(ofColor *c) {
                ofNoFill();
                setColor(c ? c : config->colors.border);
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