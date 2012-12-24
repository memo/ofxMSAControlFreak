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
		Parameter& ParameterGroup::addParameter(Parameter *param) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::addParameter " << param->getPath();
			
            ParameterGroup *currentGroup = _groupStack.top();
            // avoid infinite recursion
            if(currentGroup == this) {
                _paramMap[param->getPath()] = param;
                _paramArr.push_back(param);
                
                getNumParams();	// to check if correctly added to both containers
                return *param;
            } else {
                return currentGroup->addParameter(param);
            }
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
        //		void ParameterContainer::updateControllers(bool doChildGroups) {
        //			int np = getNumParams();
        //			for(int i=0; i<np; i++) _paramArr[i]->updateControllers();
        //
        //			if(doChildGroups) {
        //				int ng = numGroups();
        //				for(int i=0; i<ng; i++) _groupArr[i]->updateControllers();
        //			}
        //		}
		
		//		void ParameterContainer::checkValueHasChanged() {
		//			for(int i=0; i<size(); i++) _paramArr[i]->checkValueHasChanged();
		//		}
		
		
        

        
    }
}
