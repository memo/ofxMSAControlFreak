#pragma once

#include  "ofxMSAControlFreak/src/gui/Control.h"
#include  "ofxMSAControlFreak/src/gui/SliderBase.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class SliderInt : public SliderBase<int> {
                
            public:
                SliderInt(string name, int &value, int min, int max) : SliderBase<int>(name, value, min, max) {
                    controlType = "SliderInt";
                    setIncrement(1);
                }
                
            };
            
        }
    }
}