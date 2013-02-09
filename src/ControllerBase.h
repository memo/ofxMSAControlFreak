
#pragma once

#include "ofMain.h"

namespace msa {
	namespace controlfreak {
		
		class Parameter;
		
        class ControllerBase {
        public:
            class Channel {
            public:
                //--------------------------------------------------------------
                Channel(Parameter *param, bool bOnlyUpdateOnChange):_param(param), _bOnlyUpdateOnChange(bOnlyUpdateOnChange) {}
                virtual ~Channel() {}
                virtual void update() = 0;
            protected:
                Parameter	*_param;
                bool        _bOnlyUpdateOnChange;
            };
            
            
            virtual ~ControllerBase();
            void add(Channel *channel);

        protected:
            vector<Channel*> channels;

            
        };
		
	}
}