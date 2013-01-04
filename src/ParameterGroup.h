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

        class ParameterGroup;
        typedef std::tr1::shared_ptr<ParameterGroup> ParameterGroupPtr;
        
        
        class ParameterGroup : public Parameter {
        public:
            
            // factory method for creating new instances
            static ParameterGroupPtr create(string name = "MSAControlFreak", ParameterGroup *parent = NULL, Type::Index typeIndex = Type::kGroup);
            
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
            Parameter& addParameter(Parameter* param);      // if you create a new pointer
            Parameter& addParameter(ParameterPtr param);    // if you already have a smart pointer
            
            
            
            //---- Accessing parameters -----------------------
			
            // getters for Parameters, so you access parameter properties etc.

            // These return a reference to the Parameter
            // they throw an exception if you enter a wrong name
            Parameter& get(int index);         // get parameter by index
            Parameter& get(string path);       // get parameter by name


            // returns a SHARED pointer to the Parameter
            ParameterPtr getPtr(int index);     // get parameter by index
            ParameterPtr getPtr(string path);   // get parameter by name

            
            // get a reference or pointer to a Group
            // same as the get() above, but with a type-cast in the method
            ParameterGroup& getGroup(string path);
            ParameterGroup* getGroupPtr(string path);

            
            // returns a reference of pointer type-cast to the correct Parameter sub-class (e.g. ParameterNamedIndex)
            // use this if you need to access properties and methods unique to that Parameter sub-class
            template <typename ParameterType> ParameterType& get(string path);
            template <typename ParameterType> ParameterType* getPtr(string path);

            
            
            // get values directly out of thhe Parameter Group
//            AnyValue getValue(int index);
//            AnyValue getValue(string path);
            
//            template <typename ValueType> ValueType getValue(string path);
            
            
            // get number of parameters in this group (only gets number of direct children, not children of children)
            int getNumParams() const;
            
            

            
            // get values by name
//            ParameterInt* getInt(string path);
//            ParameterFloat* getFloat(string path);
//            ParameterBool* getBool(string path);
//            ParameterNamedIndex* getNamedIndex(string path);
//            ParameterGroup* getGroup(string path);
            
            // generic function to get value as any type (type==parameter class, not basic type)
            
            // [] operator overloads for above
//            ParameterPtr operator[](int index);
//            ParameterPtr operator[](string path);
            
            
        protected:
            ParameterGroup(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kGroup);

			map<string, ParameterPtr>	_paramMap;		// map for all parameters
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
        template <typename ParameterType>
        ParameterType* ParameterGroup::getPtr(string path) {
            ParameterPtr p = getPtr(path);
            if(!p) {
                ofLogError() << "msa::ControlFreak::ParameterGroup::get<ParameterType>: Could not FIND parameter " << path << " in group " << getPath();
                return NULL;
            }
            
            ParameterType *tp = dynamic_cast<ParameterType*>(p.get());
            if(!tp) {
                ofLogError() << "msa::ControlFreak::ParameterGroup::get<ParameterType>: Could not CONVERT parameter " << path << " in group " << getPath();
                return NULL;
            }
            
            return tp;
        }

        
        //--------------------------------------------------------------
        template <typename ParameterType>
        ParameterType& ParameterGroup::get(string path) {
            return *getPtr<ParameterType>(path);
        }

        
        
        //--------------------------------------------------------------
//        template <typename ValueType>
//        ValueType ParameterGroup::getValue(string path) {
//            ParameterPtr p = getPtr(path);
//            if(!p) {
//                ofLogError() << "msa::ControlFreak::ParameterGroup::getValue<ValueType>: Could not FIND parameter " << path << " in group " << getPath();
//                return ValueType();
//            }
//            return p->value().extract<ValueType>();
//        }

        
    }
}