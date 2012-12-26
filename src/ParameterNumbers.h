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
            //            friend class ParameterGroup;
            
            template <typename T> T operator=(const T & v) { this->setValue(v); }
			template <typename T> operator T() const { return this->getValue(); }
            
            ParameterInt(ParameterGroup *parent, string name, Type::Index typeIndex = Type::kInt)
            : ParameterSingleValueT<int>(parent, name, typeIndex) { setRange(0, 100); setIncrement(1); }
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterFloat : public ParameterSingleValueT<float> {
        public:
            //            friend class ParameterGroup;
            template <typename T> T operator=(const T & v) { this->setValue(v); }
			template <typename T> operator T() const { return this->getValue(); }
            
            ParameterFloat(ParameterGroup *parent, string name, Type::Index typeIndex = Type::kFloat)
            : ParameterSingleValueT<float>(parent, name, typeIndex) { setRange(0, 1); setIncrement(0.01); }
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterBool : public ParameterSingleValueT<bool> {
        public:
            //            friend class ParameterGroup;
            template <typename T> T operator=(const T & v) { this->setValue(v); }
			template <typename T> operator T() const { return this->getValue(); }
            
            ParameterBool(ParameterGroup *parent, string name, Type::Index typeIndex = Type::kToggle)
            : ParameterSingleValueT<bool>(parent, name, typeIndex) { setRange(0, 1); setIncrement(1); }
        };
        
        
    }
}