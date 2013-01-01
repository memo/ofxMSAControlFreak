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
                void onDraw() {
                    if(!parameter) return;
                    
                    ofFill();
                    setToggleColor(parameter->getValue());
                    ofRect(0, 0, height, height);
                    
                    if(parameter->getValue()) {
                        setTextColor();
                        ofSetLineWidth(2);
                        ofLine(0, 0, height, height);
                        ofLine(height, 0, 0, height);
                    }
                    
                    setBGColor();
                    ofRect(height, 0, width - height, height);
                    
                    drawText(height + config->layout.textPos.x, config->layout.textPos.y);
//                    drawBorder();
                    
                    BoolBase::onDraw();
                }
                
            };

            
        }
    }
}