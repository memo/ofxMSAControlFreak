
// protected constructor, can only be created via Parameters


#pragma once

#include "MSACore.h"
#include "MSACFController.h"
#include "MSACFParameterTypes.h"

#include <boost/property_tree/ptree.hpp>

namespace msa {
	namespace ControlFreak {
		
#define kPathDivider	'.'
		
		class Parameters;
        
//        typedef std::tr1::shared_ptr<ParameterT> ParameterRef;

		template <typename T>
		class ParameterT {
		public:
			
			friend class Parameters;
			
			ParameterT(string path="", T value=T(), T vmin=T(), T vmax=T()) : _path(path), _value(value), _min(vmin), _max(vmax) {
				printf("ParameterT<T>::ParameterT %s\n", _path.c_str());
				
                //				setValueType(typeIndex);
                //				setClamp(true);
				
				// set name
                //				size_t lastDividerPos = _path.rfind(kPathDivider);
                //				_name = lastDividerPos == string::npos ? _path : _path.substr(lastDividerPos+1);
			}
            
			virtual ~ParameterT() {}
			
			string path() const;
			string name() const;		// return name
			string fullName() const;	// return name prefixed with controllers
			
			ParameterT<T>& setValue(T &v);
			ParameterT<T>& setRange(T& vmin, T& vmax);
			
			T min() const;
			T max() const;
			T value() const;
			
//			Types::Index valueType() const;
//			string valueTypeName() const;
			
			ParameterT<T>& setClamp(bool b);			// enable or disable clamping
			bool isClamped() const;                 // returns whether clamp is enabled or not
			
			operator T() const;                     // cast operator
			T operator=(const T &value);            // assignment operator
			
			ParameterT<T>& setNormalized(float norm);				// input 0...1 number, maps to range
			float normalized() const;					// return 0...1 number mapped from range
			
			ParameterT<T>& setMappedFrom(float value, T& imin, T& imax);
			float mappedTo(T &newMin, T &newMax) const;	// returns value mapped to new range

			
			ParameterT<T>& addController(Controller *controller);
			ParameterT<T>& updateControllers();
//			void checkValueHasChanged();
			
			virtual void writeToPropertyTree(boost::property_tree::ptree& pt);
			virtual void readFromPropertyTree(boost::property_tree::ptree& pt);
            
            
		protected:
			Types::Index			_valueTypeIndex;
			T                       _min, _max, _value;
			string					_path;
			string					_name;
			bool					_isClamped;
			vector<Controller*>		_controllers;
			Parameters              *_parent;
			
//			void setValueType(Types::Index type);
//			void setValueType(string s);
			
			// used by all setters for common setting behaviour
		};
		
		
		//------------------------------------------------------------
		//------------------------------------------------------------
		//------------------------------------------------------------
		template <typename T>
		string ParameterT<T>::path() const {
			return _path;
		}
		
		//------------------------------------------------------------
		template <typename T>
		string ParameterT<T>::name() const {
			return _name;
		}
		
		//------------------------------------------------------------
		template <typename T>
		string ParameterT<T>::fullName() const {
			string s;
			for(int i=0; i<_controllers.size(); i++) s += "[" + _controllers[i]->toString() + "]";
			return s + " " + name();
		}
		
		//------------------------------------------------------------
		template <typename T>
		ParameterT<T>& ParameterT<T>::setValue(T& v) {
            _value = v;
            // TODO: clamp
//			switch(_valueTypeIndex) {
//				case Types::kFloat:
//					_value = _isClamped ? ofClamp(f, _min, _max) : (float)f;
//					break;
//					
//				case Types::kInt:
//				case Types::kNamedIndex:
//					_value = _isClamped ? ofClamp(f, _min, _max) : (int)f;
//					break;
//					
//				case Types::kToggle:
//				case Types::kBang:
//					_value = _isClamped ? ofClamp(f, _min, _max) : (bool)f;
//					break;
//					
//				default:
//					assert(false);
//			}
			//				checkValueHasChanged();
//			updateControllers();
            return *this;
		}
        
		//------------------------------------------------------------
		template <typename T>
		ParameterT<T>& ParameterT<T>::setRange(T& vmin, T& vmax) {
			_min = vmin;
			_max = vmax;
			setValue(_value);
			return *this;
		}
        
        
		//------------------------------------------------------------
		template <typename T>
		T ParameterT<T>::min() const {
			return _min;
		}
		
