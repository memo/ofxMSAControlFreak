/*
 *  MSACFParameterIndex.cpp
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"


namespace msa {
	namespace ControlFreak {
		
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
        int ParameterNamedIndex::getNumLabels() {
            return _labels.size();
        }

        //--------------------------------------------------------------
		string ParameterNamedIndex::getSelectedLabel() {
			return getLabel(value());
		}
		
        //--------------------------------------------------------------
        string ParameterNamedIndex::getLabel(int i) {
            return _labels.size() && i >= 0 && i < getNumLabels() ? _labels[i] : "";
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
        void ParameterNamedIndex::writeToXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::ControlFreak::ParameterNamedIndex::writeToXml: " << getPath();
            
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
			ofLogVerbose() << "msa::ControlFreak::ParameterNamedIndex::readFromXml: " << getPath();
            
            ParameterInt::readFromXml(xml, bFullSchema);
        }
        
        
		
	}
}
