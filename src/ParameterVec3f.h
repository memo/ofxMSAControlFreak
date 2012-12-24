#pragma once

#include "ofxMSAControlFreak/src/ParameterComplexValueT.h"

namespace msa {
    namespace ControlFreak {
     
        class ParameterVec3f : public ParameterComplexValueT<ofVec3f> {
        public:
//            friend class ParameterContainer;
            
            ParameterVec3f(ParameterContainer *parent, string name)
            : ParameterComplexValueT<ofVec3f>(parent, name, Type::kVec3f) {
                ParameterFloat *px = new ParameterFloat(this, "x");
//                px->setValueVariable(_vvalue.x);
                addParameter(px);

                ParameterFloat *py = new ParameterFloat(this, "y");
                addParameter(py);

                ParameterFloat *pz = new ParameterFloat(this, "z");
                addParameter(pz);
            }
        };
        
    }
}