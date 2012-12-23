#pragma once


#include "ofxMSAControlFreak/src/ParameterNumberT.h"

namespace msa {
    namespace ControlFreak {
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterInt : public ParameterNumberT<int> {
        protected:
            friend class ParameterGroup;
            ParameterInt(ParameterGroup *parent, string path, Types::Index typeIndex)
            : ParameterNumberT<int>(parent, path, typeIndex) { setRange(0, 100); setIncrement(1); }
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterFloat : public ParameterNumberT<float> {
        protected:
            friend class ParameterGroup;
            ParameterFloat(ParameterGroup *parent, string path, Types::Index typeIndex)
            : ParameterNumberT<float>(parent, path, typeIndex) { setRange(0, 1); setIncrement(0.1); }
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class ParameterBool : public ParameterNumberT<bool> {
        protected:
            friend class ParameterGroup;
            ParameterBool(ParameterGroup *parent, string path, Types::Index typeIndex)
            : ParameterNumberT<bool>(parent, path, typeIndex) { setRange(0, 1); setIncrement(1); }
        };
        
        
    }
}