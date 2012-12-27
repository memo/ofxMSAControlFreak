/*
 
 Template base class for any Parameter that can have a value (either simple or complex), with a range

 Protected constructor, can only be created via ParameterGroup
 
 */



#pragma once

#include "ofxMSAControlFreak/src/Parameter.h"
//#include "ofxMSAControlFreak/src/ValueT.h"

namespace msa {
	namespace ControlFreak {
		
		template <typename T>
		class ParameterValueT : public Parameter {
		public:

			// set and get value
            ParameterValueT<T>& setValue(T v);
			T& getValue() const;
            
            // whether the value changed this frame or not
            bool hasChanged();
            
            // operators for assigning and casting (same functionality as above)
            T operator=(const T & v) { kCheckBadParameter(T()); this->setValue(v); }
			operator T() const { kCheckBadParameter(T()); return this->getValue(); }
			
            // set min/max range values
			ParameterValueT<T>& setRange(T vmin, T vmax);
			T getMin() const;
			T getMax() const;

            // set and get whether clamping to range is enabled
			ParameterValueT<T>& setClamp(bool b);
            bool getClamp() const;
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            ParameterValueT<T>& setSnap(bool b);
            bool getSnap() const;
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            ParameterValueT<T>& setIncrement(T inc);
            T getIncrement() const;

            
            // increase or decrease by increment amount
            ParameterValueT<T>& inc(T amount);
            ParameterValueT<T>& dec(T amount);
            
            // set and get as 0...1 values normalized to min/max range
			ParameterValueT<T>& setNormalized(float norm);
			float getNormalized() const;
            
            // set and get mapped to a new range
            ParameterValueT<T>& setMappedFrom(T v, T inputMin, T inputMax);
            T getMappedTo(T newMin, T newMax) const;
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            virtual ParameterValueT<T>& trackVariable(T *pv);

			
            // add a controller TODO: add external controllers instead of internal?
//			ParameterValueT<T>& addController(Controller *controller);
//			void updateControllers();
            //			void checkValueHasChanged();
			
            
        protected:
            ParameterValueT(ParameterGroup *parent, string name, Type::Index typeIndex);
            
            // override these functions to implement clamping and snapping for any type
            virtual void clamp() {};
            virtual void snap() {};
            
            
            // this actually changes the value
            // while setValue is used externally, that also does clamp and snap
            // this just sets the variable
            void _setValue(T v);
            
            // from Parameter:
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull) = 0;
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull) = 0;
            virtual void update();
            
		private:
            // pointer to externally stored variable. if set to NULL, points to internal member
            T   *_pvalue;
            
            // internally stored value;
			T   _value;
            
            T   _min, _max, _inc;
            
