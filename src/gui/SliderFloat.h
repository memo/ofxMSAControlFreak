#pragma once

#include  "ofxMSAControlFreak/src/gui/SliderBase.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class SliderFloat : public SliderBase<float> {
                
            public:
                SliderFloat(Panel* parent, string name, float &value, float min, float max) : SliderBase<float>(parent, name, value, min, max) {
                    controlType = "SliderFloat";
                }
            };
            
        }
    }
}