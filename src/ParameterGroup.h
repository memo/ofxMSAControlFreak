/*
 
 A container / group class, contains other parameters, including other groups (can go infinintely deep)
 
 */

#pragma once

#include "ofxMSACore/src/MSACore.h"

#include "ofxMSAControlFreak/src/Parameter.h"
#include "ofxMSAControlFreak/src/ParameterNamedIndex.h"

namespace msa {
	namespace ControlFreak {
		
		// container for multiple parameters and groups
		class ParameterGroup : public Parameter {
		public:
            
			ParameterGroup(ParameterGroup *parent = NULL, string name = "MSAControlFreak", string pathDivider = ".");
			~ParameterGroup();
			
            // groups can contain subgroups
			void startGroup(string name="");
			void endGroup();

			
			// all of the below are added to the _currentPath
			ParameterInt& addInt(string name);
			ParameterFloat& addFloat(string name);
			ParameterBool& addToggle(string name);
			ParameterBool& addBang(string name);
			ParameterNamedIndex& addNamedIndex(string name);
            //            Parameter& addVec2(string name);
            //            Parameter& addVec3(string name);
            //            Parameter& addVec4(string name);
            //            Parameter& addColor(string name);
			
			
			int numParams();
			Parameter& operator[](string path);		// access by name
			Parameter& operator[](int index);		// access by index
			
			
			// if name is omitted, last used name is used (by default same as group name)
			void setFilename(string filename = "");
			
			bool saveXml(bool bFull, string filename = "");
			bool loadXml(bool bFull, string filename = "");
            
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);

//			void checkValueHasChanged();
//			void updateControllers(bool doChildGroups = true);		// update all controllers
			
            // get path dividier
			string getPathDivider();
            // this cannot be changed once the group is created
            // TODO: this could be implemented, is a bit of a pain

            
		protected:
			string			_filename;
            string          _pathDivider;
            stack<ParameterGroup*> _groupStack; // keep track of stack of groups when creating

			Parameter& addParameter(Parameter *param);

			map<string, Parameter*>	_paramMap;		// map for all parameters
			vector<Parameter*>		_paramArr;		// array needed to access sequentially (for display etc.)
		};

	}
}