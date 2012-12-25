/*
 
 Template base class for any parameter which contains a complex value (e.g. vector, color, matrix etc.)
 
 */

#pragma once

#include "ParameterContainer.h"

namespace msa {
    namespace ControlFreak {
        
        template <typename T>
        class ParameterComplexValueT : public ParameterValueT<T> {
        public:

			ParameterComplexValueT(ParameterContainer *parent, string name, Type::Index typeIndex)
            : ParameterValueT<T>(parent, name, typeIndex) {
                ofLogVerbose() << "msa::ControlFreak::ParameterComplexValueT::ParameterComplexValueT " <<  this->getPath();
                
            }

            
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull) { ParameterContainer::writeToXml(xml, bFull); }
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull) { ParameterContainer::readFromXml(xml, bFull); }
            
		protected:
            
            virtual void clamp() {}
            virtual void snap() {}
        };
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        
    }
}