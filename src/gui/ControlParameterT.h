#pragma once

#include "ofxMSAControlFreak/src/gui/Control.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            template <typename T>
            class ControlParameterT : public Control {
            public:
                ControlParameterT(Panel *parent, string s) : Control(parent) {
                    parameterOwner = true;
                    parameter = new T(NULL, s);
                }

                ~ControlParameterT() {
                    if(parameterOwner && parameter) delete parameter;
                }
                
                ControlParameterT(Panel *parent, Parameter *p) : Control(parent) {
                    parameter = dynamic_cast<T*>(p);
                    if(!parameter) ofLogError() << "msa::ControlFreak::gui::Control - type-casting parameter " << p->getPath();
                    if(parameter) name = parameter->getPath();
                    parameterOwner = false;
                }

                T &getParameter() {
                    return *parameter;
                }
                
            protected:
                T *parameter;
                bool parameterOwner;
            };

        }
    }
}