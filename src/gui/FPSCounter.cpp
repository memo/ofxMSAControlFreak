
#include  "ofxMSAControlFreak/src/gui/FPSCounter.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            FPSCounter::FPSCounter() : Control("FPS Counter") {
                controlType = "FPSCounter";
                setup();
            }
            
            void FPSCounter::setup() {
                setSize(config->gridSize.x - config->padding.x, config->titleHeight);
            }
            
            
            void FPSCounter::draw(float x, float y) {
                setPos(x, y);
                
                glPushMatrix();
                glTranslatef(x, y, 0);
                
                ofEnableAlphaBlending();
                ofFill();
                setTextBGColor(false);
                ofRect(0, 0, width, height);
                
                setTextColor(false);
                ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 3, 15);
                
                glPopMatrix();
            }
        }
    }
}