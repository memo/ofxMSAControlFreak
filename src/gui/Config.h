#pragma once

#include "ofMain.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Config {
            public:
                ofPoint	gridSize;
                
                float	buttonHeight;
                float	toggleHeight;
                float	sliderHeight;
                float	sliderTextHeight;
                float	slider2DTextHeight;
                float	titleHeight;
                float	comboBoxHeight;
                float	comboBoxTextHeight;
                
                ofPoint padding;
                ofPoint offset;
                ofPoint	slider2DSize;
                
                int	textColor;
                int textOverColor;
                int textBGColor;
                int textBGOverColor;
                
                int fullColor;
                int	fullOverColor;
                int fullActiveColor;
                int emptyColor;
                int borderColor;
                
                Config();
            };
            
            
            extern Config defaultSimpleGuiConfig;
            
        }
    }
}