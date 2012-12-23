
// protected constructor, can only be created via ParameterGroup


#pragma once

#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
	namespace ControlFreak {
		
		template <typename T>
		class ParameterNumberT : public Parameter {
		public:
            friend class ParameterGroup;
			
			virtual ~ParameterNumberT() {}
			
			// set and get value
            ParameterNumberT<T>& setValue(T v);
			T getValue() const;
			
            // operators for assigning and casting (same functionality as above)
			T operator=(const T & v);
			operator T() const;
			
            // set min/max range values
			ParameterNumberT<T>& setRange(T vmin, T vmax);
			T getMin() const;
			T getMax() const;

            // set and get whether clamping to range is enabled
			ParameterNumberT<T>& setClamp(bool b);
			bool isClamped() const;
			
            // set and get increment amount (when using inc/dec methods)
            ParameterNumberT<T>& setIncrement(T inc);
            T getIncrement() const;
            
            // increase or decrease by increment amount
            ParameterNumberT<T>& inc();
            ParameterNumberT<T>& dec();
            
            // set and get as 0...1 values normalized to min/max range
			ParameterNumberT<T>& setNormalized(float norm);
			float getNormalized() const;
            
            // set and get mapped to a new range
            ParameterNumberT<T>& setMappedFrom(T v, T inputMin, T inputMax);
            T getMappedTo(T newMin, T newMax) const;

			
            // add a controller TODO: add external controllers instead of internal?
			ParameterNumberT<T>& addController(Controller *controller);
			void updateControllers();
            //			void checkValueHasChanged();
			
            
            // from Parameter:
			virtual string fullName() const;	// return name prefixed with controllers
			
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull, string tag, int tagid);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull, string tag, int tagid);
            
		protected:
			T                       _min, _max, _value, _inc;
			bool					_isClamped;
			vector<Controller*>		_controllers;
			
			ParameterNumberT(ParameterGroup *parent, string path, Types::Index typeIndex);
		};
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        template <typename T>
        ParameterNumberT<T>& ParameterNumberT<T>::setValue(T v) {
            _value = _isClamped ? ofClamp(v, getMin(), getMax()) : v;
			//				checkValueHasChanged();
			updateControllers();
            return *this;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterNumberT<T>::getValue() const {
			return _value;
		}
		
        
        //--------------------------------------------------------------
        template <typename T>
        T ParameterNumberT<T>::operator=(const T & v) {
			setValue(v);
		}
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterNumberT<T>::operator T() const {
			return (T)getValue();
		}
		
        
        //--------------------------------------------------------------
        template <typename T>
		ParameterNumberT<T>& ParameterNumberT<T>::setRange(T vmin, T vmax) {
            _min = vmin;
            _max = vmax;
			setValue(getValue());
			return *this;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterNumberT<T>::getMin() const {
			return _min;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T ParameterNumberT<T>::getMax() const {
			return _max;
		}

        
        //--------------------------------------------------------------
		template <typename T>
		ParameterNumberT<T>& ParameterNumberT<T>::setClamp(bool b) {
			_isClamped = b;
			if(_isClamped) setValue(getValue());	// clamp immediately
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		bool ParameterNumberT<T>::isClamped() const {
			return _isClamped;
		}
        

        //--------------------------------------------------------------
		template <typename T>
		ParameterNumberT<T>& ParameterNumberT<T>::setIncrement(T inc) {
            _inc = inc;
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterNumberT<T>::getIncrement() const {
            return _inc;
        }
        
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterNumberT<T>& ParameterNumberT<T>::inc() {
            setValue(getValue() + _inc);
            return *this;
        }
    
        //--------------------------------------------------------------
		template <typename T>
		ParameterNumberT<T>& ParameterNumberT<T>::dec() {
            setValue(getValue() - _inc);
            return *this;
        }
		
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterNumberT<T>& ParameterNumberT<T>::setNormalized(float norm) {
			setValue(setMappedFrom(norm, 0, 1));
            return *this;
		}
		
        //--------------------------------------------------------------
        template <typename T>
        float ParameterNumberT<T>::getNormalized() const {
			return getMappedTo(0, 1);
		}
		
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterNumberT<T>& ParameterNumberT<T>::setMappedFrom(T v, T inputMin, T inputMax) {
			setValue(ofMap(v, inputMin, inputMax, getMin(), getMax()));
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T ParameterNumberT<T>::getMappedTo(T newMin, T newMax) const {
			return ofMap(getValue(), getMin(), getMax(), newMin, newMax);
		}
		

		
        //--------------------------------------------------------------
		template <typename T>
		ParameterNumberT<T>& ParameterNumberT<T>::addController(Controller *controller) {
			controller->setParam(this);
			controller->updateController();
			_controllers.push_back(controller);
			return *this;
		}
		
		
        //--------------------------------------------------------------
		template <typename T>
		void ParameterNumberT<T>::updateControllers() {
			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
		}
		
		//		void ParameterNumberT<T>::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}

		
        //--------------------------------------------------------------
  		template <typename T>
		string ParameterNumberT<T>::fullName() const {
			string s;
			for(int i=0; i<_controllers.size(); i++) s += "[" + _controllers[i]->toString() + "]";
			return s + " " + name();
		}
        
        //--------------------------------------------------------------
		template <typename T>
        void ParameterNumberT<T>::writeToXml(ofxXmlSettings &xml, bool bFull, string tag, int tagid) {
			ofLogVerbose() << "msa::ControlFreak::ParameterNumberT<T>::writeToXml " << _path.c_str();
            xml.addAttribute(tag, "type", typeName(), tagid);
            xml.addAttribute(tag, "value", getValue(), tagid);
            if(bFull) {
                xml.addAttribute(tag, "min", getMin(), tagid);
                xml.addAttribute(tag, "max", getMax(), tagid);
            }
        }
        
        //--------------------------------------------------------------
		template <typename T>
        void ParameterNumberT<T>::readFromXml(ofxXmlSettings &xml, bool bFull, string tag, int tagid) {
			ofLogVerbose() << "msa::ControlFreak::ParameterNumberT<T>::readFromXml " << _path.c_str();
        }
        
        
        
        //--------------------------------------------------------------
		template <typename T>
        ParameterNumberT<T>::ParameterNumberT(ParameterGroup *parent, string path, Types::Index typeIndex) : Parameter(parent, path, typeIndex) {
            ofLogVerbose() << "msa::ControlFreak::ParameterNumberT<T>::Parameter " <<  _path.c_str();
            
            setClamp(false);
            setValue(0);
            setRange(0, 100);
        }
        
        
	}
}