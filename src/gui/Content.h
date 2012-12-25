#pragma once

#include  "ofxMSAControlFreak/src/gui/Control.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            class Content  : public Control {
            public:
                float			fixwidth;
                float			fixheight;
                ofBaseDraws		*content;
                
                Content(Page* parent, string name, ofBaseDraws& content, float fixwidth=250.0);
                void setup();
                void draw(float x, float y);
            };
            
        }
    }
}