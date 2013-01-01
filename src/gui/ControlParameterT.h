#pragma once

#include "ofxMSAControlFreak/src/gui/Control.h"
#include "ofxMSAControlFreak/src/gui/Config.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"
#include "ofxMSAControlFreak/src/gui/Renderer.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            template <typename T>
            class ControlParameterT : public Control {
            public:
                //--------------------------------------------------------------
                ControlParameterT(Panel *parent, string s) : Control(parent) {
                    parameterOwner = true;
//                    ParameterGroup *parentParam = parent ? &(parent->getParameter()) : NULL;
                    parameter = new T(NULL, s);
//                    name = parameter->getPath();
                }

                //--------------------------------------------------------------
                ControlParameterT(Panel *parent, Parameter *p) : Control(parent) {
                    parameter = dynamic_cast<T*>(p);
                    if(!parameter) ofLogError() << "msa::ControlFreak::gui::Control - type-casting parameter " << p->getPath();
//                    if(parameter) name = parameter->getPath();
                    parameterOwner = false;
                }

                //--------------------------------------------------------------
                ~ControlParameterT() {
                    if(parameterOwner && parameter) delete parameter;
                }
                

                //--------------------------------------------------------------
                T &getParameter() {
                    return *parameter;
                }
                
                //--------------------------------------------------------------
                void drawText(int x, int y, string s = "", ofColor *c = NULL) {
                    setColor(c ? c : getConfig().colors.text);
                    getConfig().drawString(s.empty() ? parameter->getName() : s, x, y);
                }
                
                //--------------------------------------------------------------
                void setTooltip(string s="") {
                    // if s is empty, use string from parameter
                    if(s.empty()) s = parameter->getTooltip();
                    if(doTooltip() && !s.empty()) {
                        Renderer::instance().setToolTip(parameter->getTooltip());
                    }
                }

                //--------------------------------------------------------------
                virtual void draw() {
                    setTooltip();
                    Control::draw();
                }
                
            protected:
                T *parameter;
                bool parameterOwner;
            };

        }
    }
}