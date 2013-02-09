/*
 
 A few Parameter types for int, float, bool Parameters
 
 */

#pragma once


#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
    namespace controlfreak {

        class ParameterFloat : public Parameter {
        public:
            ParameterFloat(string name, ParameterGroup *parent = NULL)
            : Parameter(name, parent, new ParameterNumberValueT<float>()) { setRange(0.0f, 1.0f); setIncrement(0.01f); }

            template <typename T> T operator=(const T & v) { set(v); }
			template <typename T> operator T() const { return value(); }
        };
        
    }
}