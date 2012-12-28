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

                
                // Colors
                // 0: normal, 1:over, 2:active
                struct {
                    ofColor bg[3];
                    ofColor text[3];
                    struct {
                        ofColor full[3];
                        ofColor empty[3];
                    } slider, toggle;
                    ofColor border[3];
                } colors;
                
                
                Config();
                void drawString(string s, float x, float y);
            };
            
        }
    }
}