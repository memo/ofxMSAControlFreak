#pragma once

#include  "ofxMSAControlFreak/src/gui/Control.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class FPSCounter : public Control {
            public:
                FPSCounter(Panel *parent);
                void setup();
                void draw(float x, float y);
            };
            
        }
    }
}