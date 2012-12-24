/*
 *  MSACFParameters.cpp
 *  UK Summer Games v2
 *
 *  Created by Memo Akten on 23/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "ofxMSAControlFreak/src/ControlFreak.h"


namespace msa {
	namespace ControlFreak {
        
        //--------------------------------------------------------------
		ParameterGroup::ParameterGroup(ParameterGroup *parent, string name, string pathDivider)
        : Parameter(parent, name, Types::kGroup), _pathDivider(pathDivider) {
            _groupStack.push(this); // start with this as current group
		}
		
        //--------------------------------------------------------------
		ParameterGroup::~ParameterGroup() {
			int np = numParams();
			for(int i=0; i<np; i++) delete _paramArr[i];
		}
        

        //--------------------------------------------------------------
        int ParameterGroup::numParams() {
			assert(_paramArr.size() == _paramMap.size());	// probably tried to add a parameter with the same name (in the same group)
			return _paramMap.size();
		}
		
        //--------------------------------------------------------------
		Parameter& ParameterGroup::operator[](string path) {
            vector<string> pathbits = ofSplitString(path, _pathDivider, true, true);
            ParameterGroup *p = this;
            for(int i=0; i<pathbits.size(); i++) {
//                p = &_paramMap[pathbits[i]];
                // TODO:
            }
			return *_paramMap[path];
		}
		
        //--------------------------------------------------------------
		Parameter& ParameterGroup::operator[](int index) {
			return *_paramArr[index];
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
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::writeToXml " << getPath().c_str();
            
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
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::readFromXml " << getPath().c_str();
            
        }


        //--------------------------------------------------------------
		Parameter& ParameterGroup::addParameter(Parameter *param) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::addParameter " << param->getPath().c_str();
			
            ParameterGroup *currentGroup = _groupStack.top();
            // avoid infinite recursion
            if(currentGroup == this) {
                _paramMap[param->getPath()] = param;
                _paramArr.push_back(param);
                
                numParams();	// to check if correctly added to both containers
                return *param;
            } else {
                return currentGroup->addParameter(param);
            }
		}
        
		
        //--------------------------------------------------------------
		ParameterInt& ParameterGroup::addInt(string name) {
			return (ParameterInt&) addParameter(new ParameterInt(_groupStack.top(), name, Types::kInt));
		}
		
        //--------------------------------------------------------------
		ParameterFloat& ParameterGroup::addFloat(string name) {
			return (ParameterFloat&) addParameter(new ParameterFloat(_groupStack.top(), name, Types::kFloat));
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addToggle(string name) {
			return (ParameterBool&) addParameter(new ParameterBool(_groupStack.top(), name, Types::kToggle));
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addBang(string name) {
			return (ParameterBool&) addParameter(new ParameterBool(_groupStack.top(), name, Types::kBang));
		}
		
        //--------------------------------------------------------------
		ParameterNamedIndex& ParameterGroup::addNamedIndex(string name) {
			return (ParameterNamedIndex&) addParameter(new ParameterNamedIndex(_groupStack.top(), name));
		}
        
        
        //--------------------------------------------------------------
		void ParameterGroup::startGroup(string name) {
            _groupStack.push( (ParameterGroup*)&addParameter(new ParameterGroup(_groupStack.top(), name, getPathDivider())) );
		}
		
        //--------------------------------------------------------------
		void ParameterGroup::endGroup() {
			_groupStack.pop();
		}
        
		
        //--------------------------------------------------------------
        //		void ParameterGroup::updateControllers(bool doChildGroups) {
        //			int np = numParams();
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
		
		
        //--------------------------------------------------------------
		string ParameterGroup::getPathDivider() {
            return _pathDivider;
        }
        
		
	}
}