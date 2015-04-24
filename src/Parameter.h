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
 
 Individual parameter or group / container
 Base class for all Parameters
 
 Protected constructor, can only be created via ParameterGroup

 */


#pragma once

#include "ofxMSACore/src/MSACore.h"

#include "ofxXmlSettings.h"

#include "Poco/DynamicAny.h"
#include "Poco/Any.h"

namespace msa {
	namespace controlfreak {
        
        typedef Poco::DynamicAny AnyValue;
        class Parameter;
		
		class ParameterGroup;
        
		class Parameter {
		public:

			friend class ParameterGroup;
            friend class Master;
            
			Parameter(string name, ParameterGroup *parent = NULL);
			virtual ~Parameter();
            
            Parameter& setName(string s);
			string getName() const;
            
            Parameter& setTooltip(string s);
            string getTooltip() const;
            
			string getPath() const;        // return path (including parents)

            ParameterGroup* getParent() const;
            
			string getTypeName() const;
            
            
            //--------------------------------------------------------------
            // set and get value
            // operators for assigning and casting
            template<typename T> T operator=(const T & v) { set(v); }
			template<typename T> operator T() const { return (T)value(); }
			

            //--------------------------------------------------------------
//            virtual void setParameter(Parameter *p) {}
            
            virtual Parameter& set(AnyValue v) {}
            virtual AnyValue value() const {}
            virtual AnyValue oldValue() const {}
            
            // whether the value changed this frame or not
            // 'dir' specifies direction of change to check for. 0: any direction, +ve: rising, -ve: dropping
            virtual bool hasChanged(int dir=0) {}
            
            // clear the changed flag (if you want to programmatically change the value, but don't want to trigger anything else)
            virtual void clearChanged() {}
            
            // set min/max range values
            virtual Parameter& setRange(AnyValue vmin, AnyValue vmax) {}
            virtual AnyValue getMin() const {}
            virtual AnyValue getMax() const {}
            virtual AnyValue getRangeLength() const {}
            
            // set and get whether clamping to range is enabled
            virtual Parameter& setClamp(bool b) {}
            virtual bool& getClamp() {}
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            virtual Parameter& setSnap(bool b) {}
            virtual bool& getSnap() {}
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            virtual Parameter& setIncrement(AnyValue inc) {}
            virtual AnyValue getIncrement() const {}
            
            
            // increase or decrease by increment amount
            virtual Parameter& inc(AnyValue amount) {}
            virtual Parameter& dec(AnyValue amount) {}
            
            // set and get as 0...1 values normalized to min/max range
            virtual Parameter& setNormalized(float norm) {}
            virtual float getNormalized(bool bClamp = false) const {}
            
            // set and get mapped to a new range
            virtual Parameter& setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) {}
            virtual AnyValue getMappedTo(AnyValue newMin, AnyValue newMax, bool bClamp = false) const {}
            
            
            // set to a random value between min, max range
            virtual Parameter& setRandom() {}
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            virtual Parameter& trackVariable(void *pv) {}
            virtual void* getTrackedVariable() {}

            
        protected:
            virtual void update() {}

            // override these functions to implement clamping and snapping for any type
            virtual void clamp() {}
            virtual void snap() {}
            
            virtual void writeToXml(ofxXmlSettings &xml, bool bFullSchema);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFullSchema);
            
            void setParent(ParameterGroup *parent);

            string              _xmlTag;
            int                 _xmlTagId;
            
        private:
			string				_name;
            string              _tooltip;
			ParameterGroup		*_pparent;
		};
		
	}
}