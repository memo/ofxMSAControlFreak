/*
 
 A container contains other parameters, including other groups (can go infinintely deep)
 
 */

#pragma once

#include "ofxMSACore/src/MSACore.h"

#include "ofxMSAControlFreak/src/Parameter.h"
//#include "ofxMSAControlFreak/src/ParameterValueT.h"

namespace msa {
	namespace ControlFreak {
        
        template <typename T>
        class ParameterValueT;
        
//        class ParameterInt;
//        class ParameterFloat;
//        class ParameterBool;
        class ParameterNamedIndex;
        class ParameterVec3f;

        
		class ParameterContainer : public Parameter {
		public:
            
            ParameterContainer(ParameterContainer *parent, string name, Type::Index typeIndex);
			~ParameterContainer();
			
			int getNumParams() const;
            
            ParameterValueT<int>& getInt(string path);
            ParameterValueT<float>& getFloat(string path);
            ParameterValueT<bool>& getBool(string path);
            ParameterNamedIndex& getNamedIndex(string path);
            ParameterContainer& getContainer(string path);
            
            
            Parameter& getParameter(int index);       // access by index
            Parameter& getParameter(string path);     // access by name
                        
            // [] operator overloads for above
//			Parameter& operator[](int index);
//            Parameter& operator[](string path);
            
			virtual Parameter& addParameter(Parameter *param);
            
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bFull);
            virtual void readFromXml(ofxXmlSettings &xml, bool bFull);
            
            
            // Advanced
//            template <typename T>
//            ParameterValueT<T>& getValue(string path) const;
            

            
            
		protected:
			map<string, Parameter*>	_paramMap;		// map for all parameters
			vector<Parameter*>		_paramArr;		// array needed to access sequentially (for display etc.)
		};

        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
//        template <typename T>
//        ParameterValueT<T>& ParameterContainer::getValue(string path) const {
//            ParameterValueT<T> *p = (ParameterValueT<T>*)&getParameter(path);
//            return *p;// ? p->getValue() : T();
//        }

	}
}