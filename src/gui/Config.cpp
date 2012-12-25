#include  "ofxMSAControlFreak/src/gui/Config.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Config defaultSimpleGuiConfig;
            
            
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
                
                textColor			= 0x888888;
                textOverColor		= 0xFFFFFF;
                textBGColor			= 0x000000;
                textBGOverColor		= 0x222222;
                
                fullColor			= 0xaaaaaa;
                fullOverColor		= 0xffffff;
                fullActiveColor		= 0x881818;
                emptyColor			= 0x333333;
                
                borderColor			= 0x333333;
            }
            
            
            void Config::drawString(string s, float x, float y) {
                if(!font.isLoaded()) font.loadFont("fonts/Verdana.ttf", 8, false, false, false);
                font.drawString(s, floor(x), floor(y));
            }

        }
    }
}