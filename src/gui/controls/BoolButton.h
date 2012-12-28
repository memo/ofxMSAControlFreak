#pragma once

#include "ofxMSAControlFreak/src/gui/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolButton : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolButton(Panel *parent, string s) : BoolBase(parent, s) {}

                //--------------------------------------------------------------
                BoolButton(Panel *parent, Parameter *p) : BoolBase(parent, p) {}
                
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
                    
                    // draw border
                    ofNoFill();
                    ofSetColor(config->borderColor);
                    glLineWidth(1.0);
                    ofRect(0, 0, width, height);

                    ofDisableAlphaBlending();
                    
                    glPopMatrix();
                    
                    
                    BoolBase::draw();
                }
            };
            
        }
    }
}