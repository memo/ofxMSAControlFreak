/*
 
 Individual parameter or group / container
 Base class for everything
 
 */

// protected constructor, can only be created via ParameterGroup


#pragma once

#include "ofxMSACore/src/MSACore.h"

#include "ofxMSAControlFreak/src/Controller.h"
#include "ofxMSAControlFreak/src/ParameterTypes.h"

#include "ofxXmlSettings.h"

namespace msa {
	namespace ControlFreak {
		
		class ParameterGroup;
        
		class Parameter {
		public:
			
			friend class ParameterGroup;
			
			virtual ~Parameter() {}
			
            Parameter& setName(string s);
			string getName() const;
            
			string getPath() const;        // return path (including parents)

            ParameterGroup* getParent() const;
            
			Types::Index getType() const;
			string getTypeName() const;
			
            virtual string fullName() const;	// return name prefixed with controllers
			
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
            
		protected:
			Types::Index			_typeIndex;
			string					_name;
//			string					_path;
			ParameterGroup			*_parent;
            
            string                  _xmlTag;
            int                     _xmlTagId;
			
			Parameter(ParameterGroup *parent, string name, Types::Index typeIndex);

            void setParent(ParameterGroup *parent);
		};
		
	
	}
}