            T   _oldValue;
            
            
			bool    _doClamp;
            bool    _doSnap;
			vector<Controller*>		_controllers;
		};
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
		template <typename T>
        ParameterValueT<T>::ParameterValueT(ParameterGroup *parent, string name, Type::Index typeIndex)
        : Parameter(parent, name, typeIndex) {
//            ofLogVerbose() << "msa::ControlFreak::ParameterValueT::ParameterValueT " <<  getPath();
            trackVariable(NULL);
            setClamp(false);
            setSnap(false);
        }
        
        
        //--------------------------------------------------------------
        template <typename T>
        ParameterValueT<T>& ParameterValueT<T>::setValue(T v) {
            kCheckBadParameter(*this);
            
            // set value and clamp if nessecary
            _setValue(v);
            if(_doClamp) clamp();
            if(_doSnap) snap();
            
			//				checkValueHasChanged();
//			updateControllers();
            return *this;
		}
        
        //--------------------------------------------------------------
        template <typename T>
        void ParameterValueT<T>::_setValue(T v) {
            kCheckBadParameter();
            
            *_pvalue = v;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T& ParameterValueT<T>::getValue() const {
            kCheckBadParameter();
            
			return *_pvalue;
		}
        
        
        //--------------------------------------------------------------
		template <typename T>
        bool ParameterValueT<T>::hasChanged() {
//            bool ret = (getValue() != _oldValue);
//            if(ret) _oldValue = getValue();
            return true;
        }

        //--------------------------------------------------------------
        template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setRange(T vmin, T vmax) {
            kCheckBadParameter(*this);
            
            _min = vmin;
            _max = vmax;

			setValue(getValue());
			return *this;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterValueT<T>::getMin() const {
            kCheckBadParameter(T());
            
			return _min;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T ParameterValueT<T>::getMax() const {
            kCheckBadParameter(T());
            
			return _max;
		}

        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setClamp(bool b) {
            kCheckBadParameter(*this);
            
			_doClamp = b;
			if(_doClamp) clamp();
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		bool ParameterValueT<T>::getClamp() const {
            kCheckBadParameter(false);
            
			return _doClamp;
		}
        
        //--------------------------------------------------------------
		template <typename T>
        ParameterValueT<T>& ParameterValueT<T>::setSnap(bool b) {
            kCheckBadParameter(*this);
            
            _doSnap = b;
			if(_doSnap) snap();
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
        bool ParameterValueT<T>::getSnap() const {
            kCheckBadParameter(false);
            
            return _doSnap;
        }

        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setIncrement(T inc) {
            kCheckBadParameter(*this);
            
            _inc = inc;
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
		T ParameterValueT<T>::getIncrement() const {
            kCheckBadParameter(T());
            
            return _inc ? _inc : T(1);
        }
        
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::inc(T amount) {
            kCheckBadParameter(*this);
            
            setValue(getValue() + getIncrement() * amount);
            return *this;
        }
    
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::dec(T amount) {
            kCheckBadParameter(*this);
            
            setValue(getValue() - getIncrement() * amount);
            return *this;
        }
		
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setNormalized(float norm) {
            kCheckBadParameter(*this);
            
			setValue(setMappedFrom(norm, 0, 1));
            return *this;
		}
		
        //--------------------------------------------------------------
        template <typename T>
        float ParameterValueT<T>::getNormalized() const {
            kCheckBadParameter(0);
            
			return getMappedTo(0, 1);
		}
		
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setMappedFrom(T v, T inputMin, T inputMax) {
            kCheckBadParameter(*this);
            
			setValue(ofMap(v, inputMin, inputMax, getMin(), getMax()));
//            setValue(  ((v - inputMin) / (inputMax - inputMin) * (getMax() - getMin()) + getMin())  );
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T ParameterValueT<T>::getMappedTo(T newMin, T newMax) const {
            kCheckBadParameter(T());
            
			return ofMap(getValue(), getMin(), getMax(), newMin, newMax);
//            return ((getValue() - getMin()) / (getMax() - getMin()) * (newMax - newMin) + newMin);
		}
		

        //--------------------------------------------------------------
		template <typename T>
        ParameterValueT<T>& ParameterValueT<T>::trackVariable(T *pv) {
//            ofLogVerbose() << "msa::ControlFreak::ParameterValueT::trackVariable " <<  getPath() << " " << pv;
            kCheckBadParameter(*this);
            
            _pvalue = pv ? pv : &_value;
            return *this;
        }
        

        //--------------------------------------------------------------
//		template <typename T>
//		ParameterValueT<T>& ParameterValueT<T>::addController(Controller *controller) {
//            ofLogVerbose() << "msa::ControlFreak::ParameterValueT::addController " <<  getPath() << " " << controller;
////			controller->setParam(this);
//			controller->updateController();
//			_controllers.push_back(controller);
//			return *this;
//		}
//		
//		
//        //--------------------------------------------------------------
//		template <typename T>
//		void ParameterValueT<T>::updateControllers() {
//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
//		}
		
		//		void ParameterValueT<T>::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}

		
        //--------------------------------------------------------------
        template <typename T>
        void ParameterValueT<T>::update() {
            kCheckBadParameter();
            
            Parameter::update();
            if(_doClamp) clamp();
            if(_doSnap) snap();
            
//            _oldValue = getValue();
        }
        
        
	}
}