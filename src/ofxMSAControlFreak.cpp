//
//  ofxMSAControlFreak.cpp
//  ofxMSAControlFreak example
//
//  Created by Memo Akten on 27/01/2013.
//
//

#include "ofxMSAControlFreak.h"


namespace msa {
    namespace controlfreak {
        
        void update() {
            Master::instance().update();
        }
        
    }
}