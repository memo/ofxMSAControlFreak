/*
 
 A few Parameter types for int, float, bool Parameters
 
 */

#pragma once


#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
    namespace ControlFreak {
        
        class ParameterBool : public Parameter {
        public:
            //--------------------------------------------------------------
            enum Mode {
                kToggle,    // toggle on/off
                kPush,      // on while active, off when released
                kBang       // on for only one frame
            };
            
            //--------------------------------------------------------------
            ParameterBool(string name, ParameterGroup *parent = NULL)
            : Parameter(name, parent, new ParameterNumberValueT<bool>()) { setRange(0, 1); setIncrement(1); setMode(kToggle); }
            
            template <typename T> T operator=(const T & v) { set(v); }
			template <typename T> operator T() const { return value(); }
            
            //--------------------------------------------------------------
            ParameterBool& setMode(Mode mode) {
                _mode = mode;
                return *this;
            }
            
            //--------------------------------------------------------------
            Mode getMode() {
                return _mode;
            }
            
            //--------------------------------------------------------------
            void toggle() {
                set(!value());
            }
            
        protected:
            Mode _mode;

        };
        
        
    }
}