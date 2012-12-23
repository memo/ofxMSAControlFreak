/*
 *  MSACFController.cpp
 *  UK Summer Games v2
 *
 *  Created by Memo Akten on 23/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "ofxMSAControlFreak/src/Controller.h"
#include "ofxMSAControlFreak/src/Parameter.h"


namespace msa {
	namespace ControlFreak {
		
		void Controller::setParam(Parameter *param) {
			_param = param;
		}
		
		
//		void Controller::checkValueHasChanged() {
//			if(_param->getValue() != _oldValue) {
//				_oldValue = *_param;
//				sendValue();
//			}
//		}
		
	}
}