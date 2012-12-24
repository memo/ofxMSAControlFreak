/*
 
 A container contains other parameters, including other groups (can go infinintely deep)
 
 */

#pragma once

#include "ofxMSACore/src/MSACore.h"

#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
	namespace ControlFreak {
		
		class ParameterContainer : public Parameter {
		public:
            
            ParameterContainer(ParameterContainer *parent, string name, Type::Index typeIndex);
			~ParameterContainer();
			
			int getNumParams();
            Parameter& getParameter(int index);     // access by index
            Parameter& getParameter(string path);   // access by name
            
            // [] operator overloads for above
			Parameter& operator[](int index);
            Parameter& operator[](string path);
			
			virtual Parameter& addParameter(Parameter *param);
            
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
            
		protected:
			map<string, Parameter*>	_paramMap;		// map for all parameters
			vector<Parameter*>		_paramArr;		// array needed to access sequentially (for display etc.)
		};

	}
}