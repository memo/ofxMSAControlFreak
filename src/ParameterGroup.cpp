/*
 *  MSACFParameters.cpp
 *  UK Summer Games v2
 *
 *  Created by Memo Akten on 23/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "ofxMSAControlFreak/src/ControlFreak.h"
#include "ofxMSAControlFreak/src/ParameterGroup.h"

//#include <boost/property_tree/xml_parser.hpp>
//#include <boost/property_tree/info_parser.hpp>
//#include <boost/property_tree/json_parser.hpp>
//#include <boost/foreach.hpp>

namespace msa {
	namespace ControlFreak {
        
        //--------------------------------------------------------------
		ParameterGroup::ParameterGroup(string name, string pathDivider) {
			setName(name);
			_pathStack.push("");
            _pathDivider = pathDivider;
			_filename = "MSAControlFreak.xml";
		}
		
        //--------------------------------------------------------------
		ParameterGroup::~ParameterGroup() {
			int np = numParams();
			for(int i=0; i<np; i++) delete _paramArr[i];
		}
        
        //--------------------------------------------------------------
		void ParameterGroup::setName(string s) {
			_name = s;
			_filename = _name;
		}
		
        //--------------------------------------------------------------
		string ParameterGroup::name() {
			return _name;
		}
		
        
		
        //--------------------------------------------------------------
        //		void ParameterGroup::updateParamFromTree(string path) {
        //			printf("ParameterGroup::updateParamFromTree: %s\n", path.c_str());
        //			Types::Index type	= Types::indexForName(_ptree.get<string>(path + kPathDivider + "type"));
        //			float min			= _ptree.get<float>(path + kPathDivider + "min");
        //			float max			= _ptree.get<float>(path + kPathDivider + "max");
        //			float value			= _ptree.get<float>(path + kPathDivider + "value");
        //
        //			if(_paramMap[path] == NULL) {
        //				switch (type) {
        //					case Types::kFloat:
        //						addFloat(path);
        //						break;
        //
        //					case Types::kInt:
        //						addInt(path);
        //						break;
        //
        //					case Types::kToggle:
        //						addToggle(path);
        //						break;
        //
        //					case Types::kBang:
        //						addBang(path);
        //						break;
        //
        //					case Types::kNamedIndex:
        //						addNamedIndex(path);
        //						break;
        //
        //					default:
        //						assert(false);
        //						break;
        //				}
        //			}
        //
        //			_paramMap[path]->readFromPropertyTree(_ptree);
        //		}
        
        
        //--------------------------------------------------------------
        int ParameterGroup::numParams() {
			assert(_paramArr.size() == _paramMap.size());	// probably tried to add a parameter with the same name (in the same group)
			return _paramMap.size();
		}
		
        //--------------------------------------------------------------
		Parameter& ParameterGroup::operator[](string name) {
			return *_paramMap[name];
		}
		
        //--------------------------------------------------------------
		Parameter& ParameterGroup::operator[](int index) {
			return *_paramArr[index];
		}
		
        //--------------------------------------------------------------
		// if parameter non empty, saves the filename
		void ParameterGroup::setFilename(string filename) {
			if(filename.empty() == false) _filename = filename;
		}
		
        //--------------------------------------------------------------
		bool ParameterGroup::saveXml(bool bFull, string filename) {
			setFilename(filename);
            ofxXmlSettings xml;
            
            for(int i=0; i<_paramArr.size(); i++) {
                Parameter &p = *_paramArr[i];
                
                if(p.type() == Types::kCommand) {
                    ParameterInt &pi = (ParameterInt&) p;
                    if(pi.getValue() == Types::kStartGroup) {
                        int tagid = xml.addTag("group");
                        xml.addAttribute("group", "name", pi.name(), tagid);
                        xml.pushTag("group", tagid);
                        
                    } else if(pi.getValue() == Types::kEndGroup) {
                        xml.popTag();
                    }
                } else {
                    string tag = "parameter";// + ofToString(i);
                    int tagid = xml.addTag(tag);
                    xml.addAttribute(tag, "name", p.name(), tagid);
                    xml.addAttribute(tag, "path", p.path(), tagid);
                    p.writeToXml(xml, bFull, tag, tagid);
                }
            }
            return xml.saveFile(_filename + (bFull ? "-schema.xml" : "-values.xml"));
		}
		
        //--------------------------------------------------------------
		bool ParameterGroup::loadXml(bool bFull, string filename) {
			setFilename(filename);
		}
        
        //--------------------------------------------------------------
		string ParameterGroup::makePath(string parent, string child) {
			return parent.empty() ? child : parent + getPathDivider() + child;
		}
        
        //--------------------------------------------------------------
		string ParameterGroup::addToPath(string name) {
			return makePath(_pathStack.top(), name);
		}
		
        //--------------------------------------------------------------
		Parameter& ParameterGroup::addParameter(Parameter *param) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::addParameter " << param->path().c_str();
			
			_paramMap[param->path()] = param;
			_paramArr.push_back(param);
			
			numParams();	// to check if correctly added to both containers
			
			return *param;
		}
        
		
        //--------------------------------------------------------------
		ParameterInt& ParameterGroup::addInt(string name) {
			return (ParameterInt&) addParameter(new ParameterInt(this, addToPath(name), Types::kInt));
		}
		
        //--------------------------------------------------------------
		ParameterFloat& ParameterGroup::addFloat(string name) {
			return (ParameterFloat&) addParameter(new ParameterFloat(this, addToPath(name), Types::kFloat));
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addToggle(string name) {
			return (ParameterBool&) addParameter(new ParameterBool(this, addToPath(name), Types::kToggle));
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addBang(string name) {
			return (ParameterBool&) addParameter(new ParameterBool(this, addToPath(name), Types::kBang));
		}
		
        //--------------------------------------------------------------
		ParameterNamedIndex& ParameterGroup::addNamedIndex(string name) {
			return (ParameterNamedIndex&) addParameter(new ParameterNamedIndex(this, addToPath(name)));
		}
        
        //--------------------------------------------------------------
        void ParameterGroup::addCommand(string name, Types::Command command) {
            ((ParameterInt&)addParameter(new ParameterInt(this, addToPath(name), Types::kCommand))).setValue(command);
        }
        
		//-------------- group functions --------------
		void ParameterGroup::startGroup(string name) {
            addCommand(name, Types::kStartGroup);
			_pathStack.push(addToPath(name));
		}
		
        //--------------------------------------------------------------
		void ParameterGroup::endGroup() {
            addCommand(_pathStack.top(), Types::kEndGroup);
			_pathStack.pop();
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