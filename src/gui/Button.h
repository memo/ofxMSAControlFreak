#pragma once

#include  "ofxMSAControlFreak/src/gui/ValueControl.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Button : public ValueControl<bool> {
            public:
                bool			beToggle;
                bool			beenPressed;
                
                Button(string name, bool &value);
                void setup();
                
                void readFromXml(ofxXmlSettings &XML);
                void writeToXml(ofxXmlSettings &XML);
                
                void keyPressed( int key );
                
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