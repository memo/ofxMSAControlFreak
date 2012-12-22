/*
 *  MSACFParameterIndex.cpp
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "MSACFParameterNamedIndex.h"
#include <boost/foreach.hpp>


namespace MSA {
	namespace ControlFreak {
		
		void ParameterNamedIndex::writeToPropertyTree(boost::property_tree::ptree& pt) {
			Parameter::writeToPropertyTree(pt);
//			pt.put(_path + kPathDivider + "count", _labels.size());
			for(int i=0; i<_labels.size(); i++) {
				pt.put(_path + kPathDivider + "labels" + kPathDivider + _labels[i], "");
//				pt.put(_path + kPathDivider + "labels" + kPathDivider + "label" + ofToString(i), _labels[i]);
//				pt.put(_path + kPathDivider + "label" + ofToString(i), _labels[i]);
			}
		}

		
		void ParameterNamedIndex::readFromPropertyTree(boost::property_tree::ptree& pt) {
			Parameter::readFromPropertyTree(pt);

			_labels.clear();
		
			string rootPath = _path + kPathDivider + "labels";
			
			BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child(rootPath)) {   
//				string path = rootPath + kPathDivider + v.first;
//				string value = v.second.get<string>("");
				_labels.push_back(v.first);
			}
			
		}

		
	}
}
