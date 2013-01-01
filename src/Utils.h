/*
 *  MSACGParameterTypes.h
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

using namespace std;

namespace msa {
	namespace ControlFreak {
        
        void setPathDivider(char divider = '.');
        char getPathDivider();

        namespace Type {
            enum Index {
                kUnknown,
                kFloat,
                kInt,
                kBool,
                kNamedIndex,
                kGroup,
                kVec2f,
                kVec3f,
                kVec4f,
                kColoru8,
                kColorf32,
                kNumTypes
            };

            Type::Index indexForName(string s);
            string nameForIndex(Type::Index i);
        }
        
        
	}
}