/*
 
 Template base class for any parameter which contains a simple single value (e.g. number)
 
 */

#pragma once

#include "ofxMSAControlFreak/src/ParameterValueT.h"

namespace msa {
    namespace ControlFreak {
        
        template <typename T>
        class ParameterSingleValueT : public ParameterValueT<T> {
        public:

            ParameterSingleValueT(ParameterContainer *parent, string name, Type::Index typeIndex)
            : ParameterValueT<T>(parent, name, typeIndex) {
                ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::ParameterSingleValueT " <<  this->getPath().c_str();
                this->setValue(0);
            }
            

            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
            
		protected:
            virtual T clamp(T v);
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
		template <typename T>
        void ParameterSingleValueT<T>::writeToXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::writeToXml " << this->getPath().c_str();
            
            Parameter::writeToXml(xml, bFull);  // IMPORTANT: always start with parents write to xml
            xml.addAttribute(this->_xmlTag, "value", this->getValue(), this->_xmlTagId);
            if(bFull) {
                xml.addAttribute(this->_xmlTag, "min", this->getMin(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "max", this->getMax(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "clamped", this->isClamped(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "inc", this->getIncrement(), this->_xmlTagId);
            }
        }
        
        //--------------------------------------------------------------
		template <typename T>
        void ParameterSingleValueT<T>::readFromXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::readFromXml " << this->getPath().c_str();
        }
        
        //--------------------------------------------------------------
        template <typename T>
        T ParameterSingleValueT<T>::clamp(T v) {
            return this->isClamped() ? ( v < this->getMin() ? this->getMin() : v > this->getMax() ? this->getMax() : v) : v;
        }
    }
}