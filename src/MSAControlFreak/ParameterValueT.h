//                                      __
//     ____ ___  ___  ____ ___  ____   / /__   __
//    / __ `__ \/ _ \/ __ `__ \/ __ \ / __/ | / /
//   / / / / / /  __/ / / / / / /_/ // /_ | |/ /
//  /_/ /_/ /_/\___/_/ /_/ /_/\____(_)__/ |___/
//
//
//  Created by Memo Akten, www.memo.tv
//
//  ofxMSAControlFreak
//

/*
 
 Template base class for any Parameter that can have a value (either simple or complex), with a range
 
 Protected constructor, can only be created via ParameterGroup
 
 */



#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "ofxMSAControlFreak/src/Parameter.h"
//#include "ofxMSAControlFreak/src/ParameterValueI.h"


namespace msa {
	namespace controlfreak {
        
        class Parameter;
        
        
		template <typename T>
		class ParameterValueT : public ParameterValueI {
		public:
            
            friend class Parameter;
            
            ParameterValueT(T v = T());
            
			// set and get value
            // operators for assigning and casting
            T operator=(const T & v) { set(v); }
            operator T() const { return *_pvalue; }
			
            
            //--------------------------------------------------------------
            // from ParameterValueI
            
            void setParameter(Parameter *p);
            
            ParameterValueT<T>& set(AnyValue v);
			AnyValue value() const;
			AnyValue oldValue() const;
            
            
            // whether the value changed this frame or not
            bool hasChanged(int dir=0);
            
            // clear the changed flag (if you want to programmatically change the value, but don't want to trigger anything else)
            void clearChanged();
            
            // set min/max range values
			ParameterValueT<T>& setRange(AnyValue vmin, AnyValue vmax) {}
			AnyValue getMin() const {}
			AnyValue getMax() const {}
            AnyValue getRangeLength() {}

            // set and get whether clamping to range is enabled
			ParameterValueT<T>& setClamp(bool b) {}
            bool& getClamp() {}
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            ParameterValueT<T>& setSnap(bool b) {}
            bool& getSnap() {}
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            ParameterValueT<T>& setIncrement(AnyValue inc) {}
            AnyValue getIncrement() const {}
            
            
            // increase or decrease by increment amount
            ParameterValueT<T>& inc(AnyValue amount) {}
            ParameterValueT<T>& dec(AnyValue amount) {}
            
            // set and get as 0...1 values normalized to min/max range
			ParameterValueT<T>& setNormalized(float norm) {}
			float getNormalized(bool bClamp = false) const {}
            
            // set and get mapped to a new range
            ParameterValueT<T>& setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) {}
            AnyValue getMappedTo(AnyValue newMin, AnyValue newMax, bool bClamp = false) const {}
            
            
            // set to a random value between min, max range
            ParameterValueT<T>& setRandom() {}
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            ParameterValueT<T>& trackVariable(void *pv);
            virtual void* getTrackedVariable();
            
            
        protected:
            
            virtual void update();
            
            // override these functions to implement clamping and snapping for any type
            virtual void clamp() {}
            virtual void snap() {}
            
            virtual void writeToXml(ofxXmlSettings &xml, bool bFullSchema);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFullSchema);
            
            
            // this actually changes the value
            // while set is used externally, that also does clamp and snap
            // this just sets the variable
            void _setValue(AnyValue v);
            
            
		private:
            Parameter   *_parameter;
            
            // pointer to externally stored variable. if set to NULL, points to internal member
            T   *_pvalue;
            
            // internally stored value;
			T   _value;
            T   _oldValue;

            bool    _hasChanged;
		};
        
        
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        template<typename T>
        ParameterValueT<T>::ParameterValueT(T v) {
            trackVariable(NULL);
            set(v);
        }
        
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::setParameter(Parameter *p) {
            _parameter = p;
        }
        
        //--------------------------------------------------------------
        template<typename T>
        ParameterValueT<T>& ParameterValueT<T>::set(AnyValue v) {
            _setValue(v);
            return *this;
		}
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::_setValue(AnyValue v) {
            *_pvalue = (T)v;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterValueT<T>::value() const {
			return *_pvalue;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterValueT<T>::oldValue() const {
			return _oldValue;
		}
        
        //--------------------------------------------------------------
        template<typename T>
        bool ParameterValueT<T>::hasChanged(int dir) {
//            if(dir == 0) {
                return _hasChanged;
//            } else if(dir > 0) {
//                return *_pvalue > _oldValue;
//            } else {
//                return *_pvalue < _oldValue;
//            }
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::clearChanged() {
            _oldValue = *_pvalue;
            _hasChanged = false;
        }
        
        
        //--------------------------------------------------------------
        template<typename T>
        ParameterValueT<T>& ParameterValueT<T>::trackVariable(void *pv) {
            //            ofLogVerbose() << "msa::controlfreak::ParameterValueT<T>::trackVariable: " <<  getPath() << " " << pv;
            _pvalue = pv ? (T*)pv : &_value;
            return *this;
        }
        
        
        //--------------------------------------------------------------
        template<typename T>
        void* ParameterValueT<T>::getTrackedVariable() {
            return _pvalue;
        }
 
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::update() {
            _hasChanged = (*_pvalue != _oldValue);
            if(_hasChanged) {
                _oldValue = *_pvalue;
            }
        }

        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::writeToXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::ParameterValueT<T>::writeToXml: " << _parameter->getPath();
            
            //            Parameter::writeToXml(xml, bFullSchema);  // IMPORTANT: always start with parents write to xml
            xml.addAttribute(_parameter->_xmlTag, "value", *_pvalue, _parameter->_xmlTagId);
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::readFromXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::ParameterValueT<T>::readFromXml: " << _parameter->getPath();
            //            Parameter::readFromXml(xml, bFullSchema);
            set(xml.getAttribute(_parameter->_xmlTag, "value", T(), _parameter->_xmlTagId));
        }
        
	}
}