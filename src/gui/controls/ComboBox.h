#pragma once

#include "ofxMSAControlFreak/src/gui/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            class Panel;
            
            class ComboBox : public ControlParameterT<ParameterNamedIndex> {
            public:
                ComboBox(Panel *parent, Parameter *p) : ControlParameterT<ParameterNamedIndex>(parent, p) {}
//                
//                void keyPressed( int key );
//                void onPress(int x, int y, int button);
//                void onRelease(int x, int y, int button);
//                void onReleaseOutside(int x, int y, int button);
//                
//                void onPressOutside(int x, int y, int button);
//                void onMouseMove(int x, int y);
//                void onDragOver(int x, int y, int button);
//                void onDragOutside(int x, int y, int button);
//                
//                bool hitTest(int tx, int ty);
//                
//                void draw(float x, float y);

                
            protected:
                void setCBTextColor();
                void setCBTextBGColor();
                void releaseEventStealingFocus();
                
                int            mouseChoice;
                bool           hasFocus;
                bool           mouseMovedSinceClick;
                string          title;
                vector<string>  choices;
            };
            
        }
    }
}