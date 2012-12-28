//
//  Renderer.cpp
//  ofxMSAControlFreak example
//
//  Created by Memo Akten on 28/12/2012.
//
//

#pragma once

#include "ofMain.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Control;
            class Config;
            
            class Renderer {
            public:
                friend class Gui;
                
                ~Renderer();
                
                static Renderer &instance();
                
                void addControl(Control *c);
                void clearControls();
                void draw(Config *config);
                
                void setToolTip(string s, int x = -1, int y = -1);
                
            protected:
                Config *config;
                vector<Control *> controls;
                
                struct {
                    string s;
                    int x;
                    int y;
                } tooltip;
                
                void drawToolTip();
                
                Renderer();
                
                static Renderer *renderer;
            };
            
        }
    }
}