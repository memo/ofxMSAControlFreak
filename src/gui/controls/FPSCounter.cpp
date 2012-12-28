
#include "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            FPSCounter::FPSCounter(Panel *parent) : ControlParameterT<Parameter>(parent, NULL) {
                setup();
            }
            
            void FPSCounter::setup() {
                width = config->layout.gridSize.x - config->layout.padding.x;
                height = config->layout.buttonHeight;
            }
            
            
            void FPSCounter::draw() {
                glPushMatrix();
                glTranslatef(x, y, 0);
                
                ofEnableAlphaBlending();
                ofFill();
                setBGColor();
                ofRect(0, 0, width, height);
                
                setTextColor();
                config->drawString("FPS: " + ofToString(ofGetFrameRate()), 3, 15);
                
                glPopMatrix();
            }
        }
    }
}