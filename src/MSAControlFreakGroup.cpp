/*
 *  MSAControlFreakGroup.cpp
 *  UK Summer Games v2
 *
 *  Created by Memo Akten on 23/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "MSAControlFreakGroup.h"
#include "MSAControlFreak.h"
//#include "boost/filesystem.hpp" TODO
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/info_parser.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

namespace MSA {
	namespace ControlFreak {

		ParameterGroup::ParameterGroup(string name) {
			setName(name);
			_gui			= NULL;
			_pathDivider	= '/';
			_pathStack.push("");
			_filename = "MSAControlFreakSettings.xml";
		}
		
		ParameterGroup::~ParameterGroup() {
			int np = numParams();
			for(int i=0; i<np; i++) delete _paramArr[i];
//			
//			int ng = numGroups();
//			for(int i=0; i<ng; i++) delete _groupArr[i];
		}

		
		void ParameterGroup::setName(string s) {
			_name = s;
			_filename = _name;
		}
		
		string ParameterGroup::name() {
			return _name;
		}
		
		
		void ParameterGroup::syncTreeToParam(Parameter *param) {
			_ptree.put(param->path(), "PARAMETER");
			_ptree.put(param->path() + "type", param->valueType());
			_ptree.put(param->path() + "min", param->min());
			_ptree.put(param->path() + "max", param->max());
			_ptree.put(param->path() + "value", param->value());
		}
		
		void ParameterGroup::syncTreeToParams() {
			int np = numParams();
			_ptree.clear();
			for(int i=0; i<np; i++) syncTreeToParam(_paramArr[i]);
		}
		
				
		
		
		void ParameterGroup::updateParam(string path, ValueType valueType, float min, float max, float value) {
			if(_paramMap[path] == NULL) {
				printf("%s param doesn't exist, creating\n", path.c_str());
				addParameter(new Parameter(this, path, valueType, min, max, value));
			} else {
				printf("%s param does exist, updating\n", path.c_str());
				_paramMap[path]->setValueType(valueType);
				_paramMap[path]->setRange(min, max);
				_paramMap[path]->setValue(value);
			}
			
		}

		void ParameterGroup::syncParamsToTree() {
			BOOST_FOREACH(boost::property_tree::ptree::value_type &v, _ptree) {   
				string path = v.first;
				string value = v.second.get<string>("");
				cout << "Path: " << path << ", Value: " << value.c_str() << endl;
				if(value == "PARAMETER") {	// we are at the root of a parameter
					string paramRoot = path;	// path to the key
					updateParam(paramRoot, _ptree.get<ValueType>(paramRoot + "type"), _ptree.get<float>(paramRoot + "min"), _ptree.get<float>(paramRoot + "max"), _ptree.get<float>(paramRoot + "value"));
				}
			}
		}

		
		
		// if parameter non empty, saves the filename
		void ParameterGroup::setFilename(string filename) {
			if(filename.empty() == false) _filename = filename;
		}
		
		bool ParameterGroup::saveToXML(string filename) {
			setFilename(filename);
			syncTreeToParams();
			boost::property_tree::write_xml(dataPath(_filename + ".xml"), _ptree);
		}
		
		bool ParameterGroup::loadFromXML(string filename) {
			setFilename(filename);
			boost::property_tree::read_xml(dataPath(_filename + ".xml"), _ptree);
			syncParamsToTree();
		}
		
		bool ParameterGroup::saveToInfo(string filename) {
			setFilename(filename);
			syncTreeToParams();
			boost::property_tree::write_info(dataPath(_filename + ".info.txt"), _ptree);
		}
		
		bool ParameterGroup::loadFromInfo(string filename) {
			setFilename(filename);
			boost::property_tree::read_info(dataPath(_filename + ".info.txt"), _ptree, _ptree);
			syncParamsToTree();
		}
		
		
		bool ParameterGroup::saveToJSON(string filename) {
			setFilename(filename);
			syncParamsToTree();
//			boost::property_tree:::write_json(dataPath(_filename + ".json"), _ptree);
		}
		
		bool ParameterGroup::loadFromJSON(string filename) {
			setFilename(filename);
//			boost::property_tree::read_json(dataPath(_filename + ".json"), _ptree, _ptree);
			syncParamsToTree();
		}

		
		
		
		void ParameterGroup::setGui(GuiBase& gui) {
			_gui = &gui;
		}
		
		GuiBase* ParameterGroup::gui() {
			return _gui;
		}
		

		string ParameterGroup::addToPath(string name) {
			return _pathStack.top() + name + _pathDivider;
		}
		
		Parameter& ParameterGroup::addParameter(Parameter *param) {
			syncTreeToParam(param);
			
			_paramMap[param->path()] = param;
			_paramArr.push_back(param);
			
			numParams();	// to check if correctly added to both containers
			
			if(gui()) gui()->addParameter(param);
			return *param;
		}

		
		Parameter& ParameterGroup::addFloat(string name, float min, float max, float defaultValue) {
			return addParameter(new Parameter(this, addToPath(name), kTypeFloat, min, max, defaultValue));
		}
		
		Parameter& ParameterGroup::addInt(string name, int min, int max, int defaultValue) {
			return addParameter(new Parameter(this, addToPath(name), kTypeInt, min, max, defaultValue));
		}
		
		Parameter& ParameterGroup::addToggle(string name, bool defaultValue) {
			return addParameter(new Parameter(this, addToPath(name), kTypeToggle, 0, 1, defaultValue));
		}
		
		Parameter& ParameterGroup::addBang(string name, bool defaultValue) {
			return addParameter(new Parameter(this, addToPath(name), kTypeBang, 0, 1, defaultValue));
		}
		
		
		//-------------- group functions --------------
		void ParameterGroup::startGroup(string name) {
			_pathStack.push(addToPath(name));
		}
		
		void ParameterGroup::endGroup() {
			_pathStack.pop();
		}
		

		
		
		
//		void ParameterGroup::updateControllers(bool doChildGroups) {
//			int np = numParams();
//			for(int i=0; i<np; i++) _paramArr[i]->updateControllers();
//			
//			if(doChildGroups) {
//				int ng = numGroups();
//				for(int i=0; i<ng; i++) _groupArr[i]->updateControllers();
//			}
//		}
		
		//		void ParameterGroup::checkValueHasChanged() {
		//			for(int i=0; i<size(); i++) _paramArr[i]->checkValueHasChanged();
		//		}
		
		
		
		
	}
}