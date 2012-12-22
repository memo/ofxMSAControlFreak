/*
 *  MSACFParameters.h
 *  UK Summer Games v2
 *
 *  Created by Memo Akten on 23/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "MSACore.h"
#include "MSACFParameter.h"
#include "MSACFParameterNamedIndex.h"
#include "MSACFGuiBase.h"
#include <stack>

#include <boost/property_tree/ptree.hpp>

namespace MSA {
	namespace ControlFreak {
		
		
		// container for multiple parameters and groups
		class Parameters {
		public:
			
			Parameters(string name = "My Parameters");
			~Parameters();
			
			void setName(string s);
			string name();
			
			void startGroup(string name="");
			void endGroup();

			
			// all of the below are added to the _currentPath
			Parameter& addFloat(string name, float min=0, float max=1, float defaultValue = 0);
			Parameter& addInt(string name, int min=0, int max=100, int defaultValue = 0);					
			Parameter& addToggle(string name, bool defaultValue = false);
			Parameter& addBang(string name, bool defaultValue = false);
			ParameterNamedIndex& addNamedIndex(string name, int count = 0, string* labels = NULL, int defaultValue = 0);
			
			
			inline int numParams();
			inline Parameter& operator[](string name);		// access by name
			inline Parameter& operator[](int index);		// access by index
			
			
			// if name is omitted, last used name is used (by default same as group name)
			void setFilename(string filename = "");
			
			bool saveToXML(string filename = "");
			bool loadFromXML(string filename = "");
			
			bool saveToInfo(string filename = "");
			bool loadFromInfo(string filename = "");
			
//			bool saveToJSON(string filename = "");
//			bool loadFromJSON(string filename = "");


//			void checkValueHasChanged();
//			void updateControllers(bool doChildGroups = true);		// update all controllers
			
			
			// GUI based functions
			void setGui(GuiBase& gui);		// all parameters & groups will be reflected in this Gui
			GuiBase* gui();					// return reference to the gui
			
			
		protected:
			string			_name;
			string			_filename;
			stack<string>	_pathStack;	// keep track of stack of groups when creating
			GuiBase			*_gui;
			
			string makePath(string parent, string child);	// concatenate paths, add divider if need be
			string addToPath(string name);		//make full path out of name (using _currentPath)
			
			void updateTreeFromParams();					// runs through all params and updates property tree
			void updateTreeFromParam(Parameter *Param);		// updates just this parameter in property tree
			
			void updateParamsFromTree(string rootPath = "");// runs through tree and updates all params
			void updateParamFromTree(string path);			// updates just this parameter from property tree

			Parameter& addParameter(Parameter *param);		// used internally, only public for advanced use (adds reference to original parameter)

			boost::property_tree::ptree _ptree;
			map<string, Parameter*>	_paramMap;		// map for all parameters
			vector<Parameter*>		_paramArr;		// array needed to access sequentially (for displaying in gui)
		};

		
		//------------------------------------------------------------

		int Parameters::numParams() {
			assert(_paramArr.size() == _paramMap.size());	// probably tried to add a parameter with the same name (in the same group)
			return _paramMap.size();
		}
		
		Parameter& Parameters::operator[](string name) {
			return *_paramMap[name];
		}
		
		Parameter& Parameters::operator[](int index) {
			return *_paramArr[index];
		}

	}
}