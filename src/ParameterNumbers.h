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
            friend class ParameterGroup;
            
            template <typename T> T operator=(const T & v) { kCheckBadParameter(T()); this->setValue(v); }
			template <typename T> operator T() const { kCheckBadParameter(T()); return this->getValue(); }
            
            ParameterInt(ParameterGroup *parent, string name, Type::Index typeIndex = Type::kInt)
            : ParameterSingleValueT<int>(parent, name, typeIndex) { setRange(0, 100); setIncrement(1); }
            
        protected:
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterFloat : public ParameterSingleValueT<float> {
        public:
            friend class ParameterGroup;
            
            template <typename T> T operator=(const T & v) { kCheckBadParameter(T()); this->setValue(v); }
			template <typename T> operator T() const { kCheckBadParameter(T()); return this->getValue(); }
            
            ParameterFloat(ParameterGroup *parent, string name, Type::Index typeIndex = Type::kFloat)
            : ParameterSingleValueT<float>(parent, name, typeIndex) { setRange(0, 1); setIncrement(0.01); }
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterBool : public ParameterSingleValueT<bool> {
        public:
            friend class ParameterGroup;
            
            template <typename T> T operator=(const T & v) { kCheckBadParameter(T()); this->setValue(v); }
			template <typename T> operator T() const { kCheckBadParameter(T()); return this->getValue(); }
            
            ParameterBool(ParameterGroup *parent, string name, Type::Index typeIndex = Type::kBool)
            : ParameterSingleValueT<bool>(parent, name, typeIndex) { setRange(0, 1); setIncrement(1); setMode(kToggle); }
            
            
            enum Mode {
                kToggle,    // toggle on/off
                kPush,      // on while active, off when released
                kBang       // on for only one frame
            };
            
            ParameterBool& setMode(Mode mode) {
                kCheckBadParameter();
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