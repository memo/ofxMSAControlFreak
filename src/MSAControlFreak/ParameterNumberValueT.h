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

#include "MSAControlFreak/Parameter.h"
//#include "MSAControlFreak/ParameterValueI.h"


namespace msa {
	namespace controlfreak {
        
        class Parameter;
        
        
		template <typename T>
		class ParameterNumberValueT : public ParameterValueI {
		public:
            
            friend class Parameter;
            
            ParameterNumberValueT(T v = T());
            
			// set and get value
            // operators for assigning and casting
            T operator=(const T & v) { set(v); }
            operator T() const { return *_pvalue; }
			

            //--------------------------------------------------------------
            // from ParameterValueI
            
            void setParameter(Parameter *p);
            
            ParameterNumberValueT<T>& set(AnyValue v);
			AnyValue value() const;
			AnyValue oldValue() const;
            
            
            // whether the value changed this frame or not
            bool hasChanged(int dir=0);

            // clear the changed flag (if you want to programmatically change the value, but don't want to trigger anything else)
            void clearChanged();
            
            // set min/max range values
			ParameterNumberValueT<T>& setRange(AnyValue vmin, AnyValue vmax);
			AnyValue getMin() const;
			AnyValue getMax() const;
            AnyValue getRangeLength() const;

            
            // set and get whether clamping to range is enabled
			ParameterNumberValueT<T>& setClamp(bool b);
            bool& getClamp();
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            ParameterNumberValueT<T>& setSnap(bool b);
            bool& getSnap();
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            ParameterNumberValueT<T>& setIncrement(AnyValue inc);
            AnyValue getIncrement() const;
            
            
            // increase or decrease by increment amount
            ParameterNumberValueT<T>& inc(AnyValue amount);
            ParameterNumberValueT<T>& dec(AnyValue amount);
            
            // set and get as 0...1 values normalized to min/max range
			ParameterNumberValueT<T>& setNormalized(float norm);
			float getNormalized(bool bClamp = false) const;
            
            // set and get mapped to a new range
            ParameterNumberValueT<T>& setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax);
            AnyValue getMappedTo(AnyValue newMin, AnyValue newMax, bool bClamp = false) const;
            
            
            // set to a random value between min, max range
            ParameterNumberValueT<T>& setRandom();
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            ParameterNumberValueT<T>& trackVariable(void *pv);
            virtual void* getTrackedVariable();

            
            virtual void update();

        protected:
        
            // override these functions to implement clamping and snapping for any type
            virtual void clamp();
            virtual void snap();
            
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
            T   _min, _max, _inc;
            T   _oldValue;
            
			bool    _doClamp;
            bool    _doSnap;
            bool    _hasChanged;
		};
        
        
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        template<typename T>
        ParameterNumberValueT<T>::ParameterNumberValueT(T v) {
            trackVariable(NULL);
            setIncrement(T(1));
            setClamp(false);
            setSnap(false);
            set(v);
        }
        
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterNumberValueT<T>::setParameter(Parameter *p) {
            _parameter = p;
        }

