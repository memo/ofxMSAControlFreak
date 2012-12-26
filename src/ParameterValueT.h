/*
 
 Template base class for any Parameter that can have a value (either simple or complex), with a range

 Protected constructor, can only be created via ParameterGroup
 
 */



#pragma once

#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
	namespace ControlFreak {
		
		template <typename T>
		class ParameterValueT : public Parameter {
		public:

            ParameterValueT(ParameterGroup *parent, string name, Type::Index typeIndex);
            
			// set and get value
            ParameterValueT<T>& setValue(T v);
			T& getValue() const;
            
            // operators for assigning and casting (same functionality as above)
            T operator=(const T & v) { this->setValue(v); }
			operator T() const { return this->getValue(); }
			
            // set min/max range values
			ParameterValueT<T>& setRange(T vmin, T vmax);
			T& getMin() const;
			T& getMax() const;

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
            T& getIncrement() const;

            
            // increase or decrease by increment amount
            ParameterValueT<T>& inc();
            ParameterValueT<T>& dec();
            
            // set and get as 0...1 values normalized to min/max range
			ParameterValueT<T>& setNormalized(float norm);
			float getNormalized() const;
            
            // set and get mapped to a new range
            ParameterValueT<T>& setMappedFrom(T v, T inputMin, T inputMax);
            T getMappedTo(T newMin, T newMax) const;
            
            
            // OPTIONAL
            // track vaiables and keep values in sync (send NULL to clear)
            virtual ParameterValueT<T>& setValueVariable(T *pv);
            virtual ParameterValueT<T>& setRangeVariables(T *pmin, T *pmax);
            virtual ParameterValueT<T>& setIncrementVariable(T *pinc);

			
            // add a controller TODO: add external controllers instead of internal?
			ParameterValueT<T>& addController(Controller *controller);
			void updateControllers();
            //			void checkValueHasChanged();
			
            
            // from Parameter:
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull) = 0;
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull) = 0;
            virtual void update();

        protected:
            // override these functions to implement clamping and snapping for any type
            virtual void clamp() {};
            virtual void snap() {};
            
            
            // this actually changes the value
            // while setValue is used externally, that also does clamp and snap
            // this just sets the variable
            void _setValue(T v);

		private:
            // pointers to externally stored values
            // if they are set to NULL, they point to the below internal members
            T   *_pvalue, *_pmin, *_pmax, *_pinc;
            
            // internally stored values
            // these are only used as targets if any of the above is set to NULL
			T   _value, _min, _max, _inc;
            
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
        : Parameter(parent, name, typeIndex), _pvalue(NULL), _pmin(NULL), _pmax(NULL), _pinc(NULL) {
            ofLogVerbose() << "msa::ControlFreak::ParameterValueT::ParameterValueT " <<  getPath();
            setValueVariable(NULL);
            setRangeVariables(NULL, NULL);
            setIncrementVariable(NULL);
            setClamp(false);
            setSnap(false);
        }
        
        
        //--------------------------------------------------------------
        template <typename T>
        ParameterValueT<T>& ParameterValueT<T>::setValue(T v) {
            // set value and clamp if nessecary
            _setValue(v);
            if(_doClamp) clamp();
            if(_doSnap) snap();
            
			//				checkValueHasChanged();
			updateControllers();
            return *this;
		}
        
        //--------------------------------------------------------------
        template <typename T>
        void ParameterValueT<T>::_setValue(T v) {
            *_pvalue = v;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T& ParameterValueT<T>::getValue() const {
			return *_pvalue;
		}
        
        //--------------------------------------------------------------
        template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setRange(T vmin, T vmax) {
            *_pmin = vmin;
            *_pmax = vmax;

			setValue(getValue());
			return *this;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T& ParameterValueT<T>::getMin() const {
			return *_pmin;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T& ParameterValueT<T>::getMax() const {
			return *_pmax;
		}

        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setClamp(bool b) {
			_doClamp = b;
			if(_doClamp) clamp();
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		bool ParameterValueT<T>::getClamp() const {
			return _doClamp;
		}
        
        //--------------------------------------------------------------
		template <typename T>
        ParameterValueT<T>& ParameterValueT<T>::setSnap(bool b) {
            _doSnap = b;
			if(_doSnap) snap();
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
        bool ParameterValueT<T>::getSnap() const {
            return _doSnap;
        }

        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::setIncrement(T inc) {
            *_pinc = inc;
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
		T& ParameterValueT<T>::getIncrement() const {
            return *_pinc;
        }
        
        
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::inc() {
            setValue(getValue() + getIncrement());
            return *this;
        }
    
        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::dec() {
            setValue(getValue() - getIncrement());
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
			setValue(ofMap(v, inputMin, inputMax, getMin(), getMax()));
//            setValue(  ((v - inputMin) / (inputMax - inputMin) * (getMax() - getMin()) + getMin())  );
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T ParameterValueT<T>::getMappedTo(T newMin, T newMax) const {
			return ofMap(getValue(), getMin(), getMax(), newMin, newMax);
//            return ((getValue() - getMin()) / (getMax() - getMin()) * (newMax - newMin) + newMin);
		}
		

        //--------------------------------------------------------------
		template <typename T>
        ParameterValueT<T>& ParameterValueT<T>::setValueVariable(T *pv) {
            ofLogVerbose() << "msa::ControlFreak::ParameterValueT::setValueVariable " <<  getPath() << " " << pv;
            _pvalue = pv ? pv : &_value;
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
        ParameterValueT<T>& ParameterValueT<T>::setRangeVariables(T *pmin, T *pmax) {
            ofLogVerbose() << "msa::ControlFreak::ParameterValueT::setRangeVariables " <<  getPath() << " " << pmin << " " << pmax;
            _pmin = pmin ? pmin : &_min;
            _pmax = pmax ? pmax : &_max;
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
        ParameterValueT<T>& ParameterValueT<T>::setIncrementVariable(T *pinc) {
            ofLogVerbose() << "msa::ControlFreak::ParameterValueT::setValueVariable " <<  getPath() << " " << pinc;
            _pinc = pinc ? pinc : &_inc;
            return *this;
        }

        //--------------------------------------------------------------
		template <typename T>
		ParameterValueT<T>& ParameterValueT<T>::addController(Controller *controller) {
            ofLogVerbose() << "msa::ControlFreak::ParameterValueT::addController " <<  getPath() << " " << controller;
//			controller->setParam(this);
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
        void ParameterValueT<T>::update() {
            Parameter::update();
            if(_doClamp) clamp();
            if(_doSnap) snap();
        }
        
        
	}
}