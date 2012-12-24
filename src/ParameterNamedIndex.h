/*
 
 A named index parameter type (like combo-box, or option list)
 
 */

#pragma once

#include "ofxMSAControlFreak/src/ParameterNumbers.h"


namespace msa {
	namespace ControlFreak {
		
		// todo: keep max, in sync with labels.size()
		
		class ParameterNamedIndex : public ParameterInt {
		public:
			
//			friend class ParameterGroup;
            
			ParameterNamedIndex(ParameterContainer *parent, string name)
            : ParameterInt(parent, name, Type::kNamedIndex) { setClamp(false); }
            
            
			ParameterNamedIndex& setLabels(int count, string* labels);
            ParameterNamedIndex& setLabels(vector<string>& labels);
            ParameterNamedIndex& setLabels(int count, ...);
			
			vector<string>& labels();
			string selectedLabel();
			
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
			
		protected:
			
			vector<string> _labels;
		};

		
		
	}
}