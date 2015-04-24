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
        
        class ParameterBool : public ParameterT<bool> {
        public:
            //--------------------------------------------------------------
            enum Mode {
                kToggle,    // toggle on/off
                kPush,      // on while active, off when released
                kBang       // on for only one frame
            };
            
            //--------------------------------------------------------------
            ParameterBool(string name, ParameterGroup *parent = NULL)
            : ParameterT<bool>(name, parent) { setRange(0, 1); setIncrement(1); setMode(kToggle); }
            
            template <typename T> T operator=(const T & v) { set(v); }
			template <typename T> operator T() const { return value(); }
            
            //--------------------------------------------------------------
            ParameterBool& setMode(Mode mode) {
                _mode = mode;
                return *this;
            }
            
            //--------------------------------------------------------------
            Mode getMode() {
                return _mode;
            }
            
            //--------------------------------------------------------------
            void toggle() {
                set(!value());
            }
            
        protected:
            Mode _mode;

        };
        
        
    }
}