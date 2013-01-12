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
		ParameterGroup::ParameterGroup(string name, ParameterGroup *parent)
        : Parameter(name, parent) {
            clear();
//            ofLogVerbose() << "msa::ControlFreak::ParameterGroup::ParameterGroup: " <<  getPath();
        }

        
        //--------------------------------------------------------------
		ParameterGroup::~ParameterGroup() {
            ofLogVerbose() << "msa::ControlFreak::ParameterGroup::~ParameterGroup: " <<  getPath();
            clear();
		}
        
        //--------------------------------------------------------------
		void ParameterGroup::clear() {
            _params.clear();
            
            while (!_groupStack.empty()) _groupStack.pop();
            _groupStack.push(this); // start with this as current group for adding
        }

        //--------------------------------------------------------------
		// if parameter non empty, saves the filename
		void ParameterGroup::setFilename(string filename) {
            _filename = filename;
		}
        
        //--------------------------------------------------------------
        string ParameterGroup::getFullFilename(string filename, bool bFullSchema) {
            setFilename(filename);
			if(filename.empty() == false) _filename = filename;
            if(_filename.empty()) {
                if(!ofDirectory::doesDirectoryExist("presets")) ofDirectory::createDirectory("presets");
                _filename = "presets/" + getName();
            }
            
            string fullFilename = _filename;
            if(filename.empty()) fullFilename +=  bFullSchema ? "-schema.xml" :  ".xml";
            string ext = ofFilePath::getFileExt(fullFilename);
            if(ext.empty()) fullFilename += ".xml";
            
            return fullFilename;
        }

		
        //--------------------------------------------------------------
        bool ParameterGroup::saveXmlValues(string filename) {
            return saveXml(filename, false);
        }
        
        //--------------------------------------------------------------
        bool ParameterGroup::loadXmlValues(string filename) {
            return loadXml(filename, false);
        }
        
        //--------------------------------------------------------------
        bool ParameterGroup::saveXmlSchema(string filename) {
            return saveXml(filename, true);
        }
        
        //--------------------------------------------------------------
        bool ParameterGroup::loadXmlSchema(string filename) {
            return loadXml(filename, true);
        }

        //--------------------------------------------------------------
		bool ParameterGroup::saveXml(string filename, bool bFullSchema) {
            ofxXmlSettings xml;
            xml.addTag("ofxMSAControlFreak");
            xml.addAttribute("ofxMSAControlFreak", "version", 1.0f, 0); // TODO: global version number?
            xml.addAttribute("ofxMSAControlFreak", "bFullSchema", bFullSchema, 0);
            xml.pushTag("ofxMSAControlFreak");
            writeToXml(xml, bFullSchema);
            xml.popTag();
            return xml.saveFile(getFullFilename(filename, bFullSchema));
		}
		
        //--------------------------------------------------------------
		bool ParameterGroup::loadXml(string filename, bool bFullSchema) {
            ofxXmlSettings xml;
            bool b = xml.loadFile(getFullFilename(filename, bFullSchema));
            if(!b) {
                ofLogError() << "msa::ControlFreak::ParameterGroup::loadXml: file not found " << filename;
                return false;
            }
            
            // only do full schema if it's requested, and the xml has the data
            bool bFullSchemaInXml = xml.getAttribute("ofxMSAControlFreak", "bFullSchema", 1, 0);
            if(bFullSchema != bFullSchemaInXml) {
                if(bFullSchema) {
                    ofLogWarning() << "msa::ControlFreak::ParameterGroup::loadXml: requested full schema load but XML contains only values. Loading just values.";
                } else {
                    ofLogWarning() << "msa::ControlFreak::ParameterGroup::loadXml: requested only values load but XML contains full schema. Loading just values.";
                }
            }
            
            xml.pushTag("ofxMSAControlFreak");
            readFromXml(xml, bFullSchema);
            xml.popTag();
            return b;
		}
        
        //--------------------------------------------------------------
        void ParameterGroup::writeToXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::writeToXml: " << getPath();
            
            Parameter::writeToXml(xml, bFullSchema);
            xml.pushTag(_xmlTag, _xmlTagId);
            
            for(int i=0; i<_params.size(); i++) {
                Parameter &p = _params[i];
                p.writeToXml(xml, bFullSchema);
            }
            
            xml.popTag();
        }
        
        // TODO: if xml contains more panels, only load panel which is relevant. if xml contains less panels, only load panels which exist
        //--------------------------------------------------------------
        void ParameterGroup::readFromXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::readFromXml: " << getPath() << " pushLevel: " << xml.getPushLevel();

            Parameter::readFromXml(xml, bFullSchema);
            string s = xml.getAttribute(_xmlTag, "name", "", _xmlTagId);
            if(s != getName()) {
                ofLogError() << "msa::ControlFreak::ParameterGroup::readFromXml: trying to load '" << s << "' into ParameterGroup '" << getPath() << "'";
                return;
            }
            xml.pushTag(_xmlTag, _xmlTagId);
            
            int numTags = xml.getNumTags(_xmlTag);

            for(int i=0; i<numTags; i++) {
                string xname = xml.getAttribute(_xmlTag, "name", "", i);
                string xpath = xml.getAttribute(_xmlTag, "path", "", i);
                printf("Parameter %i %s %s\n", i, xname.c_str(), xpath.c_str());
                Parameter *p = getPtr(xname);
                if(p) {
                    p->_xmlTagId = i;
                    p->readFromXml(xml, bFullSchema);
                } else {
                    ofLogWarning() << "Parameter " << xname << " (" << xpath << ") not found in group" << getPath();
                    // TODO: add missing controls if in schema mode?
                }
            }
            
            xml.popTag();
        }
        
        
        //--------------------------------------------------------------
        void ParameterGroup::update() {
            Parameter::update();
            for(int i=0; i<_params.size(); i++) _params[i].update();
        }
        

        //--------------------------------------------------------------
		ParameterInt& ParameterGroup::addInt(string name) {
            if(_params.exists(name)) return get<ParameterInt>(name);
            return (ParameterInt&) add(new ParameterInt(name, _groupStack.top()));
		}
		
        //--------------------------------------------------------------
		ParameterFloat& ParameterGroup::addFloat(string name) {
            if(_params.exists(name)) return get<ParameterFloat>(name);
			return (ParameterFloat&) add(new ParameterFloat(name, _groupStack.top()));
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addBool(string name) {
            if(_params.exists(name)) return get<ParameterBool>(name);
            ParameterBool *p = new ParameterBool(name, _groupStack.top());
            p->setMode(ParameterBool::kToggle);
            add(p);
			return *p;
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addBang(string name) {
            if(_params.exists(name)) return get<ParameterBool>(name);
            ParameterBool *p = new ParameterBool(name, _groupStack.top());
            p->setMode(ParameterBool::kBang);
            add(p);
			return *p;
		}
		
        //--------------------------------------------------------------
		ParameterNamedIndex& ParameterGroup::addNamedIndex(string name) {
            if(_params.exists(name)) return get<ParameterNamedIndex>(name);
			return (ParameterNamedIndex&) add(new ParameterNamedIndex(name, _groupStack.top()));
		}
        
        
        //--------------------------------------------------------------
        ParameterVec3f& ParameterGroup::addVec3f(string name) {
//            if(_params.exists(name)) return *getVec3f(name);
//			return (ParameterVec3f&) add(new ParameterVec3f(name, _groupStack.top()));
        }
        
        
        //--------------------------------------------------------------
		void ParameterGroup::startGroup(string name) {
            ParameterGroup* g;
            if(_params.exists(name)) g = getGroupPtr(name);
            else g = (ParameterGroup*)&add(new ParameterGroup(name, _groupStack.top()));
            _groupStack.push(g);
		}
		
        //--------------------------------------------------------------
		void ParameterGroup::endGroup() {
			_groupStack.pop();
		}
        
        
        //--------------------------------------------------------------
		Parameter& ParameterGroup::add(Parameter* param) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroup::add: " << param->getPath();
			
            ParameterGroup *currentGroup = _groupStack.top();
            if(currentGroup == this) {
                if(_params.exists(param->getName())) {
                    ofLogError() << "msa::ControlFreak::ParameterGroup::add: " << param->getPath() << " - path already exists, returning existing parameter";
                    return _params[param->getName()];
                } else {
                    _params.push_back(param->getName(), param);
                    param->setParent(this);
                    return *param;
                }
            } else {
                return currentGroup->add(param);
            }
		}
        
        
        //--------------------------------------------------------------
        int ParameterGroup::size() const {
			return _params.size();
		}
		
        //--------------------------------------------------------------
        Parameter& ParameterGroup::get(int index) const {
            return _params[index];
        }

        //--------------------------------------------------------------
        Parameter& ParameterGroup::get(string path) const {
            return *getPtr(path);
        }
        
        //--------------------------------------------------------------
        Parameter* ParameterGroup::getPtr(string path) const {
            // look for path divider
            size_t pathDividerPos = path.find(getPathDivider());
            
            // if path divider doesn't exist, search this group
            if(pathDividerPos == string::npos) {
                
                // if parameter doesn't exist, return with error
                if(!_params.exists(path)) {
                    ofLogError() << "msa::ControlFreak::ParameterGroup::get: " << path << " does not exist in Group: " << getPath();
                    return NULL;  // return NULL
                }
                
                return &_params[path];
                
            } else {
                // there is path divider, split the string and search the first group
                string part1 = path.substr(0, pathDividerPos);
                string part2 = path.substr(pathDividerPos+1);

                return getGroupPtr(part1)->getPtr(part2);
            }
        }
        
        //--------------------------------------------------------------
        ParameterGroup& ParameterGroup::getGroup(string path) const {
            return get<ParameterGroup>(path);
        }
        
        //--------------------------------------------------------------
        ParameterGroup* ParameterGroup::getGroupPtr(string path) const {
            return getPtr<ParameterGroup>(path);
        }
        
        
        //--------------------------------------------------------------
		Parameter& ParameterGroup::operator[](int index) const {
            return get(index);
		}

        //--------------------------------------------------------------
		Parameter& ParameterGroup::operator[](string path) const {
            return get(path);
		}
		
        //--------------------------------------------------------------
		Parameter& ParameterGroup::operator[](const char* path) const {
            return get(path);
		}
        
     }
}
