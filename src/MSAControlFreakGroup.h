/*
 *  MSAControlFreakGroup.h
 *  UK Summer Games v2
 *
 *  Created by Memo Akten on 23/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "MSACore.h"
#include "MSAControlFreakParameter.h"
#include "MSAControlFreakGuiBase.h"
#include <stack>

#include <boost/property_tree/ptree.hpp>

namespace MSA {
	namespace ControlFreak {
		
		
		// container for multiple parameters and groups
		class ParameterGroup {
		public:
			
			ParameterGroup(string name = "My ParameterGroup");
			~ParameterGroup();
			
			void setName(string s);
			string name();
			
			void startGroup(string name="");
			void endGroup();

			
			// all of the below are added to the _currentPath
			Parameter& addFloat(string name, float min=0, float max=1, float defaultValue = 0);
			Parameter& addInt(string name, int min=0, int max=100, int defaultValue = 0);					
			Parameter& addToggle(string name, bool defaultValue = false);
			Parameter& addBang(string name, bool defaultValue = false);
			
			
			inline int numParams();
			inline Parameter& operator[](string name);		// access by name
			inline Parameter& operator[](int index);		// access by index
			
			
			// if name is omitted, last used name is used (by default same as group name)
			void setFilename(string filename);
			
			bool saveToXML(string filename = "");
			bool loadFromXML(string filename = "");
			
			bool saveToInfo(string filename = "");
			bool loadFromInfo(string filename = "");
			
			bool saveToJSON(string filename = "");
			bool loadFromJSON(string filename = "");


//			void checkValueHasChanged();
//			void updateControllers(bool doChildGroups = true);		// update all controllers
			
			
			// GUI based functions
			void setGui(GuiBase& gui);		// all parameters & groups will be reflected in this Gui
			GuiBase* gui();					// return reference to the gui
			
			
		protected:
			string						_name;
			boost::property_tree::ptree _ptree;
			string						_filename;
			stack<string>				_pathStack;	// keep track of stack of groups when creating
			GuiBase		*_gui;
			char						_pathDivider;
			
			string addToPath(string name);		//make full path out of name (using _currentPath)
			
			void syncTreeToParam(Parameter *Param);		// updates just this parameter in property tree
			void syncTreeToParams();					// runs through all params and updates property tree
			
			void syncParamsToTree();
			void updateParam(string path, ValueType valueType, float min, float max, float value);

//			Parameter& addParameter(string path, float min, float max, ValueType type);
			
			Parameter& addParameter(Parameter *param);			// used internally, only public for advanced use (adds reference to original parameter)
//			
			map<string, Parameter*>	_paramMap;		// map for all parameters
			vector<Parameter*>		_paramArr;		// array needed to access sequentially (for displaying in gui)
//			
//			map<string, ParameterGroup*>		_groupMap;		// map for all groups
//			vector<ParameterGroup*>			_groupArr;		// array needed to access sequentially (for displaying in gui)
		};
		
		
		
		//-------------- parameter functions --------------
		int ParameterGroup::numParams() {
			assert(_paramArr.size() == _paramMap.size());	// probably tried to add a parameter with the same name (in the same group)
			return _paramMap.size();
		}
		
		Parameter& ParameterGroup::operator[](string name) {
			return *_paramMap[name];
		}
		
		Parameter& ParameterGroup::operator[](int index) {
			return *_paramArr[index];
		}
//		
		
		
		//-------------- group functions --------------
//		int ParameterGroup::numGroups() {
//			assert(_groupArr.size() == _groupMap.size());
//			return _groupMap.size();
//		}
//		
//		ParameterGroup& ParameterGroup::group(string name) {
//			return *_groupMap[name];
//		}
//		
//		ParameterGroup& ParameterGroup::group(int index) {
//			return *_groupArr[index];
//		}
		
	}
}