/*
 *  MSACFParameters.cpp
 *  UK Summer Games v2
 *
 *  Created by Memo Akten on 23/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "MSACFParameters.h"
#include "MSAControlFreak.h"
//#include "boost/filesystem.hpp" TODO
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/info_parser.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

namespace msa {
	namespace ControlFreak {

		Parameters::Parameters(string name) {
			setName(name);
			_gui			= NULL;
			_pathStack.push("");
			_filename = "MSAControlFreak.xml";
		}
		
		Parameters::~Parameters() {
			int np = numParams();
			for(int i=0; i<np; i++) delete _paramArr[i];
		}

		
		void Parameters::setName(string s) {
			_name = s;
			_filename = _name;
		}
		
		string Parameters::name() {
			return _name;
		}
		
		
		void Parameters::updateTreeFromParam(Parameter *param) {
			param->writeToPropertyTree(_ptree);
		}
		
		void Parameters::updateTreeFromParams() {
			printf("Parameters::updateTreeFromParams\n");
			_ptree.clear();
			int np = numParams();
			for(int i=0; i<np; i++) updateTreeFromParam(_paramArr[i]);
		}
		
		
		void Parameters::updateParamFromTree(string path) {
			printf("Parameters::updateParamFromTree: %s\n", path.c_str());
			Types::Index valueType	= Types::indexForName(_ptree.get<string>(path + kPathDivider + "type"));
			float min			= _ptree.get<float>(path + kPathDivider + "min");
			float max			= _ptree.get<float>(path + kPathDivider + "max");
			float value			= _ptree.get<float>(path + kPathDivider + "value");
			
			if(_paramMap[path] == NULL) {
				switch (valueType) {
					case Types::kFloat:
						addFloat(path);
						break;
						
					case Types::kInt:
						addInt(path);
						break;
						
					case Types::kToggle:
						addToggle(path);
						break;
						
					case Types::kBang:
						addBang(path);
						break;
						
					case Types::kNamedIndex:
						addNamedIndex(path);
						break;
						
					default:
						assert(false);
						break;
				}
			}

			_paramMap[path]->readFromPropertyTree(_ptree);
		}

		
		void Parameters::updateParamsFromTree(string rootPath) {
			printf("\nParameters::updateParamsFromTree: %s\n", rootPath.c_str());
			
			BOOST_FOREACH(boost::property_tree::ptree::value_type &v, _ptree.get_child(rootPath)) {   
				string path = makePath(rootPath, v.first);
				string value = v.second.get<string>("");

				cout << "	path: " << path << ", Value: " << value.c_str();
				
				if(value == "PARAMETER") {	// we are at the root of a parameter
					printf("\n");
					updateParamFromTree(path);
				} else {
					boost::optional<boost::property_tree::ptree&> children = _ptree.get_child_optional(path);
					if(children) {
						//					children = 
						cout << ", numChildren: " << children->size();
						printf("\n");
						//					cout << _ptree.count(path) << endl;
						updateParamsFromTree(path);
					}
				}
				
			}
		}

		
		
		// if parameter non empty, saves the filename
		void Parameters::setFilename(string filename) {
			if(filename.empty() == false) _filename = filename;
		}
		
		bool Parameters::saveToXML(string filename) {
			setFilename(filename);
			updateTreeFromParams();
			boost::property_tree::write_xml(dataPath(_filename + ".xml"), _ptree);
		}
		
		bool Parameters::loadFromXML(string filename) {
			setFilename(filename);
			boost::property_tree::read_xml(dataPath(_filename + ".xml"), _ptree);
			updateParamsFromTree();
		}
		
		bool Parameters::saveToInfo(string filename) {
			setFilename(filename);
			updateTreeFromParams();
			boost::property_tree::write_info(dataPath(_filename + ".info.txt"), _ptree);
		}
		
		bool Parameters::loadFromInfo(string filename) {
			setFilename(filename);
			boost::property_tree::read_info(dataPath(_filename + ".info.txt"), _ptree, _ptree);
			updateParamsFromTree();
		}
		
		
//		bool Parameters::saveToJSON(string filename) {
//			setFilename(filename);
//			updateTreeFromParams();
//			boost::property_tree:::write_json(dataPath(_filename + ".json"), _ptree);
//		}
		
//		bool Parameters::loadFromJSON(string filename) {
//			setFilename(filename);
//			boost::property_tree::read_json(dataPath(_filename + ".json"), _ptree, _ptree);
//			updateParamsFromTree();
//		}

		
		
		
		void Parameters::setGui(GuiBase& gui) {
			_gui = &gui;
		}
		
		GuiBase* Parameters::gui() {
			return _gui;
		}
		
		
		string Parameters::makePath(string parent, string child) {
			return parent.empty() ? child : parent + kPathDivider + child;
		}

		string Parameters::addToPath(string name) {
			return makePath(_pathStack.top(), name);
		}
		
		Parameter& Parameters::addParameter(Parameter *param) {
			printf("Parameters::addParameter %s\n", param->path().c_str());
//			updateTreeFromParam(param);
			
			_paramMap[param->path()] = param;
			_paramArr.push_back(param);
			
			numParams();	// to check if correctly added to both containers
			
			if(gui()) gui()->addParameter(param);
			return *param;
		}

		
		Parameter& Parameters::addFloat(string name, float min, float max, float defaultValue) {
			return addParameter(new Parameter(this, addToPath(name), Types::kFloat, min, max, defaultValue));
		}
		
		Parameter& Parameters::addInt(string name, int min, int max, int defaultValue) {
			return addParameter(new Parameter(this, addToPath(name), Types::kInt, min, max, defaultValue));
		}
		
		Parameter& Parameters::addToggle(string name, bool defaultValue) {
			return addParameter(new Parameter(this, addToPath(name), Types::kToggle, 0, 1, defaultValue));
		}
		
		Parameter& Parameters::addBang(string name, bool defaultValue) {
			return addParameter(new Parameter(this, addToPath(name), Types::kBang, 0, 1, defaultValue));
		}
		
		ParameterNamedIndex& Parameters::addNamedIndex(string name, int count, string* labels, int defaultValue) {
			ParameterNamedIndex *p = new ParameterNamedIndex(this, addToPath(name), defaultValue);
			addParameter(p); 
			for(int i=0; i<count; i++) {
				p->labels().push_back(labels[i]);
			}
			return *p;
		}

		
		
		//-------------- group functions --------------
		void Parameters::startGroup(string name) {
			_pathStack.push(addToPath(name));
			if(gui()) gui()->startGroup(name);

		}
		
		void Parameters::endGroup() {
			_pathStack.pop();
			if(gui()) gui()->endGroup();
		}
		

		
		
		
//		void Parameters::updateControllers(bool doChildGroups) {
//			int np = numParams();
//			for(int i=0; i<np; i++) _paramArr[i]->updateControllers();
//			
//			if(doChildGroups) {
//				int ng = numGroups();
//				for(int i=0; i<ng; i++) _groupArr[i]->updateControllers();
//			}
//		}
		
		//		void Parameters::checkValueHasChanged() {
		//			for(int i=0; i<size(); i++) _paramArr[i]->checkValueHasChanged();
		//		}
		
		
		
		
	}
}