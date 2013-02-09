///*
// 
// Interface base class for any Value (either simple or complex)
// 
// */
//
//
//#pragma once
//
//#include "Poco/DynamicAny.h"
//
//namespace msa {
//	namespace controlfreak {
//
//        template <typename T>
//        class ValueContainerT;
//        
//        class ValueContainerI {
//        public:
////            friend class AnyValue;
//            
//            virtual ~ValueContainerI() {
//                ofLogVerbose() << "~ValueContainerI()";
//            }
//            
//            template <typename T> T operator=(const T &v) { setFromContainer(ValueContainerT<T>(v)); }
////			template <typename T> operator T() const { return getFromContainer(); }
//            
//
//            virtual string getTypeInfo() {};
//            
//        protected:
//            virtual void setFromContainer(const ValueContainerI& vci) {
//                ofLogVerbose() << "ValueContainerI::setFromContainer";
//            };
//            
//            virtual ValueContainerI getFromContainer() const {
//                ofLogVerbose() << "ValueContainerI::getFromContainer";
//            };
//        };
//        
//        
//        
//        template <typename T>
//        class ValueContainerT : public ValueContainerI {
//        public:
//            ValueContainerT() {}
//            ValueContainerT(const T &v):_value(v) {
//                ofLogVerbose() << "ValueContainerT::ValueContainerT(T) " << v;
//            }
//            
//            T operator=(const T & v) { set(v); }
//			operator T() const { return get(); }
//            
//            void set(const T &v) {
//                _value = v;
//            }
//            
//            T get() const {
//                return _value;
//            }
//            
//            string getTypeInto() {
//                return typeid(T).name();
//            }
//            
//        protected:
//            void setFromContainer(const ValueContainerI& vci) {
//                ofLogVerbose() << "ValueContainerT::setFromContainer";
//                _value = (T)vci;//.getFromContainer();
//            }
//            
//            ValueContainerI getFromContainer() const {
//                ofLogVerbose() << "ValueContainerT::getFromContainer";
//                return ValueContainerT<T>(_value);
//            }
//            
//        private:
//            T _value;
//        };
//        
//        typedef std::tr1::shared_ptr<ValueContainerI> ValueContainerIRef;
//  
//        
//		class AnyValue {
//        public:
//            AnyValue(ValueContainerI *vc = NULL):_valueContainer(ValueContainerIRef(vc)) {}
//            ~AnyValue() {
////                ofLogVerbose() << "~AnyValue()";
//            }
//            
//            template <typename T> T operator=(const T &v) { set(v); }
//            template <typename T> operator T() const { return get<T>(); }
//            
//            template <typename T> void set(const T &v) {
//                ofLogVerbose() << "AnyValue::set(T) " << v;
//                checkValueContainer<T>();
////                _valueContainer->setFromContainer(ValueContainerT<T>(v));
////                assert(_valueContainer);
////                any = v;
////                _valueContainer->setData((void*)&v);
////                ValueContainerT<T> *vc = dynamic_cast<ValueContainerT<T> *>(_valueContainer);
////                if(vc) vc->set(v);
////                else ofLogWarning() << "cannot cast";
//            }
//            
//            template <typename T> T get() const {
//                ofLogVerbose() << "(T) AnyValue::get";
////                checkValueContainer<T>();
//                assert(_valueContainer);
////                return any;
////                ValueContainerT<T> *vc = dynamic_cast<ValueContainerT<T> *>(_valueContainer);
////                if(vc) return vc->get();
////                return *(T*)_valueContainer->getData();
//                
////                ofLogWarning() << "cannot cast";
////                return T();
//            }
//            
//            template <typename T>
//            void checkValueContainer() {
//                if(_valueContainer == NULL) setValueType(new ValueContainerT<T> );
//            }
//            
//            void setValueType(ValueContainerI *value) {
//                _valueContainer = ValueContainerIRef(value);
//            }
//            
//        protected:
//            ValueContainerIRef _valueContainer;
////            Poco::DynamicAny any;
//            
//        };
//        
//        
//        
//    }
//}
