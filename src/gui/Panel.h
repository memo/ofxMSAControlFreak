#pragma once

#include "ofxMSAControlFreak/src/gui/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        
        class Parameter;
        class ParameterGroup;
        
        namespace gui {
            
            class Gui;
            class BoolButton;
            class BoolTitle;
            class BoolTitle;
            class BoolToggle;
            class ColorPicker;
            class ComboBox;
            class Content;
            class FPSCounter;
            class QuadWarp;
            class Slider2d;
            class SliderInt;
            class SliderFloat;
            
            class Panel : public ControlParameterT<ParameterGroup> {
            public:
                
                friend class Gui;
                
                Panel(Panel *parent, Parameter *p);
                ~Panel();
                
                void predraw();
                void draw();
                
                void setActiveControl(Control *control);
                void releaseActiveControl();
                Control* getActiveControl();
                
                // returns whether this panel, or any of it's parents have an active control
                bool getActive();
                
                void update();
                void mouseMoved(ofMouseEventArgs &e);
                void mousePressed(ofMouseEventArgs &e);
                void mouseDragged(ofMouseEventArgs &e);
                void mouseReleased(ofMouseEventArgs &e);
                void keyPressed(ofKeyEventArgs &e);
                void keyReleased(ofKeyEventArgs &e);
//                vector<ControlPtr>&	getControls();
                
                void addParameter(Parameter *p);
                void addParameters(ParameterGroup &parameters);
                
            protected:
                
                float heightScale;              // height scale of this panel
                float getParentHeightScale();   // height scale of parent
                float getHeightScale();         // inherited height scale
                
//                float alphaScale;              // alpha scale of this panel
//                float getParentAlphaScale();   // alpha scale of parent
//                float getAlphaScale();         // inherited height alpha

                
                
                struct Layout {
                    // for auto-layout
                    ofRectangle maxRect;
                    ofVec2f     curPos;
                    float       indent;
                    ofRectangle rect;
                    
                    ofVec2f getMaxPos() {
                        return ofVec2f(maxRect.width ? maxRect.x + maxRect.width : ofGetWidth(), maxRect.height ? maxRect.y + maxRect.height : ofGetHeight());
                    }
                    
                    ofVec2f clampPoint(ofVec2f p) {
                        ofVec2f maxPos(getMaxPos());
                        return ofVec2f(ofClamp(p.x, maxRect.getLeft(), maxPos.x), ofClamp(p.y, maxRect.getTop(), maxPos.y));
                    }
                    
                };
                typedef std::tr1::shared_ptr<Layout> LayoutPtr;
                LayoutPtr layout;
                
                
                // contains extra parameters for gui specific controls
//                ParameterGroup extraParams;
                
                
                vector<ControlPtr>	controls;
                vector<Control*> controlsToDraw;    // this contains the controls to be drawn, sorted on control.z
                
                
                BoolTitle *titleButton;       // button which controls the title of the panel
                
                
                // currently active control (only that receives events)
                Control         *activeControl;
                
                Control			&addControl(Control *control);
                
                Panel           &addPanel(Parameter *p);
                BoolButton		&addButton(Parameter *p);
                ColorPicker		&addColorPicker(Parameter *p);
                ComboBox&       addComboBox(Parameter *p);
                Content			&addContent(Parameter *p, ofBaseDraws &content, float fixwidth = -1);
                FPSCounter		&addFPSCounter();
                QuadWarp		&addQuadWarper(Parameter *p);
                Slider2d		&addSlider2d(Parameter *p);
                SliderInt		&addSliderInt(Parameter *p);
                SliderFloat		&addSliderFloat(Parameter *p);
                BoolTitle		&addTitle(Parameter *p);
                BoolToggle		&addToggle(Parameter *p);
            };
            
            typedef std::tr1::shared_ptr<Panel> PanelPtr;
            
        }
    }
}