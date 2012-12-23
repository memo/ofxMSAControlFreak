#pragma once

#include  "ofxMSAControlFreak/src/gui/Controls.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui;
            
            class Page : public Control {
            public:
                
                friend class Gui;
                
                Page(string name);
                ~Page();
                
                void draw(float x, float y, bool alignRight);
                
                Page& setXMLName(string xmlFilename);
                void loadXml();
                void saveXml();
                
                
                void SetEventStealingControl(Control &control);
                void ReleaseEventStealingControl();
                
                void update(ofEventArgs &e);
                
                void mouseMoved(ofMouseEventArgs &e);
                void mousePressed(ofMouseEventArgs &e);
                void mouseDragged(ofMouseEventArgs &e);
                void mouseReleased(ofMouseEventArgs &e);
                
                void keyPressed(ofKeyEventArgs &e);
                void keyReleased(ofKeyEventArgs &e);
                
                
                vector <Control*>&	getControls();
                
                
            protected:
                vector <Control*>	controls;
                
                //some controls can take over focus (e.g. combo box,) which means events should only be passed to them
                Control*			eventStealingControl;
                float getNextY(float y);
                
                Control			&addControl(Control& control);
                Button			&addButton(string name, bool &value);
                Content			&addContent(string name, ofBaseDraws &content, float fixwidth = -1);
                FPSCounter		&addFPSCounter();
                QuadWarp		&addQuadWarper(string name, ofBaseDraws &baseDraw, ofPoint *pts);
                SliderInt		&addSlider(string name, int &value, int min, int max);
                SliderFloat		&addSlider(string name, float &value, float min, float max);
                Slider2d		&addSlider2d(string name, ofPoint& value, float xmin, float xmax, float ymin, float ymax);
                Title			&addTitle(string name="", float height = 0);
                Toggle			&addToggle(string name, bool &value);
                ColorPicker		&addColorPicker(string name, ofFloatColor& color);
                ComboBox&       addComboBox(string name, int& value, int numChoices, string* choiceTitles);
                ComboBox&       addComboBox(string name, int& value, vector<string>& choiceTitles);

                

                ofxXmlSettings					XML;
                string							xmlFilename;
            };
            
        }
    }
}