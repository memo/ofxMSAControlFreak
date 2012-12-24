

#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"
#include "ofxMSAControlFreak/src/gui/Controls.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Gui {
            public:
                int guiFocus;
                
                Config *config;
                
                Gui();
                
                void setup();
                
                
                void loadXml();
                void saveXml();
                void setAutoSave(bool b);
                void setAlignRight(bool b);
                void setDefaultKeys(bool b);
                
                void setDraw(bool b);
                void toggleDraw();
                void show();		// simply calls setDraw(true);
                void hide();		// simply calls setDraw(false);
                bool isOn();
                
                void nextPage();
                void prevPage();
                void setPage(int i);				// 1 based index of page
                void setPage(string name);
                void setForceHeight(int h);
                void autoHeight();
                
                void nextPageWithBlank();		// cycles through pages, and closes after last page
                
                Page& page(int i);				// 1 based index of page
                Page& page(string name);			// returns page by name
                Page& currentPage();				// returns current page
                vector <Page*>&	getPages();
                
                Control& control(string name);		// returns control by name (on any page)
                
                Page& addPage(string name = "");
                
                Gui& addParameter(Parameter& parameter);
                Gui& addParameters(ParameterContainer& parameters);
                

                //--------------------------------------------------------------
                // ADVANCED FUNCTIONS
                
                // by default all gui events are managed automatically (registered when gui is visible, de-registered when gui is not visible)
                // over that behaviour with these
                void enableAutoEvents();
                void disableAutoEvents();
                bool getAutoEvents();
                
                // by default these are called automatically so you don't need to call them
                // if you've disabled AutoEvents, then you need to call them manually. IMPORTANT!
                void update(ofEventArgs& e);
                void draw(ofEventArgs& e);
                void mouseMoved(ofMouseEventArgs& e);
                void mousePressed(ofMouseEventArgs& e);
                void mouseDragged(ofMouseEventArgs& e);
                void mouseReleased(ofMouseEventArgs& e);
                void keyPressed(ofKeyEventArgs& e);
                void keyReleased(ofKeyEventArgs& e);

                
            protected:
                bool        doAutoEvents;
                bool        eventsAreRegistered;

                bool		doAutoSave;
                
                bool		alignRight;
                bool		doDefaultKeys;
                bool		doSave;//, doSaveBackup;
                bool		changePage;
                int			forceHeight;
                int			currentPageIndex;			// 1 based index of page (0 is for global controls)
                
                bool		doDraw;
                float		border;
                
                Page				*headerPage;
                Button				*titleButton;
                vector <Page*>		pages;				// 0 is for headerPage
                
                void addListeners();
                void removeListeners();
                
                
                void drawFocus(float x, float y);
                
                
                
                
//                Control&        addControl(Control& control);
//                Content&        addContent(string name, ofBaseDraws& content, float fixwidth = -1);
//                Button&         addButton(string name, bool& value);
//                FPSCounter&     addFPSCounter();
//                QuadWarp&       addQuadWarper(string name, ofBaseDraws& baseDraw, ofPoint *pts);
//                SliderInt&      addSlider(string name, int& value, int min, int max);
//                SliderFloat&    addSlider(string name, float& value, float min, float max);
//                Slider2d&       addSlider2d(string name, ofPoint& value, float xmin, float xmax, float ymin, float ymax);
//                Title&          addTitle(string name="", float height = 0);
//                Toggle&         addToggle(string name, bool& value);
//                ColorPicker&    addColorPicker(string name, ofFloatColor& color);
//                ComboBox&       addComboBox(string name, int& value, int numChoices, string* choiceTitles=NULL);
//                ComboBox&       addComboBox(string name, int& value, vector<string>& choiceTitles);
            };
            
            
            extern Gui gui;
            
        }
    }
}

