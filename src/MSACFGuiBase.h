/*
 *  GuiBase.h
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 01/10/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "MSACFParameter.h"
#include "MSACFParameterGroup.h"

namespace msa {
	namespace ControlFreak {
		
		class GuiBase {
			
			friend class ParameterGroup;
			
			
		protected:
			
			// add this parameter to the Gui
			virtual void addParameter(Parameter *param) = 0;
			
			virtual void startGroup(string name) {};
			virtual void endGroup() {};
		};
	}
}