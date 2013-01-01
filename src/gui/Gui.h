

#pragma once

#include "ofMain.h"
//#include "ofxXmlSettings.h"

#include "ofxMSAControlFreak/src/gui/Config.h"
#include "ofxMSAControlFreak/src/gui/Panel.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"


namespace msa {
    namespace ControlFreak {

        namespace gui {
            
            class BoolButton;
            class Config;
            
            class Gui {
            public:
                Config config;
                
                Gui();
                
                void setup();
                
//                void loadXml();
//                void saveXml();
//                void setAutoSave(bool b);
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
                
                Panel& page(int i);				// 1 based index of page
                Panel& page(string name);			// returns page by name
                Panel& currentPage();				// returns current page
//                vector <Panel*>&	getPages();
                
                Panel& addPage(string name = "");
                
                void addParameters(ParameterGroup &parameters);
                

                //--------------------------------------------------------------
                // ADVANCED FUNCTIONS
                
                // by default all gui events are managed automatically (registered when gui is visible, de-registered when gui is not visible)
                // over that behaviour with these
                void enableAutoEvents();
                void disableAutoEvents();
                bool getAutoEvents();
                
                
                // by default these are called automatically so you don't need to call them
                // however if you've disabled AutoEvents, then you need to call them manually from your app. IMPORTANT!
                void update(ofEventArgs& e);
                void draw(ofEventArgs& e);
                void mouseMoved(ofMouseEventArgs& e);
                void mousePressed(ofMouseEventArgs& e);
                void mouseDragged(ofMouseEventArgs& e);
                void mouseReleased(ofMouseEventArgs& e);
                void keyPressed(ofKeyEventArgs& e);
                void keyReleased(ofKeyEventArgs& e);

                
            protected:
                bool        isSetup;
                bool        doAutoEvents;
                bool        eventsAreRegistered;

                bool		doAutoSave;
                
                bool		alignRight;
                bool		doDefaultKeys;
//                bool		doSave;//, doSaveBackup;
                bool		changePage;
                int			forceHeight;
                int			currentPageIndex;			// 1 based index of page (0 is for global controls)
                
                bool		doDraw;
                float		border;
                
                BoolButton				*titleButton;
                vector<PanelPtr>		pages;				// 0 is for headerPage
                
                void addListeners();
                void removeListeners();
                
                void drawFocus(float x, float y);
                
                ParameterGroup paramsRoot;
            };
            
        }
    }
}

