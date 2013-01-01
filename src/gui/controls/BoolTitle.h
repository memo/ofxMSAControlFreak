#pragma once

#include "ofxMSAControlFreak/src/gui/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolTitle : public BoolBase {
            public:
                
                bool bRecursive;
                bool bMouseOverRecursive;
                
                //--------------------------------------------------------------
                BoolTitle(Panel *parent, string s) : BoolBase(parent, s) { bRecursive = false; }
                
                //--------------------------------------------------------------
                BoolTitle(Panel *parent, Parameter *p) : BoolBase(parent, p) { bRecursive = false; }
                
                void onPress(int x, int y, int button) {
                    BoolBase::onPress(x, y, button);
                    bRecursive = bMouseOverRecursive;
                }
                
                //--------------------------------------------------------------
                void onRelease(int x, int y, int button) {
                    BoolBase::onRelease(x, y, button);
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(!parameter) return;
                    
                    if(parameter->getName().empty()) return;
                    
                    bMouseOverRecursive = isMouseOver() && getMouseX() > (x + width - height);
                    
                    // draw bg
                    ofFill();
                    setToggleColor(parameter->getValue());
                    ofRect(0, 0, width, height);
                    
                    if(bMouseOverRecursive) ofSetColor(255, 100);
                    else ofSetColor(0, 100);
                    ofCircle(width - height/2, height/2, height/4);
                    
                    drawText(3, 15, (parameter->getValue() ? "-" : "+"));
                    drawText(15, 15);
                    ofSetLineWidth(2);
                    drawBorder(getConfig().colors.text);
                    
                    if(doTooltip()) {
                        string sverb = parameter->getValue() ? "close" : "open";
                        string starget = bMouseOverRecursive ? "panel and all sub-panels" : "panel";
//                        if(parameter->getValue()) s = "Click to close panel [" + parameter->getName() + "]";
//                        else s = "Click to open panel";
                        Renderer::instance().setToolTip("Click to " + sverb + " " + starget);
                    }
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}