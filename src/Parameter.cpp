//                                      __
//     ____ ___  ___  ____ ___  ____   / /__   __
//    / __ `__ \/ _ \/ __ `__ \/ __ \ / __/ | / /
//   / / / / / /  __/ / / / / / /_/ // /_ | |/ /
//  /_/ /_/ /_/\___/_/ /_/ /_/\____(_)__/ |___/
//
//
//  Created by Memo Akten, www.memo.tv
//
//  ofxMSAControlFreak
//


#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
	namespace controlfreak {

        
        //--------------------------------------------------------------
        Parameter::Parameter(string name, ParameterGroup *parent, ParameterValueI *pv)
        : _pparent(parent), _name(name) {
            _paramValue = pv;
            if(pv) {
                _paramValue->setParameter(this);
            }
                
            _xmlTag = "Parameter";
            _xmlTagId = 0;
            
            Master::instance().add(this);
            
//            ofLogVerbose() << "msa::controlfreak::Parameter::Parameter: " <<  getPath();
        }
		
        //--------------------------------------------------------------
        Parameter::~Parameter() {
            ofLogVerbose() << "msa::controlfreak::Parameter::~Parameter(): " << getPath();
            if(_paramValue) delete _paramValue;   // TODO
        }
        
        
        //--------------------------------------------------------------
		Parameter& Parameter::setName(string s) {
//			ofLogVerbose() << "msa::controlfreak::Parameter::setName: " << s;
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
			ofLogVerbose() << "msa::controlfreak::Parameter::setParent: '" << getPath() << "' to '" << (parent ? parent->getName(): "NULL") << "'";
            _pparent = parent;
        }
        
        //--------------------------------------------------------------
        ParameterGroup* Parameter::getParent() const {
            return _pparent;
        }

        //--------------------------------------------------------------
		string Parameter::getTypeName() const {
			return typeid(*this).name();
		}

        //--------------------------------------------------------------
        ParameterValueI* Parameter::getParamValue() {
            return _paramValue;
        }

        //--------------------------------------------------------------
        void Parameter::writeToXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::Parameter::writeToXml: " << getPath();

            _xmlTagId = xml.addTag(_xmlTag);
            xml.addAttribute(_xmlTag, "type", getTypeName(), _xmlTagId);
            xml.addAttribute(_xmlTag, "name", getName(), _xmlTagId);
            if(_paramValue) _paramValue->writeToXml(xml, bFullSchema);

            if(bFullSchema) {
                xml.addAttribute(_xmlTag, "path", getPath(), _xmlTagId);
                xml.addAttribute(_xmlTag, "tooltip", getTooltip(), _xmlTagId);
                //            xml.addAttribute(_xmlTag, "parent", _pparent ? _pparent->getName(): "none", _xmlTagId);
            }
        }
        
        //--------------------------------------------------------------
        void Parameter::readFromXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::Parameter::readFromXml: " << getPath();
            
            if(_paramValue) _paramValue->readFromXml(xml, bFullSchema);
            if(bFullSchema) {
                setTooltip(xml.getAttribute(_xmlTag, "tooltip", "", _xmlTagId));
            }
        }
        
        //--------------------------------------------------------------
//        // Controller stuff
//        void Parameter::addSender(ControllerI *controller) {
//            controllers.addSender(controller);
//            controller->setParam(this);
//        }
//        
//        //--------------------------------------------------------------
//        void Parameter::addReceiver(ControllerI *controller) {
//            controllers.addReceiver(controller);
//            controller->setParam(this);
//        }

 
	}
}