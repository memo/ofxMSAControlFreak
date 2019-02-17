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

#pragma once

//#include "ofxMSAControlFreak/src/ParameterComplexValueT.h"

namespace msa {
namespace controlfreak {

class ParameterVec3f : public ParameterGroup {
public:
    ParameterVec3f(string name, ParameterGroup *parent = NULL)
        : ParameterGroup(name, parent) {
        addFloat("x").setRange(0, 1);
        addFloat("y").setRange(0, 1);
        addFloat("z").setRange(0, 1);

    }

    ofVec3f operator=(const ofVec3f & v) { get("x").set(v.x); get("y").set(v.y); get("z").set(v.z); return v; }
    operator ofVec3f() const { return ofVec3f(get("x").value(), get("y").value(), get("z").value()); }
};
}
}
