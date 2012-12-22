
// protected constructor, can only be created via Parameters


#pragma once

#include "MSACore.h"
#include "MSACFController.h"
#include "MSACFParameterTypes.h"
#include <boost/property_tree/ptree.hpp>


namespace MSA {
	namespace ControlFreak {
		
	
		
//#define Types::kFloat		"FLOAT"
//#define Types::kInt		"INT"
//#define Types::kToggle		"TOGGLE"
//#define Types::kBang		"BANG"
//		typedef std::string Types::Index;
		
		
#define kPathDivider	'.'
		
		class Parameters;
		
		class Parameter {
		public:
			
			friend class Parameters;
			
			virtual ~Parameter() {
			}
			
			inline string path() const;
			inline string name() const;		// return name

			inline string fullName() const;	// return name prefixed with controllers
			
			inline Parameter& setRange(float vmin, float vmax);
			
			inline float min() const;
			inline float max() const;
			inline float value() const;
			inline void setValue(float f);
			
			inline Types::Index valueType() const;
			inline string valueTypeName() const;
			
			inline void setClamp(bool b);			// enable or disable clamping
			inline bool isClamped() const;			// returns whether clamp is enabled or not
			
			template<typename T> operator T() const;			// cast operator
			template<typename T> T operator=(const T & value);	// assignment operator
			
			inline void setNormalized(float norm);				// input 0...1 number, maps to range
			inline float normalized() const;					// return 0...1 number mapped from range
			
			inline void setMappedFrom(float value, float imin, float imax);
			inline float mappedTo(float newMin, float newMax) const;	// returns value mapped to new range

			
			Parameter& addController(Controller *controller);
			void updateControllers();
//			void checkValueHasChanged();
			
			virtual void writeToPropertyTree(boost::property_tree::ptree& pt);
			virtual void readFromPropertyTree(boost::property_tree::ptree& pt);
			
		protected:
			Types::Index			_valueTypeIndex;
			float					_min, _max, _value;
			string					_path;
			string					_name;
			bool					_isClamped;
			vector<Controller*>		_controllers;
			Parameters			*_parent;
			

			Parameter(Parameters *parent, string path, Types::Index typeIndex, float min, float max, float value)
			: _parent(parent), _path(path), _min(min), _max(max), _value(value) {
				printf("Parameter::Parameter %s\n", _path.c_str());
				
				setValueType(typeIndex);
				setClamp(true);
				
				// set name
				size_t lastDividerPos = _path.rfind(kPathDivider);
				_name = lastDividerPos == string::npos ? _path : _path.substr(lastDividerPos+1);
			}

			inline void setValueType(Types::Index type);
			inline void setValueType(string s);
			
			// used by all setters for common setting behaviour
		};
		
		
		//------------------------------------------------------------
		string Parameter::path() const {
			return _path;
		}
		
		string Parameter::name() const {
			return _name;
		}
		
		string Parameter::fullName() const {
			string s;
			for(int i=0; i<_controllers.size(); i++) s += "[" + _controllers[i]->toString() + "]";
			return s + " " + name();
		}
		
		
		Parameter& Parameter::setRange(float vmin, float vmax) {
			_min = vmin;
			_max = vmax;
			setValue(_value);
			return *this;
		}
		
		float Parameter::min() const {
			return _min;
		}
		
		float Parameter::max() const {
			return _max;
		}
		
		float Parameter::value() const {
			return _value;
		}
		
		Types::Index Parameter::valueType() const {
			return _valueTypeIndex;
		}
		
		string Parameter::valueTypeName() const {
			return nameForIndex(_valueTypeIndex);
		}


		void Parameter::setValueType(Types::Index type) {
			_valueTypeIndex = type;
			switch(_valueTypeIndex) {
				case Types::kToggle:
				case Types::kBang:
					setRange(0, 1);
					break;

				case Types::kFloat:
				case Types::kInt:
				case Types::kNamedIndex:
					setValue(_value);
					break;
					
					
				default:
					assert(false);
					
			}
		}
		
		void Parameter::setValueType(string s) {
			setValueType(Types::indexForName(s));
		}


		
		void Parameter::setClamp(bool b) {
			_isClamped = b;
			if(_isClamped) setValue(_value);	// clamp immediately
		}
		
		bool Parameter::isClamped() const {
			return _isClamped;
		}
		
		
		template<typename T> Parameter::operator T() const {
			return (T)_value;
		}
		
		template<typename T> T Parameter::operator=(const T & value) {
			setValue(value);
		}
		
		void Parameter::setNormalized(float norm) {
			setValue(lerp(_min, _max, norm));
		}
		
		float Parameter::normalized() const {
			float norm = (_value - _min) / (_max - _min);
			return norm;
		}
		
		void Parameter::setMappedFrom(float value, float imin, float imax) {
			setValue(lmap(value, imin, imax, _min, _max));
		}
		
		float Parameter::mappedTo(float newMin, float newMax) const {
			return lmap(_value, _min, _max, newMin, newMax);
		}
		
		
		void Parameter::setValue(float f) {
			switch(_valueTypeIndex) {
				case Types::kFloat:
					_value = _isClamped ? math<float>::clamp(f, _min, _max) : (float)f;
					break;
					
				case Types::kInt:
				case Types::kNamedIndex:
					_value = _isClamped ? math<int>::clamp(f, _min, _max) : (int)f;
					break;
					
				case Types::kToggle:
				case Types::kBang:
					_value = _isClamped ? math<bool>::clamp(f, _min, _max) : (bool)f;
					break;
					
				default:
					assert(false);
					
			}
			//				checkValueHasChanged();
			updateControllers();
		}
		
		

	
	}
}