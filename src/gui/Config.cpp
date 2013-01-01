#include "ofxMSAControlFreak/src/gui/Includes.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Config::Config() {
                layout.buttonHeight			= 23;
                layout.sliderHeight         = 7;
                layout.dropdownListTextHeight	= 15;
                
                layout.textPos              = ofVec2f(5, 16);
                layout.padding              = ofVec2f(10, 10);
                layout.indent               = 5;
//                layout.slider2DSize         = ofVec2f(buttonHeight * 4, buttonHeight * 4);
                
                layout.columnWidth			= 200 + layout.padding.x;
                

                // Colors
                colors.fade.alpha       = 0.0;
                colors.fade.speed       = 0.2;
                colors.fade.delayMillis = 250;
                
                // 0: normal, 1:over, 2:active
                colors.bg[0]        = ofColor(0);
                colors.bg[1]		= ofColor(30);
                colors.bg[2]		= ofColor(30);
                
                colors.text[0]		= ofColor(140);
                colors.text[1]		= ofColor(255);
                colors.text[1]		= ofColor(200);
                
                colors.slider.full[0]	= ofColor(128);
                colors.slider.full[1]	= ofColor(255);
                colors.slider.full[2]   = ofColor(180, 0, 0);
                
                colors.slider.empty[0]  = ofColor(40);
                colors.slider.empty[1]	= ofColor(60);
                colors.slider.empty[2]	= ofColor(60);
                
                colors.toggle.full[0]	= ofColor(160, 0, 0);
                colors.toggle.full[1]	= ofColor(200, 0, 0);
                colors.toggle.full[2]   = ofColor(255, 0, 0);
                
                colors.toggle.empty[0]  = ofColor(40);
                colors.toggle.empty[1]	= ofColor(60);
                colors.toggle.empty[2]	= ofColor(60);
                
                colors.border[0]	= ofColor(60);
                colors.border[1]	= ofColor(90);
                colors.border[2]	= ofColor(150);
                
                tooltip.offset      = ofVec2f(0, -10);
                tooltip.padding     = ofRectangle(6, 4, 13, 7);
                tooltip.bgColor     = ofColor(255, 255, 160);
                tooltip.borderColor = ofColor(0);
                tooltip.textColor   = ofColor(0);
            }
            
            
            void Config::drawString(string s, float x, float y) {
                if(!font.isLoaded()) font.loadFont("fonts/Verdana.ttf", 8, false, false, false);
                font.drawString(s, floor(x), floor(y));
            }

        }
    }
}