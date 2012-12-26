//
//  ParameterGroup.cpp
//  ofxMSAControlFreak example
//
//  Created by Memo Akten on 24/12/2012.
//
//

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        
        //--------------------------------------------------------------
		ParameterGroup::ParameterGroup(ParameterGroup *parent, string name, Type::Index typeIndex)
        : Parameter(parent, name, typeIndex) {
            ofLogVerbose() << "msa::ControlFreak::ParameterGroup::ParameterGroup " <<  getPath();
            _groupStack.push(this); // start with this as current group for adding
        }

        //--------------------------------------------------------------
		ParameterGroup::~ParameterGroup() {
            ofLogVerbose() << "msa::ControlFreak::ParameterGroup::~ParameterGroup " <<  getPath();
			int np = getNumParams();
			for(int i=0; i<np; i++) delete _paramArr[i];
		}
        
        
        
        //--------------------------------------------------------------
		// if parameter non empty, saves the filename
		void ParameterGroup::setFilename(string filename) {
			if(filename.empty() == false) _filename = filename;
            if(_filename.empty()) _filename = _name;
		}
		
        //--------------------------------------------------------------
		bool ParameterGroup::saveXml(bool bFull, string filename) {
			setFilename(filename);
            ofxXmlSettings xml;
            xml.addTag("ofxMSAControlFreak");
            xml.addAttribute("ofxMSAControlFreak", "version", 1.0f, 0);
            xml.pushTag("ofxMSAControlFreak");
            writeToXml(xml, bFull);
            xml.popTag();
            return xml.saveFile(_filename + (bFull ? "-schema.xml" : "-values.xml"));
		}
		
        //--------------------------------------------------------------
		bool ParameterGroup::loadXml(bool bFull, string filename) {
			setFilename(filename);
		}
        
        //--------------------------------------------------------------
        void ParameterGroup::writeToXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::writeToXml " << getPath();
            
            Parameter::writeToXml(xml, bFull);
            xml.pushTag(_xmlTag, _xmlTagId);
            
            for(int i=0; i<_paramArr.size(); i++) {
                Parameter &p = *_paramArr[i];
                p.writeToXml(xml, bFull);
            }
            
            xml.popTag();
        }
        
        //--------------------------------------------------------------
        void ParameterGroup::readFromXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::readFromXml " << getPath();
            
        }
        
        
        
        
        //--------------------------------------------------------------
        void ParameterGroup::update() {
            Parameter::update();
            int np = getNumParams();
            for(int i=0; i<np; i++) {
                Parameter &p = getParameter(i);
                p.update();
            }
        }
        

        
        
        //--------------------------------------------------------------
		ParameterInt& ParameterGroup::addInt(string name) {
			return (ParameterInt&) addParameter(new ParameterInt(_groupStack.top(), name, Type::kInt));
		}
		
        //--------------------------------------------------------------
		ParameterFloat& ParameterGroup::addFloat(string name) {
			return (ParameterFloat&) addParameter(new ParameterFloat(_groupStack.top(), name, Type::kFloat));
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addToggle(string name) {
			return (ParameterBool&) addParameter(new ParameterBool(_groupStack.top(), name, Type::kToggle));
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addBang(string name) {
			return (ParameterBool&) addParameter(new ParameterBool(_groupStack.top(), name, Type::kBang));
		}
		
        //--------------------------------------------------------------
		ParameterNamedIndex& ParameterGroup::addNamedIndex(string name) {
			return (ParameterNamedIndex&) addParameter(new ParameterNamedIndex(_groupStack.top(), name));
		}
        
        
        //--------------------------------------------------------------
        ParameterVec3f& ParameterGroup::addVec3f(string name) {
			return (ParameterVec3f&) addParameter(new ParameterVec3f(_groupStack.top(), name));
        }
        
        
        //--------------------------------------------------------------
		void ParameterGroup::startGroup(string name) {
            _groupStack.push( (ParameterGroup*)&addParameter(new ParameterGroup(_groupStack.top(), name)) );
		}
		
        //--------------------------------------------------------------
		void ParameterGroup::endGroup() {
			_groupStack.pop();
		}
        
        //--------------------------------------------------------------
		Parameter& ParameterGroup::addParameter(Parameter *param) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::addParameter " << param->getPath();
			
            ParameterGroup *currentGroup = _groupStack.top();
            // avoid infinite recursion
            if(currentGroup == this) {
                _paramMap[param->getName()] = param;
                _paramArr.push_back(param);
                param->setParent(this);
                getNumParams();	// to check if correctly added to both containers
                return *param;
            } else {
                return currentGroup->addParameter(param);
            }
		}
        
     
        
        
        //--------------------------------------------------------------
        int ParameterGroup::getNumParams() const {
			assert(_paramArr.size() == _paramMap.size());	// probably tried to add a parameter with the same name (in the same group)
			return _paramMap.size();
		}
		
        
        //--------------------------------------------------------------
        Parameter& ParameterGroup::getParameter(int index) {
			return *_paramArr[index];
        }
        
        //--------------------------------------------------------------
        Parameter& ParameterGroup::getParameter(string path) {
            //            ofLogVerbose() << "msa::ControlFreak::ParameterGroup::getParameter " << path;
            Parameter *p = _paramMap.at(path);
            return *p;
            //            vector<string> pathbits = ofSplitString(path, getPathDivider(), true, true);
            //            ParameterGroup *p = this;
            //            for(int i=0; i<pathbits.size(); i++) {
            //                //                p = &_paramMap[pathbits[i]];
            //                // TODO:
            //            }
            //			return *_paramMap[path];
        }
        
        //--------------------------------------------------------------
        ParameterInt& ParameterGroup::getInt(string path) {
            return dynamic_cast<ParameterInt&>(getParameter(path));
        }
        
        //--------------------------------------------------------------
        ParameterFloat& ParameterGroup::getFloat(string path) {
            return dynamic_cast<ParameterFloat&>(getParameter(path));
        }
        
        //--------------------------------------------------------------
        ParameterBool& ParameterGroup::getBool(string path) {
            return dynamic_cast<ParameterBool&>(getParameter(path));
        }
        
        //--------------------------------------------------------------
        ParameterNamedIndex& ParameterGroup::getNamedIndex(string path) {
            return dynamic_cast<ParameterNamedIndex&>(getParameter(path));
        }
        
        //--------------------------------------------------------------
        ParameterGroup& ParameterGroup::getGroup(string path) {
            return dynamic_cast<ParameterGroup&>(getParameter(path));
        }
        
        
        
        //--------------------------------------------------------------
        //		Parameter& ParameterGroup::operator[](int index) {
        //            return getParameter(index);
        //		}
        //
        //        //--------------------------------------------------------------
        //		Parameter& ParameterGroup::operator[](string path) {
        //            return getParameter(path);
        //		}
		
        
        
        
          //--------------------------------------------------------------
        //		void ParameterGroup::updateControllers(bool doChildGroups) {
        //			int np = getNumParams();
        //			for(int i=0; i<np; i++) _paramArr[i]->updateControllers();
        //
        //			if(doChildGroups) {
        //				int ng = numGroups();
        //				for(int i=0; i<ng; i++) _groupArr[i]->updateControllers();
        //			}
        //		}
		
		//		void ParameterGroup::checkValueHasChanged() {
		//			for(int i=0; i<size(); i++) _paramArr[i]->checkValueHasChanged();
		//		}
		
		
        

        
    }
}
