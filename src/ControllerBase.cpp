//
//  ControllerBase.cpp
//  ofxMSAControlFreak example-tutorial
//
//  Created by Memo Akten on 02/02/2013.
//
//

#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
	namespace controlfreak {

        
        //--------------------------------------------------------------
        ControllerBase::ControllerBase(Parameter *param, bool bOnlyUpdateOnChange) : param(param), bOnlyUpdateOnChange(bOnlyUpdateOnChange) {
        }
        
        //            virtual ~ControllerBase() {}
        
        //--------------------------------------------------------------
        bool ControllerBase::shouldUpdate() {
            return param && (param->hasChanged() || !bOnlyUpdateOnChange);
        }
        

        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        ControllerManagerBase::~ControllerManagerBase() {
            for(int i=0; i<controllers.size(); i++) {
                delete controllers[i];
            }
        }
        
        
        //--------------------------------------------------------------
        void ControllerManagerBase::add(ControllerBase *controller) {
            controllers.push_back(controller);
        }
        

    }
}