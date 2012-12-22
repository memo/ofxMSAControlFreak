
// protected constructor, can only be created via Controller::xxxxx::createController


#pragma once

#include "MSACore.h"

namespace msa {
	namespace ControlFreak {
		
		class Parameter;
		
		class Controller {
		public:
			void setParam(Parameter *param);			
//			void checkValueHasChanged();
			
			virtual void updateController()	= 0;
			virtual string toString()	= 0;
			
		protected:
			Parameter	*_param;
//			float		_oldValue;
			
			Controller() {}
		};
		
	}
}