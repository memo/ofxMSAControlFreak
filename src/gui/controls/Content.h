#pragma once

#include "ofxMSAControlFreak/src/gui/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Content  : public ControlParameterT<Parameter> {
            public:
                float			fixwidth;
                float			fixheight;
                ofBaseDraws		*content;
                
                Content(Panel *parent, Parameter *p, ofBaseDraws& content, float fixwidth=250.0);
                void setup();
                void draw(float x, float y);
            };
            
        }
    }
}