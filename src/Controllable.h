#pragma once

#include "ofxMSAControlFreak/src/ControllerI.h"
#include "ofxMSAOrderedPointerMap/src/ofxMSAOrderedPointerMap.h"

namespace msa {
    namespace ControlFreak {
        
        class Controllable {
        public:
            virtual ~Controllable() {}
            
            OrderedPointerMap<ControllerI> controllers;
            
            //--------------------------------------------------------------
            void addController(string name, ControllerI *controller) {
                controllers.push_back(name, controller);
            }
            
            //--------------------------------------------------------------
            virtual void update() {
                for(int i=0; i<controllers.size(); i++) controllers[i].update();
            }
        };
        
    }
}