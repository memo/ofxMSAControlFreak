/*
 
 Internal Master Class which keeps track of and owns all parameters

 all members private
 
 */

#pragma once

#include "ofMain.h"
#include "ofxMSAOrderedPointerMap.h"

namespace msa {
    namespace ControlFreak {
        
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
            void update();
            
            // is this dodgey? a map using the pointers address as key? so i can find the parameter quickly to erase and remove?
            msa::OrderedPointerMap<Parameter*, Parameter> _parameters;
            static Master* _instance;
            
        };
    }
}