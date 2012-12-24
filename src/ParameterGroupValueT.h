/*

 A group which can act also as complex value container (e.g. vector, color, matrix etc)

*/

#pragma once

#include "ParameterGroup.h"

namespace msa {
    namespace ControlFreak {
        
        template <typename T>
        class ParameterGroupValueT : public ParameterGroup {
        public:
            friend class ParameterGroup;
            
			// set and get value (these do the magic)
            virtual ParameterGroupValueT<T>& setValue(T v);
			virtual T getValue() const;
			
            // operators for assigning and casting (same functionality as above)
			T operator=(const T & v);
			operator T() const;
			
            // set min/max range values
			virtual ParameterGroupValueT<T>& setRange(T vmin, T vmax);
			virtual T getMin() const;
			virtual T getMax() const;
            
            // set and get whether clamping to range is enabled
			virtual ParameterGroupValueT<T>& setClamp(bool b);
			virtual bool isClamped() const;
			
            // set and get increment amount (when using inc/dec methods)
            virtual ParameterGroupValueT<T>& setIncrement(T inc);
            virtual T getIncrement() const;
            
            // increase or decrease by increment amount
            ParameterGroupValueT<T>& inc();
            ParameterGroupValueT<T>& dec();
            
            // set and get as 0...1 values normalized to min/max range
			ParameterGroupValueT<T>& setNormalized(T norm);
			T getNormalized() const;
            
            // set and get mapped to a new range
            ParameterGroupValueT<T>& setMappedFrom(T v, T inputMin, T inputMax);
            T getMappedTo(T newMin, T newMax) const;
            
			
            // add a controller TODO: add external controllers instead of internal?
			ParameterGroupValueT<T>& addController(Controller *controller);
			void updateControllers();
            //			void checkValueHasChanged();
			
            
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
            
		protected:
//			T                       _value, _min, _max, _inc;
			bool					_isClamped;
			vector<Controller*>		_controllers;
			
			ParameterGroupValueT(ParameterGroup *parent, string name, Types::Index typeIndex);
            
        };
        


        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        template <typename T>
        ParameterGroupValueT<T>& ParameterGroupValueT<T>::setValue(T v) {
            int np = getNumParams();
            for(int i=0; i<np; i++) getParameter(i).setValue(T[i]);
            return *this;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterGroupValueT<T>::getValue() const {
            T retValue;
            int np = getNumParams();
            for(int i=0; i<np; i++) T[i] = getParameter(i).getValue();
			return retValue;;
		}
		
        
        //--------------------------------------------------------------
        template <typename T>
        T ParameterGroupValueT<T>::operator=(const T & v) {
			setValue(v);
		}
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterGroupValueT<T>::operator T() const {
			return (T)getValue();
		}
		
        
        //--------------------------------------------------------------
        template <typename T>
		ParameterGroupValueT<T>& ParameterGroupValueT<T>::setRange(T vmin, T vmax) {
            _min = vmin;
            _max = vmax;
			setValue(getValue());
			return *this;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterGroupValueT<T>::getMin() const {
			return _min;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T ParameterGroupValueT<T>::getMax() const {
			return _max;
		}
        
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterGroupValueT<T>& ParameterGroupValueT<T>::setClamp(bool b) {
			_isClamped = b;
			if(_isClamped) setValue(getValue());	// clamp immediately
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		bool ParameterGroupValueT<T>::isClamped() const {
			return _isClamped;
		}
        
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterGroupValueT<T>& ParameterGroupValueT<T>::setIncrement(T inc) {
            _inc = inc;
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterGroupValueT<T>::getIncrement() const {
            return _inc;
        }
        
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterGroupValueT<T>& ParameterGroupValueT<T>::inc() {
            setValue(getValue() + _inc);
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterGroupValueT<T>& ParameterGroupValueT<T>::dec() {
            setValue(getValue() - _inc);
            return *this;
        }
		
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterGroupValueT<T>& ParameterGroupValueT<T>::setNormalized(float norm) {
			setValue(setMappedFrom(norm, 0, 1));
            return *this;
		}
		
        //--------------------------------------------------------------
        template <typename T>
        float ParameterGroupValueT<T>::getNormalized() const {
			return getMappedTo(0, 1);
		}
		
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterGroupValueT<T>& ParameterGroupValueT<T>::setMappedFrom(T v, T inputMin, T inputMax) {
            //			setValue(ofMap(v, inputMin, inputMax, getMin(), getMax()));
            setValue(  ((v - inputMin) / (inputMax - inputMin) * (getMax() - getMin()) + _min)  );
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T ParameterGroupValueT<T>::getMappedTo(T newMin, T newMax) const {
            //			return ofMap(getValue(), getMin(), getMax(), newMin, newMax);
            return ((getValue() - getMin()) / (getMax() - getMin()) * (newMax - newMin) + newMin);
		}
		
        
		
        //--------------------------------------------------------------
		template <typename T>
		ParameterGroupValueT<T>& ParameterGroupValueT<T>::addController(Controller *controller) {
			controller->setParam(this);
			controller->updateController();
			_controllers.push_back(controller);
			return *this;
		}
		
		
        //--------------------------------------------------------------
		template <typename T>
		void ParameterGroupValueT<T>::updateControllers() {
			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
		}
		
		//		void ParameterGroupValueT<T>::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}
        
		
        //--------------------------------------------------------------
  		template <typename T>
		string ParameterGroupValueT<T>::fullName() const {
			string s;
			for(int i=0; i<_controllers.size(); i++) s += "[" + _controllers[i]->toString() + "]";
			return s + " " + getName();
		}
        
        //--------------------------------------------------------------
		template <typename T>
        void ParameterGroupValueT<T>::writeToXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroupValueT<T>::writeToXml " << getPath().c_str();
            
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
        void ParameterGroupValueT<T>::readFromXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterGroupValueT<T>::readFromXml " << getPath().c_str();
        }
        
        
        
        //--------------------------------------------------------------
		template <typename T>
        ParameterGroupValueT<T>::ParameterGroupValueT(ParameterGroup *parent, string name, Types::Index typeIndex)
        : Parameter(parent, name, typeIndex) {
            ofLogVerbose() << "msa::ControlFreak::ParameterGroupValueT<T>::Parameter " <<  getPath().c_str();
            
            setClamp(false);
            setValue(0);
            setRange(0, 100);
        }
        
        
        }
    }