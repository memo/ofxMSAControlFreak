#pragma once

#include "ofxMSAControlFreak/src/gui/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        
        class Parameter;
        class ParameterGroup;
        
        namespace gui {
            
            class Gui;
            class BoolButton;
            class ColorPicker;
            class ComboBox;
            class Content;
            class FPSCounter;
            class QuadWarp;
            class Slider2d;
            class SliderInt;
            class SliderFloat;
            class BoolTitle;
            class BoolToggle;
            
            class Panel : public ControlParameterT<ParameterGroup> {
            public:
                
                friend class Gui;
                
                Panel(Panel *parent, Parameter *p);
                ~Panel();
                
                void predraw();
                void draw();
                
                void setActiveControl(Control *control);
                void releaseActiveControl();
                
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
                bool isOpen;
                float heightScale;
                
                float getHeightScale();
                
                
                struct Layout {
                    // for auto-layout
                    ofRectangle   maxRect;
                    ofVec2f       curPos;
                    
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
                
                
                vector<ControlPtr>	controls;
                vector<Control*> controlsToDraw;    // this contains the controls to be drawn, sorted on control.z
                
                //some controls can take over focus (e.g. combo box,) which means events should only be passed to them
                Control*			activeControl;
                
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
                BoolTitle		&addTitle(Parameter *p, float height = 0);
                BoolToggle		&addToggle(Parameter *p);
            };
            
            typedef std::tr1::shared_ptr<Panel> PanelPtr;
            
        }
    }
}