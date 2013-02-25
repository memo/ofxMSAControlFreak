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
        
        
        static char _pathDivider = '.';
        
        //--------------------------------------------------------------
        void setPathDivider(char divider) {
            _pathDivider = divider;
        }
        
        //--------------------------------------------------------------
        char getPathDivider() {
            return _pathDivider;
        }
        
    }
}