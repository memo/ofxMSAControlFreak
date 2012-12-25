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
                
                ValueControl(Page* page, string name, T &value) : Control(page, name), value(&value) {}
                
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