
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
			
			virtual void update() = 0;
            
            void setParam(Parameter *p) { _param = p; }
            string getName() const { return _name; }
			
		protected:
			Parameter	*_param;
            string _name;
			
			ControllerI() {}
		};
		
	}
}