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
		ParameterGroup::ParameterGroup(string name, ParameterGroup *parent)
        : Parameter(name, parent) {
            clear();
            _bOpen = true;
            makeGroup();
            _params.setOwnsObjects(false);
//            ofLogVerbose() << "msa::controlfreak::ParameterGroup::ParameterGroup: " <<  getPath();
        }

        
        //--------------------------------------------------------------
		ParameterGroup::~ParameterGroup() {
            ofLogVerbose() << "msa::controlfreak::ParameterGroup::~ParameterGroup: " <<  getPath();
            clear();    // TODO: bug if you add an existing (i.e. on the stack) parameter, since it tries to be deleted. 
		}
        
        //--------------------------------------------------------------
		void ParameterGroup::clear() {
            _params.clear();
            
            while (!_groupStack.empty()) _groupStack.pop();
            _groupStack.push(this); // start with this as current group for adding
        }
        
        //--------------------------------------------------------------
//        void ParameterGroup::update() {
//            Parameter::update();
//            for(int i=0; i<_params.size(); i++) _params[i].update();
//        }
        
        //--------------------------------------------------------------
        ParameterGroup& ParameterGroup::setMode(Mode mode) {
            _mode = mode;
            return *this;
        }

        //--------------------------------------------------------------
        ParameterGroup::Mode ParameterGroup::getMode() const {
            return _mode;
        }
        
        //--------------------------------------------------------------
        ParameterGroup& ParameterGroup::makePage() {
            setMode(kPage);
            return *this;
        }
        
        //--------------------------------------------------------------
        ParameterGroup& ParameterGroup::makeGroup() {
            setMode(kGroup);
            return *this;
        }

        //--------------------------------------------------------------
        ParameterGroup& ParameterGroup::open() {
            _bOpen = true;
            return *this;
        }

        //--------------------------------------------------------------
        ParameterGroup& ParameterGroup::close() {
            _bOpen = false;
            return *this;
        }

        
        //--------------------------------------------------------------
        bool& ParameterGroup::isOpen() {
            return _bOpen;
        }
        
        //--------------------------------------------------------------
		ParameterInt& ParameterGroup::addInt(string name) {
            return (ParameterInt&) add(new ParameterInt(name, _groupStack.top()));
		}
		
        //--------------------------------------------------------------
		ParameterFloat& ParameterGroup::addFloat(string name) {
			return (ParameterFloat&) add(new ParameterFloat(name, _groupStack.top()));
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addBool(string name) {
            ParameterBool *p = new ParameterBool(name, _groupStack.top());
            p->setMode(ParameterBool::kToggle);
            add(p);
			return *p;
		}
		
        //--------------------------------------------------------------
		ParameterBool& ParameterGroup::addBang(string name) {
            ParameterBool *p = new ParameterBool(name, _groupStack.top());
            p->setMode(ParameterBool::kBang);
            add(p);
			return *p;
		}
		
        //--------------------------------------------------------------
		ParameterNamedIndex& ParameterGroup::addNamedIndex(string name) {
			return (ParameterNamedIndex&) add(new ParameterNamedIndex(name, _groupStack.top()));
		}
        
        
        //--------------------------------------------------------------
        ParameterVec3f& ParameterGroup::addVec3f(string name) {
//			return (ParameterVec3f&) add(new ParameterVec3f(name, _groupStack.top()));
        }
        
        
        //--------------------------------------------------------------
		ParameterGroup& ParameterGroup::startGroup(string name) {
            ParameterGroup* g = static_cast<ParameterGroup*>(&add(new ParameterGroup(name, _groupStack.top())));
            g->makeGroup();
            _groupStack.push(g);
            return *g;
		}
		
        //--------------------------------------------------------------
		void ParameterGroup::endGroup() {
			_groupStack.pop();
		}
        
        //--------------------------------------------------------------
		ParameterGroup& ParameterGroup::startPage(string name) {
            startGroup(name).makePage();
        }
        
        //--------------------------------------------------------------
        void ParameterGroup::endPage() {
            endGroup();
        }
        
        //--------------------------------------------------------------
		Parameter& ParameterGroup::add(Parameter* param) {
			ofLogVerbose() << "msa::controlfreak::ParameterGroup::add: " << param->getPath();
			
            ParameterGroup *currentGroup = _groupStack.top();
            if(currentGroup == this) {
                
                if(_params.exists(param->getName())) {
//                    delete param;
                    Master::instance().erase(param);
                    string s = "msa::controlfreak::ParameterGroup::add: parameter [" + param->getPath() + "] already exists";
                    ofLogError() << s;
                    throw invalid_argument(s);
                }
                
                _params.push_back(param->getName(), param);
                param->setParent(this);
                return *param;
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
		Parameter& ParameterGroup::operator[](int index) const {
            return get(index);
		}
        

        //--------------------------------------------------------------
        Parameter& ParameterGroup::get(string path) const {
            Parameter *p = getPtr(path);
            if(p == NULL) {
                string s = "msa::controlfreak::get: parameter [" + path + "] doesn't exist";
                ofLogError() << s;
                throw invalid_argument(s);
            }

            return *getPtr(path);
        }
        
        //--------------------------------------------------------------
		Parameter& ParameterGroup::operator[](string path) const {
            return get(path);
		}
		
        //--------------------------------------------------------------
		Parameter& ParameterGroup::operator[](const char* path) const {
            return get(path);
		}
        
        
        //--------------------------------------------------------------
        Parameter* ParameterGroup::getPtr(string path) const {
            // look for path divider
            size_t pathDividerPos = path.find(getPathDivider());
            
            // if path divider doesn't exist, search this group
            if(pathDividerPos == string::npos) {
                
                // if parameter doesn't exist, return NULL with error
                if(!_params.exists(path)) {
                    ofLogError() << "msa::controlfreak::ParameterGroup::get: [" + path + "] does not exist in Group: " + getPath();
                    return NULL;
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
		// if parameter non empty, saves the filename
//		void ParameterGroup::setFilename(string filename) {
//            _filename = filename;
//		}
        
        
        //--------------------------------------------------------------
        bool ParameterGroup::hasChanged(int dir) {
            for(int i=0; i<_params.size(); i++) {
                Parameter &p = _params[i];
                if(p.hasChanged(dir)) return true;
            }
            return false;
        }
        
        //--------------------------------------------------------------
        string ParameterGroup::getFullFilepath(string filename, bool bFullSchema) {
            // default name if filename is blank
            if(filename.empty()) {
                filename = "default";
                
                // append -schema if no filename is given
                filename +=  bFullSchema ? "-schema.xml" :  ".xml";
            }
            
            // make sure filename has correct extension
            string ext = ofFilePath::getFileExt(filename);
            if(ext != "xml") filename += ".xml";

            
            string path = filename;

            // if no folder is given, use default folder
            if(ofFilePath::getEnclosingDirectory(path, false).empty()) path = ofFilePath::join(getPresetsDir(), path);
            
            // create directory path
            ofDirectory::createDirectory(ofFilePath::getEnclosingDirectory(path), true, true);
            
            return path;
        }
        
        //--------------------------------------------------------------
        string ParameterGroup::getPresetsDir() {
            string presetsDir = "ofxMSAControlFreak/" + getPath();
            ofStringReplace(presetsDir, ".", "/");
            ofFilePath::addTrailingSlash(presetsDir);
            return presetsDir;
        }

        //--------------------------------------------------------------
        vector<string> ParameterGroup::getPresetsList() {
            vector<string> ret;

            ofDirectory dir;
            dir.allowExt("xml");
            dir.listDir(getPresetsDir());
            for(int i=0; i<dir.size(); i++) {
                // TODO: do format check here?
                // TODO: only load presets which are relevant to that section?
                ret.push_back(dir.getName(i));
            }
            return ret;
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
        bool ParameterGroup::saveXmlValues(int slot) {
            return saveXml(slot, false);
        }
        
        //--------------------------------------------------------------
        bool ParameterGroup::loadXmlValues(int slot) {
            return loadXml(slot, false);
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
        bool ParameterGroup::saveXmlSchema(int slot) {
            return saveXml(slot, true);
        }
        
        //--------------------------------------------------------------
        bool ParameterGroup::loadXmlSchema(int slot) {
            return loadXml(slot, true);
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
            return xml.saveFile(getFullFilepath(filename, bFullSchema));
		}
		
        //--------------------------------------------------------------
		bool ParameterGroup::loadXml(string filename, bool bFullSchema) {
            ofxXmlSettings xml;
            bool b = xml.loadFile(getFullFilepath(filename, bFullSchema));
            if(!b) {
                ofLogError() << "msa::controlfreak::ParameterGroup::loadXml: file not found " << filename;
                return false;
            }
            
            // only do full schema if it's requested, and the xml has the data
            bool bFullSchemaInXml = xml.getAttribute("ofxMSAControlFreak", "bFullSchema", 1, 0);
            if(bFullSchema != bFullSchemaInXml) {
                if(bFullSchema) {
                    ofLogWarning() << "msa::controlfreak::ParameterGroup::loadXml: requested full schema load but XML contains only values. Loading just values.";
                } else {
                    ofLogWarning() << "msa::controlfreak::ParameterGroup::loadXml: requested only values load but XML contains full schema. Loading just values.";
                }
            }
            
            xml.pushTag("ofxMSAControlFreak");
            _xmlTagId = 0;
            readFromXml(xml, bFullSchema);
            xml.popTag();
            return b;
		}
        
        //--------------------------------------------------------------
        bool ParameterGroup::saveXml(int slot, bool bOnlyValues) {
            saveXml(getPresetForSlot(slot), bOnlyValues);
        }
        
        //--------------------------------------------------------------
        bool ParameterGroup::loadXml(int slot, bool bOnlyValues) {
            loadXml(getPresetForSlot(slot), bOnlyValues);
        }

        //--------------------------------------------------------------
        string ParameterGroup::getPresetForSlot(int slot) {
            vector<string>filenames = getPresetsList();
            if(filenames.empty()) return "";
            slot = ofClamp(slot, 0, filenames.size()-1);
            return filenames[slot];
        }

        //--------------------------------------------------------------
        void ParameterGroup::writeToXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::ParameterGroup::writeToXml: " << getPath();
            
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
			ofLogVerbose() << "msa::controlfreak::ParameterGroup::readFromXml: " << getPath() << " pushLevel: " << xml.getPushLevel();
            
            Parameter::readFromXml(xml, bFullSchema);
            string s = xml.getAttribute(_xmlTag, "name", "", _xmlTagId);
            if(s != getName()) {
                ofLogError() << "msa::controlfreak::ParameterGroup::readFromXml: trying to load '" << s << "' into ParameterGroup '" << getPath() << "'";
                return;
            }
            xml.pushTag(_xmlTag, _xmlTagId);
            
            int numTags = xml.getNumTags(_xmlTag);
            
            for(int i=0; i<numTags; i++) {
                string xname = xml.getAttribute(_xmlTag, "name", "", i);
                string xpath = xml.getAttribute(_xmlTag, "path", "", i);
//                printf("Parameter %i %s %s\n", i, xname.c_str(), xpath.c_str());
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
        
        
     }
}
