/*
 
 A few Parameter types for int, float, bool Parameters
 
 */

#pragma once


#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
    namespace ControlFreak {
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterInt : public Parameter {
        public:
            template <typename T> T operator=(const T & v) { setValue(v); }
			template <typename T> operator T() const { return value(); }
            
            ParameterInt(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kInt)
            : Parameter(name, parent, typeIndex, new ParameterValueT<int>()) { setRange(0, 100); setIncrement(1); }
            
        protected:
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterFloat : public Parameter {
        public:
            template <typename T> T operator=(const T & v) { setValue(v); }
			template <typename T> operator T() const { return value(); }
            
            ParameterFloat(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kFloat)
            : Parameter(name, parent, typeIndex, new ParameterValueT<float>()) { setRange(0.0f, 1.0f); setIncrement(0.01f); }
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterBool : public Parameter {
        public:
            template <typename T> T operator=(const T & v) { setValue(v); }
			template <typename T> operator T() const { return value(); }
            
            ParameterBool(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kBool)
            : Parameter(name, parent, typeIndex, new ParameterValueT<bool>()) { setRange(0, 1); setIncrement(1); }
            
            
            enum Mode {
                kToggle,    // toggle on/off
                kPush,      // on while active, off when released
                kBang       // on for only one frame
            };
            
            ParameterBool& setMode(Mode mode) {
                _mode = mode;
                return *this;
            }
            
            Mode getMode() {
                return _mode;
            }
            
            void toggle() {
                setValue(!value());
            }
            
        protected:
            Mode _mode;

            //--------------------------------------------------------------
//            void update() {
//                ParameterSingleValueT<bool>::update();
//                if(_isBang && value() && _oldValue) {
//                    setValue(false);
//                    _oldValue = false;
//                }
//            }
        };
        
        
    }
}