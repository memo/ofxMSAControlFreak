/*
 *  MSACGParameterTypes.cpp
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */


#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
	namespace ControlFreak {
        
        
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