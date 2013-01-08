/*
 *  MSAControlFreeParameter.cpp
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */


#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
	namespace ControlFreak {

        
        //--------------------------------------------------------------
        Parameter::Parameter(string name, ParameterGroup *parent, Type::Index typeIndex, ParameterValueI *pv)
        : _pparent(parent), _name(name), _typeIndex(typeIndex) {
            _paramValue = pv;
            if(pv) {
                _paramValue->setParameter(this);
            }
                
            _xmlTag = "Parameter";
            _xmlTagId = 0;
//            ofLogVerbose() << "msa::ControlFreak::Parameter::Parameter: " <<  getPath();
        }
		
        //--------------------------------------------------------------
        Parameter::~Parameter() {
            ofLogVerbose() << "msa::ControlFreak::Parameter::~Parameter(): " << getPath();
//            if(_paramValue) delete _paramValue;   // TODO
        }
        
        
        //--------------------------------------------------------------
		Parameter& Parameter::setName(string s) {
			ofLogVerbose() << "msa::ControlFreak::Parameter::setName: " << s;
            
            _name = s;
            return *this;
		}
        
        //--------------------------------------------------------------
		string Parameter::getName() const {
			return _name;
		}
        
        //--------------------------------------------------------------
        Parameter& Parameter::setTooltip(string s) {
            _tooltip = s;
            return *this;
        }
        
        //--------------------------------------------------------------
        string Parameter::getTooltip() const {
            return _tooltip;
        }

        //--------------------------------------------------------------
		string Parameter::getPath() const {
			return _pparent ? _pparent->getPath() + getPathDivider() + _name : _name;
		}
		
        //--------------------------------------------------------------
        void Parameter::setParent(ParameterGroup *parent) {
			ofLogVerbose() << "msa::ControlFreak::Parameter::setName: " << getPath() << " " << (parent ? parent->getName(): "NULL");
            _pparent = parent;
        }
        
        //--------------------------------------------------------------
        ParameterGroup* Parameter::getParent() const {
            return _pparent;
        }


        //--------------------------------------------------------------
		Type::Index Parameter::getType() const {
			return _typeIndex;
		}
		
        //--------------------------------------------------------------
		string Parameter::getTypeName() const {
			return nameForIndex(_typeIndex);
		}

        //--------------------------------------------------------------
        ParameterValueI* Parameter::getParamValue() {
            return _paramValue;
        }

        //--------------------------------------------------------------
        void Parameter::writeToXml(ofxXmlSettings &xml, bool bOnlyValues) {
			ofLogVerbose() << "msa::ControlFreak::Parameter::writeToXml: " << getPath();

            _xmlTagId = xml.addTag(_xmlTag);
            xml.addAttribute(_xmlTag, "type", getTypeName(), _xmlTagId);
            xml.addAttribute(_xmlTag, "name", getName(), _xmlTagId);
            if(_paramValue) _paramValue->writeToXml(xml, bOnlyValues);

            if(!bOnlyValues) {
                xml.addAttribute(_xmlTag, "path", getPath(), _xmlTagId);
                xml.addAttribute(_xmlTag, "tooltip", getTooltip(), _xmlTagId);
                //            xml.addAttribute(_xmlTag, "parent", _pparent ? _pparent->getName(): "none", _xmlTagId);
            }
        }
        
        //--------------------------------------------------------------
        void Parameter::readFromXml(ofxXmlSettings &xml, bool bOnlyValues) {
			ofLogVerbose() << "msa::ControlFreak::Parameter::readFromXml: " << getPath();
            
            if(_paramValue) _paramValue->readFromXml(xml, bOnlyValues);
            if(!bOnlyValues) {
                setTooltip(xml.getAttribute(_xmlTag, "tooltip", "", _xmlTagId));
            }
        }
        
 
	}
}