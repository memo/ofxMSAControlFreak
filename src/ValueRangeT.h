/*
 
 Interface base class for any Value (either simple or complex) that can have a range 
 
 */



//msa::ControlFreak::AnyValue i(new msa::ControlFreak::ValueContainerT<float>);
//msa::ControlFreak::AnyValue i;//(new msa::ControlFreak::ValueContainerT<float>);

//msa::ControlFreak::ValueContainerI &i = *new msa::ControlFreak::ValueContainerT<float>;


void main() {
    //    msa::ControlFreak::ValueT<float> f;
    //    Poco::Any i;
    
    //    i.setValue(4);
    //    ofLogVerbose() << (float)i;
    //    i = 3;
    //    ofLogVerbose() << (float)i;
    //    i = 2.3f;
    //    ofLogVerbose() << (float)i;
    //    i = 2.3f;
    //    ofLogVerbose() << (int)i;
    //    i = 2.3;
    //    ofLogVerbose() << (float)i;
    
    //    ofLogVerbose() << "setting to int";
    //    i.setValueType(new msa::ControlFreak::ValueContainerT<int>);
    //    i = 8;
    //    ofLogVerbose() << (int)i;
    //    i = 7;
    //    ofLogVerbose() << (float)i;
    //    i = 9.5;
    //    ofLogVerbose() << (int)i;
    
    
    //    ofLogVerbose() << "setting to ofVec3f";
    //    i.setValueType(new msa::ControlFreak::ValueContainerT<ofVec3f>);
    //
    //    i = ofVec3f(3, 4, 5);
    //    ofLogVerbose() << i.getValue<ofVec3f>();
    ////    i = 3;
    //    ofTranslate(i);
    //    ofLogVerbose() << i.getValue<ofVec3f>();
    ////
    ////    i = 6*2.5 + 10;
    ////    ofLogVerbose() << (float)i;
    //    
    //    ofLogVerbose() << "****************\n";
}


#pragma once

#include "ofMain.h"

namespace msa {
	namespace ControlFreak {
		
		template <typename T>
		class ValueRangeT {
		public:
            
            ValueRangeT();
            
			// set and get value
            ValueRangeT<T>& setValue(T v);
			T& getValue() const;
            
            // operators for assigning and casting (same functionality as above)
            T operator=(const T & v) { this->setValue(v); }
			operator T() const { return this->getValue(); }
			
            // set min/max range values
			ValueRangeT<T>& setRange(T vmin, T vmax);
			T& getMin() const;
			T& getMax() const;
            
            // set and get whether clamping to range is enabled
			ValueRangeT<T>& setClamp(bool b);
            bool getClamp() const;
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            ValueRangeT<T>& setSnap(bool b);
            bool getSnap() const;
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            ValueRangeT<T>& setIncrement(T inc);
            T& getIncrement() const;
            
            
            // increase or decrease by increment amount
            ValueRangeT<T>& inc();
            ValueRangeT<T>& dec();
            
            // set and get as 0...1 values normalized to min/max range
			ValueRangeT<T>& setNormalized(float norm);
			float getNormalized() const;
            
            // set and get mapped to a new range
            ValueRangeT<T>& setMappedFrom(T v, T inputMin, T inputMax);
            T getMappedTo(T newMin, T newMax) const;
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            virtual ValueRangeT<T>& trackVariable(T *pv);
            
			
        protected:
            // override these functions to implement clamping and snapping for any type
            virtual void clamp() {};
            virtual void snap() {};
            
            
            // this actually changes the value
            // while setValue is used externally, that also does clamp and snap
            // this just sets the variable
            void _setValue(T v);

            void update();
            
            
            
		private:
            // pointer to externally stored variable. if set to NULL, points to internal member
            T   *_pvalue;
            
            // internally stored value;
			T   _value;
            
            T   _min, _max, _inc;
            
            T   _oldValue;
            
