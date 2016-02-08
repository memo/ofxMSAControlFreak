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


#include "ofxMSAControlFreak.h"

namespace msa {
    namespace controlfreak {
        
        Master* Master::_instance = NULL;
        
        //--------------------------------------------------------------
        Master::Master() {
            cout << "Master";
            ofAddListener(ofEvents().update, this, &Master::update);
        }
        
        //--------------------------------------------------------------
        Master::~Master() {
            cout << "~Master";
            if(_instance) delete _instance;
        }
        
        //--------------------------------------------------------------
        void Master::add(Parameter *p) {
            _parameters.push_back(p, p);
        }
        
        //--------------------------------------------------------------
        void Master::erase(Parameter *p) {
            _parameters.erase(p);
        }

        //--------------------------------------------------------------
        void Master::update(ofEventArgs &e) {
            for(int i=0; i<_parameters.size(); i++) {
                Parameter &p = _parameters[i];
                p.update();
            }
        }

        //--------------------------------------------------------------
        Master& Master::instance() {
            if(_instance == NULL) _instance = new Master();
            return *_instance;
        }
        
        //--------------------------------------------------------------
        
        
    }
}
