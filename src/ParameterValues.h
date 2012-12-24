/*
 
 A few types for int, float, bool Parameters
 
 */

#pragma once


#include "ofxMSAControlFreak/src/ParameterValueT.h"

namespace msa {
    namespace ControlFreak {
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterInt : public ParameterValueT<int> {
        protected:
            friend class ParameterGroup;
            ParameterInt(ParameterGroup *parent, string name, Types::Index typeIndex)
            : ParameterValueT<int>(parent, name, typeIndex) { setRange(0, 100); setIncrement(1); }
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterFloat : public ParameterValueT<float> {
        protected:
            friend class ParameterGroup;
            ParameterFloat(ParameterGroup *parent, string name, Types::Index typeIndex)
            : ParameterValueT<float>(parent, name, typeIndex) { setRange(0, 1); setIncrement(0.1); }
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterBool : public ParameterValueT<bool> {
        protected:
            friend class ParameterGroup;
            ParameterBool(ParameterGroup *parent, string name, Types::Index typeIndex)
            : ParameterValueT<bool>(parent, name, typeIndex) { setRange(0, 1); setIncrement(1); }
        };
        
        
    }
}