			bool    _doClamp;
            bool    _doSnap;
		};
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
		template <typename T>
        ValueRangeT<T>::ValueRangeT() {
            ofLogVerbose() << "msa::ControlFreak::ValueRangeT::ValueRangeT";
            trackVariable(NULL);
            setClamp(false);
            setSnap(false);
        }
        
        
        //--------------------------------------------------------------
        template <typename T>
        ValueRangeT<T>& ValueRangeT<T>::setValue(T v) {
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
        void ValueRangeT<T>::_setValue(T v) {
            *_pvalue = v;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T& ValueRangeT<T>::getValue() const {
			return *_pvalue;
		}
        
        //--------------------------------------------------------------
        template <typename T>
		ValueRangeT<T>& ValueRangeT<T>::setRange(T vmin, T vmax) {
            _min = vmin;
            _max = vmax;
            
			setValue(getValue());
			return *this;
		}
        
        //--------------------------------------------------------------
		template <typename T>
		T& ValueRangeT<T>::getMin() const {
			return _min;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T& ValueRangeT<T>::getMax() const {
			return _max;
		}
        
        
        //--------------------------------------------------------------
		template <typename T>
		ValueRangeT<T>& ValueRangeT<T>::setClamp(bool b) {
			_doClamp = b;
			if(_doClamp) clamp();
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		bool ValueRangeT<T>::getClamp() const {
			return _doClamp;
		}
        
        //--------------------------------------------------------------
		template <typename T>
        ValueRangeT<T>& ValueRangeT<T>::setSnap(bool b) {
            _doSnap = b;
			if(_doSnap) snap();
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
        bool ValueRangeT<T>::getSnap() const {
            return _doSnap;
        }
        
        //--------------------------------------------------------------
		template <typename T>
		ValueRangeT<T>& ValueRangeT<T>::setIncrement(T inc) {
            _inc = inc;
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
		T& ValueRangeT<T>::getIncrement() const {
            return _inc;
        }
        
        
        //--------------------------------------------------------------
		template <typename T>
		ValueRangeT<T>& ValueRangeT<T>::inc() {
            setValue(getValue() + getIncrement());
            return *this;
        }
        
        //--------------------------------------------------------------
		template <typename T>
		ValueRangeT<T>& ValueRangeT<T>::dec() {
            setValue(getValue() - getIncrement());
            return *this;
        }
		
        
        //--------------------------------------------------------------
		template <typename T>
		ValueRangeT<T>& ValueRangeT<T>::setNormalized(float norm) {
			setValue(setMappedFrom(norm, 0, 1));
            return *this;
		}
		
        //--------------------------------------------------------------
        template <typename T>
        float ValueRangeT<T>::getNormalized() const {
			return getMappedTo(0, 1);
		}
		
        
        //--------------------------------------------------------------
		template <typename T>
		ValueRangeT<T>& ValueRangeT<T>::setMappedFrom(T v, T inputMin, T inputMax) {
            //			setValue(ofMap(v, inputMin, inputMax, getMin(), getMax()));
            setValue(  ((v - inputMin) / (inputMax - inputMin) * (getMax() - getMin()) + getMin())  );
            return *this;
		}
		
        //--------------------------------------------------------------
		template <typename T>
		T ValueRangeT<T>::getMappedTo(T newMin, T newMax) const {
            //			return ofMap(getValue(), getMin(), getMax(), newMin, newMax);
            return ((getValue() - getMin()) / (getMax() - getMin()) * (newMax - newMin) + newMin);
		}
		
        
        //--------------------------------------------------------------
		template <typename T>
        ValueRangeT<T>& ValueRangeT<T>::trackVariable(T *pv) {
            ofLogVerbose() << "msa::ControlFreak::ValueRangeT::trackVariable";
            _pvalue = pv ? pv : &_value;
            return *this;
        }
        
        //--------------------------------------------------------------
        template <typename T>
        void ValueRangeT<T>::update() {
            if(_doClamp) clamp();
            if(_doSnap) snap();
        }
        
        
	}
}