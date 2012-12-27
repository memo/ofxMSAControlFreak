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
                
                textColor			= ofColor::fromHex(0x888888);
                textOverColor		= ofColor::fromHex(0xFFFFFF);
                textBGColor			= ofColor::fromHex(0x000000);
                textBGOverColor		= ofColor::fromHex(0x222222);
                
                fullColor			= ofColor::fromHex(0xaaaaaa);
                fullOverColor		= ofColor::fromHex(0xffffff);
                fullActiveColor		= ofColor::fromHex(0x881818);
                emptyColor			= ofColor::fromHex(0x333333);
                
                borderColor			= ofColor::fromHex(0x333333);
            }
            
            
            void Config::drawString(string s, float x, float y) {
                if(!font.isLoaded()) font.loadFont("fonts/Verdana.ttf", 8, false, false, false);
                font.drawString(s, floor(x), floor(y));
            }

        }
    }
}