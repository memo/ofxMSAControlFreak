/*
 
 Individual parameter or group / container
 Base class for all Parameters
 
 Protected constructor, can only be created via ParameterGroup

 */


#pragma once

#include "ofxMSACore/src/MSACore.h"

#include "ofxMSAControlFreak/src/Controller.h"
#include "ofxMSAControlFreak/src/Utils.h"

#include "ofxXmlSettings.h"

namespace msa {
	namespace ControlFreak {
		
		class ParameterGroup;
        
		class Parameter {
		public:
            
#define kCheckBadParameter(ret) 
            //{ if(this->getType() == Type::kUnknown) return ret; }

			
			friend class ParameterGroup;
            
			virtual ~Parameter() {}
			
            Parameter& setName(string s);
			string getName() const;
            
			string getPath() const;        // return path (including parents)

            ParameterGroup* getParent() const;
            
			Type::Index getType() const;
			string getTypeName() const;
            
//            template <typename T>
//            Parameter& setValue(T v);
//			T& getValue() const;
            
		protected:
			Parameter(ParameterGroup *parent, string name, Type::Index typeIndex);

			Type::Index			_typeIndex;
			string				_name;
			ParameterGroup		*_parent;
            
            string              _xmlTag;
            int                 _xmlTagId;
			
            void setParent(ParameterGroup *parent);
            
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
            virtual void update() {}

            // dummy parameter, sent back from 'getParameter' functions, if parameter can't be found
            static Parameter dummy;
		};
		
	
	}
}