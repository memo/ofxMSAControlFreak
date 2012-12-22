/*
 *  MSAControlFreeParameter.cpp
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */


#include "MSACFParameter.h"

namespace msa {
	namespace ControlFreak {

		
		Parameter& Parameter::addController(Controller *controller) {
			controller->setParam(this);
			controller->updateController();
			_controllers.push_back(controller);
			return *this;
		}
		
		
		void Parameter::updateControllers() {
			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
		}
		
		//		void Parameter::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}
		
		void Parameter::writeToPropertyTree(boost::property_tree::ptree& pt) {
			printf("Parameter::writeToPropertyTree %s\n", _path.c_str());
			pt.put(_path, "PARAMETER");
			pt.put(_path + kPathDivider + "type", valueTypeName());
			pt.put(_path + kPathDivider + "min", _min);
			pt.put(_path + kPathDivider + "max", _max);
			pt.put(_path + kPathDivider + "value", _value);
		}
		
		void Parameter::readFromPropertyTree(boost::property_tree::ptree& pt) {
			printf("Parameter::readFromPropertyTree %s\n", _path.c_str());
			setValueType(pt.get<string>(_path + kPathDivider + "type"));
			setRange(pt.get<float>(_path + kPathDivider + "min"), pt.get<float>(_path + kPathDivider + "max"));
			setValue(pt.get<float>(_path + kPathDivider + "value"));
		}
	}
}