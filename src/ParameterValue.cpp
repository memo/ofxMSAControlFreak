
#include "ofxMSAControlFreak/src/ControlFreak.h"
#include "ofxMSAControlFreak/src/ParameterValue.h"


namespace msa {
	namespace ControlFreak {
        
        //--------------------------------------------------------------
//        ParameterValue::ParameterValue(Parameter* parameter) {
//            this->_parameter = parameter;
//            trackVariable(NULL);
//            setClamp(false);
//            setSnap(false);
//        }
        
        
        //--------------------------------------------------------------
        ParameterValue& ParameterValue::setValue(AnyValue v) {
            _setValue(v);
            if(_doClamp) clamp();
            if(_doSnap) snap();
            
			//				checkValueHasChanged();
            //			updateControllers();
            return *this;
		}
        
        //--------------------------------------------------------------
        void ParameterValue::_setValue(AnyValue v) {
            *_pvalue = v;
		}
        
        //--------------------------------------------------------------
		AnyValue& ParameterValue::value() const {
			return *_pvalue;
		}
        
        
        //--------------------------------------------------------------
        bool ParameterValue::hasChanged() {
            //            bool ret = (value() != _oldValue);
            //            if(ret) _oldValue = value();
            return true;
        }
        
        //--------------------------------------------------------------
		ParameterValue& ParameterValue::setRange(AnyValue vmin, AnyValue vmax) {
            _min = vmin;
            _max = vmax;
            
			setValue(value());
			return *this;
		}
        
        //--------------------------------------------------------------
		AnyValue ParameterValue::getMin() const {
			return _min;
		}
		
        //--------------------------------------------------------------
		AnyValue ParameterValue::getMax() const {
			return _max;
		}
        
        
        //--------------------------------------------------------------
		ParameterValue& ParameterValue::setClamp(bool b) {
			_doClamp = b;
			if(_doClamp) clamp();
            return *this;
		}
		
        //--------------------------------------------------------------
		bool ParameterValue::getClamp() const {
			return _doClamp;
		}
        
        //--------------------------------------------------------------
        ParameterValue& ParameterValue::setSnap(bool b) {
            _doSnap = b;
			if(_doSnap) snap();
            return *this;
        }
        
        //--------------------------------------------------------------
        bool ParameterValue::getSnap() const {
            return _doSnap;
        }
        
        //--------------------------------------------------------------
		ParameterValue& ParameterValue::setIncrement(AnyValue inc) {
            _inc = inc;
            return *this;
        }
        
        //--------------------------------------------------------------
		AnyValue ParameterValue::getIncrement() const {
            return _inc ? _inc : AnyValue(1);
        }
        
        
        //--------------------------------------------------------------
		ParameterValue& ParameterValue::inc(AnyValue amount) {
            setValue(value() + getIncrement() * amount);
            return *this;
        }
        
        //--------------------------------------------------------------
		ParameterValue& ParameterValue::dec(AnyValue amount) {
            setValue(value() - getIncrement() * amount);
            return *this;
        }
		
        
        //--------------------------------------------------------------
		ParameterValue& ParameterValue::setNormalized(float norm) {
			setMappedFrom(norm, 0, 1);
            return *this;
		}
		
        //--------------------------------------------------------------
        float ParameterValue::getNormalized() const {
			return getMappedTo(0, 1);
		}
		
        
        //--------------------------------------------------------------
		ParameterValue& ParameterValue::setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) {
			setValue(ofMap(v, inputMin, inputMax, getMin(), getMax()));
            //            setValue(  ((v - inputMin) / (inputMax - inputMin) * (getMax() - getMin()) + getMin())  );
            return *this;
		}
		
        //--------------------------------------------------------------
		AnyValue ParameterValue::getMappedTo(AnyValue newMin, AnyValue newMax) const {
			return ofMap(value(), getMin(), getMax(), newMin, newMax);
            //            return ((value() - getMin()) / (getMax() - getMin()) * (newMax - newMin) + newMin);
		}
		
        
        
        //--------------------------------------------------------------
        ParameterValue& ParameterValue::setRandom() {
            setValue(ofRandom(getMin(), getMax()));
            return *this;
        }
        
        //--------------------------------------------------------------
        ParameterValue& ParameterValue::trackVariable(AnyValue *pv) {
            //            ofLogVerbose() << "msa::ControlFreak::ParameterValue::trackVariable: " <<  getPath() << " " << pv;
            _pvalue = pv ? pv : &_value;
            return *this;
        }
        
        
        //--------------------------------------------------------------
        //        //		ParameterValue& ParameterValue::addController(Controller *controller) {
        //            ofLogVerbose() << "msa::ControlFreak::ParameterValue::addController: " <<  getPath() << " " << controller;
        ////			controller->setParam(this);
        //			controller->updateController();
        //			_controllers.push_back(controller);
        //			return *this;
        //		}
        //
        //
        //        //--------------------------------------------------------------
        //        //		void ParameterValue::updateControllers() {
        //			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
        //		}
		
		//		void ParameterValue::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}
        
		
        //--------------------------------------------------------------
        void ParameterValue::update() {
            if(_doClamp) clamp();
            if(_doSnap) snap();
            
            //            _oldValue = value();
        }

        //--------------------------------------------------------------
        void ParameterValue::writeToXml(ofxXmlSettings &xml, bool bOnlyValues) {
			ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::writeToXml: " << _parameter->getPath();
            
            
//            Parameter::writeToXml(xml, bOnlyValues);  // IMPORTANT: always start with parents write to xml
//            xml.addAttribute(_parameter->_xmlTag, "value", value(), _parameter->_xmlTagId);
//            if(!bOnlyValues) {
//                xml.addAttribute(_parameter->_xmlTag, "min", getMin(), _parameter->_xmlTagId);
//                xml.addAttribute(_parameter->_xmlTag, "max", getMax(), _parameter->_xmlTagId);
//                xml.addAttribute(_parameter->_xmlTag, "doClamp", getClamp(), _parameter->_xmlTagId);
//                xml.addAttribute(_parameter->_xmlTag, "inc", getIncrement(), _parameter->_xmlTagId);
//                xml.addAttribute(_parameter->_xmlTag, "doSnap", getSnap(), _parameter->_xmlTagId);
//            }
        }
        
        //--------------------------------------------------------------
        void ParameterValue::readFromXml(ofxXmlSettings &xml, bool bOnlyValues) {
//            Parameter::readFromXml(xml, bOnlyValues);
//            setValue(xml.getAttribute(_parameter->_xmlTag, "value", AnyValue(), _parameter->_xmlTagId));
            
			ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::readFromXml: " << _parameter->getPath();
        }
        
        //--------------------------------------------------------------
        void ParameterValue::clamp() {
            _setValue( value() < getMin() ? getMin() : value() > getMax() ? getMax() : value() );
        }
        
        //--------------------------------------------------------------
        void ParameterValue::snap() {
            //            float inv = 1.0f / getIncrement();
//            int ival = floor((value() - getMin()) / getIncrement());
//            _setValue(getMin() + (AnyValue) (ival * getIncrement()) );
        }

	}
}