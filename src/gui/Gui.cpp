#include  "ofxMSAControlFreak/src/gui/Gui.h"
#include  "ofxMSAControlFreak/src/gui/Includes.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            Gui gui;
            
            //--------------------------------------------------------------
            Gui::Gui() {
                config          = NULL;
                doDefaultKeys   = false;
                headerPage      = NULL;
                titleButton		= NULL;
                eventsAreRegistered = false;
            }
            
            //--------------------------------------------------------------
            void Gui::setup() {
                config              = &defaultSimpleGuiConfig;
                
                doSave              = false;
                changePage          = false;
                
                headerPage          = &addPage("Header");
                headerPage->height  = config->buttonHeight * 2;
                headerPage->width   = 0;
                titleButton         = &headerPage->addButton("title", changePage);
                
                headerPage->addToggle("Auto Save", doAutoSave);
                headerPage->addButton("Save Settings", doSave);
                headerPage->addFPSCounter();
                
                addPage();
                setAutoSave(true);
                setAlignRight(false);
                setDraw(false);
                setPage(1);
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
                if(doAutoSave) saveXml();
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
            void Gui::setAutoSave(bool b) {
                doAutoSave = b;
            }
            
            
            //--------------------------------------------------------------
            void Gui::loadXml() {
                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Gui::readFromXml");// + file);
                
                for(int i=1; i < pages.size(); i++) {
                    pages[i]->loadXml();
                }
                
                setPage(1);
            }
            
            
            //--------------------------------------------------------------
            void Gui::saveXml() {
                doSave = false;
                
                for(int i=1; i < pages.size(); i++) {
                    pages[i]->saveXml();
                }
                
                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Gui::writeToXml");
            }
            
            
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
                //	ofSetHexColor(config->focusColor.r, config->focusColor.g, config->focusColor.b, 200);
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
                
                if(titleButton) titleButton->setName(ofToString(currentPageIndex) + ": " + pages[currentPageIndex]->name);
            }
            
            
            //--------------------------------------------------------------
            void Gui::setPage(string name) {
                //	Page *page;
                for(int i=1; i < pages.size(); i++) {
                    if(name.compare(pages[i]->name) == 0) {
                        setPage(i);
                        break;
                    }
                }
            }
            
            
            //--------------------------------------------------------------
            Page& Gui::page(int i) {
                if(!config) setup();
                return *pages.at(i);
            }
            
            //--------------------------------------------------------------
            Page& Gui::page(string name) {
                if(!config) setup();
                for(int i=1; i<pages.size(); i++) if(name.compare(pages[i]->name) == 0) return *pages[i];
            }
            
            
            //--------------------------------------------------------------
            Page& Gui::currentPage() {
                return page(currentPageIndex);
            }
            
            //--------------------------------------------------------------
            vector <Page*>&	Gui::getPages() {
                return pages;
            }
            
            
            
            //--------------------------------------------------------------
            Page& Gui::addPage(string name) {
                if(!config) setup();
                
                Page *newPage = new Page(NULL, name);//ofToString(pages.size(), 0) + ": " + name);
                pages.push_back(newPage);
                if(name == "") newPage->setName("SETTINGS");
                static bool b;
                //	if(pages.size() > 1) headerPage->addTitle(newPage->name);		// if this isn't the first page, add to header
                //	if(pages.size() > 1) newPage->addTitle(newPage->name);		// if this isn't the first page, add to header
                setPage(pages.size() - 1);
                return *newPage;
            }
            
            
            //            //--------------------------------------------------------------
            //            Control& Gui::control(string name) {
            //                for(int i = 0; i < pages.size(); i++) {
            //                    for(int j = 0; j < pages[i]->getControls().size(); j++) {
            //                        if(name==pages[i]->getControls()[j]->name) {
            //                            return *pages[i]->getControls()[j];
            //                        }
            //                    }
            //                }
            //                //	return NULL;
            //            }
            //
            //
            //            //--------------------------------------------------------------
            //            Control& Gui::addControl(Control& control) {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addControl(control);
            //            }
            //
            //            //--------------------------------------------------------------
            //            Button& Gui::addButton(string name, bool& value) {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addButton(name, value);
            //            }
            //
            //            //--------------------------------------------------------------
            //            Content& Gui::addContent(string name, ofBaseDraws& content, float fixwidth) {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addContent(name, content, fixwidth);
            //            }
            //
            //            //--------------------------------------------------------------
            //            FPSCounter& Gui::addFPSCounter() {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addFPSCounter();
            //            }
            //
            //            //--------------------------------------------------------------
            //            QuadWarp& Gui::addQuadWarper(string name, ofBaseDraws& baseDraw, ofPoint *pts) {
            //                return pages[currentPageIndex]->addQuadWarper(name, baseDraw, pts);
            //            }
            //            //
            //            //MovieSlider& Gui::addMovieSlider(string name, ofVideoPlayer& input) {
            //            //	return pages[currentPageIndex]->addMovieSlider(name, input);
            //            //}
            //
            //            //--------------------------------------------------------------
            //            SliderInt& Gui::addSlider(string name, int& value, int min, int max) {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addSlider(name, value, min, max);
            //            }
            //
            //            //--------------------------------------------------------------
            //            SliderFloat& Gui::addSlider(string name, float& value, float min, float max) {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addSlider(name, value, min, max);
            //            }
            //
            //            //--------------------------------------------------------------
            //            Slider2d& Gui::addSlider2d(string name, ofPoint& value, float xmin, float xmax, float ymin, float ymax) {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addSlider2d(name, value, xmin, xmax, ymin, ymax);
            //            }
            //
            //            //--------------------------------------------------------------
            //            Title& Gui::addTitle(string name, float height) {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addTitle(name, height);
            //            }
            //
            //            //--------------------------------------------------------------
            //            Toggle& Gui::addToggle(string name, bool& value) {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addToggle(name, value);
            //            }
            //
            //
            //            //--------------------------------------------------------------
            //            ColorPicker& Gui::addColorPicker(string name, ofFloatColor& color) {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addColorPicker(name, color);
            //            }
            //
            //
            //            //--------------------------------------------------------------
            //            ComboBox& Gui::addComboBox(string name, int& value, int numChoices, string* choiceTitles)  {
            //                if(!config) setup();
            //                return pages[currentPageIndex]->addComboBox(name, value, numChoices, choiceTitles);
            //            }
            //
            //            //--------------------------------------------------------------
            //            ComboBox& Gui::addComboBox(string name, int& value, vector<string>& choiceTitles) {
            //                return addComboBox(name, value, choiceTitles.size(), &choiceTitles[0]);
            //            }
            //
            
            
            //--------------------------------------------------------------
            Gui& Gui::addParameter(Parameter& parameter) {
                // if parameter already exists, remove it first
                
                ParameterContainer *pc = dynamic_cast<ParameterContainer*>(&parameter);
                if(pc && pc->getNumParams() > 0) addParameters(*pc);
                
                switch(parameter.getType()) {
                    case Type::kFloat: {
                        ParameterFloat &p = (ParameterFloat&)parameter;
                        currentPage().addSlider(p.getName(), p.getValue(), p.getMin(), p.getMax()).setIncrement(p.getIncrement());
                    }
                        break;
                        
                    case Type::kInt: {
                        ParameterInt &p = (ParameterInt&)parameter;
                        currentPage().addSlider(p.getName(), p.getValue(), p.getMin(), p.getMax()).setIncrement(p.getIncrement());
                    }
                        break;
                        
                    case Type::kToggle: {
                        ParameterBool &p = (ParameterBool&)parameter;
                        currentPage().addToggle(p.getName(), p.getValue());
                    }
                        break;
                        
                    case Type::kBang: {
                        ParameterBool &p = (ParameterBool&)parameter;
                        currentPage().addButton(p.getName(), p.getValue());
                    }
                        break;
                        
                    case Type::kNamedIndex: {
                        ParameterNamedIndex &p = (ParameterNamedIndex&)parameter;
                        currentPage().addComboBox(p.getName(), p.getValue(), p.getLabels());
                    }
                        break;
                        
                    default:
                        ofLogWarning() << "msa::ControlFreak::Gui::addParameter - unknown type adding parameter " << parameter.getPath() << " " << parameter.getTypeName();
                        break;
                }
            }
            
            //--------------------------------------------------------------
            Gui& Gui::addParameters(ParameterContainer& parameters) {
                if(!config) setup();
                
                currentPage().addTitle(parameters.getName());
                int np = parameters.getNumParams();
                for(int i=0; i<np; i++) {
                    addParameter(parameters.getParameter(i));
                }
                currentPage().addTitle("");
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
                if(!config) setup();
                
                if(changePage) {
                    nextPage();
                    changePage = false;
                }
                
                headerPage->update(e);
                if(forceHeight) {
                    pages[currentPageIndex]->height = forceHeight;
                } else {
                    pages[currentPageIndex]->height = ofGetHeight();
                }
                pages[currentPageIndex]->update(e);
                
                
                //	if(doSaveBackup) doSave = true;
                
                if(doSave) saveXml();
            }
            
            //--------------------------------------------------------------
            void Gui::draw(ofEventArgs& e) {
                if(!doDraw) return;
                
                ofPushStyle();
                glDisable(GL_DEPTH_TEST);
                ofSetLineWidth(3);
                glDisableClientState(GL_COLOR_ARRAY);
                
                headerPage->draw(0, 0, alignRight);		// this is the header
                ofSetHexColor(config->borderColor);
                if(alignRight) ofLine(ofGetWidth() - headerPage->width, headerPage->height, headerPage->width, headerPage->height);
                else ofLine(0, headerPage->height, headerPage->width, headerPage->height);
                pages[currentPageIndex]->draw(0.0f, headerPage->height, alignRight);
                
                ofPopStyle();
            }
            
            //--------------------------------------------------------------
            void Gui::mouseMoved(ofMouseEventArgs& e) {
                headerPage->mouseMoved(e);
                pages[currentPageIndex]->mouseMoved(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mousePressed(ofMouseEventArgs& e) {
                headerPage->mousePressed(e);
                pages[currentPageIndex]->mousePressed(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mouseDragged(ofMouseEventArgs& e) {
                headerPage->mouseDragged(e);
                pages[currentPageIndex]->mouseDragged(e);
            }
            
            //--------------------------------------------------------------
            void Gui::mouseReleased(ofMouseEventArgs& e) {
                headerPage->mouseReleased(e);
                pages[currentPageIndex]->mouseReleased(e);
                //	if(doAutoSave) doSave = true;
                if(doAutoSave) saveXml();
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
                    headerPage->keyPressed(e);
                    pages[currentPageIndex]->keyPressed(e);
                }
                
            }
            
            //--------------------------------------------------------------
            void Gui::keyReleased(ofKeyEventArgs& e) {
                headerPage->keyReleased(e);
                pages[currentPageIndex]->keyReleased(e);
            }
            
            
        }
    }
}
