/*
 
 Template base class for any parameter which contains a complex value (e.g. vector, color, matrix etc.)
 
 */

#pragma once

#include "ParameterGroup.h"

namespace msa {
    namespace ControlFreak {
        
        template <typename T>
        class ParameterComplexValueT : public ParameterGroup {
        public:

			ParameterComplexValueT(ParameterGroup *parent, string name, Type::Index typeIndex)
            : ParameterGroup(parent, name, typeIndex) {
                ofLogVerbose() << "msa::ControlFreak::ParameterComplexValueT::ParameterComplexValueT " <<  this->getPath();
                
            }

            
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull) { ParameterGroup::writeToXml(xml, bFull); }
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull) { ParameterGroup::readFromXml(xml, bFull); }
            
		protected:
            
            virtual void clamp() {}
            virtual void snap() {}
        };
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        
    }
}