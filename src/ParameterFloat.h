/*
 
 A few Parameter types for int, float, bool Parameters
 
 */

#pragma once


#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
    namespace ControlFreak {

        class ParameterFloat : public Parameter {
        public:
            template <typename T> T operator=(const T & v) { set(v); }
			template <typename T> operator T() const { return value(); }
            
            ParameterFloat(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kFloat)
            : Parameter(name, parent, typeIndex, new ParameterValueT<float>()) { setRange(0.0f, 1.0f); setIncrement(0.01f); }
        };
        
    }
}