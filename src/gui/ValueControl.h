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
                
                ValueControl(Panel *parent, string name, string controlType, T &value) : Control(parent, name, controlType), value(&value) {}
                
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