        //--------------------------------------------------------------
        template<typename T>
        ParameterNumberValueT<T>& ParameterNumberValueT<T>::set(AnyValue v) {
            _setValue(v);
            if(_doClamp) clamp();
            if(_doSnap) snap();
            
			//				checkValueHasChanged();
            //			updateControllers();
            return *this;
		}
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterNumberValueT<T>::_setValue(AnyValue v) {
            *_pvalue = v;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterNumberValueT<T>::value() const {
			return *_pvalue;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterNumberValueT<T>::oldValue() const {
			return _oldValue;
		}
        
        //--------------------------------------------------------------
        template<typename T>
        bool ParameterNumberValueT<T>::hasChanged(int dir) {
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
        void ParameterNumberValueT<T>::clearChanged() {
            _oldValue = *_pvalue;
            _hasChanged = false;
        }

        
        //--------------------------------------------------------------
        template<typename T>
		ParameterNumberValueT<T>& ParameterNumberValueT<T>::setRange(AnyValue vmin, AnyValue vmax) {
            _min = vmin;
            _max = vmax;
            
			set(*_pvalue);
			return *this;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterNumberValueT<T>::getMin() const {
			return _min;
		}
		
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterNumberValueT<T>::getMax() const {
			return _max;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterNumberValueT<T>::getRangeLength() const {
			return _max - _min;
		}

        //--------------------------------------------------------------
        template<typename T>
		ParameterNumberValueT<T>& ParameterNumberValueT<T>::setClamp(bool b) {
			_doClamp = b;
			if(_doClamp) clamp();
            return *this;
		}
		
        //--------------------------------------------------------------
        template<typename T>
		bool& ParameterNumberValueT<T>::getClamp() {
			return _doClamp;
		}
        
        //--------------------------------------------------------------
        template<typename T>
        ParameterNumberValueT<T>& ParameterNumberValueT<T>::setSnap(bool b) {
            _doSnap = b;
			if(_doSnap) snap();
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
        bool& ParameterNumberValueT<T>::getSnap() {
            return _doSnap;
        }
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterNumberValueT<T>& ParameterNumberValueT<T>::setIncrement(AnyValue inc) {
            _inc = inc;
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterNumberValueT<T>::getIncrement() const {
            return _inc;
        }
        
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterNumberValueT<T>& ParameterNumberValueT<T>::inc(AnyValue amount) {
            set(*_pvalue + _inc * amount);
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterNumberValueT<T>& ParameterNumberValueT<T>::dec(AnyValue amount) {
            set(*_pvalue - _inc * amount);
            return *this;
        }
		
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterNumberValueT<T>& ParameterNumberValueT<T>::setNormalized(float norm) {
			setMappedFrom(norm, 0, 1);
            return *this;
		}
		
        //--------------------------------------------------------------
        template<typename T>
        float ParameterNumberValueT<T>::getNormalized(bool bClamp) const {
			return getMappedTo(0, 1, bClamp);
		}
		
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterNumberValueT<T>& ParameterNumberValueT<T>::setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) {
			set(ofMap(v, inputMin, inputMax, _min, _max));
            //            set(  ((v - inputMin) / (inputMax - inputMin) * (_max - _min) + _min)  );
            return *this;
		}
		
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterNumberValueT<T>::getMappedTo(AnyValue newMin, AnyValue newMax, bool bClamp) const {
			return ofMap(*_pvalue, _min, _max, newMin, newMax, bClamp);
            //            return ((*_pvalue - _min) / (_max - _min) * (newMax - newMin) + newMin);
		}
		
        
        
        //--------------------------------------------------------------
        template<typename T>
        ParameterNumberValueT<T>& ParameterNumberValueT<T>::setRandom() {
            set(ofRandom(_min, _max));
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
        ParameterNumberValueT<T>& ParameterNumberValueT<T>::trackVariable(void *pv) {
            //            ofLogVerbose() << "msa::controlfreak::ParameterNumberValueT<T>::trackVariable: " <<  getPath() << " " << pv;
            _pvalue = pv ? (T*)pv : &_value;
            return *this;
        }
        
        
        //--------------------------------------------------------------
        template<typename T>
        void* ParameterNumberValueT<T>::getTrackedVariable() {
            return _pvalue;
        }
        
        //--------------------------------------------------------------
        //        //		ParameterNumberValueT<T>& ParameterNumberValueT<T>::addler(Controller *controller) {
        //            ofLogVerbose() << "msa::controlfreak::ParameterNumberValueT<T>::addler: " <<  getPath() << " " << controller;
        ////			controller->setParam(this);
        //			controller->updateController();
        //			_controllers.push_back(controller);
        //			return *this;
        //		}
        //
        //
        //        //--------------------------------------------------------------
        //        //		void ParameterNumberValueT<T>::updateControllers() {
        //			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
        //		}
		
		//		void ParameterNumberValueT<T>::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}
        
		
        //--------------------------------------------------------------
        template<typename T>
        void ParameterNumberValueT<T>::update() {
            if(_doClamp) clamp();
            if(_doSnap) snap();
            _hasChanged = (*_pvalue != _oldValue);
            if(_hasChanged) {
                _oldValue = *_pvalue;
            }
        }

        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterNumberValueT<T>::clamp() {
            _setValue( *_pvalue < _min ? _min : *_pvalue > _max ? _max : *_pvalue );
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterNumberValueT<T>::snap() {
            //            float inv = 1.0f / _inc;
            int ival = round((*_pvalue - _min) / _inc);
            _setValue(_min + (ival * _inc) );
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterNumberValueT<T>::writeToXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::ParameterNumberValueT<T>::writeToXml: " << _parameter->getPath();

//            Parameter::writeToXml(xml, bFullSchema);  // IMPORTANT: always start with parents write to xml
            xml.addAttribute(_parameter->_xmlTag, "value", *_pvalue, _parameter->_xmlTagId);
            if(bFullSchema) {
                xml.addAttribute(_parameter->_xmlTag, "min", _min, _parameter->_xmlTagId);
                xml.addAttribute(_parameter->_xmlTag, "max", _max, _parameter->_xmlTagId);
                xml.addAttribute(_parameter->_xmlTag, "doClamp", getClamp(), _parameter->_xmlTagId);
                xml.addAttribute(_parameter->_xmlTag, "inc", _inc, _parameter->_xmlTagId);
                xml.addAttribute(_parameter->_xmlTag, "doSnap", getSnap(), _parameter->_xmlTagId);
            }
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterNumberValueT<T>::readFromXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::ParameterNumberValueT<T>::readFromXml: " << _parameter->getPath();
            //            Parameter::readFromXml(xml, bFullSchema);
            set(xml.getAttribute(_parameter->_xmlTag, "value", T(), _parameter->_xmlTagId));
            if(bFullSchema) {
                setRange(xml.getAttribute(_parameter->_xmlTag, "min", _min, _parameter->_xmlTagId), 
                         xml.getAttribute(_parameter->_xmlTag, "max", _max, _parameter->_xmlTagId));
                setIncrement(xml.getAttribute(_parameter->_xmlTag, "inc", _inc, _parameter->_xmlTagId));
                setClamp(xml.getAttribute(_parameter->_xmlTag, "doClamp", getClamp(), _parameter->_xmlTagId));
                setSnap(xml.getAttribute(_parameter->_xmlTag, "doSnap", getSnap(), _parameter->_xmlTagId));
            }
        }
        
	}
}
