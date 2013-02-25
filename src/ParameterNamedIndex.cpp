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
		ParameterNamedIndex& ParameterNamedIndex::setLabels(int count, string* labels) {
            _labels.clear();
			for(int i=0; i<count; i++) _labels.push_back(labels[i]);
            setRange(0, _labels.size());
			return *this;
		}
        
        //--------------------------------------------------------------
        ParameterNamedIndex& ParameterNamedIndex::setLabels(vector<string>& labels) {
            _labels.clear();
            _labels = labels;
            setRange(0, _labels.size());
			return *this;
		}
        
        //--------------------------------------------------------------
        ParameterNamedIndex& ParameterNamedIndex::setLabels(int count, ...) {
            _labels.clear();
            va_list vl;
            va_start(vl, count);
            for(int i=0; i<count; i++) {
                _labels.push_back( va_arg(vl, char *) );
            }
            va_end(vl);
            setRange(0, _labels.size());
			return *this;
        }
        
        
        //--------------------------------------------------------------
        int ParameterNamedIndex::size() {
            return _labels.size();
        }
        

        //--------------------------------------------------------------
		string ParameterNamedIndex::getSelectedLabel() {
			return getLabel(value());
		}
		
        //--------------------------------------------------------------
        string ParameterNamedIndex::getLabel(int i) {
            return _labels.size() && i >= 0 && i < size() ? _labels[i] : "";
        }

        //--------------------------------------------------------------
		vector<string>& ParameterNamedIndex::getLabels() {
			return _labels;
		}
		
        //--------------------------------------------------------------
        void ParameterNamedIndex::clearLabels() {
            _labels.clear();
        }
        
        //--------------------------------------------------------------
        void ParameterNamedIndex::addLabel(string s) {
            _labels.push_back(s);
        }

        
        //--------------------------------------------------------------
        ParameterNamedIndex& ParameterNamedIndex::setMode(Mode mode) {
            _mode = mode;
            return *this;
        }
        
        //--------------------------------------------------------------
        ParameterNamedIndex::Mode ParameterNamedIndex::getMode() {
            return _mode;
        }
        
        
        //--------------------------------------------------------------
        void ParameterNamedIndex::writeToXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::ParameterNamedIndex::writeToXml: " << getPath();
            
            ParameterInt::writeToXml(xml, bFullSchema);  // IMPORTANT: always start with parents write to xml
            if(bFullSchema) {
                xml.addAttribute(_xmlTag, "selectedLabel", getSelectedLabel(), _xmlTagId);
                xml.pushTag(_xmlTag, _xmlTagId);
                for(int i=0; i<_labels.size(); i++) {
                    xml.addValue("label" + ofToString(i), _labels[i]);
                }
                xml.popTag();
            }
        }
        
        //--------------------------------------------------------------
        void ParameterNamedIndex::readFromXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::ParameterNamedIndex::readFromXml: " << getPath();
            
            ParameterInt::readFromXml(xml, bFullSchema);
        }
        
        
		
	}
}
