
#include "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            FPSCounter::FPSCounter(Panel *parent) : ControlParameterT<Parameter>(parent, NULL) {
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
                config->drawString("FPS: " + ofToString(ofGetFrameRate()), 3, 15);
                
                glPopMatrix();
            }
        }
    }
}