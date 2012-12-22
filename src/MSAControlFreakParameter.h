
// protected constructor, can only be created via ParameterGroup


#pragma once

#include "MSACore.h"
#include "MSAControlFreakController.h"

namespace MSA {
	namespace ControlFreak {
		
//		enum ValueType {
//			kTypeFloat,
//			kTypeInt,
//			kTypeToggle
//		};
		
#define kTypeFloat		"FLOAT"
#define kTypeInt		"INT"
#define kTypeToggle		"TOGGLE"
#define kTypeBang		"BANG"
		
		typedef std::string ValueType;

		class ParameterGroup;
		
		class Parameter {
		public:
			
			friend class ParameterGroup;
			
			inline string path() const;
			inline string name() const;		// return name

			inline string fullName() const;	// return name prefixed with controllers
			
			inline Parameter& setRange(float vmin, float vmax);
			
			inline float min() const;
			inline float max() const;
			inline float value() const;
			
			inline ValueType valueType() const;
			
			inline void setClamp(bool b);		// enable or disable clamping
			inline bool isClamped();			// returns whether clamp is enabled or not
			
			template<typename T> operator T() const;			// cast operator
			template<typename T> T operator=(const T & value);	// assignment operator
			
			inline void setNormalized(float norm);				// input 0...1 number, maps to range
			inline float normalized() const;					// return 0...1 number mapped from range
			
			inline void setMappedFrom(float value, float imin, float imax);
			inline float mappedTo(float newMin, float newMax) const;	// returns value mapped to new range

			
			inline Parameter& addController(Controller *controller);
			inline void updateControllers();
			
//			inline void checkValueHasChanged();
			
		protected:
			ValueType				_valueType;
			float					_min, _max, _value;
			string					_path;
			bool					_isClamped;
			vector<Controller*>		_controllers;
			ParameterGroup			*_parent;
			

			Parameter(ParameterGroup *parent, string path, ValueType type, float min, float max, float value) : _parent(parent), _path(path), _min(min), _max(max), _value(value) {
				setValueType(type);
				setClamp(true);
			}

			inline void setValueType(ValueType type);
			
			// used by all setters for common setting behaviour
			inline void setValue(float f);
		};
		
		
		//------------------------------------------------------------
		string Parameter::path() const {
			return _path;
		}
		
		string Parameter::name() const {
			return _path; // TODO
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
		
		ValueType Parameter::valueType() const {
			return _valueType;
		}

		void Parameter::setValueType(ValueType type) {
			_valueType = type;
			if(_valueType == kTypeToggle || _valueType == kTypeBang) {
				setRange(0, 1);
			} else if(_valueType == kTypeInt){
				setValue(_value);
			}
//			switch(_valueType) {
//				case kTypeToggle:
//					setRange(0, 1);
//
//				case kTypeInt:
//					setValue(_value);
//					break;
//					
//			}
		}

		
		void Parameter::setClamp(bool b) {
			_isClamped = b;
			if(_isClamped) setValue(_value);	// clamp immediately
		}
		
		bool Parameter::isClamped() {
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
		
		
		void Parameter::setValue(float f) {
			if(_valueType == kTypeFloat) {
				_value = _isClamped ? math<float>::clamp(f, _min, _max) : (float)f;
			} else if(_valueType == kTypeInt) {
				_value = _isClamped ? math<int>::clamp(f, _min, _max) : (int)f;
			} else if(_valueType == kTypeToggle) {
				_value = _isClamped ? math<bool>::clamp(f, _min, _max) : (bool)f;
			}
			
//			switch(_valueType) {
//				case kTypeFloat:
//					_value = math<float>::clamp(f, _min, _max);
//					break;
//					
//				case kTypeInt:
//					_value = math<int>::clamp(f, _min, _max);
//					break;
//					
//				case kTypeToggle:
//					_value = math<bool>::clamp(f, _min, _max);
//					break;
//			}
			//				checkValueHasChanged();
			updateControllers();
		}
		
		

	
	}
}