/*
 *  MSACFParameters.h
 *  UK Summer Games v2
 *
 *  Created by Memo Akten on 23/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "ofxMSACore/src/MSACore.h"
#include "ofxMSAControlFreak/src/Parameter.h"
#include "ofxMSAControlFreak/src/ParameterNamedIndex.h"
//#include "ofxMSAControlFreak/src/GuiBase.h"

//#include <boost/property_tree/ptree.hpp>

namespace msa {
	namespace ControlFreak {
		
		
		// container for multiple parameters and groups
		class ParameterGroup {
		public:
			
			ParameterGroup(string name = "My ParameterGroup", string pathDivider = "/");
			~ParameterGroup();
			
			void setName(string s);
			string name();
			
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
			Parameter& operator[](string name);		// access by name
			Parameter& operator[](int index);		// access by index
			
			
			// if name is omitted, last used name is used (by default same as group name)
			void setFilename(string filename = "");
			
			bool saveXml(bool bFull, string filename = "");
			bool loadXml(bool bFull, string filename = "");

//			void checkValueHasChanged();
//			void updateControllers(bool doChildGroups = true);		// update all controllers
			
			string getPathDivider();
            
		protected:
			string			_name;
			string			_filename;
            string          _pathDivider;
			stack<string>	_pathStack;	// keep track of stack of groups when creating
			
			string makePath(string parent, string child);	// concatenate paths, add divider if need be
			string addToPath(string name);		//make full path out of name (using _currentPath)
			
			Parameter& addParameter(Parameter *param);		// used internally, only public for advanced use (adds reference to original parameter)

			map<string, Parameter*>	_paramMap;		// map for all parameters
			vector<Parameter*>		_paramArr;		// array needed to access sequentially (for displaying in gui)
            
            
            void addCommand(string name, Types::Command command);
		};

	}
}