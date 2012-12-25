//
//  ParameterVec3f.cpp
//  ofxMSAControlFreak example
//
//  Created by Memo Akten on 24/12/2012.
//
//

#include "ofxMSAControlFreak/src/ControlFreak.h"


namespace msa {
    namespace ControlFreak {

        ParameterVec3f::ParameterVec3f(ParameterContainer *parent, string name)
        : ParameterComplexValueT<ofVec3f>(parent, name, Type::kVec3f) {
            addParameter(new ParameterFloat(this, "x"));
            addParameter(new ParameterFloat(this, "y"));
            addParameter(new ParameterFloat(this, "z"));
        }
        
        
        //--------------------------------------------------------------
        ParameterValueT<ofVec3f>& ParameterVec3f::setValueVariable(ofVec3f *pv) {
            ParameterValueT<ofVec3f>::setValueVariable(pv);
            int np = getNumParams();
            for(int i=0; i<np; i++) {
                ParameterFloat &p = (ParameterFloat&)getParameter(i);
                p.setValueVariable(&getValue()[i]);
            }
        }
        
        //--------------------------------------------------------------
        ParameterValueT<ofVec3f>& ParameterVec3f::setRangeVariables(ofVec3f *pmin, ofVec3f *pmax) {
            ParameterValueT<ofVec3f>::setRangeVariables(pmin, pmax);
            int np = getNumParams();
            for(int i=0; i<np; i++) {
                ParameterFloat &p = (ParameterFloat&)getParameter(i);
                p.setRangeVariables(&getMin()[i], &getMax()[i]);
            }
        }
        
        //--------------------------------------------------------------
        ParameterValueT<ofVec3f>& ParameterVec3f::setIncrementVariable(ofVec3f *pinc) {
            ParameterValueT<ofVec3f>::setIncrementVariable(pinc);
            int np = getNumParams();
            for(int i=0; i<np; i++) {
                ParameterFloat &p = (ParameterFloat&)getParameter(i);
                p.setIncrementVariable(&getIncrement()[i]);
            }
        }


    }
}