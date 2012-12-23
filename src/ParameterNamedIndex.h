/*
 *  MSACFParameterIndex.h
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "ofxMSAControlFreak/src/ParameterNumbers.h"


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
			string selectedLabel() const;
			
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull, string tag, int tagid);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull, string tag, int tagid);
			
		protected:
			ParameterNamedIndex(ParameterGroup *parent, string path)
            : ParameterInt(parent, path, Types::kNamedIndex) { setClamp(false); }
			
			vector<string> _labels;
		};

		
		
	}
}