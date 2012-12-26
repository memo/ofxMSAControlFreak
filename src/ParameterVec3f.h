#pragma once

#include "ofxMSAControlFreak/src/ParameterComplexValueT.h"

namespace msa {
    namespace ControlFreak {
     
        class ParameterVec3f : public ParameterComplexValueT<ofVec3f> {
        public:
//            friend class ParameterGroup;
            
            ParameterVec3f(ParameterGroup *parent, string name);
            
            virtual ParameterValueT<ofVec3f>& setValueVariable(ofVec3f *pv);
            virtual ParameterValueT<ofVec3f>& setRangeVariables(ofVec3f *pmin, ofVec3f *pmax);
            virtual ParameterValueT<ofVec3f>& setIncrementVariable(ofVec3f *pinc);

        };
        
    }
}
