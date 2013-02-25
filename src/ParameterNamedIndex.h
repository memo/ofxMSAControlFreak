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

/*
 
 A named index parameter type (like combo-box, or option list)
 
 */

#pragma once

#include "ofxMSAControlFreak/src/ParameterInt.h"


namespace msa {
	namespace controlfreak {
		
		// todo: keep max, in sync with labels.size()
		
		class ParameterNamedIndex : public ParameterInt {
		public:
			
			friend class ParameterGroup;
            
            enum Mode {
                kDropdown,
                kList,
                kOptions
            };
            
			ParameterNamedIndex(string name, ParameterGroup *parent = NULL)
            : ParameterInt(name, parent) { setClamp(true); setMode(kDropdown); }
          
            template <typename T> T operator=(const T & v) { set(v); }
			template <typename T> operator T() const { return value(); }

			ParameterNamedIndex& setLabels(int count, string* labels);
            ParameterNamedIndex& setLabels(vector<string>& labels);
            ParameterNamedIndex& setLabels(int count, ...);
			
            int size();
            string getLabel(int i);
			string getSelectedLabel();
			vector<string>& getLabels();
            void clearLabels();
            void addLabel(string s);
            
            ParameterNamedIndex& setMode(Mode mode);
            Mode getMode();
			
		protected:
            Mode _mode;
			vector<string> _labels;
            
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFullSchema);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFullSchema);
		};

	}
}