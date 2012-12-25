
// protected constructor, can only be created via Controller::xxxxx::createController


#pragma once

#include "ofxMSACore/src/MSACore.h"

namespace msa {
	namespace ControlFreak {
		
		class ParameterT;
		
		class Controller {
		public:
//			void setParam(Parameter *param);			
//			void checkValueHasChanged();
			
			virtual void updateController()	= 0;
			virtual string toString()	= 0;
			
		protected:
			ParameterT	*_param;
//			float		_oldValue;
			
			Controller() {}
		};
		
	}
}