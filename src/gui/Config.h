#pragma once

#include "ofMain.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Config {
            public:
                ofTrueTypeFont font;
                ofPoint	gridSize;
                
                float	buttonHeight;
                float	toggleHeight;
                float	sliderHeight;
                float	sliderTextHeight;
                float	slider2DTextHeight;
                float	titleHeight;
                float	comboBoxHeight;
                float	comboBoxTextHeight;
                
                ofPoint textPos;
                ofPoint padding;
                ofPoint offset;
                ofPoint	slider2DSize;
                
                ofColor textColor;
                ofColor textOverColor;
                ofColor textBGColor;
                ofColor textBGOverColor;
                
                ofColor fullColor;
                ofColor fullOverColor;
                ofColor fullActiveColor;
                ofColor emptyColor;
                ofColor borderColor;
                
                Config();
                void drawString(string s, float x, float y);
            };
            
        }
    }
}