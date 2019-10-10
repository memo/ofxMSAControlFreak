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

class ParameterColorf32 : public ParameterGroup {
public:
    ParameterColorf32(string name, ParameterGroup *parent = NULL)
        : ParameterGroup(name, parent) {
        addFloat("r").setRange(0, 1);
        addFloat("g").setRange(0, 1);
        addFloat("b").setRange(0, 1);
        addFloat("a").setRange(0, 1);
    }

	ParameterColorf32& set(const ofFloatColor & v) { get("r").set(v.r); get("g").set(v.g); get("b").set(v.b); get("a").set(v.a); return *this; }
	ofFloatColor operator=(const ofFloatColor & v) { set(v); return v; }
    operator ofFloatColor() const { return ofFloatColor(get("r").value(), get("g").value(), get("b").value(), get("a").value()); }
};
}
}
