/*
 *  MSACFParameterIndex.h
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "ofxMSAControlFreak/src/Parameter.h"


namespace msa {
	namespace ControlFreak {
		
		// todo: keep max, in sync with labels.size()
		
		class ParameterNamedIndex : public Parameter {
		public:
			
			friend class ParameterGroup;
            
			ParameterNamedIndex& setLabels(int count, string* labels);
            ParameterNamedIndex& setLabels(vector<string>& labels);
            ParameterNamedIndex& setLabels(int count, ...);
			
			inline vector<string>& labels();
			inline string selectedLabel() const;
			
            virtual void writeSchemaToXml(ofxXmlSettings &xml);
            virtual void readSchemaFromXml(ofxXmlSettings &xml);
			
		protected:
			ParameterNamedIndex(ParameterGroup *parent, string path) : Parameter(parent, path, Types::kNamedIndex) {
				setClamp(false);
			}
			
			vector<string> _labels;
		};

		
		//------------------------------------------------------------
		
		vector<string>& ParameterNamedIndex::labels() {
			return _labels;
		}
		
		string ParameterNamedIndex::selectedLabel() const {
			return _labels.at(value());
		}
		
		
//		template<typename T> ParameterNamedIndex::operator T() const {
//			return (T)_value;
//		}
//		
//		template<typename T> T ParameterNamedIndex::operator=(const T & value) {
//			setValue(value);
//		}
//		
		
		
		
	}
}