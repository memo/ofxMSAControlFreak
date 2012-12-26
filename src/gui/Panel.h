#pragma once

#include "ofxMSAControlFreak/src/gui/Control.h"

namespace msa {
    namespace ControlFreak {
        
        class Parameter;
        class ParameterGroup;
        
        namespace gui {
            
            class Gui;
            class Control;
            class Button;
            class ColorPicker;
            class ComboBox;
            class Content;
            class FPSCounter;
            class QuadWarp;
            class Slider2d;
            class SliderInt;
            class SliderFloat;
            class Title;
            class Toggle;
            
            class Panel : public Control {
            public:
                
                friend class Gui;
                
                Panel(Panel *parent, string name);
                ~Panel();
                
                void draw(float x, float y);
                
                Panel& setXMLName(string xmlFilename);
                void loadXml();
                void saveXml();
                
                
                void setActiveControl(Control *control);
                void releaseActiveControl();
                
                void update();
                void mouseMoved(ofMouseEventArgs &e);
                void mousePressed(ofMouseEventArgs &e);
                void mouseDragged(ofMouseEventArgs &e);
                void mouseReleased(ofMouseEventArgs &e);
                void keyPressed(ofKeyEventArgs &e);
                void keyReleased(ofKeyEventArgs &e);
                
                vector <Control*>&	getControls();
                
                void addParameter(Parameter &parameter);
                void addParameters(ParameterGroup &parameters);
                
            protected:
                bool isOpen;
                float heightScale;
                
                float getHeightScale();
                
                ofRectangle   maxRect;
                vector <Control*>	controls;
                
                //some controls can take over focus (e.g. combo box,) which means events should only be passed to them
                Control*			activeControl;
                float getNextY(float y);
                
                Control			&addControl(Control *control);
                
                Panel           &addPanel(string name);
                Button			&addButton(string name, bool &value);
                ColorPicker		&addColorPicker(string name, ofFloatColor &color);
                ComboBox&       addComboBox(string name, int &value, int numChoices, string *choiceTitles);
                ComboBox&       addComboBox(string name, int &value, vector<string> &choiceTitles);
                Content			&addContent(string name, ofBaseDraws &content, float fixwidth = -1);
                FPSCounter		&addFPSCounter();
                QuadWarp		&addQuadWarper(string name, ofBaseDraws &baseDraw, ofPoint *pts);
                Slider2d		&addSlider2d(string name, ofPoint &value, float xmin, float xmax, float ymin, float ymax);
                SliderInt		&addSlider(string name, int &value, int min, int max);
                SliderFloat		&addSlider(string name, float &value, float min, float max);
                Title			&addTitle(string name="", float height = 0);
                Toggle			&addToggle(string name, bool &value);

                ofxXmlSettings					XML;
                string							xmlFilename;
            };
            
        }
    }
}