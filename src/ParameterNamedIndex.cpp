/*
 *  MSACFParameterIndex.cpp
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "ofxMSAControlFreak/src/ParameterNamedIndex.h"
//#include <boost/foreach.hpp>

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
        void ParameterNamedIndex::writeSchemaToXml(ofxXmlSettings &xml) {
            for(int i=0; i<_labels.size(); i++) {
                xml.addValue("label" + ofToString(i), _labels[i]);
            }
        }
        
        //--------------------------------------------------------------
        void ParameterNamedIndex::readSchemaFromXml(ofxXmlSettings &xml) {
            
        }
        
        
		
	}
}
