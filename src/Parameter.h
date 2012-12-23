
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
			
			string name() const;		// return name
			string path() const;        // return path (including parents)

			Types::Index type() const;
			string typeName() const;
			
			
            virtual string fullName() const;	// return name prefixed with controllers
			
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull, string tag, int tagid);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull, string tag, int tagid);
            
		protected:
			Types::Index			_typeIndex;
			string					_path;
			string					_name;
			ParameterGroup			*_parent;
			
			Parameter(ParameterGroup *parent, string path, Types::Index typeIndex);
		};
		
	
	}
}