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

            T operator=(const T & v) { kCheckBadParameter(T()); this->setValue(v); }
			operator T() const { kCheckBadParameter(T()); return this->getValue(); }

		protected:
            ParameterSingleValueT(ParameterGroup *parent, string name, Type::Index typeIndex)
            : ParameterValueT<T>(parent, name, typeIndex) {
//                ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::ParameterSingleValueT " <<  this->getPath();
                this->setValue(0);
            }
            
            // from ParameterValueT
            virtual void clamp();
            virtual void snap();
            
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
		template <typename T>
        void ParameterSingleValueT<T>::writeToXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::writeToXml " << this->getPath();
            
            kCheckBadParameter();
            
            Parameter::writeToXml(xml, bFull);  // IMPORTANT: always start with parents write to xml
            xml.addAttribute(this->_xmlTag, "value", this->getValue(), this->_xmlTagId);
            if(bFull) {
                xml.addAttribute(this->_xmlTag, "min", this->getMin(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "max", this->getMax(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "doClamp", this->getClamp(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "inc", this->getIncrement(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "doSnap", this->getSnap(), this->_xmlTagId);
            }
        }
        
        //--------------------------------------------------------------
		template <typename T>
        void ParameterSingleValueT<T>::readFromXml(ofxXmlSettings &xml, bool bFull) {
            kCheckBadParameter();
            
			ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::readFromXml " << this->getPath();
        }
        
        //--------------------------------------------------------------
        template <typename T>
        void ParameterSingleValueT<T>::clamp() {
            kCheckBadParameter();
            
            this->_setValue( this->getValue() < this->getMin() ? this->getMin() : this->getValue() > this->getMax() ? this->getMax() : this->getValue() );
        }
        
        //--------------------------------------------------------------
        template <typename T>
        void ParameterSingleValueT<T>::snap() {
            kCheckBadParameter();
//            float inv = 1.0f / this->getIncrement();
            int ival = floor((this->getValue() - this->getMin()) / this->getIncrement());
            this->_setValue(this->getMin() + (T) (ival * this->getIncrement()) );
        }
        

    }
}