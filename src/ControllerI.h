
// protected constructor, can only be created via Controller::xxxxx::createController


#pragma once

namespace msa {
	namespace ControlFreak {
		
		class Parameter;
        class Controllable;
		
		class ControllerI {
		public:
            
            friend class Parameter;
            friend class Controllable;
            
            virtual ~ControllerI() {}
//			void setParam(Parameter *param);			
//			void checkValueHasChanged();
			
			virtual void update() = 0;
//			virtual string toString() = 0;
			
		protected:
			Parameter	*_param;
			
			ControllerI() {}
		};
		
	}
}