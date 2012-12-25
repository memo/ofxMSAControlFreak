#pragma once

#include  "ofxMSAControlFreak/src/gui/Control.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class QuadWarp : public Control {
            public:
                ofPoint			*pts;
                ofPoint			*curPoint;
                ofBaseDraws		*baseDraw;
                
                // for doubleclick
                ofPoint			lastPressPlace;
                float			lastPressTime;
                
                QuadWarp(string name, ofBaseDraws &baseDraw, ofPoint *pts);
                void setup();
                void readFromXml(ofxXmlSettings &XML);
                void writeToXml(ofxXmlSettings &XML);
                void onPress(int x, int y, int button);
                void onPressOutside(int x, int y, int button);
                void onDragOver(int x, int y, int button);
                void onDragOutside(int x, int y, int button);
                void draw(float x, float y);
            };
            
        }
    }
}