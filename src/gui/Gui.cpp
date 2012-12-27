#include "ofxMSAControlFreak/src/gui/Gui.h"
#include "ofxMSAControlFreak/src/gui/Includes.h"



namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //            Gui gui;
            
            //--------------------------------------------------------------
            Gui::Gui() {
                isSetup         = false;
                doDefaultKeys   = false;
//                headerPage      = NULL;
                titleButton		= NULL;
                eventsAreRegistered = false;
            }
            
            //--------------------------------------------------------------
            void Gui::setup() {
                isSetup = true;
                
                //                doSave              = false;
                changePage          = false;
                
                //                headerPage          = &addPage("Header");
                //                headerPage->maxRect.set(config.padding.x, config.padding.y, 0, config.buttonHeight + config.padding.y);
                //                titleButton         = &headerPage->addButton("title", changePage);
                //
                //                headerPage->addToggle("Auto Save", doAutoSave);
                //                headerPage->addButton("Save Settings", doSave);
                //                headerPage->addFPSCounter();
                
                addPage();
                //                setAutoSave(true);
                setAlignRight(false);
                setDraw(false);
                setPage(0);
                autoHeight();
                
                ofAddListener(ofEvents().keyPressed, this, &Gui::keyPressed);
            }
            
            //--------------------------------------------------------------
            void Gui::setForceHeight(int h) {
                forceHeight = h;
            }
            
            //--------------------------------------------------------------
            void Gui::autoHeight() {
                forceHeight = 0;
            }
            
            
            //--------------------------------------------------------------
            void Gui::addListeners() {
                if(!eventsAreRegistered) {
                    eventsAreRegistered = true;
                    //	ofAddListener(ofEvents().setup, this, &Gui::setup);
                    ofAddListener(ofEvents().update, this, &Gui::update);
                    ofAddListener(ofEvents().draw, this, &Gui::draw);
                    //	ofAddListener(ofEvents().exit, this, &Gui::exit);
                    
                    ofAddListener(ofEvents().mousePressed, this, &Gui::mousePressed);
                    ofAddListener(ofEvents().mouseMoved, this, &Gui::mouseMoved);
                    ofAddListener(ofEvents().mouseDragged, this, &Gui::mouseDragged);
                    ofAddListener(ofEvents().mouseReleased, this, &Gui::mouseReleased);
                    
                    //	ofAddListener(ofEvents().keyPressed, this, &Gui::keyPressed);
                    ofAddListener(ofEvents().keyReleased, this, &Gui::keyReleased);
                }
            }
            
            
            //--------------------------------------------------------------
            void Gui::removeListeners() {
                if(eventsAreRegistered) {
                    eventsAreRegistered = false;
                    //	ofRemoveListener(ofEvents().setup, this, &Gui::setup);
                    ofRemoveListener(ofEvents().update, this, &Gui::update);
                    ofRemoveListener(ofEvents().draw, this, &Gui::draw);
                    //	ofRemoveListener(ofEvents().exit, this, &Gui::exit);
                    
                    ofRemoveListener(ofEvents().mousePressed, this, &Gui::mousePressed);
                    ofRemoveListener(ofEvents().mouseMoved, this, &Gui::mouseMoved);
                    ofRemoveListener(ofEvents().mouseDragged, this, &Gui::mouseDragged);
                    ofRemoveListener(ofEvents().mouseReleased, this, &Gui::mouseReleased);
                    
                    //	ofRemoveListener(ofEvents().keyPressed, this, &Gui::keyPressed);
                    ofRemoveListener(ofEvents().keyReleased, this, &Gui::keyReleased);
                }
            }
            
            //--------------------------------------------------------------
            void Gui::setDraw(bool b) {
                doDraw = b;
                if(doDraw) addListeners();
                else removeListeners();
                //                if(doAutoSave) saveXml();
            }
            
            //--------------------------------------------------------------
            void Gui::show() {
                setDraw(true);
            }
            
            //--------------------------------------------------------------
            void Gui::hide() {
                setDraw(false);
            }
            
            //--------------------------------------------------------------
            void Gui::toggleDraw() {
                setDraw(!doDraw);
            }
            
            //--------------------------------------------------------------
            bool Gui::isOn() {
                return doDraw;
            }
            
            
            //--------------------------------------------------------------
            //            void Gui::setAutoSave(bool b) {
            //                doAutoSave = b;
            //            }
            //
            
            //--------------------------------------------------------------
            //            void Gui::loadXml() {
            //                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Gui::readFromXml");// + file);
            //
            //                for(int i=1; i < pages.size(); i++) {
            //                    pages[i]->loadXml();
            //                }
            //
            //                setPage(1);
            //            }
            
            
            //--------------------------------------------------------------
            //            void Gui::saveXml() {
            //                doSave = false;
            //
            //                for(int i=1; i < pages.size(); i++) {
            //                    pages[i]->saveXml();
            //                }
            //
            //                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Gui::writeToXml");
            //            }
            
            
            //--------------------------------------------------------------
            void Gui::setAlignRight(bool b) {
                alignRight = b;
            }
            
            //--------------------------------------------------------------
            void Gui::setDefaultKeys(bool b) {
                doDefaultKeys = b;
            }
            
            
            //--------------------------------------------------------------
            void Gui::drawFocus(float x, float y) {
                glPushMatrix();
                glTranslatef(x, y, 0);
                ofFill();
                //	ofSetHexColor(config.focusColor.r, config.focusColor.g, config.focusColor.b, 200);
                ofRect(0, 0, 10, 10);
                glPopMatrix();
            }
            
            
            //--------------------------------------------------------------
            void Gui::nextPage() {
                setPage(currentPageIndex + 1);
            }
            
            //--------------------------------------------------------------
            void Gui::prevPage() {
                setPage(currentPageIndex - 1);
            }
            
            //--------------------------------------------------------------
            void Gui::nextPageWithBlank() {
                if(doDraw) {
                    setPage(currentPageIndex + 1);
                    if(currentPageIndex == 1) setDraw(false);
                } else {
                    setDraw(true);
                    setPage(1);
                }
            }
            
            
            
            //--------------------------------------------------------------
            void Gui::setPage(int i) {
                currentPageIndex = i;
                if(currentPageIndex >= pages.size()) currentPageIndex = 1;
                else if(currentPageIndex < 1) currentPageIndex = pages.size()-1;
                
                //                if(titleButton) titleButton->setName(ofToString(currentPageIndex) + ": " + pages[currentPageIndex]->name);
                if(titleButton) titleButton->getParameter()->setName(ofToString(currentPageIndex) + ": " + pages[currentPageIndex]->parameter->getName());
            }
            
            
            //--------------------------------------------------------------
            void Gui::setPage(string name) {
                //	Panel *page;
                //                for(int i=1; i < pages.size(); i++) {
                //                    if(name.compare(pages[i]->name) == 0) {
                //                        setPage(i);
                //                        break;
                //                    }
                //                }
            }
            
            
            //--------------------------------------------------------------
            Panel& Gui::page(int i) {
                if(!isSetup) setup();
                return *pages.at(i);
            }
            
            //--------------------------------------------------------------
            Panel& Gui::page(string name) {
                if(!isSetup) setup();
                for(int i=1; i<pages.size(); i++) if(name.compare(pages[i]->parameter->getName()) == 0) return *pages[i];
            }
            
            
            //--------------------------------------------------------------
            Panel& Gui::currentPage() {
                return page(currentPageIndex);
            }
            
            //--------------------------------------------------------------
