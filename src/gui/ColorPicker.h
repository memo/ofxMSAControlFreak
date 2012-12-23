#pragma once

#include  "ofxMSAControlFreak/src/gui/Control.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class ColorPicker : public Control {
            public:
                
                ofFloatColor    *value;
                float		min, max;
                
                float		barwidth[4];
                float		pct[4];
                
                ColorPicker(string name, ofFloatColor& color, float max = 1);
                void setup();
                void readFromXml(ofxXmlSettings &XML);
                void writeToXml(ofxXmlSettings &XML);
                float getValue(int i);
                void setValue(float f, int i);
                void updateSlider();	
                void onPress(int x, int y, int button);
                void onDragOver(int x, int y, int button);
                void onDragOutside(int x, int y, int button);
                void update();
                void draw(float x, float y);
            };
            
        }
    }
}