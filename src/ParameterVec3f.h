#pragma once

#include "ofxMSAControlFreak/src/ParameterGroup.h"

namespace msa {
    namespace ControlFreak {
     
        class ParameterVec3f : public ParameterGroup {
        protected:
            friend class ParameterGroup;
            
            ParameterVec3f(ParameterGroup *parent, string name)
            : ParameterValueT<int>(parent, name, Types::kVec3f) { }
        };
        
    }
}