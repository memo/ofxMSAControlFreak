/*
 
 A named index parameter type (like combo-box, or option list)
 
 */

#pragma once

#include "ofxMSAControlFreak/src/ParameterValues.h"


namespace msa {
	namespace ControlFreak {
		
		// todo: keep max, in sync with labels.size()
		
		class ParameterNamedIndex : public  ParameterInt {
		public:
			
			friend class ParameterGroup;
            
			ParameterNamedIndex& setLabels(int count, string* labels);
            ParameterNamedIndex& setLabels(vector<string>& labels);
            ParameterNamedIndex& setLabels(int count, ...);
			
			vector<string>& labels();
			string selectedLabel();
			
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
			
		protected:
			ParameterNamedIndex(ParameterGroup *parent, string name)
            : ParameterInt(parent, name, Types::kNamedIndex) { setClamp(false); }
			
			vector<string> _labels;
		};

		
		
	}
}