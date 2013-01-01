#pragma once

#include "ofMain.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            // for auto-layout
            class LayoutManager {
            public:
                ofRectangle maxRect;
                ofVec2f     curPos;
                ofRectangle rect;
                
                ofVec2f getMaxPos() {
                    return ofVec2f(maxRect.width ? maxRect.x + maxRect.width : ofGetWidth(), maxRect.height ? maxRect.y + maxRect.height : ofGetHeight());
                }
                
                ofVec2f clampPoint(ofVec2f p) {
                    ofVec2f maxPos(getMaxPos());
                    return ofVec2f(ofClamp(p.x, maxRect.getLeft(), maxPos.x), ofClamp(p.y, maxRect.getTop(), maxPos.y));
                }
            };
            
            
            typedef std::tr1::shared_ptr<LayoutManager> LayoutManagerPtr;
            
        }
    }
}

