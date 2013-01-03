/*
 
 A few Parameter types for int, float, bool Parameters
 
 */

#pragma once


#include "ofxMSAControlFreak/src/ParameterSingleValueT.h"

namespace msa {
    namespace ControlFreak {
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterInt : public ParameterSingleValueT<int> {
        public:
            template <typename T> T operator=(const T & v) { this->setValue(v); }
			template <typename T> operator T() const { return this->getValue(); }
            
            ParameterInt(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kInt)
            : ParameterSingleValueT<int>(name, parent, typeIndex) { setRange(0, 100); setIncrement(1); }
            
        protected:
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterFloat : public ParameterSingleValueT<float> {
        public:
            template <typename T> T operator=(const T & v) { this->setValue(v); }
			template <typename T> operator T() const { return this->getValue(); }
            
            ParameterFloat(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kFloat)
            : ParameterSingleValueT<float>(name, parent, typeIndex) { setRange(0, 1); setIncrement(0.01); }
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterBool : public ParameterSingleValueT<bool> {
        public:
            template <typename T> T operator=(const T & v) { this->setValue(v); }
			template <typename T> operator T() const { return this->getValue(); }
            
            ParameterBool(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kBool)
            : ParameterSingleValueT<bool>(name, parent, typeIndex) { setRange(0, 1); setIncrement(1); setMode(kToggle); }
            
            
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
            
        protected:
            Mode _mode;

            //--------------------------------------------------------------
//            void update() {
//                ParameterSingleValueT<bool>::update();
//                if(_isBang && getValue() && _oldValue) {
//                    setValue(false);
//                    _oldValue = false;
//                }
//            }
        };
        
        
    }
}