        //------------------------------------------------------------
		template <typename T>
        T ParameterT<T>::max() const {
			return _max;
		}
		
		//------------------------------------------------------------
		template <typename T>
		T ParameterT<T>::value() const {
			return _value;
		}
		
        
		//------------------------------------------------------------
//		template <typename T>
//		Types::Index ParameterT<T>::valueType() const {
//			return _valueTypeIndex;
//		}
//		
//		//------------------------------------------------------------
//		template <typename T>
//		string ParameterT<T>::valueTypeName() const {
//			return nameForIndex(_valueTypeIndex);
//		}


		//------------------------------------------------------------
//		template <typename T>
//		void ParameterT<T>::setValueType(Types::Index type) {
//			_valueTypeIndex = type;
//			switch(_valueTypeIndex) {
//				case Types::kToggle:
//				case Types::kBang:
//					setRange(0, 1);
//					break;
//
//				case Types::kFloat:
//				case Types::kInt:
//				case Types::kNamedIndex:
//					setValue(_value);
//					break;
//					
//					
//				default:
//					assert(false);
//					
//			}
//		}
//		
//		//------------------------------------------------------------
//		template <typename T>
//		void ParameterT<T>::setValueType(string s) {
//			setValueType(Types::indexForName(s));
//		}


		
		//------------------------------------------------------------
		template <typename T>
		ParameterT<T>& ParameterT<T>::setClamp(bool b) {
			_isClamped = b;
			if(_isClamped) setValue(_value);	// clamp immediately
            return *this;
		}
		
		//------------------------------------------------------------
		template <typename T>
		bool ParameterT<T>::isClamped() const {
			return _isClamped;
		}
		
		
		//------------------------------------------------------------
		template <typename T>
        ParameterT<T>::operator T() const {
			return (T)_value;
		}
		
		//------------------------------------------------------------
		template <typename T>
        T ParameterT<T>::operator=(const T & value) {
			setValue(value);
            return value;
		}
		
		//------------------------------------------------------------
		template <typename T>
		ParameterT<T>& ParameterT<T>::setNormalized(float norm) {
			setValue(ofLerp(_min, _max, norm));
            return *this;
		}
		
		//------------------------------------------------------------
		template <typename T>
		float ParameterT<T>::normalized() const {
			float norm = (_value - _min) / (_max - _min);
			return norm;
		}
		
		//------------------------------------------------------------
		template <typename T>
		ParameterT<T>& ParameterT<T>::setMappedFrom(float value, T& imin, T& imax) {
			setValue(ofMap(value, imin, imax, _min, _max));
            return *this;
		}
		
		//------------------------------------------------------------
		template <typename T>
		float ParameterT<T>::mappedTo(T& newMin, T& newMax) const {
			return ofMap(_value, _min, _max, newMin, newMax);
		}
        
		//------------------------------------------------------------
		template <typename T>
        ParameterT<T>& ParameterT<T>::addController(Controller *controller) {
//			controller->setParam(this);// TODO
			controller->updateController();
			_controllers.push_back(controller);
			return *this;
		}
		
		
		//------------------------------------------------------------
		template <typename T>
		ParameterT<T>& ParameterT<T>::updateControllers() {
			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
            return *this;
		}
		
		//		void Parameter::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}
		
		//------------------------------------------------------------
		template <typename T>
		void ParameterT<T>::writeToPropertyTree(boost::property_tree::ptree& pt) {
			printf("Parameter::writeToPropertyTree %s\n", _path.c_str());
			pt.put(_path, "PARAMETER");
//			pt.put(_path + kPathDivider + "type", valueTypeName());// TODO:
			pt.put(_path + kPathDivider + "min", _min);
			pt.put(_path + kPathDivider + "max", _max);
			pt.put(_path + kPathDivider + "value", _value);
		}
		
		//------------------------------------------------------------
		template <typename T>
		void ParameterT<T>::readFromPropertyTree(boost::property_tree::ptree& pt) {
			printf("Parameter::readFromPropertyTree %s\n", _path.c_str());
			setValueType(pt.get<string>(_path + kPathDivider + "type"));
			setRange(pt.get<float>(_path + kPathDivider + "min"), pt.get<float>(_path + kPathDivider + "max"));
			setValue(pt.get<float>(_path + kPathDivider + "value"));
		}

		

	
	}
}