#pragma once

#include "ofxMSAControlFreak/src/gui/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolToggle : public ControlParameterT<ParameterBool> {
            public:
                //--------------------------------------------------------------
                BoolToggle(Panel *parent, Parameter *p) : ControlParameterT<ParameterBool>(parent, p) {
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
                    
                    glPushMatrix();
                    glTranslatef(x, y, 0);
                    
                    ofEnableAlphaBlending();
                    ofFill();
                    setFullColor(parameter->getValue());
                    ofRect(0, 0, height, height);
                    
                    if(parameter->getValue()) {
                        setTextColor();
                        ofLine(0, 0, height, height);
                        ofLine(height, 0, 0, height);
                    }
                    
                    setTextBGColor();
                    ofRect(height, 0, width - height, height);
                    
                    setTextColor();
                    config->drawString(parameter->getName(), height + config->textPos.x, config->textPos.y);
                    ofDisableAlphaBlending();
                    
                    glPopMatrix();
                }
                
            };

            
        }
    }
}