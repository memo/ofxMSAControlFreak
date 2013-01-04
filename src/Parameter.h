/*
 
 Individual parameter or group / container
 Base class for all Parameters
 
 Protected constructor, can only be created via ParameterGroup

 */


#pragma once

#include "ofxMSACore/src/MSACore.h"

#include "ofxMSAControlFreak/src/ParameterValue.h"
#include "ofxMSAControlFreak/src/Utils.h"

#include "ofxXmlSettings.h"

namespace msa {
	namespace ControlFreak {
		
		class ParameterGroup;
        
        class Parameter;
        typedef std::tr1::shared_ptr<Parameter> ParameterPtr;

//        class ParameterValue;
        
		class Parameter : public ParameterValueI {
		public:

			friend class ParameterGroup;
            friend class ParameterValue;
            
			Parameter(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kUnknown, ParameterValue *pv = NULL);
			virtual ~Parameter();
            
            Parameter& setName(string s);
			string getName() const;
            
            Parameter& setTooltip(string s);
            string getTooltip() const;
            
			string getPath() const;        // return path (including parents)

            ParameterGroup* getParent() const;
            
			Type::Index getType() const;
			string getTypeName() const;
            
            

            //--------------------------------------------------------------
            // set and get value
            // operators for assigning and casting
            template<typename T> T operator=(const T & v) { setValue(v); }
			template<typename T> operator T() const { return (T)value(); }
			

            //--------------------------------------------------------------
            // from ParameterValueI
            
            virtual ParameterValueI& setValue(AnyValue v) { if(_value) return _value->setValue(v); }
			virtual AnyValue& value() const { if(_value) return _value->value(); }
            
            // whether the value changed this frame or not
            virtual bool hasChanged() { if(_value) return _value->hasChanged(); }
            
            // set min/max range values
			virtual ParameterValueI& setRange(AnyValue vmin, AnyValue vmax) { if(_value) return _value->setRange(vmin, vmax); }
			virtual AnyValue getMin() const { if(_value) return _value->getMin(); }
			virtual AnyValue getMax() const { if(_value) return _value->getMax(); }
            
            // set and get whether clamping to range is enabled
			virtual ParameterValueI& setClamp(bool b) { if(_value) return _value->setClamp(b); }
            virtual bool getClamp() const { if(_value) return _value->getClamp(); }
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            virtual ParameterValueI& setSnap(bool b) { if(_value) return _value->setSnap(b); }
            virtual bool getSnap() const { if(_value) return _value->getSnap(); }
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            virtual ParameterValueI& setIncrement(AnyValue inc) { if(_value) return _value->setIncrement(inc); }
            virtual AnyValue getIncrement() const { if(_value) return _value->getIncrement(); }
            
            
            // increase or decrease by increment amount
            virtual ParameterValueI& inc(AnyValue amount) { if(_value) return _value->inc(amount); }
            virtual ParameterValueI& dec(AnyValue amount) { if(_value) return _value->dec(amount); }
            
            // set and get as 0...1 values normalized to min/max range
			virtual ParameterValueI& setNormalized(float norm) { if(_value) return _value->setNormalized(norm); }
			virtual float getNormalized() const { if(_value) return _value->getNormalized(); }
            
            // set and get mapped to a new range
            virtual ParameterValueI& setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) { if(_value) return _value->setMappedFrom(v, inputMin, inputMax); }
            virtual AnyValue getMappedTo(AnyValue newMin, AnyValue newMax) const  { if(_value) return _value->getMappedTo(newMin, newMax); }
            
            
            // set to a random value between min, max range
            virtual ParameterValueI& setRandom() { if(_value) return _value->setRandom(); }
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            virtual ParameterValueI& trackVariable(AnyValue *pv) { if(_value) return _value->trackVariable(pv); }
            
            
		protected:
            string              _xmlTag;
            int                 _xmlTagId;
            
            void setParent(ParameterGroup *parent);
            
            virtual void writeToXml(ofxXmlSettings &xml, bool bOnlyValues);
            virtual void readFromXml(ofxXmlSettings &xml, bool bOnlyValues);
            virtual void update() {}
            
        private:
			Type::Index			_typeIndex;
			string				_name;
            string              _tooltip;
			ParameterGroup		*_pparent;
            ParameterValuePtr   _value;
			
            
            
		};
		
	}
}