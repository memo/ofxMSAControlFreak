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
        
        class Parameter;
        typedef std::tr1::shared_ptr<Parameter> ParameterPtr;

        
		class Parameter {
		public:
            
//#define kCheckBadParameter(ret)
            //{ if(this->getType() == Type::kUnknown) return ret; }

			friend class ParameterGroup;
            
			Parameter(string name, ParameterGroup *parent, Type::Index typeIndex = Type::kUnknown);
			virtual ~Parameter();
            
            Parameter& setName(string s);
			string getName() const;
            
            Parameter& setTooltip(string s);
            string getTooltip() const;
            
			string getPath() const;        // return path (including parents)

            ParameterGroup* getParent() const;
            
			Type::Index getType() const;
			string getTypeName() const;
            
//            template <typename T>
//            Parameter& setValue(T v);
//			T& getValue() const;
            
		protected:
			Type::Index			_typeIndex;
			string				_name;
            string              _tooltip;
			ParameterGroup		*_pparent;
            
            string              _xmlTag;
            int                 _xmlTagId;
			
            void setParent(ParameterGroup *parent);
            
            virtual void writeToXml(ofxXmlSettings &xml, bool bOnlyValues);
            virtual void readFromXml(ofxXmlSettings &xml, bool bOnlyValues);
            virtual void update() {}
		};
		
	}
}