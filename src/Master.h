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

/*
 
 Internal Master Class which keeps track of and owns all parameters

 all members private
 
 */

#pragma once

#include "ofMain.h"
#include "ofxMSAOrderedPointerMap.h"

namespace msa {
    namespace controlfreak {
        
        class Parameter;
        
        class Master {
        private:
            friend class Parameter;
            friend class ParameterGroup;
            friend void update();
            
            Master();
            ~Master();
            
            static Master& instance();

            void add(Parameter* p);
            void erase(Parameter *p);
            void update(ofEventArgs &e);
            
            // is this dodgey? a map using the pointers address as key? so i can find the parameter quickly to erase and remove?
            msa::OrderedPointerMap<Parameter*, Parameter> _parameters;
            static Master* _instance;
            
        };
    }
}