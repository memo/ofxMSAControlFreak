#pragma once

#include "ofxMSAControlFreak/src/gui/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolTitle : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolTitle(Panel *parent, string s) : BoolBase(parent, s) {}
                
                //--------------------------------------------------------------
                BoolTitle(Panel *parent, Parameter *p) : BoolBase(parent, p) {}
                
                //--------------------------------------------------------------
                void setup() {
                    width = config->gridSize.x - config->padding.x;
                    if(height == 0) height = config->titleHeight;
                    if(parameter->getName().empty()) height/=2;
                }
                
                //--------------------------------------------------------------
                void draw() {
                    if(!parameter) return;
                    
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
                    
                    BoolBase::draw();
                }

            };
        }
    }
}