//            vector <Panel*>&	Gui::getPages() {
//                return pages;
//            }
            
            
            //--------------------------------------------------------------
            Panel& Gui::addPage(string name) {
                if(!isSetup) setup();
                
                paramsRoot.startGroup(name);
                
                Panel *newPage = new Panel(NULL, &paramsRoot.getParameter(name));//ofToString(pages.size(), 0) + ": " + name);
                newPage->setConfig(&config);
                pages.push_back(std::tr1::shared_ptr<Panel>(newPage));
                //                if(name == "") newPage->setName("SETTINGS");
                //                static bool b;
                //	if(pages.size() > 1) headerPage->addTitle(newPage->name);		// if this isn't the first page, add to header
                //	if(pages.size() > 1) newPage->addTitle(newPage->name);		// if this isn't the first page, add to header
                setPage(pages.size() - 1);
                return *newPage;
            }
            
            
            //--------------------------------------------------------------
            void Gui::addParameters(ParameterGroup &parameters) {
                if(!isSetup) setup();
                currentPage().addParameters(parameters);
            }
            
            
            //--------------------------------------------------------------
            void Gui::enableAutoEvents() {
                doAutoEvents = true;
                setDraw(doDraw); // add or remove listeners
            }
            
            //--------------------------------------------------------------
            void Gui::disableAutoEvents() {
                doAutoEvents = false;
                removeListeners();
            }
            
            //--------------------------------------------------------------
            bool Gui::getAutoEvents() {
                return doAutoEvents;
            }
            
            
            //--------------------------------------------------------------
            //void Gui::setup(ofEventArgs& e) {
            void Gui::update(ofEventArgs& e) {
                if(!isSetup) setup();
                
                if(changePage) {
                    nextPage();
                    changePage = false;
                }
                
//                headerPage->_update(e);
                //                if(forceHeight) {
                //                    pages[currentPageIndex]->height = forceHeight;
                //                } else {
                //                    pages[currentPageIndex]->height = ofGetHeight();
                //                }
                pages[currentPageIndex]->_update(e);
                
                
                //	if(doSaveBackup) doSave = true;
                
                //                if(doSave) saveXml();
            }
            
            //--------------------------------------------------------------
            void Gui::draw(ofEventArgs& e) {
                if(!doDraw) return;
                
                ofPushStyle();
                glDisable(GL_DEPTH_TEST);
                ofSetLineWidth(3);
                glDisableClientState(GL_COLOR_ARRAY);
                
//                headerPage->draw(0, 0);		// this is the header
//                pages[currentPageIndex]->maxRect.set(config.padding.x, headerPage->height + config.padding.y, 0, 0);
//                pages[currentPageIndex]->draw(config.padding.x, headerPage->height + config.padding.y);
                if(pages[currentPageIndex]->layout == NULL) pages[currentPageIndex]->layout = Panel::LayoutPtr(new Panel::Layout);
                
                pages[currentPageIndex]->layout->maxRect.set(config.padding.x, config.padding.y, 0, 0);
                pages[currentPageIndex]->setPosition(config.padding.x, config.padding.y);
                pages[currentPageIndex]->predraw();
                pages[currentPageIndex]->draw();
                
                ofPopStyle();
            }
            
            //--------------------------------------------------------------
            void Gui::mouseMoved(ofMouseEventArgs& e) {
//                headerPage->_mouseMoved(e);
                pages[currentPageIndex]->_mouseMoved(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mousePressed(ofMouseEventArgs& e) {
//                headerPage->_mousePressed(e);
                pages[currentPageIndex]->_mousePressed(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mouseDragged(ofMouseEventArgs& e) {
//                headerPage->_mouseDragged(e);
                pages[currentPageIndex]->_mouseDragged(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mouseReleased(ofMouseEventArgs& e) {
//                headerPage->_mouseReleased(e);
                pages[currentPageIndex]->_mouseReleased(e);
                //	if(doAutoSave) doSave = true;
                //                if(doAutoSave) saveXml();
            }
            
            //--------------------------------------------------------------
            void Gui::keyPressed(ofKeyEventArgs& e) {
                if(doDefaultKeys) {
                    if(e.key == ' ') {
                        toggleDraw();
                    } else if(e.key>='0' && e.key<='9') {
                        setPage((int)(e.key - '0'));
                        setDraw(true);
                    } else if(doDraw) {
                        switch(e.key) {
                            case '[': prevPage(); break;
                            case ']': nextPage(); break;
                        }
                    }
                }
                
                if(doDraw) {
//                    headerPage->_keyPressed(e);
                    pages[currentPageIndex]->_keyPressed(e);
                }
                
            }
            
            //--------------------------------------------------------------
            void Gui::keyReleased(ofKeyEventArgs& e) {
//                headerPage->_keyReleased(e);
                pages[currentPageIndex]->_keyReleased(e);
            }
            
            
        }
    }
}
