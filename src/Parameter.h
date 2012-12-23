
// protected constructor, can only be created via ParameterGroup


#pragma once

#include "ofxMSACore/src/MSACore.h"
#include "ofxMSAControlFreak/src/Controller.h"
#include "ofxMSAControlFreak/src/ParameterTypes.h"

#include "ofxXmlSettings.h"

namespace msa {
	namespace ControlFreak {
		
		class ParameterGroup;
        
        union Value {
            int vi;
            float vf;
        };
        
		
		class Parameter {
		public:
			
			friend class ParameterGroup;
			
			virtual ~Parameter() {}
			
			string path() const;
			string name() const;		// return name

			string fullName() const;	// return name prefixed with controllers
			
			Parameter& setRange(int vmin, int vmax);
			Parameter& setRange(float vmin, float vmax);
			
			float min() const;
			float max() const;
			float value() const;
            
			Parameter& setValue(int v);
			Parameter& setValue(float v);
			
			Types::Index type() const;
			string typeName() const;
			
			Parameter& setClamp(bool b);                        // enable or disable clamping
			bool isClamped() const;                             // returns whether clamp is enabled or not
			
			template<typename T> operator T() const;			// cast operator
			template<typename T> T operator=(const T & v);      // assignment operator
			
			Parameter& setNormalized(float norm);				// input 0...1 number, maps to range
			float normalized() const;                           // return 0...1 number mapped from range
			
			Parameter& setMappedFrom(float v, float imin, float imax);
			float mappedTo(float newMin, float newMax) const;	// returns value mapped to new range

			
			Parameter& addController(Controller *controller);
			void updateControllers();
//			void checkValueHasChanged();
			
            virtual void writeSchemaToXml(ofxXmlSettings &xml);
            virtual void readSchemaFromXml(ofxXmlSettings &xml);
            
            virtual void writeValueToXml(ofxXmlSettings &xml);
            virtual void readValueFromXml(ofxXmlSettings &xml);
            
		protected:
			Types::Index			_typeIndex;
			Value					_min, _max, _value;
			string					_path;
			string					_name;
			bool					_isClamped;
			vector<Controller*>		_controllers;
			ParameterGroup			*_parent;
			
			Parameter(ParameterGroup *parent, string path, Types::Index typeIndex);
            
			Parameter& setType(Types::Index type);
			Parameter& setType(string s);
		};
		
	
	}
}