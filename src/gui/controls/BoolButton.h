#pragma once

#include "ofxMSAControlFreak/src/gui/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolButton : public ControlParameterT<ParameterBool> {
            public:
                //--------------------------------------------------------------
                BoolButton(Panel *parent, Parameter *p) : ControlParameterT<ParameterBool>(parent, p) {
                    setSize(config->gridSize.x - config->padding.x, config->buttonHeight);
                }
                
                //--------------------------------------------------------------
                void toggle() {
                    if(!parameter) return;
                    parameter->setValue(!parameter->getValue());
                }

                //--------------------------------------------------------------
                void keyPressed( int key ) {
                    if(key==keyboardShortcut) toggle();
                }
                
                //--------------------------------------------------------------
                void onKeyEnter() {
                    toggle();
                }

                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
                    if(!parameter) return;
                    parameter->setValue(true);
                    //                beenPressed = true;
                    //                if(beToggle) (*value) = !(*value);
                    //                else (*value) = true;
                }
                
                //--------------------------------------------------------------
                void onRelease(int x, int y, int button) {
                    //                if(!beToggle) (*value) = false;
                }
                
                //--------------------------------------------------------------
                void draw(float x, float y) {
                    if(!parameter) return;
                    
                    setPos(x, y);
                    
                    if(parameter->getName().empty()) return;
                    
                    glPushMatrix();
                    glTranslatef(x, y, 0);
                    
                    ofEnableAlphaBlending();
                    ofFill();
                    if(parameter->getValue()) ofSetColor(config->fullActiveColor);
                    else ofSetColor(config->emptyColor);
                    ofRect(0, 0, width, height);
                    
                    // if a toggle
                    //                if(value && (*value) && beToggle) {
                    //                    setTextColor();
                    //                }
                    
                    setTextColor(parameter->getValue());
                    config->drawString(parameter->getName(), 3, 15);
                    
                    ofDisableAlphaBlending();
                    
                    glPopMatrix();
                }
            };
            
        }
    }
}