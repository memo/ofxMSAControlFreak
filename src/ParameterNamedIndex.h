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
			
			friend class ParameterGroup;
            
			ParameterNamedIndex(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kNamedIndex)
            : ParameterInt(name, parent, typeIndex) { setClamp(true); }
          
            template <typename T> T operator=(const T & v) { set(v); }
			template <typename T> operator T() const { return value(); }

			ParameterNamedIndex& setLabels(int count, string* labels);
            ParameterNamedIndex& setLabels(vector<string>& labels);
            ParameterNamedIndex& setLabels(int count, ...);
			
            int getNumLabels();
            string getLabel(int i);
			string getSelectedLabel();
			vector<string>& getLabels();
			
		protected:
			vector<string> _labels;
            
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bOnlyValues);
            virtual void readFromXml(ofxXmlSettings &xml, bool bOnlyValues);
		};

	}
}