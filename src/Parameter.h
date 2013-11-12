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

#include "ofxMSAControlFreak/src/ParameterValueI.h"
//#include "ofxMSAControlFreak/src/Controllers.h"
#include "ofxMSAControlFreak/src/Utils.h"

#include "ofxXmlSettings.h"

namespace msa {
	namespace controlfreak {
		
		class ParameterGroup;
        
		class Parameter : public ParameterValueI {
		public:

			friend class ParameterGroup;
            friend class Master;
            template<typename T>
            friend class ParameterNumberValueT;
            
			Parameter(string name, ParameterGroup *parent = NULL, ParameterValueI *pv = NULL);
			virtual ~Parameter();
            
            Parameter& setName(string s);
			string getName() const;
            
            Parameter& setTooltip(string s);
            string getTooltip() const;
            
			string getPath() const;        // return path (including parents)

            ParameterGroup* getParent() const;
            
			string getTypeName() const;
            
            
            ParameterValueI* getParamValue();
            
            

            //--------------------------------------------------------------
            // set and get value
            // operators for assigning and casting
            template<typename T> T operator=(const T & v) { set(v); }
			template<typename T> operator T() const { return (T)value(); }
			

            //--------------------------------------------------------------
            // from ParameterValueI
            
            virtual ParameterValueI& set(AnyValue v) { if(_paramValue) return _paramValue->set(v); }
			virtual AnyValue value() const { if(_paramValue) return _paramValue->value(); }
			virtual AnyValue oldValue() const { if(_paramValue) return _paramValue->oldValue(); }
            
            // whether the value changed this frame or not
            virtual bool hasChanged(int dir=0) { if(_paramValue) return _paramValue->hasChanged(dir); }

            // clear the changed flag (if you want to programmatically change the value, but don't want to trigger anything else)
            virtual void clearChanged() { if(_paramValue) _paramValue->clearChanged(); }

            // set min/max range values
			virtual ParameterValueI& setRange(AnyValue vmin, AnyValue vmax) { if(_paramValue) return _paramValue->setRange(vmin, vmax); }
			virtual AnyValue getMin() const { if(_paramValue) return _paramValue->getMin(); }
			virtual AnyValue getMax() const { if(_paramValue) return _paramValue->getMax(); }
			virtual AnyValue getRangeLength() const { if(_paramValue) return _paramValue->getRangeLength(); }

            // set and get whether clamping to range is enabled
			virtual ParameterValueI& setClamp(bool b) { if(_paramValue) return _paramValue->setClamp(b); }
            virtual bool& getClamp() { if(_paramValue) return _paramValue->getClamp(); }
            
            // set and get whether snapping is enabled.
            // if enabled, value is snapped to the closest increment (as set by setIncrement())
            virtual ParameterValueI& setSnap(bool b) { if(_paramValue) return _paramValue->setSnap(b); }
            virtual bool& getSnap() { if(_paramValue) return _paramValue->getSnap(); }
            
            // set and get increment amount, which snapping snaps to
            // if snapping is disabled, sliders still use this value when using keyboard up/down or inc/dec
            virtual ParameterValueI& setIncrement(AnyValue inc) { if(_paramValue) return _paramValue->setIncrement(inc); }
            virtual AnyValue getIncrement() const { if(_paramValue) return _paramValue->getIncrement(); }
            
            
            // increase or decrease by increment amount
            virtual ParameterValueI& inc(AnyValue amount) { if(_paramValue) return _paramValue->inc(amount); }
            virtual ParameterValueI& dec(AnyValue amount) { if(_paramValue) return _paramValue->dec(amount); }
            
            // set and get as 0...1 values normalized to min/max range
			virtual ParameterValueI& setNormalized(float norm) { if(_paramValue) return _paramValue->setNormalized(norm); }
			virtual float getNormalized(bool bClamp = false) const { if(_paramValue) return _paramValue->getNormalized(bClamp); }
            
            // set and get mapped to a new range
            virtual ParameterValueI& setMappedFrom(AnyValue v, AnyValue inputMin, AnyValue inputMax) { if(_paramValue) return _paramValue->setMappedFrom(v, inputMin, inputMax); }
            virtual AnyValue getMappedTo(AnyValue newMin, AnyValue newMax, bool bClamp = false) const  { if(_paramValue) return _paramValue->getMappedTo(newMin, newMax, bClamp); }
            
            
            // set to a random value between min, max range
            virtual ParameterValueI& setRandom() { if(_paramValue) return _paramValue->setRandom(); }
            
            
            // OPTIONAL
            // track variables and keep values in sync (send NULL to clear)
            virtual ParameterValueI& trackVariable(void *pv) { if(_paramValue) return _paramValue->trackVariable(pv); }
            virtual void* getTrackedVariable() { if(_paramValue) return _paramValue->getTrackedVariable(); }
            
            
            
            //--------------------------------------------------------------
            // Controller stuff
//            void addSender(ControllerI *controller);
//            void addReceiver(ControllerI *controller);
            
        protected:
//            Controllers controllers;
            
            virtual void update() { if(_paramValue) _paramValue->update(); }
            
            virtual void clamp() { if(_paramValue) _paramValue->clamp(); }
            virtual void snap() { if(_paramValue) _paramValue->snap(); }
            
            string              _xmlTag;
            int                 _xmlTagId;
            
            void setParent(ParameterGroup *parent);
            
            virtual void writeToXml(ofxXmlSettings &xml, bool bFullSchema);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFullSchema);
            
        private:
			string				_name;
            string              _tooltip;
			ParameterGroup		*_pparent;
            ParameterValueI*   _paramValue;
			
            
            
		};
		
	}
}