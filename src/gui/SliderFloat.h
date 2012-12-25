#pragma once

#include  "ofxMSAControlFreak/src/gui/SliderBase.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class SliderFloat : public SliderBase<float> {
                
            public:
                SliderFloat(Page* page, string name, float &value, float min, float max) : SliderBase<float>(page, name, value, min, max) {
                    controlType = "SliderFloat";
                }
            };
            
        }
    }
}