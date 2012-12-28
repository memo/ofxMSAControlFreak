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
                    
                    ofPushMatrix();
                    ofTranslate(x, y);
                    ofEnableAlphaBlending();
                    
                    // draw bg
                    ofFill();
                    setToggleColor(parameter->getValue());
                    ofRect(0, 0, width, height);
                    
                    drawText(3, 15);
                    drawBorder();

                    ofDisableAlphaBlending();
                    ofPopMatrix();
                    
                    BoolBase::draw();
                }
            };
            
        }
    }
}