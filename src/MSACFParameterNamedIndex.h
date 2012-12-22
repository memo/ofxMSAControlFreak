

#pragma once

#include "MSACFParameterT.h"


namespace msa {
	namespace ControlFreak {
		
		// todo: keep max, in sync with labels.size()
		
		class ParameterNamedIndex : public ParameterT<int> {
		public:
			
			friend class Parameters;
			
			ParameterNamedIndex(string path="", int value=0) : ParameterT<int>(path, value, 0, 1) {
				setClamp(false);
			}
			
			inline vector<string>& labels();
			inline string selectedLabel() const;
			
			void writeToPropertyTree(boost::property_tree::ptree& pt);
			void readFromPropertyTree(boost::property_tree::ptree& pt);
//			template<typename T> operator T() const;			// cast operator
//			template<typename T> T operator=(const T & value);	// assignment operator

			
		protected:
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