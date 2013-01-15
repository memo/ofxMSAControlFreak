/*
 
 A parameter group, contains other parameters, including other groups (can go infinitely deep)
 with API to handle creating more subgroups
 The main public facing class of ofxMSAControlFreak
 
 */

#pragma once

#include "ofxMSAControlFreak/src/Parameter.h"
#include "ofxMSAOrderedPointerMap/src/ofxMSAOrderedPointerMap.h"

namespace msa {
    namespace ControlFreak {
        
        class ParameterInt;
        class ParameterFloat;
        class ParameterBool;
        class ParameterNamedIndex;
        class ParameterVec3f;

        class ParameterGroup : public Parameter {
        public:
            
            ParameterGroup(string name = "MSAControlFreak", ParameterGroup *parent = NULL);
            ~ParameterGroup();

            
            // call this once every frame to make sure any external controllers (e.g. midi, osc etc.) stay in sync and Parameter::hasChanged() is correct
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
            Parameter& add(Parameter* param);      // if you create a new pointer (it will be owned and deleted by this Group)
            
            
            
            //---- Accessing parameters -----------------------
			
            // get number of parameters in this group (only gets number of direct children, not children of children)
            int size() const;
            

            // get Parameter by index (returns reference to Parameter)
            // throws an exception if parameter doesn't exist
            Parameter& get(int index) const;
            Parameter& operator[](int index) const;
            
            
            // get Parameter by path (returns reference to Parameter)
            // throws an exception if parameter doesn't exist
            Parameter& get(string path) const;
            Parameter& operator[](string path) const;
            Parameter& operator[](const char* path) const;

            // returns a pointer to the Parameter (so you can check against NULL to see if it exists and avoid an exception)
            Parameter* getPtr(string path) const;

            
            // get a reference or pointer to a Group
            // same as the get() above, but with a type-cast in the method
            ParameterGroup& getGroup(string path) const;      // throws exception if group doesn't exist
            ParameterGroup* getGroupPtr(string path) const;   // returns NULL if group doesn't exist

            
            // returns a reference of pointer type-cast to the correct Parameter sub-class (e.g. ParameterNamedIndex)
            // use this if you need to access properties and methods unique to that Parameter sub-class
            template <typename ParameterType> ParameterType& get(string path) const;
            template <typename ParameterType> ParameterType* getPtr(string path) const;
            
            
            
            //---- Saving/loading from XML -----------------------

            // if name is omitted, last used name is used (by default same as group name)
//			void setFilename(string filename = "");
			
            // save and load all parameter (values only) to an xml file
            // if no folder is given, file is placed in default location (presets/group-path/)
            // if no filename is given, default file and location is used (presets/group-path/default.xml)
			bool saveXmlValues(string filename = "");
			bool loadXmlValues(string filename = "");
            
            // save and load all parameter (full schema) to an xml file
            // filename and folder defaults as above
			bool saveXmlSchema(string filename = "");
			bool loadXmlSchema(string filename = "");
            
            
            // write or read all parameters to an xml variable
            void writeToXml(ofxXmlSettings &xml, bool bOnlyValues);
            void readFromXml(ofxXmlSettings &xml, bool bOnlyValues);
            

        
            string getFullPath(string filename, bool bFullSchema);
            string getPresetsDir();
            vector<string> getPresetsList();
            
        protected:
            
            OrderedPointerMap<string, Parameter> _params;
            
//            string _filename;
            
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
        ParameterType* ParameterGroup::getPtr(string path) const {
            Parameter* p = getPtr(path);
            if(!p) {
                ofLogError() << "msa::ControlFreak::ParameterGroup::get<ParameterType>: Could not FIND parameter " << path << " in group " << getPath();
                return NULL;
            }
            
            ParameterType *tp = dynamic_cast<ParameterType*>(p);
            if(!tp) {
                ofLogError() << "msa::ControlFreak::ParameterGroup::get<ParameterType>: Could not CONVERT parameter " << path << " in group " << getPath();
                return NULL;
            }
            
            return tp;
        }

        
        //--------------------------------------------------------------
        template <typename ParameterType>
        ParameterType& ParameterGroup::get(string path) const {
            return *getPtr<ParameterType>(path);
        }

                
    }
}