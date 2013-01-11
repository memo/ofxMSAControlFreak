/*
 
 A few Parameter types for int, float, bool Parameters
 
 */

#pragma once


#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
    namespace ControlFreak {
        
        class ParameterInt : public Parameter {
        public:
            template <typename T> T operator=(const T & v) { set(v); }
			template <typename T> operator T() const { return value(); }
            
            ParameterInt(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kInt)
            : Parameter(name, parent, typeIndex, new ParameterValueT<int>()) { setRange(0, 100); setIncrement(1); }
            
        };
        
    }
}