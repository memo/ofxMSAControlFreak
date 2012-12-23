#pragma once

#include  "ofxMSAControlFreak/src/gui/Control.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Slider2d : public Control {
            public:
                ofPoint		*value;
                ofPoint		point, min, max;
                
                Slider2d(string name, ofPoint& value, float xmin, float xmax, float ymin, float ymax);
                void setup();
                void readFromXml(ofxXmlSettings &XML);
                void writeToXml(ofxXmlSettings &XML);
                void setValue(float x, float y);
                void setMin(float x, float y);
                void setMax(float x, float y);
                void onPress(int x, int y, int button);
                void onDragOver(int x, int y, int button);
                void onDragOutside(int x, int y, int button);
                void onRelease();
                void update();
                void draw(float x, float y);
            };
        }
    }
}