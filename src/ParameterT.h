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
		class ParameterT : public Parameter {
		public:
            
            ParameterT(string name, ParameterGroup *parent = NULL, T v = T());
            
			// set and get value
            // operators for assigning and casting
            T operator=(const T & v) { set(v); }
            operator T() const { return *_pvalue; }
			

            //--------------------------------------------------------------
            // from Parameter
            
//            void setParameter(Parameter *p) override;
            
            Parameter& set(AnyValue v) override;
			AnyValue value() const override;
			AnyValue oldValue() const override;
            
            
            // whether the value changed this frame or not
            // 'dir' specifies direction of change to check for. 0: any direction, +ve: rising, -ve: dropping
            bool hasChanged(int dir=0) override;

            // clear the changed flag (if you want to programmatically change the value, but don't want to trigger anything else)
            void clearChanged() override;
            
            // set min/max range values
			Parameter& setRange(AnyValue vmin, AnyValue vmax) override;
			AnyValue getMin() const override;
			AnyValue getMax() const override;
            AnyValue getRangeLength() const override;
            
            // set and get whether clamping to range is enabled
			Parameter& setClamp(bool b) override;
            bool& getClamp() override;
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            Parameter& setSnap(bool b) override;
            bool& getSnap() override;
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            Parameter& setIncrement(AnyValue inc) override;
            AnyValue getIncrement() const override;
            
            
            // increase or decrease by increment amount
            Parameter& inc(AnyValue amount) override;
            Parameter& dec(AnyValue amount) override;
            
            // set and get as 0...1 values normalized to min/max range
			Parameter& setNormalized(float norm) override;
			float getNormalized(bool bClamp = false) const override;
            
            // set and get mapped to a new range
            Parameter& setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) override;
            AnyValue getMappedTo(AnyValue newMin, AnyValue newMax, bool bClamp = false) const override;
            
            
            // set to a random value between min, max range
            Parameter& setRandom() override;
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            Parameter& trackVariable(void *pv) override;
            void* getTrackedVariable() override;

            
        protected:
        
            void update() override;

            // override these functions to implement clamping and snapping for any type
            void clamp() override;
            void snap() override;
            
            void writeToXml(ofxXmlSettings &xml, bool bFullSchema) override;
            void readFromXml(ofxXmlSettings &xml, bool bFullSchema) override;
            
            
            // this actually changes the value
            // while set is used externally, that also does clamp and snap
            // this just sets the variable
            void _setValue(AnyValue v);
            

		private:
//            Parameter   *_parameter;
            
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
        ParameterT<T>::ParameterT(string name, ParameterGroup *parent, T v):
        Parameter(name, parent) {
            trackVariable(NULL);
            setIncrement(T(1));
            setClamp(true);
            setSnap(false);
            set(v);
        }
        
        
        //--------------------------------------------------------------
