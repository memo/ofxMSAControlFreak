#include  "ofxMSAControlFreak/src/gui/Page.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            Page::Page(string name) : Control(name) {
                disableAllEvents();
                width = 0;
                height = ofGetHeight();
                eventStealingControl = NULL;
                setXMLName(name + "_settings.xml");
            }
            
            Page::~Page() {
                // delete all controls
            }
            
            
            Page& Page::setXMLName(string s) {
                xmlFilename = s;
                return *this;
            }
            
            
            void Page::loadXml() {
                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Page::loadXml: " + xmlFilename);
                
                if(xmlFilename.compare("") == 0) return;
                
                if(XML.loadFile(xmlFilename) == false) {
                    ofLog(OF_LOG_ERROR, "Error loading xmlFilename: " + xmlFilename);
                    return;
                }
                
                XML.pushTag("controls");
                for(int i=0; i < controls.size(); i++) {
                    controls[i]->readFromXml(XML);
                }
                XML.popTag();
            }
            
            
            void Page::saveXml() {
                if(controls.size() <= 1 || xmlFilename.compare("") == 0) return;	// if it has no controls (title counts as one control)
                
                XML.clear();	// clear cause we are building a new xml file
                
                XML.addTag("controls");
                XML.pushTag("controls");
                for(int i=0; i < controls.size(); i++) {
                    controls[i]->writeToXml(XML);
                }
                XML.popTag();
                
                XML.saveFile(xmlFilename);
                //	if(doSaveBackup)
                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Page::saveXml: " + xmlFilename + " " + ofToString(controls.size(), 0) + " items");
            }
            
            
            float Page::getNextY(float y) {
                return y;
                int iy = (int)ceil(y/config->gridSize.y);
                return (iy) * config->gridSize.y;
            }
            
            
            void Page::draw(float x, float y, bool alignRight) {
                setPos(x += config->offset.x, y += config->offset.y);
                if(alignRight) x = ofGetWidth() - x -  config->gridSize.x;
                
                float posX		= 0;
                float posY		= 0;
                float stealingX = 0;
                float stealingY = 0;
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                
                for(int i=0; i<controls.size(); i++) {
                    Control& control = *controls[i];
                    
                    if(control.newColumn) {
                        if(alignRight) posX -= config->gridSize.x;
                        else posX += config->gridSize.x;
                        posY = 0;
                    }
                    
                    float controlX = posX + x;
                    float controlY = posY + y;
                    
                    //we don't draw the event stealing controls until the end because they can expand and overlap with other controls (e.g. combo box)
                    if(eventStealingControl == &control) {
                        stealingX = controlX;
                        stealingY = controlY;
                    } else {
                        //			printf("drawing control: %s %s\n", control.controlType.c_str(), control.name.c_str());
                        control.draw(controlX, controlY);
                    }
                    
                    if(control.hasTitle) {
                        ofNoFill();
                        ofSetHexColor(config->borderColor);
                        glLineWidth(0.5f);
                        ofRect(controlX, controlY, control.width, control.height);
                    }
                    posY = getNextY(posY + control.height + config->padding.y);
                    
                    if(posY + y >= height - control.height - config->padding.y) {
                        if(alignRight) posX -= config->gridSize.x;
                        else posX += config->gridSize.x;
                        posY = 0;
                    }
                    
                    //		if(guiFocus == controls[i]->guiID) controls[i]->focused = true;		// MEMO
                    //		else							   controls[i]->focused = false;
                }
                //event stealing controls get drawn on top
                if(eventStealingControl) {
                    eventStealingControl->draw(stealingX, stealingY);
                    if(eventStealingControl->hasTitle) {
                        ofNoFill();
                        ofSetHexColor(config->borderColor);
                        glLineWidth(0.5f);
                        ofRect(stealingX, stealingY, eventStealingControl->width, eventStealingControl->height);
                    }
                }
            }
            
            
            Control& Page::addControl(Control& control) {
                controls.push_back(&control);
                width += control.width + config->padding.x;
                return control;
            }
            
            Button& Page::addButton(string name, bool& value) {
                return (Button&)addControl(* new Button(name, value));
            }
            
            Content& Page::addContent(string name, ofBaseDraws& content, float fixwidth) {
                if(fixwidth == -1) fixwidth = config->gridSize.x - config->padding.x;
                return (Content&)addControl(* new Content(name, content, fixwidth));
            }
            
            FPSCounter& Page::addFPSCounter() {
                return (FPSCounter&)addControl(* new FPSCounter());
            }
            
            QuadWarp& Page::addQuadWarper(string name, ofBaseDraws& baseDraw, ofPoint *pts) {
                return (QuadWarp&)addControl(* new QuadWarp(name, baseDraw, pts));
            }
            //
            //MovieSlider& Page::addMovieSlider(string name, ofVideoPlayer& input) {
            //	return (MovieSlider&)addControl(* new MovieSlider(name, input));
            //}
            
            SliderInt& Page::addSlider(string name, int& value, int min, int max) {
                return (SliderInt&)addControl(* new SliderInt(name, value, min, max));
            }
            
            SliderFloat& Page::addSlider(string name, float& value, float min, float max) {
                return (SliderFloat&)addControl(* new SliderFloat(name, value, min, max));
            }
            
            Slider2d& Page::addSlider2d(string name, ofPoint& value, float xmin, float xmax, float ymin, float ymax) {
                return (Slider2d&)addControl(* new Slider2d(name, value, xmin, xmax, ymin, ymax));
            }
            
            Title& Page::addTitle(string name, float height) {
                return (Title&)addControl(* new Title(name, height));
            }
            
            Toggle& Page::addToggle(string name, bool& value) {
                return (Toggle&)addControl(* new Toggle(name, value));
            }
            
            ColorPicker& Page::addColorPicker(string name, ofFloatColor& color) {
                return (ColorPicker&)addControl(* new ColorPicker(name, color));
            }
            
            
            ComboBox& Page::addComboBox(string name, int& value, int numChoices, string* choiceTitles) {
                return (ComboBox&)addControl(* new ComboBox(name, value, numChoices, this, choiceTitles));
            }
            
            ComboBox& Page::addComboBox(string name, int& value, vector<string>& choiceTitles) {
                return (ComboBox&)addComboBox(name, value, choiceTitles.size(), &choiceTitles[0]);
            }

            
            
            void Page::update(ofEventArgs& e) {
                for(int i=0; i<controls.size(); i++) controls[i]->update();
            }
            
            void Page::SetEventStealingControl(Control& control) {
                eventStealingControl = &control;
            }
            void Page::ReleaseEventStealingControl() {
                eventStealingControl = NULL;
            }
            
            void Page::mouseMoved(ofMouseEventArgs& e) {
                if(eventStealingControl)
                    eventStealingControl->_mouseMoved(e);
                else
                    for(int i=0; i<controls.size(); i++) controls[i]->_mouseMoved(e);
            }
            
            void Page::mousePressed(ofMouseEventArgs& e) {
                if(eventStealingControl)
                    eventStealingControl->_mousePressed(e);
                else
                    for(int i=0; i<controls.size(); i++) controls[i]->_mousePressed(e);
            }
            
            void Page::mouseDragged(ofMouseEventArgs& e) {
                if(eventStealingControl)
                    eventStealingControl->_mouseDragged(e);
                else
                    for(int i=0; i<controls.size(); i++) controls[i]->_mouseDragged(e);
            }
            
            void Page::mouseReleased(ofMouseEventArgs& e) {
                if(eventStealingControl)
                    eventStealingControl->_mouseReleased(e);
                else
                    for(int i=0; i<controls.size(); i++) controls[i]->_mouseReleased(e);
            }
            
            void Page::keyPressed(ofKeyEventArgs& e) {
                bool keyUp		= e.key == OF_KEY_UP;
                bool keyDown	= e.key == OF_KEY_DOWN;
                bool keyLeft	= e.key == OF_KEY_LEFT;
                bool keyRight	= e.key == OF_KEY_RIGHT;
                bool keyEnter	= e.key == OF_KEY_RETURN;
                
                for(int i=0; i<controls.size(); i++) {
                    Control *c = controls[i];
                    if(c->isMouseOver()) {
                        if(keyUp)		c->onKeyUp();
                        if(keyDown)		c->onKeyDown();
                        if(keyLeft)		c->onKeyLeft();
                        if(keyRight)	c->onKeyRight();
                        if(keyEnter)	c->onKeyEnter();
                        c->_keyPressed(e);
                    }
                }
            }
            
            void Page::keyReleased(ofKeyEventArgs& e) {
                for(int i=0; i<controls.size(); i++) if(controls[i]->isMouseOver()) controls[i]->_keyReleased(e);
            }
            
            
            vector <Control*>&	Page::getControls() {
                return controls;
            }
            
        }
    }
}
