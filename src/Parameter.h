/*
 
 Individual parameter or group / container
 Base class for all Parameters
 
 Protected constructor, can only be created via ParameterContainer

 */


#pragma once

#include "ofxMSACore/src/MSACore.h"

#include "ofxMSAControlFreak/src/Controller.h"
#include "ofxMSAControlFreak/src/Utils.h"

#include "ofxXmlSettings.h"

namespace msa {
	namespace ControlFreak {
		
		class ParameterContainer;
        
		class Parameter {
		public:
			
			friend class ParameterContainer;
            
			Parameter(ParameterContainer *parent, string name, Type::Index typeIndex);
			virtual ~Parameter() {}
			
            Parameter& setName(string s);
			string getName() const;
            
			string getPath() const;        // return path (including parents)

            ParameterContainer* getParent() const;
            
			Type::Index getType() const;
			string getTypeName() const;
			
            virtual string fullName() const;	// return name prefixed with controllers
			
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
            
		protected:
			Type::Index			_typeIndex;
			string					_name;
//			string					_path;
			ParameterContainer			*_parent;
            
            string                  _xmlTag;
            int                     _xmlTagId;
			
            void setParent(ParameterContainer *parent);
		};
		
	
	}
}