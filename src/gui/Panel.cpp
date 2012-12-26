#include  "ofxMSAControlFreak/src/gui/Includes.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            Panel::Panel(Panel *parent, string name) : Control(parent, name, "Panel") {
                disableAllEvents();
                width = 0;
                height = 0;//ofGetHeight();
                maxRect.set(0, 0, 0, 0);
                activeControl = NULL;
                setXMLName(name + "_settings.xml");
                
                isOpen = true;
                heightScale = 1.0;
            }
            
            //--------------------------------------------------------------
            Panel::~Panel() {
                // delete all controls
            }
            
            
            //--------------------------------------------------------------
            Panel& Panel::setXMLName(string s) {
                xmlFilename = s;
                return *this;
            }
            
            
            //--------------------------------------------------------------
            void Panel::loadXml() {
                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Panel::loadXml: " + xmlFilename);
                
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
            
            
            //--------------------------------------------------------------
            void Panel::saveXml() {
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
                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Panel::saveXml: " + xmlFilename + " " + ofToString(controls.size(), 0) + " items");
            }
            
            
            //--------------------------------------------------------------
            float Panel::getHeightScale() {
                return parent ? heightScale * parent->getHeightScale() : heightScale;
            }

            //--------------------------------------------------------------
            float Panel::getNextY(float y) {
                return y;
                int iy = (int)ceil(y/config->gridSize.y);
                return (iy) * config->gridSize.y;
            }
            
            
            //--------------------------------------------------------------
            void Panel::draw(float x, float y) {//, bool alignRight) {
                bool alignRight = false;
                
                if(isOpen) {
                    if(heightScale<0.98f) heightScale += (1-heightScale) * 0.2f;
                    else heightScale = 1.0f;
                } else {
                    if(heightScale > 0.02) heightScale += (0-heightScale) * 0.2;
                    else heightScale = 0.0f;
                }
                
                if(parent) maxRect = parent->maxRect;
                ofVec2f maxPos(maxRect.width ? maxRect.x + maxRect.width : ofGetWidth(), maxRect.height ? maxRect.y + maxRect.height : ofGetHeight());
                
                ofPushStyle();
                
                setPos(ofClamp(x, maxRect.getLeft(), maxPos.x), ofClamp(y, maxRect.getTop(), maxPos.y));
//                y += config->padding.y * 5;
                setSize(0, 0);
                
                ofVec2f curPos(x, y);
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                
                //                ofLogVerbose() << "\n\nDrawing : " << name << " " << maxY << " " << maxRect.x << " " <<maxRect.y << " " <<maxRect.width << " " <<maxRect.height;
                int numControls = getHeightScale() ? controls.size() : 1;
                
                for(int i=0; i<numControls; i++) {
                    Control& control = *controls[i];
                    
                    //                    ofLogVerbose() << control.name << " " << control.controlType;
                    
                    if(control.newColumn || curPos.y + (control.height + config->padding.y) * getHeightScale() > maxPos.y) {
                        curPos.x += config->gridSize.x;
                        curPos.y = maxRect.y;
                    }
                    
                    control.draw(curPos.x, curPos.y);
                    
                    curPos.y += (control.height + config->padding.y) * getHeightScale();
                    
                    if(control.hasTitle) {
                        ofNoFill();
                        ofSetHexColor(config->borderColor);
                        glLineWidth(1.0);
                        ofRect(curPos.x, curPos.y, control.width, control.height * getHeightScale());
                    }
                    
                    growToInclude((ofRectangle&)control);
                }
                
//                height += config->padding.y * 2;
                
                // draw panel title again so it's on top
                if(controls[0] && getHeightScale() < 0.9) controls[0]->draw();
                
                //event stealing controls get drawn on top
                if(activeControl) {
                    activeControl->draw();
                    if(activeControl->hasTitle) {
                        ofNoFill();
                        ofSetHexColor(config->borderColor);
                        ofSetLineWidth(1);
                        ofRect((ofRectangle&)*activeControl);//, stealingY, activeControl->width, activeControl->height);
                    }
                }
                
                
                ofNoFill();
                ofSetColor(128, 0, 0);
                ofSetLineWidth(1);
                ofRect(x, y, width, height);
                ofPopStyle();
//                height = 0;
            }
            
            
            //--------------------------------------------------------------
            Control& Panel::addControl(Control *control) {
                controls.push_back(control);
                //                width += control->width + config->padding.x;
                return *control;
            }
            
            //--------------------------------------------------------------
            Panel& Panel::addPanel(string name) {
                return (Panel&)addControl(new Panel(this, name));
            }
            
            //--------------------------------------------------------------
            Button& Panel::addButton(string name, bool &value) {
                return (Button&)addControl(new Button(this, name, value));
            }
            
            //--------------------------------------------------------------
            ColorPicker& Panel::addColorPicker(string name, ofFloatColor &color) {
                return (ColorPicker&)addControl(new ColorPicker(this, name, color));
            }
            
            //--------------------------------------------------------------
            ComboBox& Panel::addComboBox(string name, int &value, int numChoices, string* choiceTitles) {
                return (ComboBox&)addControl(new ComboBox(this, name, value, numChoices, choiceTitles));
            }
            
            //--------------------------------------------------------------
            ComboBox& Panel::addComboBox(string name, int &value, vector<string> &choiceTitles) {
                return (ComboBox&)addComboBox(name, value, choiceTitles.size(), &choiceTitles[0]);
            }
            
            //--------------------------------------------------------------
            Content& Panel::addContent(string name, ofBaseDraws &content, float fixwidth) {
                if(fixwidth == -1) fixwidth = config->gridSize.x - config->padding.x;
                return (Content&)addControl(new Content(this, name, content, fixwidth));
            }
            
            //--------------------------------------------------------------
            FPSCounter& Panel::addFPSCounter() {
                return (FPSCounter&)addControl(new FPSCounter(this));
            }
            
            //--------------------------------------------------------------
            QuadWarp& Panel::addQuadWarper(string name, ofBaseDraws &baseDraw, ofPoint *pts) {
                return (QuadWarp&)addControl(new QuadWarp(this, name, baseDraw, pts));
            }
            
            //--------------------------------------------------------------
            SliderInt& Panel::addSlider(string name, int &value, int min, int max) {
                return (SliderInt&)addControl(new SliderInt(this, name, value, min, max));
            }
            
            //--------------------------------------------------------------
            SliderFloat& Panel::addSlider(string name, float &value, float min, float max) {
                return (SliderFloat&)addControl(new SliderFloat(this, name, value, min, max));
            }
            
            //--------------------------------------------------------------
            Slider2d& Panel::addSlider2d(string name, ofPoint &value, float xmin, float xmax, float ymin, float ymax) {
                return (Slider2d&)addControl(new Slider2d(this, name, value, xmin, xmax, ymin, ymax));
            }
            
            //--------------------------------------------------------------
            Title& Panel::addTitle(string name, float height) {
                return (Title&)addControl(new Title(this, name, height));
            }
            
            //--------------------------------------------------------------
            Toggle& Panel::addToggle(string name, bool &value) {
                return (Toggle&)addControl(new Toggle(this, name, value));
            }
            
            
            
            //--------------------------------------------------------------
            void Panel::addParameter(Parameter& parameter) {
                ofLogVerbose() << "msa::ControlFreak::gui::Panel::addParameter - " << name << ": " << parameter.getPath();
                // if parameter already exists, remove it first
                
                ParameterGroup *pc = dynamic_cast<ParameterGroup*>(&parameter);
                if(pc && pc->getNumParams() > 0) {
                    Panel &panel = addPanel(parameter.getPath());
                    panel.addParameters(*pc);
                }
                
                switch(parameter.getType()) {
                    case Type::kFloat: {
                        ParameterFloat &p = (ParameterFloat&)parameter;
                        addSlider(p.getName(), p.getValue(), p.getMin(), p.getMax()).setIncrement(p.getIncrement());
                    }
                        break;
                        
                    case Type::kInt: {
                        ParameterInt &p = (ParameterInt&)parameter;
                        addSlider(p.getName(), p.getValue(), p.getMin(), p.getMax()).setIncrement(p.getIncrement());
                    }
                        break;
                        
                    case Type::kToggle: {
                        ParameterBool &p = (ParameterBool&)parameter;
                        addToggle(p.getName(), p.getValue());
                    }
                        break;
                        
                    case Type::kBang: {
                        ParameterBool &p = (ParameterBool&)parameter;
                        addButton(p.getName(), p.getValue());
                    }
                        break;
                        
                    case Type::kNamedIndex: {
                        ParameterNamedIndex &p = (ParameterNamedIndex&)parameter;
                        addComboBox(p.getName(), p.getValue(), p.getLabels());
                    }
                        break;
                        
                    default:
                        ofLogWarning() << "msa::ControlFreak::Gui::addParameter - unknown type adding parameter " << parameter.getPath() << " " << parameter.getTypeName();
                        break;
                }
            }
            
            //--------------------------------------------------------------
            void Panel::addParameters(ParameterGroup& parameters) {
                ofLogVerbose() << "msa::ControlFreak::gui::Panel::addParameters - " << name << ": " << parameters.getPath();
                
                if(!config) setup();
                
                //                addTitle(parameters.getPath());
                //                addToggle(parameters.getPath(), *(new bool));
                addButton(parameters.getPath(), isOpen).setToggleMode(true);
                isOpen = true;
                int np = parameters.getNumParams();
                for(int i=0; i<np; i++) {
                    addParameter(parameters.getParameter(i));
                }
//                addTitle("");
            }
            
            //--------------------------------------------------------------
            void Panel::setActiveControl(Control* control) {
                activeControl = control;
            }
            
            //--------------------------------------------------------------
            void Panel::releaseActiveControl() {
                activeControl = NULL;
            }
            
            //--------------------------------------------------------------
            void Panel::update() {
                if(controls[0]) controls[0]->update();
                if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) controls[i]->update();
            }
            
            //--------------------------------------------------------------
            void Panel::mouseMoved(ofMouseEventArgs &e) {
                if(activeControl)
                    activeControl->_mouseMoved(e);
                else {
                    if(controls[0]) controls[0]->_mouseMoved(e);
                    if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) controls[i]->_mouseMoved(e);
                }
            }
            
            //--------------------------------------------------------------
            void Panel::mousePressed(ofMouseEventArgs &e) {
                if(activeControl)
                    activeControl->_mousePressed(e);
                else {
                    if(controls[0]) {
                        controls[0]->_mousePressed(e);
                        if(controls[0]->hitTest(e.x, e.y)) setActiveControl(controls[0]);
                    }
                    if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) {
                        controls[i]->_mousePressed(e);
                        if(controls[i]->hitTest(e.x, e.y)) setActiveControl(controls[i]);
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Panel::mouseDragged(ofMouseEventArgs &e) {
                if(activeControl)
                    activeControl->_mouseDragged(e);
                else {
                    if(controls[0]) controls[0]->_mouseDragged(e);
                    if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) controls[i]->_mouseDragged(e);
                }
            }
            
            //--------------------------------------------------------------
            void Panel::mouseReleased(ofMouseEventArgs &e) {
                if(activeControl)
                    activeControl->_mouseReleased(e);
                else {
                    if(controls[0]) controls[0]->_mouseReleased(e);
                    if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) controls[i]->_mouseReleased(e);
                }
                
                releaseActiveControl();
            }
            
            //--------------------------------------------------------------
            void Panel::keyPressed(ofKeyEventArgs &e) {
                bool keyUp		= e.key == OF_KEY_UP;
                bool keyDown	= e.key == OF_KEY_DOWN;
                bool keyLeft	= e.key == OF_KEY_LEFT;
                bool keyRight	= e.key == OF_KEY_RIGHT;
                bool keyEnter	= e.key == OF_KEY_RETURN;
                
                Control *c = controls[0];
                if(c->isMouseOver()) {
                    if(keyUp)		c->onKeyUp();
                    if(keyDown)		c->onKeyDown();
                    if(keyLeft)		c->onKeyLeft();
                    if(keyRight)	c->onKeyRight();
                    if(keyEnter)	c->onKeyEnter();
                    c->_keyPressed(e);
                }
                
                if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) {
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
            
            //--------------------------------------------------------------
            void Panel::keyReleased(ofKeyEventArgs &e) {
                if(controls[0]->isMouseOver()) controls[0]->_keyReleased(e);
                if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) if(controls[i]->isMouseOver()) controls[i]->_keyReleased(e);
            }
            
            //--------------------------------------------------------------
            vector <Control*>&	Panel::getControls() {
                return controls;
            }
            
        }
    }
}
