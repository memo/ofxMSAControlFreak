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

        class ParameterFloat : public ParameterT<float>  {
        public:
            ParameterFloat(string name, ParameterGroup *parent = NULL)
            : ParameterT<float>(name, parent) { setRange(0.0f, 1.0f); setIncrement(0.01f); }

            template <typename T> T operator=(const T & v) { set(v); }
			template <typename T> operator T() const { return value(); }
        };
        
    }
}