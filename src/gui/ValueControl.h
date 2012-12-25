#pragma once

#include  "ofxMSAControlFreak/src/gui/Control.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            template <typename T>
            class ValueControl : public Control {
            public:
                T	*value;
                T	oldValue;
                
                ValueControl(string name, T &value) : Control(name), value(&value) {}
                
                virtual bool changed() {
                    if(*value != oldValue) {
                        oldValue = *value;
                        return true;
                    }
                    return false;
                }
                
                //	void update() {
                //	}
            };
        }
    }
}