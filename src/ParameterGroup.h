/*

 A parameter group, with API to handle creating more subgroups
 The main public facing class
 
*/

#pragma once

#include "ofxMSAControlFreak/src/ParameterContainer.h"

namespace msa {
    namespace ControlFreak {
        
        class ParameterInt;
        class ParameterFloat;
        class ParameterBool;
        class ParameterNamedIndex;
        
        class ParameterGroup : public ParameterContainer {
        public:
            ParameterGroup(ParameterContainer *parent = NULL, string name = "MSAControlFreak")
            : ParameterContainer(parent, name, Type::kGroup) {
                ofLogVerbose() << "msa::ControlFreak::ParameterGroup::ParameterGroup " <<  getPath().c_str();
                _groupStack.push(this); // start with this as current group
            }
            
            
            // groups can contain subgroups
			void startGroup(string name="");
			void endGroup();
            
			

			ParameterInt& createInt(string name);
			ParameterFloat& createFloat(string name);
			ParameterBool& createToggle(string name);
			ParameterBool& createBang(string name);
			ParameterNamedIndex& createNamedIndex(string name);
            //            Parameter& addVec2(string name);
            //            Parameter& addVec3(string name);
            //            Parameter& addVec4(string name);
            //            Parameter& addColor(string name);
			
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