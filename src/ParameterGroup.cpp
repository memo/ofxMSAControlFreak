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
        
        Parameter Parameter::dummy(NULL, "DUMMY", Type::kUnknown);
        ParameterGroup ParameterGroup::dummy(NULL, "DUMMY", Type::kUnknown);
        ParameterInt ParameterInt::dummy(NULL, "DUMMY", Type::kUnknown);
        ParameterFloat ParameterFloat::dummy(NULL, "DUMMY", Type::kUnknown);
        ParameterBool ParameterBool::dummy(NULL, "DUMMY", Type::kUnknown);
        ParameterNamedIndex ParameterNamedIndex::dummy(NULL, "DUMMY", Type::kUnknown);
        
        
        //--------------------------------------------------------------
		ParameterGroup::ParameterGroup(ParameterGroup *parent, string name, Type::Index typeIndex)
        : Parameter(parent, name, typeIndex) {
            clear();
//            ofLogVerbose() << "msa::ControlFreak::ParameterGroup::ParameterGroup " <<  getPath();
        }

        //--------------------------------------------------------------
		ParameterGroup::~ParameterGroup() {
            ofLogVerbose() << "msa::ControlFreak::ParameterGroup::~ParameterGroup " <<  getPath();
            clear();
		}
        
        //--------------------------------------------------------------
		void ParameterGroup::clear() {
//            int np = getNumParams();
//            for(int i=0; i<np; i++) delete _paramArr[i];
            _paramArr.clear();
            _paramMap.clear();
            
            while (!_groupStack.empty()) _groupStack.pop();
            _groupStack.push(this); // start with this as current group for adding
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
            return xml.saveFile(_filename);// + (bFull ? "-schema.xml" : "-values.xml"));
		}
		
        //--------------------------------------------------------------
		bool ParameterGroup::loadXml(bool bFull, string filename) {
			setFilename(filename);
            ofxXmlSettings xml;
            bool b = xml.loadFile(_filename);
            xml.pushTag("ofxMSAControlFreak");
            readFromXml(xml, bFull);
            xml.popTag();
            return b;
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
            
            Parameter::readFromXml(xml, bFull);
            string s = xml.getAttribute(_xmlTag, "name", "", _xmlTagId);
            if(s != getName()) {
                ofLogError() << "msa::ControlFreak::ParameterGroup::readFromXml - trying to load '" << s << "' into ParameterGroup '" << getPath() <<"'";
                return;
            }
            xml.pushTag(_xmlTag, _xmlTagId);
            
            int numTags = xml.getNumTags(_xmlTag);
            printf("readFromXml\n");
            // TODO, add parameters to group if they aren't in there?
            for(int i=0; i<numTags; i++) {
                string s = xml.getAttribute(_xmlTag, "name", "", i);
                printf("%i %s\n", i, s.c_str());
                Parameter &p = getParameter(s);
                p.readFromXml(xml, bFull);
            }
            
            xml.popTag();
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
            if(_paramMap.find(name) != _paramMap.end()) return getInt(name);
            return (ParameterInt&) addParameter(new ParameterInt(_groupStack.top(), name, Type::kInt));
		}
		
        //--------------------------------------------------------------
		ParameterFloat& ParameterGroup::addFloat(string name) {
            if(_paramMap.find(name) != _paramMap.end()) return getFloat(name);
			return (ParameterFloat&) addParameter(new ParameterFloat(_groupStack.top(), name, Type::kFloat));
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addBool(string name) {
            if(_paramMap.find(name) != _paramMap.end()) return getBool(name);
            ParameterBool *p = new ParameterBool(_groupStack.top(), name, Type::kBool);
            p->setMode(ParameterBool::kToggle);
            addParameter(p);
			return *p;
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addBang(string name) {
            if(_paramMap.find(name) != _paramMap.end()) return getBool(name);
            ParameterBool *p = new ParameterBool(_groupStack.top(), name, Type::kBool);
            p->setMode(ParameterBool::kBang);
            addParameter(p);
			return *p;
		}
		
        //--------------------------------------------------------------
		ParameterNamedIndex& ParameterGroup::addNamedIndex(string name) {
            if(_paramMap.find(name) != _paramMap.end()) return getNamedIndex(name);
			return (ParameterNamedIndex&) addParameter(new ParameterNamedIndex(_groupStack.top(), name));
		}
        
        
        //--------------------------------------------------------------
        ParameterVec3f& ParameterGroup::addVec3f(string name) {
//            if(_paramMap.find(name) != _paramMap.end()) return getVec3f(name);
			return (ParameterVec3f&) addParameter(new ParameterVec3f(_groupStack.top(), name));
        }
        
        
        //--------------------------------------------------------------
		void ParameterGroup::startGroup(string name) {
            ParameterGroup* g;
            if(_paramMap.find(name) != _paramMap.end()) g = &getGroup(name);
            else g = (ParameterGroup*)&addParameter(new ParameterGroup(_groupStack.top(), name));
            _groupStack.push(g);
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
                map<string, Parameter*>::iterator p = _paramMap.find(param->getName());
                if(p == _paramMap.end()) {
                    _paramMap[param->getName()] = param;
                    _paramArr.push_back(ParameterPtr(param));
                    param->setParent(this);
                    getNumParams();	// to check if correctly added to both containers
                    return *param;
                } else {
                    ofLogError() << "msa::ControlFreak::ParameterGroup::addParameter - " << param->getPath() << " - path already exists, returning existing parameter";
                    delete param;
                    return *_paramMap[param->getName()];
                }
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
            
            // look for path divider
            size_t pathDividerPos = path.find(getPathDivider());
            
            // if path divider doesn't exist, search this group
            if(pathDividerPos == string::npos) {
                
                // if parameter doesn't exist, return with error
                if(_paramMap.find(path) == _paramMap.end()) {
                    ofLogError() << "msa::ControlFreak::ParameterGroup::getParameter - " << path << " does not exist in Group: " << getPath();
                    return Parameter::dummy;
                } else {
                    return *_paramMap[path];
                }
            } else {
                // there is path divider, split the string and search the first group
                
                string part1 = path.substr(0, pathDividerPos);
                string part2 = path.substr(pathDividerPos+1);
//                ofLogNotice() << "FIRST GROUP: " << part1 << " PART2: " << part2;
                return getGroup(part1).getParameter(part2);
                
            }
        }
        
        //--------------------------------------------------------------
        ParameterInt& ParameterGroup::getInt(string path) {
            return get<ParameterInt>(path);
        }
        
        //--------------------------------------------------------------
        ParameterFloat& ParameterGroup::getFloat(string path) {
            return get<ParameterFloat>(path);
        }
        
        //--------------------------------------------------------------
        ParameterBool& ParameterGroup::getBool(string path) {
            return get<ParameterBool>(path);
        }
        
        //--------------------------------------------------------------
        ParameterNamedIndex& ParameterGroup::getNamedIndex(string path) {
            return get<ParameterNamedIndex>(path);
        }
        
        //--------------------------------------------------------------
        ParameterGroup& ParameterGroup::getGroup(string path) {
            return get<ParameterGroup>(path);
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
