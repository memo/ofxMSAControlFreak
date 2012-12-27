#pragma once

#include "ofxMSAControlFreak/src/gui/Control.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            template <typename T>
            class ControlParameterT : public Control {
            public:
                ControlParameterT(Panel *parent, Parameter *p) : Control(parent) {
                    parameter = dynamic_cast<T*>(p);
                    if(!parameter) ofLogError() << "msa::ControlFreak::gui::Control - type-casting parameter " << p->getPath();
                    if(parameter) name = parameter->getPath();
                }

                T* getParameter() {
                    return parameter;
                }
                
            protected:
                T *parameter;
            };

        }
    }
}