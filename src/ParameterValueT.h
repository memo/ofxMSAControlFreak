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
	namespace ControlFreak {
        
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
            
            // whether the value changed this frame or not
            bool hasChanged();
            
            // set min/max range values
			ParameterValueT<T>& setRange(AnyValue vmin, AnyValue vmax);
			AnyValue getMin() const;
			AnyValue getMax() const;
            
            // set and get whether clamping to range is enabled
			ParameterValueT<T>& setClamp(bool b);
            bool& getClamp();
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            ParameterValueT<T>& setSnap(bool b);
            bool& getSnap();
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            ParameterValueT<T>& setIncrement(AnyValue inc);
            AnyValue getIncrement() const;
            
            
            // increase or decrease by increment amount
            ParameterValueT<T>& inc(AnyValue amount);
            ParameterValueT<T>& dec(AnyValue amount);
            
            // set and get as 0...1 values normalized to min/max range
			ParameterValueT<T>& setNormalized(float norm);
			float getNormalized() const;
            
            // set and get mapped to a new range
            ParameterValueT<T>& setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax);
            AnyValue getMappedTo(AnyValue newMin, AnyValue newMax) const;
            
            
            // set to a random value between min, max range
            ParameterValueT<T>& setRandom();
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            ParameterValueT<T>& trackVariable(void *pv);
            virtual void* getTrackedVariable();

            
            virtual void update();

        protected:
        
            // override these functions to implement clamping and snapping for any type
            virtual void clamp();
            virtual void snap();
            
            virtual void writeToXml(ofxXmlSettings &xml, bool bOnlyValues);
            virtual void readFromXml(ofxXmlSettings &xml, bool bOnlyValues);
            
            
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
//			vector<Controller*>		_controllers;
		};
        
        
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        template<typename T>
        ParameterValueT<T>::ParameterValueT(T v) {
            trackVariable(NULL);
            setIncrement(T(1));
            setClamp(false);
            setSnap(false);
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
            if(_doClamp) clamp();
            if(_doSnap) snap();
            
			//				checkValueHasChanged();
            //			updateControllers();
            return *this;
		}
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::_setValue(AnyValue v) {
            *_pvalue = v;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterValueT<T>::value() const {
			return *_pvalue;
		}
        
        
        //--------------------------------------------------------------
        template<typename T>
        bool ParameterValueT<T>::hasChanged() {
            // TODO
            bool ret = (*_pvalue != _oldValue);
            if(ret) _oldValue = *_pvalue;
            return ret;
        }
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterValueT<T>& ParameterValueT<T>::setRange(AnyValue vmin, AnyValue vmax) {
            _min = vmin;
            _max = vmax;
            
			set(*_pvalue);
			return *this;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterValueT<T>::getMin() const {
			return _min;
		}
		
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterValueT<T>::getMax() const {
			return _max;
		}
        
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterValueT<T>& ParameterValueT<T>::setClamp(bool b) {
			_doClamp = b;
			if(_doClamp) clamp();
            return *this;
		}
		
        //--------------------------------------------------------------
        template<typename T>
		bool& ParameterValueT<T>::getClamp() {
			return _doClamp;
		}
        
        //--------------------------------------------------------------
        template<typename T>
        ParameterValueT<T>& ParameterValueT<T>::setSnap(bool b) {
            _doSnap = b;
			if(_doSnap) snap();
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
        bool& ParameterValueT<T>::getSnap() {
            return _doSnap;
        }
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterValueT<T>& ParameterValueT<T>::setIncrement(AnyValue inc) {
            _inc = inc;
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterValueT<T>::getIncrement() const {
            return _inc;
        }
        
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterValueT<T>& ParameterValueT<T>::inc(AnyValue amount) {
            set(*_pvalue + _inc * amount);
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterValueT<T>& ParameterValueT<T>::dec(AnyValue amount) {
            set(*_pvalue - _inc * amount);
            return *this;
        }
		
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterValueT<T>& ParameterValueT<T>::setNormalized(float norm) {
			setMappedFrom(norm, 0, 1);
            return *this;
		}
		
        //--------------------------------------------------------------
        template<typename T>
        float ParameterValueT<T>::getNormalized() const {
			return getMappedTo(0, 1);
		}
		
        
        //--------------------------------------------------------------
        template<typename T>
		ParameterValueT<T>& ParameterValueT<T>::setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) {
			set(ofMap(v, inputMin, inputMax, _min, _max));
            //            set(  ((v - inputMin) / (inputMax - inputMin) * (_max - _min) + _min)  );
            return *this;
		}
		
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterValueT<T>::getMappedTo(AnyValue newMin, AnyValue newMax) const {
			return ofMap(*_pvalue, _min, _max, newMin, newMax);
            //            return ((*_pvalue - _min) / (_max - _min) * (newMax - newMin) + newMin);
		}
		
        
        
        //--------------------------------------------------------------
        template<typename T>
        ParameterValueT<T>& ParameterValueT<T>::setRandom() {
            set(ofRandom(_min, _max));
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
        ParameterValueT<T>& ParameterValueT<T>::trackVariable(void *pv) {
            //            ofLogVerbose() << "msa::ControlFreak::ParameterValueT<T>::trackVariable: " <<  getPath() << " " << pv;
            _pvalue = pv ? (T*)pv : &_value;
            return *this;
        }
        
        
        //--------------------------------------------------------------
        template<typename T>
        void* ParameterValueT<T>::getTrackedVariable() {
            return _pvalue;
        }
        
        //--------------------------------------------------------------
        //        //		ParameterValueT<T>& ParameterValueT<T>::addController(Controller *controller) {
        //            ofLogVerbose() << "msa::ControlFreak::ParameterValueT<T>::addController: " <<  getPath() << " " << controller;
        ////			controller->setParam(this);
        //			controller->updateController();
        //			_controllers.push_back(controller);
        //			return *this;
        //		}
        //
        //
        //        //--------------------------------------------------------------
        //        //		void ParameterValueT<T>::updateControllers() {
        //			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
        //		}
		
		//		void ParameterValueT<T>::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}
        
		
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::update() {
            if(_doClamp) clamp();
            if(_doSnap) snap();
            
            //            _oldValue = *_pvalue;
        }

        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::clamp() {
            _setValue( *_pvalue < _min ? _min : *_pvalue > _max ? _max : *_pvalue );
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::snap() {
            //            float inv = 1.0f / _inc;
            int ival = floor((*_pvalue - _min) / _inc);
            _setValue(_min + (ival * _inc) );
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::writeToXml(ofxXmlSettings &xml, bool bOnlyValues) {
			ofLogVerbose() << "msa::ControlFreak::ParameterValueT<T>::writeToXml: " << _parameter->getPath();

//            Parameter::writeToXml(xml, bOnlyValues);  // IMPORTANT: always start with parents write to xml
            xml.addAttribute(_parameter->_xmlTag, "value", *_pvalue, _parameter->_xmlTagId);
            if(!bOnlyValues) {
                xml.addAttribute(_parameter->_xmlTag, "min", _min, _parameter->_xmlTagId);
                xml.addAttribute(_parameter->_xmlTag, "max", _max, _parameter->_xmlTagId);
                xml.addAttribute(_parameter->_xmlTag, "doClamp", getClamp(), _parameter->_xmlTagId);
                xml.addAttribute(_parameter->_xmlTag, "inc", _inc, _parameter->_xmlTagId);
                xml.addAttribute(_parameter->_xmlTag, "doSnap", getSnap(), _parameter->_xmlTagId);
            }
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterValueT<T>::readFromXml(ofxXmlSettings &xml, bool bOnlyValues) {
			ofLogVerbose() << "msa::ControlFreak::ParameterValueT<T>::readFromXml: " << _parameter->getPath();
            //            Parameter::readFromXml(xml, bOnlyValues);
            set(xml.getAttribute(_parameter->_xmlTag, "value", T(), _parameter->_xmlTagId));
            if(!bOnlyValues) {
                setRange(xml.getAttribute(_parameter->_xmlTag, "min", _min, _parameter->_xmlTagId), 
                         xml.getAttribute(_parameter->_xmlTag, "max", _max, _parameter->_xmlTagId));
                setIncrement(xml.getAttribute(_parameter->_xmlTag, "inc", _inc, _parameter->_xmlTagId));
                setClamp(xml.getAttribute(_parameter->_xmlTag, "doClamp", getClamp(), _parameter->_xmlTagId));
                setSnap(xml.getAttribute(_parameter->_xmlTag, "doSnap", getSnap(), _parameter->_xmlTagId));
            }
        }
        
	}
}