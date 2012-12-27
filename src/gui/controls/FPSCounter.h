#pragma once

#include "ofxMSAControlFreak/src/gui/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class FPSCounter : public ControlParameterT<Parameter> {
            public:
                FPSCounter(Panel *parent);
                void setup();
                void draw();
            };
            
        }
    }
}