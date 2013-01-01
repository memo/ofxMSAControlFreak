#include "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Control::Control(Panel *parent) {
                this->_parent = parent;
                if(_parent) {
                    this->_config = &_parent->getConfig();
                    width   = getConfig().layout.columnWidth;
                    height  = getConfig().layout.buttonHeight;
                }
                
                z = 0;
                _alpha = 1;
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
                return getParent() ? getParent()->getRoot() : dynamic_cast<Panel*>(this);
            }
            
            //--------------------------------------------------------------
            Config &Control::getConfig() {
                return *_config;
            }
            
            //--------------------------------------------------------------
            int Control::getDepth() {
                return getParent() ? getParent()->getDepth() + 1 : 0;
            }
            
            //--------------------------------------------------------------
            bool Control::getActive() {
                return getRoot()->getActiveControl() && getRoot()->getActiveControl() == this;
            }
            
            //--------------------------------------------------------------
            bool Control::getParentActive() {
                return getParent() ? getActive() || getParent()->getActive() || getParent()->getParentActive() : getActive();
            }
            
            //--------------------------------------------------------------
            int Control::getState() {
                if(isMousePressed()) return 2;
                else if(isMouseOver()) return 1;
                else return 0;
            }
            
            //--------------------------------------------------------------
            ofColor Control::setColor(ofColor c) {
                c.a *= _alpha;
                ofSetColor(c);
                return c;
            }
            
            //--------------------------------------------------------------
            ofColor Control::setColor(ofColor *c) {
                ofColor cc = c[getState()];
                return setColor(c[getState()]);
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
                
                float targetAlpha = getStateChangeMillis() > getConfig().colors.fade.delayMillis && getRoot()->getActiveControl() && !getParentActive() ? getConfig().colors.fade.alpha : 1.0f;
                float diff = (targetAlpha - _alpha);
                _alpha += diff * getConfig().colors.fade.speed;
                if(fabsf(diff) < 0.05) _alpha = targetAlpha;
                
                onDraw();
                
                drawBorder();
                
                ofPopMatrix();
                ofPopStyle();
            }
            
            
        }
    }
}