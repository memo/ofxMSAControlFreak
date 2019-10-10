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

 Internal Master Class which keeps track of and owns all parameters

 all members private
 
 */

#pragma once

#include "ofMain.h"
#include "ofxMSAOrderedPointerMap.h"

namespace msa {
namespace controlfreak {

class Parameter;

class Master {
public:
	// a bit hacky to do this here? set global time
	void setTime(float t) { currentTime = t; }
	float getTime() { return currentTime >= 0 ? currentTime : ofGetElapsedTimef(); }

	static Master& instance();

private:
	float currentTime=-1;

    friend class Parameter;
    friend class ParameterGroup;
    friend void update();

    Master();
    ~Master();

    void add(Parameter* p);
    void erase(Parameter *p);
    void update(ofEventArgs &e);

    // is this dodgey? a map using the pointers address as key? so i can find the parameter quickly to erase and remove?
    msa::OrderedPointerMap<Parameter*, Parameter> _parameters;
    static Master* _instance;

};
}
}
