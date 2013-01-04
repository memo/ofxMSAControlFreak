/*
 
 Template base class for any Parameter that can have a value (either simple or complex), with a range
 
 Protected constructor, can only be created via ParameterGroup
 
 */



#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "ofxMSAControlFreak/src/ParameterValueI.h"

#include "Poco/DynamicAny.h"

namespace msa {
	namespace ControlFreak {
        
        typedef Poco::DynamicAny AnyValue;
        
        class Parameter;
        
        class ParameterValue;
        typedef std::tr1::shared_ptr<ParameterValue> ParameterValuePtr;
		
		class ParameterValue : public ParameterValueI {
		public:
            
            friend class Parameter;
            
            template<typename T>
            ParameterValue(T t) {
                trackVariable(NULL);
                setClamp(false);
                setSnap(false);
            }
            
			// set and get value
            // operators for assigning and casting
            template<typename T> T operator=(const T & v) { setValue(v); }
			template<typename T> operator T() const { return value(); }
			

            //--------------------------------------------------------------
            // from ParameterValueI
            
            ParameterValue& setValue(AnyValue v);
			AnyValue& value() const;
            
            // whether the value changed this frame or not
            bool hasChanged();
            
            // set min/max range values
			ParameterValue& setRange(AnyValue vmin, AnyValue vmax);
			AnyValue getMin() const;
			AnyValue getMax() const;
            
            // set and get whether clamping to range is enabled
			ParameterValue& setClamp(bool b);
            bool getClamp() const;
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            ParameterValue& setSnap(bool b);
            bool getSnap() const;
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            ParameterValue& setIncrement(AnyValue inc);
            AnyValue getIncrement() const;
            
            
            // increase or decrease by increment amount
            ParameterValue& inc(AnyValue amount);
            ParameterValue& dec(AnyValue amount);
            
            // set and get as 0...1 values normalized to min/max range
			ParameterValue& setNormalized(float norm);
			float getNormalized() const;
            
            // set and get mapped to a new range
            ParameterValue& setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax);
            AnyValue getMappedTo(AnyValue newMin, AnyValue newMax) const;
            
            
            // set to a random value between min, max range
            ParameterValue& setRandom();
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            virtual ParameterValue& trackVariable(AnyValue *pv);
            

			
            
            
        protected:
            // override these functions to implement clamping and snapping for any type
            virtual void clamp();
            virtual void snap();
            
            
            // this actually changes the value
            // while setValue is used externally, that also does clamp and snap
            // this just sets the variable
            void _setValue(AnyValue v);
            
            // from Parameter:
            virtual void writeToXml(ofxXmlSettings &xml, bool bOnlyValues);
            virtual void readFromXml(ofxXmlSettings &xml, bool bOnlyValues);
            virtual void update();
            
		private:
 
            
            Parameter   *_parameter;
            
            // pointer to externally stored variable. if set to NULL, points to internal member
            AnyValue   *_pvalue;
            
            // internally stored value;
			AnyValue   _value;
            AnyValue   _min, _max, _inc;
            AnyValue   _oldValue;
            
			bool    _doClamp;
            bool    _doSnap;
//			vector<Controller*>		_controllers;
		};
        
        
	}
}