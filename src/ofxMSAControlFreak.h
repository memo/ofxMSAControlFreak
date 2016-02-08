//                                      __
//     ____ ___  ___  ____ ___  ____   / /__   __
//    / __ `__ \/ _ \/ __ `__ \/ __ \ / __/ | / /
//   / / / / / /  __/ / / / / / /_/ // /_ | |/ /
//  /_/ /_/ /_/\___/_/ /_/ /_/\____(_)__/ |___/
//
//
//  Created by Memo Akten, www.memo.tv
//
//  ofxMSAControlFreak
//

/*
 
 
 TODO:
 
 - implement curve types to sliders
 - for the parameter? or the controller?
 - adjust parameter range in runtime from GUI
 - link parameters to each other (as controller?)
 - add time element for loadValues, and morphing (for animation)
 - presets don't load if you change the name of the parameter group in code (think of a way for that to work)
 - implement smoothing (for floats)
 - wrap up controllers (midi, osc, dmx etc).
 - dynamically update GUI when adding or removing parameters
 
 */



#pragma once

#include "MSAControlFreak/Master.h"
#include "MSAControlFreak/Parameter.h"
#include "MSAControlFreak/ParameterNumberValueT.h"
#include "MSAControlFreak/ParameterBool.h"
#include "MSAControlFreak/ParameterInt.h"
#include "MSAControlFreak/ParameterFloat.h"
#include "MSAControlFreak/ParameterNamedIndex.h"
#include "MSAControlFreak/ParameterGroup.h"
#include "MSAControlFreak/ParameterVec3f.h"
#include "MSAControlFreak/Utils.h"
#include "MSAControlFreak/ControllerBase.h"

