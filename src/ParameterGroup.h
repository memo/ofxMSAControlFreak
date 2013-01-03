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
			
            // save and load all parameter (values only) to an xml file
            // leave filename blank for default (inherits name of parameter group + "-values.xml")
			bool saveXmlValues(string filename = "");
			bool loadXmlValues(string filename = "");

            // save and load all parameter (full schema) to an xml file
            // leave filename blank for default (inherits name of parameter group + "-schema.xml")
			bool saveXmlSchema(string filename = "");
			bool loadXmlSchema(string filename = "");
            
            // write or read all parameters to an xml variable
            void writeToXml(ofxXmlSettings &xml, bool bOnlyValues);
            void readFromXml(ofxXmlSettings &xml, bool bOnlyValues);
            
            // call this every frame to make sure any external controllers (e.g. midi, osc etc.) stay in sync
            void update();
            
            
            // remove all parameters
            void clear();
            
            
            //---- Adding parameters -----------------------
            
            // creates and adds a parameter
			ParameterInt& addInt(string name);
			ParameterFloat& addFloat(string name);
			ParameterBool& addBool(string name);
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
            
            
            // getters, return NULL if they can't find the parameter
            
            // get parameter by index
            Parameter* getParameter(int index);
            
            // get parameter by name
            Parameter* getParameter(string path);
            
            
            // get values by name
            ParameterInt* getInt(string path);
            ParameterFloat* getFloat(string path);
            ParameterBool* getBool(string path);
            ParameterNamedIndex* getNamedIndex(string path);
            ParameterGroup* getGroup(string path);
            
            // generic function to get value as any type (type==parameter class, not basic type)
            template <typename T>
            T* get(string path);
            
            // [] operator overloads for above
            //	Parameter& operator[](int index);
            //  Parameter& operator[](string path);
            
            
        protected:
			map<string, Parameter*>	_paramMap;		// map for all parameters
			vector<ParameterPtr>	_paramArr;		// array needed to access sequentially (for display etc.)
            
            string _filename;
            
            // keep track of stack of groups when creating with startGroup, endGroup
            stack<ParameterGroup*> _groupStack;
            
            
            // save and load all parameters to an xml file
			bool saveXml(string filename, bool bOnlyValues);
			bool loadXml(string filename, bool bOnlyValues);
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        template <typename T>
        T* ParameterGroup::get(string path) {
            Parameter *p = getParameter(path);
            if(!p) {
                ofLogError() << "msa::ControlFreak::ParameterGroup::get<T> - Could not FIND parameter " << path << " in group " << getPath();
                return NULL;
            }
            
            T *tp = dynamic_cast<T*>(p);
            if(!tp) {
                ofLogError() << "msa::ControlFreak::ParameterGroup::get<T> - Could not CONVERT parameter " << path << " in group " << getPath();
                return NULL;
            }
            
            return tp;
        }
        
    }
}