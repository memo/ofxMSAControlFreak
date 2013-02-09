//
//  Master.cpp
//  ofxMSAControlFreak example1
//
//  Created by Memo Akten on 24/01/2013.
//
//

#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
    namespace controlfreak {
        
        Master* Master::_instance = NULL;
        
        //--------------------------------------------------------------
        Master::Master() {
            cout << "Master";
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
        void Master::update() {
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
