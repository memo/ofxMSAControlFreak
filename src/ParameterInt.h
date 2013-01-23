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
            
            ParameterInt(string name, ParameterGroup *parent)
            : Parameter(name, parent, new ParameterNumberValueT<int>()) { setRange(0, 100); setIncrement(1); }
            
        };
        
    }
}