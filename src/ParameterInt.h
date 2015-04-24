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

#pragma once


#include "ofxMSAControlFreak/src/ParameterT.h"

namespace msa {
    namespace controlfreak {
        
        class ParameterInt : public ParameterT<int> {
        public:
            ParameterInt(string name, ParameterGroup *parent = NULL)
            : ParameterT<int>(name, parent) { setRange(0, 100); setIncrement(1); }
            
            template <typename T> T operator=(const T & v) { set(v); }
			template <typename T> operator T() const { return value(); }
        };
        
    }
}