/*
 *  MSAControlFreeParameter.cpp
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */


#include "ofxMSAControlFreak/src/Parameter.h"
#include "ofxMSAControlFreak/src/ParameterGroup.h"

namespace msa {
	namespace ControlFreak {

#define kGetValueOf(v)      (_typeIndex == Types::kFloat ? v.vf : v.vi)
#define kSetValueOf(v, a)   { if(_typeIndex == Types::kFloat) v.vf=(a); else v.vi=(a); }

        //--------------------------------------------------------------
		string Parameter::path() const {
			return _path;
		}
		
        //--------------------------------------------------------------
		string Parameter::name() const {
			return _name;
		}
		
        //--------------------------------------------------------------
		string Parameter::fullName() const {
			string s;
			for(int i=0; i<_controllers.size(); i++) s += "[" + _controllers[i]->toString() + "]";
			return s + " " + name();
		}
		
		
        //--------------------------------------------------------------
		Parameter& Parameter::setRange(int vmin, int vmax) {
			kSetValueOf(_min, vmin);
			kSetValueOf(_max, vmax);
			setValue(value());
			return *this;
		}
        
        //--------------------------------------------------------------
		Parameter& Parameter::setRange(float vmin, float vmax) {
			kSetValueOf(_min, vmin);
			kSetValueOf(_max, vmax);
			setValue(value());
			return *this;
		}
		
        //--------------------------------------------------------------
		float Parameter::min() const {
			return kGetValueOf(_min);
		}
		
        //--------------------------------------------------------------
		float Parameter::max() const {
			return kGetValueOf(_max);
		}
		
        //--------------------------------------------------------------
		float Parameter::value() const {
			return kGetValueOf(_value);
		}
		
        //--------------------------------------------------------------
		Types::Index Parameter::type() const {
			return _typeIndex;
		}
		
        //--------------------------------------------------------------
		string Parameter::typeName() const {
			return nameForIndex(_typeIndex);
		}
        
        
        //--------------------------------------------------------------
		Parameter& Parameter::setType(Types::Index type) {
			_typeIndex = type;
			switch(_typeIndex) {
				case Types::kToggle:
				case Types::kBang:
					setRange(0, 1);
					break;
                    
                case Types::kFloat:
                    setRange(0, 1);
                    break;
                    
                case Types::kInt:
                    setRange(0, 100);
                    break;
                    
                default:
                    setRange(0, 1000);
			}
            
            setValue(kGetValueOf(_value));
            return *this;
		}
		
        //--------------------------------------------------------------
		Parameter& Parameter::setType(string s) {
			setType(Types::indexForName(s));
            return *this;
		}
        
		
        //--------------------------------------------------------------
		Parameter& Parameter::setClamp(bool b) {
			_isClamped = b;
			if(_isClamped) setValue(value());	// clamp immediately
            return *this;
		}
		
        //--------------------------------------------------------------
		bool Parameter::isClamped() const {
			return _isClamped;
		}
		
		
        //--------------------------------------------------------------
		template<typename T> Parameter::operator T() const {
			return (T)value();
		}
		
        //--------------------------------------------------------------
		template<typename T> T Parameter::operator=(const T & v) {
			setValue(v);
		}
		
        //--------------------------------------------------------------
		Parameter& Parameter::setNormalized(float norm) {
			setValue(ofLerp(min(), max(), norm));
            return *this;
		}
		
        //--------------------------------------------------------------
		float Parameter::normalized() const {
			return ofNormalize(value(), min(), max());
		}
		
        //--------------------------------------------------------------
		Parameter& Parameter::setMappedFrom(float v, float imin, float imax) {
			setValue(ofMap(value(), imin, imax, min(), max()));
            return *this;
		}
		
        //--------------------------------------------------------------
		float Parameter::mappedTo(float newMin, float newMax) const {
			return ofMap(value(), min(), max(), newMin, newMax);
		}
		
        //--------------------------------------------------------------
		Parameter& Parameter::setValue(int v) {
            kSetValueOf(_value, _isClamped ? ofClamp(v, min(), max()) : v);
			//				checkValueHasChanged();
			updateControllers();
            return *this;
		}
        
        //--------------------------------------------------------------
		Parameter& Parameter::setValue(float v) {
            kSetValueOf(_value, _isClamped ? ofClamp(v, min(), max()) : v);
			//				checkValueHasChanged();
			updateControllers();
            return *this;
		}
        
        //--------------------------------------------------------------
        Parameter::Parameter(ParameterGroup *parent, string path, Types::Index typeIndex) : _parent(parent), _path(path) {
            ofLogVerbose() << "msa::ControlFreak::Parameter::Parameter " <<  _path.c_str();
            
            setType(typeIndex);
            setClamp(false);
            setValue(0);
            
            // set name
            if(parent) {
                size_t lastDividerPos = _path.rfind(parent->getPathDivider());
                _name = lastDividerPos == string::npos ? _path : _path.substr(lastDividerPos+1);
            } else {
                _name = _path;
            }
        }

		
        //--------------------------------------------------------------
		Parameter& Parameter::addController(Controller *controller) {
			controller->setParam(this);
			controller->updateController();
			_controllers.push_back(controller);
			return *this;
		}
		
		
        //--------------------------------------------------------------
		void Parameter::updateControllers() {
			for(int i=0; i<_controllers.size(); i++) _controllers[i]->updateController();
		}
		
		//		void Parameter::checkValueHasChanged() {
		//			for(int i=0; i<_controllers.size(); i++) _controllers[i]->checkValueHasChanged();
		//		}
		
        
        //--------------------------------------------------------------
        void Parameter::writeSchemaToXml(ofxXmlSettings &xml) {
			ofLogVerbose() << "msa::ControlFreak::Parameter::writeSchemaToXml " << _path.c_str();
        }
        
        //--------------------------------------------------------------
        void Parameter::readSchemaFromXml(ofxXmlSettings &xml) {
			ofLogVerbose() << "msa::ControlFreak::Parameter::readSchemaFromXml " << _path.c_str();
        }
 
        //--------------------------------------------------------------
        void Parameter::writeValueToXml(ofxXmlSettings &xml) {
			ofLogVerbose() << "msa::ControlFreak::Parameter::writeValueToXml " << _path.c_str();
        }
        
        //--------------------------------------------------------------
        void Parameter::readValueFromXml(ofxXmlSettings &xml) {
			ofLogVerbose() << "msa::ControlFreak::Parameter::readValueFromXml " << _path.c_str();
        }


	}
}