/*
 *  MSAControlFreak.h
 *  UK Summer Games v2
 *
 *  Created by Memo Akten on 23/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

/*
 
 
 TODO:
 
 + implement GUI Controller, and Controller::valueChanged(), so no need for update()
 
 + add option for clamp or not
 
 - implement curve types to sliders
 - for the parameter? or the controller?
 
 - implement smoothing (for floats)
 
 + multiple types (int, bool, float)
 
 - adjust parameter range in runtime from GUI
 
 - link parameters to each other (as controller?)
 
 - multiple presets (animation):
 
 Parameter::addPreset(value, name = "default");		// adds a value to a parameter as a preset
 Parameter::applyPreset(name, time);					// apply preset (if it exists) in time seconds
 Parameter::savePreset(name);						// save current value as preset with name
 
 ParameterContainer::applyPreset(name, time);						// apply preset (if it exists) to all parameters in group, in time seconds
 ParameterContainer::savePreset(name);							// save current value for all parameters in group as preset with name
 
 Global::applyPreset(name, time);					// apply preset (if it exists) to all parameters in all groups, in time seconds
 Global::savePreset(name);							// save current value for all parameters in all groups as preset with name
 
 writeToXml();
 readFromXml;
 
 
 myParameter.addPreset(5, "default");
 params.applyPreset("default");
 
 
 */



#pragma once

#include "ofxMSAControlFreak/src/Parameter.h"
#include "ofxMSAControlFreak/src/ParameterNumbers.h"
#include "ofxMSAControlFreak/src/ParameterNamedIndex.h"
#include "ofxMSAControlFreak/src/ParameterGroup.h"
#include "ofxMSAControlFreak/src/ParameterVec3f.h"
#include "ofxMSAControlFreak/src/Utils.h"
#include "ofxMSAControlFreak/src/Controller.h"


/*
 
 Parameter
    ParameterContainer
        ParameterValueT
            ParameterSingleValueT
                ParameterInt
                    ParameterNamedIndex
                ParameterFloat
                ParameterBool
            ParameterContainerValueT
 
 
 
 
                                
 
 */

