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

class ParameterColoru8 : public ParameterGroup {
public:
    ParameterColoru8(string name, ParameterGroup *parent = NULL)
        : ParameterGroup(name, parent) {
        addInt("r").setRange(0, 255);
        addInt("g").setRange(0, 255);
        addInt("b").setRange(0, 255);
        addInt("a").setRange(0, 255);
    }

    ofColor operator=(const ofColor & v) { get("r").set(v.r); get("g").set(v.g); get("b").set(v.b); get("a").set(v.a); return v; }
    operator ofColor() const { return ofColor(get("r").value(), get("g").value(), get("b").value(), get("a").value()); }
};
}
}
