/*
 *  MSACGParameterTypes.h
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include <string>

using namespace std;

namespace msa {
	namespace ControlFreak {
		namespace Types {
			
			enum Index {
				kFloat,
				kInt,
				kToggle,
				kBang,
				kNamedIndex,
                kGroup,
                kVec2f,
                kVec3f,
                kVec4f,
                kColoru8,
                kColorf,
				kNumTypes
			};
			
			Index indexForName(string s);
			string nameForIndex(Index i);
		}
	}
}