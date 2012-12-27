
#include "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            FPSCounter::FPSCounter(Panel *parent) : ControlParameterT<Parameter>(parent, NULL) {
                setup();
            }
            
            void FPSCounter::setup() {
                width = config->gridSize.x - config->padding.x;
                height = config->titleHeight;
            }
            
            
            void FPSCounter::draw() {
                glPushMatrix();
                glTranslatef(x, y, 0);
                
                ofEnableAlphaBlending();
                ofFill();
                setTextBGColor(false);
                ofRect(0, 0, width, height);
                
                setTextColor(false);
                config->drawString("FPS: " + ofToString(ofGetFrameRate()), 3, 15);
                
                glPopMatrix();
            }
        }
    }
}