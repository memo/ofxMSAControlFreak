#pragma once

#include  "ofxMSAControlFreak/src/gui/Control.h"
#include  "ofxMSAControlFreak/src/gui/SliderBase.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class SliderFloat : public SliderBase<float> {
                
            public:
                SliderFloat(string name, float &value, float min, float max) : SliderBase<float>(name, value, min, max) {
                    controlType = "SliderFloat";
                }
            };
            
        }
    }
}