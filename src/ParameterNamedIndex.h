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
            
			ParameterNamedIndex(ParameterGroup *parent, string name, Type::Index typeIndex = Type::kNamedIndex)
            : ParameterInt(parent, name, typeIndex) { setClamp(false); }
          
            template <typename T> T operator=(const T & v) { kCheckBadParameter(T()); this->setValue(v); }
			template <typename T> operator T() const { kCheckBadParameter(T()); return this->getValue(); }

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
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
			
            // dummy parameter, sent back from 'getParameter' functions, if parameter can't be found
            static ParameterNamedIndex dummy;
		};

	}
}