/*
 
 Template base class for anything that has a single value, with a range
 
 */

// protected constructor, can only be created via ParameterGroup


#pragma once

#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
	namespace ControlFreak {
		
		template <typename T>
		class ParameterValueT : public Parameter {
		public:
            friend class ParameterGroup;
			
			// set and get value
            ParameterValueT<T>& setValue(T v);
			T getValue() const;
			
            // operators for assigning and casting (same functionality as above)
			T operator=(const T & v);
			operator T() const;
			
            // set min/max range values
			ParameterValueT<T>& setRange(T vmin, T vmax);
			T getMin() const;
			T getMax() const;

            // set and get whether clamping to range is enabled
			ParameterValueT<T>& setClamp(bool b);
			bool isClamped() const;
			
            // set and get increment amount (when using inc/dec methods)
            ParameterValueT<T>& setIncrement(T inc);
            T getIncrement() const;
            
            // increase or decrease by increment amount
            ParameterValueT<T>& inc();
            ParameterValueT<T>& dec();
            
            // set and get as 0...1 values normalized to min/max range
			ParameterValueT<T>& setNormalized(float norm);
			float getNormalized() const;
            
            // set and get mapped to a new range
            ParameterValueT<T>& setMappedFrom(T v, T inputMin, T inputMax);
            T getMappedTo(T newMin, T newMax) const;

			
            // add a controller TODO: add external controllers instead of internal?
			ParameterValueT<T>& addController(Controller *controller);
			void updateControllers();
            //			void checkValueHasChanged();
			
            
            // from Parameter:
			virtual string fullName() const;	// return name prefixed with controllers
			
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
            
		protected:
			T                       _value, _min, _max, _inc;
			bool					_isClamped;
			vector<Controller*>		_controllers;
			
			ParameterValueT(ParameterGroup *parent, string name, Types::Index typeIndex);
		};
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        template <typename T>
        ParameterValueT<T>& ParameterValueT<T>::setValue(T v) {
            _value = _isClamped ? ( v < _min ? _min : _value > _max ? _max : v) : v;
			//				checkValueHasChanged();
			updateControllers();
            return *this;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterValueT<T>::getValue() const {
			return _value;
		}
		
        
        //--------------------------------------------------------------
        template <typename T>
        T ParameterValueT<T>::operator=(const T & v) {
			setValue(v);
		}
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>::operator T() const {
			return (T)getValue();
		}
		
        
        //--------------------------------------------------------------
        template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setRange(T vmin, T vmax) {
            _min = vmin;
            _max = vmax;
			setValue(getValue());
			return *this;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterValueT<T>::getMin() const {
			return _min;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T ParameterValueT<T>::getMax() const {
			return _max;
		}

        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setClamp(bool b) {
			_isClamped = b;
			if(_isClamped) setValue(getValue());	// clamp immediately
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		bool ParameterValueT<T>::isClamped() const {
			return _isClamped;
		}
        

        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setIncrement(T inc) {
            _inc = inc;
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterValueT<T>::getIncrement() const {
            return _inc;
        }
        
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::inc() {
            setValue(getValue() + _inc);
            return *this;
        }
    
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::dec() {
            setValue(getValue() - _inc);
            return *this;
        }
		
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setNormalized(float norm) {
			setValue(setMappedFrom(norm, 0, 1));
            return *this;
		}
		
        //--------------------------------------------------------------
        template <typename T>
        float ParameterValueT<T>::getNormalized() const {
			return getMappedTo(0, 1);
		}
		
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setMappedFrom(T v, T inputMin, T inputMax) {
//			setValue(ofMap(v, inputMin, inputMax, getMin(), getMax()));
            setValue(  ((v - inputMin) / (inputMax - inputMin) * (getMax() - getMin()) + _min)  );
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T ParameterValueT<T>::getMappedTo(T newMin, T newMax) const {
//			return ofMap(getValue(), getMin(), getMax(), newMin, newMax);
            return ((getValue() - getMin()) / (getMax() - getMin()) * (newMax - newMin) + newMin);
		}
		

		
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::addController(Controller *controller) {
			controller->setParam(this);
			controller->updateController();
			_controllers.push_back(controller);
			return *this;
		}
		
		
        //--------------------------------------------------------------
		template <typename T>
		void ParameterValueT<T>::updateControllers() {
			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
		}
		
		//		void ParameterValueT<T>::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}

		
        //--------------------------------------------------------------
  		template <typename T>
		string ParameterValueT<T>::fullName() const {
			string s;
			for(int i=0; i<_controllers.size(); i++) s += "[" + _controllers[i]->toString() + "]";
			return s + " " + getName();
		}
        
        //--------------------------------------------------------------
		template <typename T>
        void ParameterValueT<T>::writeToXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterValueT<T>::writeToXml " << getPath().c_str();
            
            Parameter::writeToXml(xml, bFull);  // IMPORTANT: always start with parents write to xml
            xml.addAttribute(_xmlTag, "value", getValue(), _xmlTagId);
            if(bFull) {
                xml.addAttribute(_xmlTag, "min", getMin(), _xmlTagId);
                xml.addAttribute(_xmlTag, "max", getMax(), _xmlTagId);
                xml.addAttribute(_xmlTag, "clamped", isClamped(), _xmlTagId);
                xml.addAttribute(_xmlTag, "inc", getIncrement(), _xmlTagId);
            }
        }
        
        //--------------------------------------------------------------
		template <typename T>
        void ParameterValueT<T>::readFromXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterValueT<T>::readFromXml " << getPath().c_str();
        }
        
        
        
        //--------------------------------------------------------------
		template <typename T>
        ParameterValueT<T>::ParameterValueT(ParameterGroup *parent, string name, Types::Index typeIndex)
        : Parameter(parent, name, typeIndex) {
            ofLogVerbose() << "msa::ControlFreak::ParameterValueT<T>::Parameter " <<  getPath().c_str();
            
            setClamp(false);
            setValue(0);
            setRange(0, 100);
        }
        
        
	}
}