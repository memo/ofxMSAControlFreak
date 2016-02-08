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
 
Interface for any Parameter that has a value
 
 */


#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "Poco/DynamicAny.h"
#include "Poco/Any.h"

namespace msa {
	namespace controlfreak {
        
        typedef Poco::DynamicAny AnyValue;
        class Parameter;

        
		class ParameterValueI {
		public:
            
            friend class Parameter;
            
            virtual ~ParameterValueI() {};
            
            virtual void setParameter(Parameter *p) {}
            
            virtual ParameterValueI& set(AnyValue v) = 0;
			virtual AnyValue value() const = 0;
			virtual AnyValue oldValue() const = 0;
            
            // whether the value changed this frame or not
            // 'dir' specifies direction of change to check for. 0: any direction, +ve: rising, -ve: dropping
            virtual bool hasChanged(int dir=0) = 0;
            
            // clear the changed flag (if you want to programmatically change the value, but don't want to trigger anything else)
            virtual void clearChanged() = 0;
            
            // set min/max range values
			virtual ParameterValueI& setRange(AnyValue vmin, AnyValue vmax) = 0;
			virtual AnyValue getMin() const = 0;
			virtual AnyValue getMax() const = 0;
            virtual AnyValue getRangeLength() const = 0;
            
            // set and get whether clamping to range is enabled
			virtual ParameterValueI& setClamp(bool b) = 0;
            virtual bool& getClamp() = 0;
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            virtual ParameterValueI& setSnap(bool b) = 0;
            virtual bool& getSnap() = 0;
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            virtual ParameterValueI& setIncrement(AnyValue inc) = 0;
            virtual AnyValue getIncrement() const = 0;
            
            
            // increase or decrease by increment amount
            virtual ParameterValueI& inc(AnyValue amount) = 0;
            virtual ParameterValueI& dec(AnyValue amount) = 0;
            
            // set and get as 0...1 values normalized to min/max range
			virtual ParameterValueI& setNormalized(float norm) = 0;
			virtual float getNormalized(bool bClamp = false) const = 0;
            
            // set and get mapped to a new range
            virtual ParameterValueI& setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) = 0;
            virtual AnyValue getMappedTo(AnyValue newMin, AnyValue newMax, bool bClamp = false) const = 0;
            
            
            // set to a random value between min, max range
            virtual ParameterValueI& setRandom() = 0;
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            virtual ParameterValueI& trackVariable(void *pv) = 0;
            virtual void* getTrackedVariable() = 0;
            
        protected:
            virtual void update() = 0;
            
            virtual void clamp() = 0;
            virtual void snap() = 0;
            
            virtual void writeToXml(ofxXmlSettings &xml, bool bFullSchema) = 0;
            virtual void readFromXml(ofxXmlSettings &xml, bool bFullSchema) = 0;
		};
        
        
	}
}