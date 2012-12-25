/*
 *  MSACFParameterIndex.cpp
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "ofxMSAControlFreak/src/ControlFreak.h"


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
		vector<string>& ParameterNamedIndex::getLabels() {
			return _labels;
		}
		
        //--------------------------------------------------------------
		string ParameterNamedIndex::getSelectedLabel() {
			return _labels.at(getValue());
		}
		
        
        //--------------------------------------------------------------
        void ParameterNamedIndex::writeToXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterNamedIndex::writeToXml " << getPath();
            
            ParameterInt::writeToXml(xml, bFull);  // IMPORTANT: always start with parents write to xml
            if(bFull) {
                xml.addAttribute(_xmlTag, "selectedLabel", getSelectedLabel(), _xmlTagId);
                xml.pushTag(_xmlTag, _xmlTagId);
                for(int i=0; i<_labels.size(); i++) {
                    xml.addValue("label" + ofToString(i), _labels[i]);
                }
                xml.popTag();
            }
        }
        
        //--------------------------------------------------------------
        void ParameterNamedIndex::readFromXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterNamedIndex::readFromXml " << getPath();
            
        }
        
        
		
	}
}
