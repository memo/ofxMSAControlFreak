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
                    
                    ofPushMatrix();
                    ofTranslate(x, y);
                    
                    ofEnableAlphaBlending();
                    ofFill();
                    setToggleColor(parameter->getValue());
                    ofRect(0, 0, height, height);
                    
                    if(parameter->getValue()) {
                        setTextColor();
                        ofLine(0, 0, height, height);
                        ofLine(height, 0, 0, height);
                    }
                    
                    setBGColor();
                    ofRect(height, 0, width - height, height);
                    
                    drawText(height + config->textPos.x, config->textPos.y);
                    drawBorder();

                    ofDisableAlphaBlending();
                    ofPopMatrix();
                    
                    BoolBase::draw();
                }
                
            };

            
        }
    }
}