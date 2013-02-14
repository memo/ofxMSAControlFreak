
#pragma once

#include "ofMain.h"
#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
	namespace controlfreak {

        //--------------------------------------------------------------
        // an individual Controller which controls a parameter (either a sender or receiver)
        class ControllerBase {
        public:
            Parameter	*param;
            bool        bOnlyUpdateOnChange;
            
            ControllerBase(Parameter *param, bool bOnlyUpdateOnChange);
            bool shouldUpdate();
        };
        
        
        //--------------------------------------------------------------
		// A base class for something which can control a bunch of parameters
        class ControllerManagerBase {
        public:
            virtual ~ControllerManagerBase();
            void add(ControllerBase *controller);

        protected:
            vector<ControllerBase*> controllers;

            
        };
		
	}
}