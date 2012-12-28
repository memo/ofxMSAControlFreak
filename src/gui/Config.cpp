#include "ofxMSAControlFreak/src/gui/Includes.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Config::Config() {
                sliderHeight		= 6;
                sliderTextHeight	= 20;
                titleHeight			= sliderHeight + sliderTextHeight;
                toggleHeight		= titleHeight;
                buttonHeight		= titleHeight;
                slider2DTextHeight	= titleHeight * 1.5;
                comboBoxHeight		= titleHeight;	//15
                comboBoxTextHeight	= 15;
                
                textPos.set         (5, 16);
                padding.set			(titleHeight/2, 10);
                offset.set			(titleHeight/2, titleHeight/2);
                slider2DSize.set	(titleHeight * 4, titleHeight * 4);
                
                gridSize.x			= 200 + padding.x;
                gridSize.y			= toggleHeight + padding.y;
                

                // Colors
                // 0: normal, 1:over, 2:active
                colors.bg[0]        = ofColor(0);
                colors.bg[1]		= ofColor(33);
                colors.bg[2]		= ofColor(33);
                
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
            }
            
            
            void Config::drawString(string s, float x, float y) {
                if(!font.isLoaded()) font.loadFont("fonts/Verdana.ttf", 8, false, false, false);
                font.drawString(s, floor(x), floor(y));
            }

        }
    }
}