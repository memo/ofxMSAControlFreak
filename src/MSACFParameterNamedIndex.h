/*
 *  MSACFParameterIndex.h
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "MSACFParameter.h"


namespace MSA {
	namespace ControlFreak {
		
		// todo: keep max, in sync with labels.size()
		
		class ParameterNamedIndex : public Parameter {
		public:
			
			friend class Parameters;

			
			inline vector<string>& labels();
			inline string selectedLabel() const;
			
			void writeToPropertyTree(boost::property_tree::ptree& pt);
			void readFromPropertyTree(boost::property_tree::ptree& pt);

//			template<typename T> operator T() const;			// cast operator
//			template<typename T> T operator=(const T & value);	// assignment operator

			
		protected:
			ParameterNamedIndex(Parameters *parent, string path, int value)
			: Parameter(parent, path, Types::kNamedIndex, 0, 1, value) {
				setClamp(false);
			}
			
			vector<string> _labels;

		};

		
		//------------------------------------------------------------
		
		vector<string>& ParameterNamedIndex::labels() {
			return _labels;
		}
		
		string ParameterNamedIndex::selectedLabel() const {
			return _labels.at(_value);
		}
		
		
//		template<typename T> ParameterNamedIndex::operator T() const {
//			return (T)_value;
//		}
//		
//		template<typename T> T ParameterNamedIndex::operator=(const T & value) {
//			setValue(value);
//		}
//		
		
		
		
	}
}