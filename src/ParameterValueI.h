/*
 
Interface for any Parameter that has a value
 
 */


#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "Poco/DynamicAny.h"
//#include "Poco/Any.h"

namespace msa {
	namespace ControlFreak {
        
        typedef Poco::DynamicAny AnyValue;
        
        
        class ParameterValueI;
        typedef std::tr1::shared_ptr<ParameterValueI> ParameterValueIPtr;

        class Parameter;
        
		class ParameterValueI {
		public:
            
            virtual ~ParameterValueI() {};
            
            virtual void setParameter(Parameter *p) {}
            
            virtual ParameterValueI& setValue(AnyValue v) = 0;
			virtual AnyValue value() const = 0;
            
            // whether the value changed this frame or not
            virtual bool hasChanged() = 0;
            
            // set min/max range values
			virtual ParameterValueI& setRange(AnyValue vmin, AnyValue vmax) = 0;
			virtual AnyValue getMin() const = 0;
			virtual AnyValue getMax() const = 0;
            
            // set and get whether clamping to range is enabled
			virtual ParameterValueI& setClamp(bool b) = 0;
            virtual bool getClamp() const = 0;
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            virtual ParameterValueI& setSnap(bool b) = 0;
            virtual bool getSnap() const = 0;
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            virtual ParameterValueI& setIncrement(AnyValue inc) = 0;
            virtual AnyValue getIncrement() const = 0;
            
            
            // increase or decrease by increment amount
            virtual ParameterValueI& inc(AnyValue amount) = 0;
            virtual ParameterValueI& dec(AnyValue amount) = 0;
            
            // set and get as 0...1 values normalized to min/max range
			virtual ParameterValueI& setNormalized(float norm) = 0;
			virtual float getNormalized() const = 0;
            
            // set and get mapped to a new range
            virtual ParameterValueI& setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) = 0;
            virtual AnyValue getMappedTo(AnyValue newMin, AnyValue newMax) const = 0;
            
            
            // set to a random value between min, max range
            virtual ParameterValueI& setRandom() = 0;
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            virtual ParameterValueI& trackVariable(void *pv) = 0;

		};
        
        
	}
}