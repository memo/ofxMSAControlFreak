#pragma once

#include  "ofxMSAControlFreak/src/gui/Control.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Toggle : public Control {
            public:
                bool	*value;
                bool	momentary;
                
                Toggle(Panel* parent, string name, bool &value);
                Toggle& setMomentary(bool m);
                void setup();
                
                void readFromXml(ofxXmlSettings &XML);
                void writeToXml(ofxXmlSettings &XML);
                
                bool getValue();
                void setValue(bool b);
                void toggle();
                void onPress(int x, int y, int button);
                void onRelease(int x, int y, int button);
                void keyPressed( int key );
                void keyReleased( int key );
                void onKeyEnter();
                void update();
                void draw(float x, float y);
            };
            
        }
    }
}