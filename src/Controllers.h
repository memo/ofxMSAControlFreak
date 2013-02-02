#pragma once

#include "ofxMSAControlFreak/src/ControllerI.h"
#include "ofxMSAOrderedPointerMap/src/ofxMSAOrderedPointerMap.h"

namespace msa {
    namespace ControlFreak {
        
        class Controllers {
        public:
//            virtual Controllers() {}
            
            OrderedPointerMap<string, ControllerI> senders;
            OrderedPointerMap<string, ControllerI> receivers;
            
            //--------------------------------------------------------------
            void addSender(ControllerI *controller) {
                senders.push_back(controller->getName(), controller);
            }
            
            //--------------------------------------------------------------
            void addReceiver(ControllerI *controller) {
                receivers.push_back(controller->getName(), controller);
            }

            
            //--------------------------------------------------------------
            void update() {
                for(int i=0; i<senders.size(); i++) senders[i].update();
                for(int i=0; i<receivers.size(); i++) receivers[i].update();
            }
        };
        
    }
}