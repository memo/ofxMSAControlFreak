/*
 *  MSAControlFreeParameter.cpp
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */


#include "ofxMSAControlFreak/src/Parameter.h"
#include "ofxMSAControlFreak/src/ParameterGroup.h"

namespace msa {
	namespace ControlFreak {

        //--------------------------------------------------------------
		string Parameter::path() const {
			return _path;
		}
		
        //--------------------------------------------------------------
		string Parameter::name() const {
			return _name;
		}
		
        //--------------------------------------------------------------
		string Parameter::fullName() const {
			string s;
//			for(int i=0; i<_controllers.size(); i++) s += "[" + _controllers[i]->toString() + "]";
			return s + " " + name();
		}
		
        //--------------------------------------------------------------
		Types::Index Parameter::type() const {
			return _typeIndex;
		}
		
        //--------------------------------------------------------------
		string Parameter::typeName() const {
			return nameForIndex(_typeIndex);
		}

		
        //--------------------------------------------------------------
        void Parameter::writeToXml(ofxXmlSettings &xml, bool bFull, string tag, int tagid) {
			ofLogVerbose() << "msa::ControlFreak::Parameter::writeToXml " << _path.c_str();
        }
        
        //--------------------------------------------------------------
        void Parameter::readFromXml(ofxXmlSettings &xml, bool bFull, string tag, int tagid) {
			ofLogVerbose() << "msa::ControlFreak::Parameter::readFromXml " << _path.c_str();
        }
        
        
        //--------------------------------------------------------------
        Parameter::Parameter(ParameterGroup *parent, string path, Types::Index typeIndex) : _parent(parent), _path(path), _typeIndex(typeIndex) {
            ofLogVerbose() << "msa::ControlFreak::Parameter::Parameter " <<  _path.c_str();
            
            if(parent) {
                size_t lastDividerPos = _path.rfind(parent->getPathDivider());
                _name = lastDividerPos == string::npos ? _path : _path.substr(lastDividerPos+1);
            } else {
                _name = _path;
            }
        }

 
	}
}