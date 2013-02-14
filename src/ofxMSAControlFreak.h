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
 
 - implement curve types to sliders
 - for the parameter? or the controller?
 - adjust parameter range in runtime from GUI
 - link parameters to each other (as controller?)
 - add time element for loadValues, and morphing (for animation)
 - presets don't load if you change the name of the parameter group in code (think of a way for that to work)
 - implement smoothing (for floats)
 - wrap up controllers (midi, osc, dmx etc).
 */



#pragma once

#include "ofxMSAControlFreak/src/Master.h"
#include "ofxMSAControlFreak/src/Parameter.h"
#include "ofxMSAControlFreak/src/ParameterNumberValueT.h"
#include "ofxMSAControlFreak/src/ParameterBool.h"
#include "ofxMSAControlFreak/src/ParameterInt.h"
#include "ofxMSAControlFreak/src/ParameterFloat.h"
#include "ofxMSAControlFreak/src/ParameterNamedIndex.h"
#include "ofxMSAControlFreak/src/ParameterGroup.h"
#include "ofxMSAControlFreak/src/ParameterVec3f.h"
#include "ofxMSAControlFreak/src/Utils.h"
#include "ofxMSAControlFreak/src/ControllerBase.h"


namespace msa {
    namespace controlfreak {
        
        
        // update everything
        void update();
    }
}