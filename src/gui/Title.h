#pragma once

#include  "ofxMSAControlFreak/src/gui/Control.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Title : public Control {
            public:
                
                bool*			value;
                bool			beToggle;
                bool			beenPressed;
                
                Title(Panel* parent, string name, float height);
                void setup();
                
                void readFromXml(ofxXmlSettings &XML);
                void writeToXml(ofxXmlSettings &XML);
                
                bool getValue();
                void setValue(bool b);
                void toggle();
                void setToggleMode(bool b);
                void onPress(int x, int y, int button);
                void onRelease(int x, int y, int button);
                void draw(float x, float y);
            };
        }
    }
}