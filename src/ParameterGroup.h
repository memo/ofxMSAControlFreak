/*
 
 A parameter group, contains other parameters, including other groups (can go infinitely deep)
 with API to handle creating more subgroups
 The main public facing class of ofxMSAControlFreak
 
 */

#pragma once

#include "ofxMSAControlFreak/src/Parameter.h"

namespace msa {
    namespace ControlFreak {
        
        class ParameterInt;
        class ParameterFloat;
        class ParameterBool;
        class ParameterNamedIndex;
        class ParameterVec3f;

//        class ParameterValueT;
        
        class ParameterGroup : public Parameter {
        public:
            ParameterGroup(ParameterGroup *parent = NULL, string name = "MSAControlFreak", Type::Index typeIndex = Type::kGroup);
            ~ParameterGroup();
            
            
            // if name is omitted, last used name is used (by default same as group name)
			void setFilename(string filename = "");
			
            // save and load all parameters to an xml file
			bool saveXml(bool bFull, string filename = "");
			bool loadXml(bool bFull, string filename = "");
            
            
            // write or read all parameters to an xml variable
            void writeToXml(ofxXmlSettings &xml, bool bFull);
            void readFromXml(ofxXmlSettings &xml, bool bFull);
            
            // call this every frame to make sure any external controllers (e.g. midi, osc etc.) stay in sync
            void update();
            
            
            
            //---- Adding parameters -----------------------
            
            // creates and adds a parameter
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
            
            // create a group. groups can be nested in other groups (infinitely deep)
			void startGroup(string name="");
			void endGroup();
            
            // ADVANCED, RESERVED FOR FUTURE USE
            Parameter& addParameter(Parameter *param);
            
            
            
            //---- Accessing parameters -----------------------
			
            // get number of parameters in this group (only gets number of direct children, not children of children)
            int getNumParams() const;
            
            // get parameter by index
            Parameter& getParameter(int index);
            
            // get parameter by name
            Parameter& getParameter(string path);
            
            
            // get values by name
            ParameterInt& getInt(string path);
            ParameterFloat& getFloat(string path);
            ParameterBool& getBool(string path);
            ParameterNamedIndex& getNamedIndex(string path);
            ParameterGroup& getGroup(string path);
            
            // ADVANCED, RESERVED FOR FUTURE USE
//            template <typename T>
//            ParameterValueT<T>& getValue(string path) const;
            
            
            // [] operator overloads for above
            //	Parameter& operator[](int index);
            //  Parameter& operator[](string path);
            
            
        protected:
			map<string, Parameter*>	_paramMap;		// map for all parameters
			vector<Parameter*>		_paramArr;		// array needed to access sequentially (for display etc.)
            
            string _filename;
            
            // keep track of stack of groups when creating with startGroup, endGroup
            stack<ParameterGroup*> _groupStack;
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
//        template <typename T>
//        ParameterValueT<T>& ParameterGroup::getValue(string path) const {
//            ParameterValueT<T> *p = (ParameterValueT<T>*)&getParameter(path);
//            return *p;// ? p->getValue() : T();
//        }
        
        
    }
}