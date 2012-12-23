
// protected constructor, can only be created via ParameterGroup


#pragma once

#include "MSACore.h"
#include "MSACFController.h"
#include "MSACFParameterTypes.h"

#include <boost/property_tree/ptree.hpp>

namespace msa {
	namespace ControlFreak {
		
#define kPathDivider	'.'
		
		class ParameterGroup;
		
		class Parameter {
		public:
			
			friend class ParameterGroup;
			
			virtual ~Parameter() {}
			
			inline string path() const;
			inline string name() const;		// return name

			inline string fullName() const;	// return name prefixed with controllers
			
			inline Parameter& setRange(float vmin, float vmax);
			
			inline float min() const;
			inline float max() const;
			inline float value() const;
			inline Parameter& setValue(float f);
			
			inline Types::Index valueType() const;
			inline string valueTypeName() const;
			
			inline Parameter& setClamp(bool b);			// enable or disable clamping
			inline bool isClamped() const;			// returns whether clamp is enabled or not
			
			template<typename T> operator T() const;			// cast operator
			template<typename T> T operator=(const T & value);	// assignment operator
			
			inline Parameter& setNormalized(float norm);				// input 0...1 number, maps to range
			inline float normalized() const;					// return 0...1 number mapped from range
			
			inline Parameter& setMappedFrom(float value, float imin, float imax);
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
			ParameterGroup			*_parent;
			

			Parameter(ParameterGroup *parent, string path, Types::Index typeIndex, float min, float max, float value)
			: _parent(parent), _path(path), _min(min), _max(max), _value(value) {
				printf("Parameter::Parameter %s\n", _path.c_str());
				
				setValueType(typeIndex);
				setClamp(true);
				
				// set name
				size_t lastDividerPos = _path.rfind(kPathDivider);
				_name = lastDividerPos == string::npos ? _path : _path.substr(lastDividerPos+1);
			}

			inline Parameter& setValueType(Types::Index type);
			inline Parameter& setValueType(string s);
			
			// used by all setters for common setting behaviour
		};
		
		
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
		string Parameter::path() const {
			return _path;
		}
		
        //--------------------------------------------------------------
		string Parameter::name() const {
			return _name;
		}
		
        //--------------------------------------------------------------
		string Parameter::fullName() const {
			string s;
			for(int i=0; i<_controllers.size(); i++) s += "[" + _controllers[i]->toString() + "]";
			return s + " " + name();
		}
		
		
        //--------------------------------------------------------------
		Parameter& Parameter::setRange(float vmin, float vmax) {
			_min = vmin;
			_max = vmax;
			setValue(_value);
			return *this;
		}
		
        //--------------------------------------------------------------
		float Parameter::min() const {
			return _min;
		}
		
        //--------------------------------------------------------------
		float Parameter::max() const {
			return _max;
		}
		
        //--------------------------------------------------------------
		float Parameter::value() const {
			return _value;
		}
		
        //--------------------------------------------------------------
		Types::Index Parameter::valueType() const {
			return _valueTypeIndex;
		}
		
        //--------------------------------------------------------------
		string Parameter::valueTypeName() const {
			return nameForIndex(_valueTypeIndex);
		}


        //--------------------------------------------------------------
		Parameter& Parameter::setValueType(Types::Index type) {
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
            return *this;
		}
		
        //--------------------------------------------------------------
		Parameter& Parameter::setValueType(string s) {
			setValueType(Types::indexForName(s));
            return *this;
		}


		
        //--------------------------------------------------------------
		Parameter& Parameter::setClamp(bool b) {
			_isClamped = b;
			if(_isClamped) setValue(_value);	// clamp immediately
            return *this;
		}
		
        //--------------------------------------------------------------
		bool Parameter::isClamped() const {
			return _isClamped;
		}
		
		
        //--------------------------------------------------------------
		template<typename T> Parameter::operator T() const {
			return (T)_value;
		}
		
        //--------------------------------------------------------------
		template<typename T> T Parameter::operator=(const T & value) {
			setValue(value);
		}
		
        //--------------------------------------------------------------
		Parameter& Parameter::setNormalized(float norm) {
			setValue(ofLerp(_min, _max, norm));
            return *this;
		}
		
        //--------------------------------------------------------------
		float Parameter::normalized() const {
			float norm = (_value - _min) / (_max - _min);
			return norm;
		}
		
        //--------------------------------------------------------------
		Parameter& Parameter::setMappedFrom(float value, float imin, float imax) {
			setValue(ofMap(value, imin, imax, _min, _max));
            return *this;
		}
		
        //--------------------------------------------------------------
		float Parameter::mappedTo(float newMin, float newMax) const {
			return ofMap(_value, _min, _max, newMin, newMax);
		}
		
		
        //--------------------------------------------------------------
		Parameter& Parameter::setValue(float f) {
			switch(_valueTypeIndex) {
				case Types::kFloat:
					_value = _isClamped ? ofClamp(f, _min, _max) : (float)f;
					break;
					
				case Types::kInt:
				case Types::kNamedIndex:
					_value = _isClamped ? ofClamp(f, _min, _max) : (int)f;
					break;
					
				case Types::kToggle:
				case Types::kBang:
					_value = _isClamped ? ofClamp(f, _min, _max) : (bool)f;
					break;
					
				default:
					assert(false);
					
			}
			//				checkValueHasChanged();
			updateControllers();
            return *this;
		}
		
		

	
	}
}