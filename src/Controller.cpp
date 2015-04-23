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


#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
	namespace controlfreak {

        
        //--------------------------------------------------------------
        Controller::Controller(Parameter *param, bool bOnlyUpdateOnChange) : param(param), bOnlyUpdateOnChange(bOnlyUpdateOnChange) {
        }
        
        //            virtual ~Controller() {}
        
        //--------------------------------------------------------------
        bool Controller::shouldUpdate() {
            return param && (param->hasChanged() || !bOnlyUpdateOnChange);
        }
        

        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
//        ControllerManagerBase::~ControllerManagerBase() {
//            for(int i=0; i<controllers.size(); i++) {
//                delete controllers[i];
//            }
//        }
//        
//        
//        //--------------------------------------------------------------
//        void ControllerManagerBase::add(Controller *controller) {
//            controllers.push_back(controller);
//        }
//        

    }
}