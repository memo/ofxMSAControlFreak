/*

 A parameter group, with API to handle creating more subgroups
 The main public facing class
 
*/

#pragma once

#include "ofxMSAControlFreak/src/ParameterContainer.h"

namespace msa {
    namespace ControlFreak {
        
//        class ParameterInt;
//        class ParameterFloat;
//        class ParameterBool;
        class ParameterNamedIndex;
        class ParameterVec3f;
        
        class ParameterGroup : public ParameterContainer {
        public:
            ParameterGroup(ParameterContainer *parent = NULL, string name = "MSAControlFreak")
            : ParameterContainer(parent, name, Type::kGroup) {
                ofLogVerbose() << "msa::ControlFreak::ParameterGroup::ParameterGroup " <<  getPath();
                _groupStack.push(this); // start with this as current group
            }
            
            // groups can contain subgroups
			void startGroup(string name="");
			void endGroup();
            
			ParameterInt& addInt(string name);
			ParameterFloat& addFloat(string name);
			ParameterBool& addToggle(string name);
			ParameterBool& addBang(string name);
			ParameterNamedIndex& addNamedIndex(string name);
            Parameter& addVec2(string name);
            ParameterVec3f& addVec3f(string name);
            Parameter& addVec4(string name);
            Parameter& addColoru8(string name);
            Parameter& addColorf32(string name);
			
            Parameter& addParameter(Parameter *param);
            
            // if name is omitted, last used name is used (by default same as group name)
			void setFilename(string filename = "");
			
			bool saveXml(bool bFull, string filename = "");
			bool loadXml(bool bFull, string filename = "");
            
            //			void checkValueHasChanged();
            //			void updateControllers(bool doChildGroups = true);		// update all controllers
            
        protected:
            string _filename;
            
            // keep track of stack of groups when creating with startGroup, endGroup
            stack<ParameterGroup*> _groupStack;

        };
        
    }
}