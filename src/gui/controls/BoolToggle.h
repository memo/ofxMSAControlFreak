#pragma once

#include "ofxMSAControlFreak/src/gui/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolToggle : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolToggle(Panel *parent, string s) : BoolBase(parent, s) {}
                
                //--------------------------------------------------------------
                BoolToggle(Panel *parent, Parameter *p) : BoolBase(parent, p) {}
               
                //--------------------------------------------------------------
                void draw() {
                    if(!parameter) return;
                    
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