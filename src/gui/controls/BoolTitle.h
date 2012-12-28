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
                    
                    // draw border
                    ofNoFill();
                    ofSetLineWidth(1);
                    ofSetColor(config->textColor);
                    ofRect(0, 0, width, height);
                    
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