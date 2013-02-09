//
//  ControllerBase.cpp
//  ofxMSAControlFreak example-tutorial
//
//  Created by Memo Akten on 02/02/2013.
//
//

#include "ControllerBase.h"


namespace msa {
	namespace controlfreak {


        //--------------------------------------------------------------
        ControllerBase::~ControllerBase() {
            for(int i=0; i<channels.size(); i++) {
                delete channels[i];
            }
        }
        
        
        //--------------------------------------------------------------
        void ControllerBase::add(Channel *channel) {
            channels.push_back(channel);
        }
        

    }
}