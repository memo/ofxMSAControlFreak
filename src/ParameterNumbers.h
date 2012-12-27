/*
 
 A few Parameter types for int, float, bool Parameters
 
 */

#pragma once


#include "ofxMSAControlFreak/src/ParameterSingleValueT.h"

namespace msa {
    namespace ControlFreak {
        
        
        //        typedef ParameterSingleValueT<float> ParameterFloat;
        //        typedef ParameterSingleValueT<int> ParameterInt;
        //        typedef ParameterSingleValueT<bool> ParameterBool;
        
        
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
            
            // dummy parameter, sent back from 'getParameter' functions, if parameter can't be found
            static ParameterInt dummy;
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
            
        protected:
            
            // dummy parameter, sent back from 'getParameter' functions, if parameter can't be found
            static ParameterFloat dummy;
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterBool : public ParameterSingleValueT<bool> {
        public:
            friend class ParameterGroup;
            
            template <typename T> T operator=(const T & v) { kCheckBadParameter(T()); this->setValue(v); }
			template <typename T> operator T() const { kCheckBadParameter(T()); return this->getValue(); }
            
            ParameterBool(ParameterGroup *parent, string name, Type::Index typeIndex = Type::kBool)
            : ParameterSingleValueT<bool>(parent, name, typeIndex) { setRange(0, 1); setIncrement(1); setBang(false); }
            
            //--------------------------------------------------------------
            // if Bang is true, parameter will only be true for one frame (i.e. sends a bang)
            void setBang(bool b) {
                kCheckBadParameter();
                _isBang = b;
            }
            
            //--------------------------------------------------------------
            bool getBang() {
                kCheckBadParameter(false);
                return _isBang;
            }
            
        protected:
            bool _isBang;
            
            // dummy parameter, sent back from 'getParameter' functions, if parameter can't be found
            static ParameterBool dummy;
            
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