//        template<typename T>
//        void ParameterT<T>::setParameter(Parameter *p) {
//            _parameter = p;
//        }

        //--------------------------------------------------------------
        template<typename T>
        Parameter& ParameterT<T>::set(AnyValue v) {
            _setValue(v);
            if(_doClamp) clamp();
            if(_doSnap) snap();
            
			//				checkValueHasChanged();
            //			updateControllers();
            return *this;
		}
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterT<T>::_setValue(AnyValue v) {
            *_pvalue = v;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterT<T>::value() const {
			return *_pvalue;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterT<T>::oldValue() const {
			return _oldValue;
		}
        
        //--------------------------------------------------------------
        template<typename T>
        bool ParameterT<T>::hasChanged(int dir) {
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
        void ParameterT<T>::clearChanged() {
            _oldValue = *_pvalue;
            _hasChanged = false;
        }

        
        //--------------------------------------------------------------
        template<typename T>
		Parameter& ParameterT<T>::setRange(AnyValue vmin, AnyValue vmax) {
            _min = vmin;
            _max = vmax;
            
			set(*_pvalue);
			return *this;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterT<T>::getMin() const {
			return _min;
		}
		
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterT<T>::getMax() const {
			return _max;
		}
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterT<T>::getRangeLength() const {
			return _max - _min;
		}

        //--------------------------------------------------------------
        template<typename T>
		Parameter& ParameterT<T>::setClamp(bool b) {
			_doClamp = b;
			if(_doClamp) clamp();
            return *this;
		}
		
        //--------------------------------------------------------------
        template<typename T>
		bool& ParameterT<T>::getClamp() {
			return _doClamp;
		}
        
        //--------------------------------------------------------------
        template<typename T>
        Parameter& ParameterT<T>::setSnap(bool b) {
            _doSnap = b;
			if(_doSnap) snap();
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
        bool& ParameterT<T>::getSnap() {
            return _doSnap;
        }
        
        //--------------------------------------------------------------
        template<typename T>
		Parameter& ParameterT<T>::setIncrement(AnyValue inc) {
            _inc = inc;
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterT<T>::getIncrement() const {
            return _inc;
        }
        
        
        //--------------------------------------------------------------
        template<typename T>
		Parameter& ParameterT<T>::inc(AnyValue amount) {
            set(*_pvalue + _inc * amount);
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
		Parameter& ParameterT<T>::dec(AnyValue amount) {
            set(*_pvalue - _inc * amount);
            return *this;
        }
		
        
        //--------------------------------------------------------------
        template<typename T>
		Parameter& ParameterT<T>::setNormalized(float norm) {
			setMappedFrom(norm, 0, 1);
            return *this;
		}
		
        //--------------------------------------------------------------
        template<typename T>
        float ParameterT<T>::getNormalized(bool bClamp) const {
			return getMappedTo(0, 1, bClamp);
		}
		
        
        //--------------------------------------------------------------
        template<typename T>
		Parameter& ParameterT<T>::setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) {
			set(ofMap(v, inputMin, inputMax, _min, _max));
            //            set(  ((v - inputMin) / (inputMax - inputMin) * (_max - _min) + _min)  );
            return *this;
		}
		
        //--------------------------------------------------------------
        template<typename T>
		AnyValue ParameterT<T>::getMappedTo(AnyValue newMin, AnyValue newMax, bool bClamp) const {
			return ofMap(*_pvalue, _min, _max, newMin, newMax, bClamp);
            //            return ((*_pvalue - _min) / (_max - _min) * (newMax - newMin) + newMin);
		}
		
        
        
        //--------------------------------------------------------------
        template<typename T>
        Parameter& ParameterT<T>::setRandom() {
            set(ofRandom(_min, _max));
            return *this;
        }
        
        //--------------------------------------------------------------
        template<typename T>
        Parameter& ParameterT<T>::trackVariable(void *pv) {
            //            ofLogVerbose() << "msa::controlfreak::ParameterT<T>::trackVariable: " <<  getPath() << " " << pv;
            _pvalue = pv ? (T*)pv : &_value;
            return *this;
        }
        
        
        //--------------------------------------------------------------
        template<typename T>
        void* ParameterT<T>::getTrackedVariable() {
            return _pvalue;
        }
        
        //--------------------------------------------------------------
        //        //		Parameter& ParameterT<T>::addler(Controller *controller) {
        //            ofLogVerbose() << "msa::controlfreak::ParameterT<T>::addler: " <<  getPath() << " " << controller;
        ////			controller->setParam(this);
        //			controller->updateController();
        //			_controllers.push_back(controller);
        //			return *this;
        //		}
        //
        //
        //        //--------------------------------------------------------------
        //        //		void ParameterT<T>::updateControllers() {
        //			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
        //		}
		
		//		void ParameterT<T>::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}
        
		
        //--------------------------------------------------------------
        template<typename T>
        void ParameterT<T>::update() {
            if(_doClamp) clamp();
            if(_doSnap) snap();
            _hasChanged = (*_pvalue != _oldValue);
            if(_hasChanged) {
                _oldValue = *_pvalue;
            }
        }

        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterT<T>::clamp() {
            _setValue( *_pvalue < _min ? _min : *_pvalue > _max ? _max : *_pvalue );
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterT<T>::snap() {
            //            float inv = 1.0f / _inc;
            int ival = round((*_pvalue - _min) / _inc);
            _setValue(_min + (ival * _inc) );
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterT<T>::writeToXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::ParameterT<T>::writeToXml: " << getPath();

            Parameter::writeToXml(xml, bFullSchema);  // IMPORTANT: always start with parents write to xml
            xml.addAttribute(_xmlTag, "value", *_pvalue, _xmlTagId);
            if(bFullSchema) {
                xml.addAttribute(_xmlTag, "min", _min, _xmlTagId);
                xml.addAttribute(_xmlTag, "max", _max, _xmlTagId);
                xml.addAttribute(_xmlTag, "doClamp", getClamp(), _xmlTagId);
                xml.addAttribute(_xmlTag, "inc", _inc, _xmlTagId);
                xml.addAttribute(_xmlTag, "doSnap", getSnap(), _xmlTagId);
            }
        }
        
        //--------------------------------------------------------------
        template<typename T>
        void ParameterT<T>::readFromXml(ofxXmlSettings &xml, bool bFullSchema) {
			ofLogVerbose() << "msa::controlfreak::ParameterT<T>::readFromXml: " << getPath();
            Parameter::readFromXml(xml, bFullSchema);
            set(xml.getAttribute(_xmlTag, "value", T(), _xmlTagId));
            if(bFullSchema) {
                setRange(xml.getAttribute(_xmlTag, "min", _min, _xmlTagId), 
                         xml.getAttribute(_xmlTag, "max", _max, _xmlTagId));
                setIncrement(xml.getAttribute(_xmlTag, "inc", _inc, _xmlTagId));
                setClamp(xml.getAttribute(_xmlTag, "doClamp", getClamp(), _xmlTagId));
                setSnap(xml.getAttribute(_xmlTag, "doSnap", getSnap(), _xmlTagId));
            }
        }
        
	}
}