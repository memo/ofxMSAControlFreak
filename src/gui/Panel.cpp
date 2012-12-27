#include "ofxMSAControlFreak/src/gui/Includes.h"

#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            //--------------------------------------------------------------
            Panel::Panel(Panel *parent, Parameter *p) : ControlParameterT<ParameterGroup>(parent, p) {
                disableAllEvents();
                width = 0;
                height = 0;//ofGetHeight();
                maxRect.set(0, 0, 0, 0);
                activeControl = NULL;
//                setXMLName(p->getName() + "_settings.xml");
                
                isOpen = true;
                heightScale = 1.0;
            }
            
            //--------------------------------------------------------------
            Panel::~Panel() {
                // delete all controls
            }
            
            
            //--------------------------------------------------------------
//            Panel& Panel::setXMLName(string s) {
//                xmlFilename = s;
//                return *this;
//            }
            
            
            //--------------------------------------------------------------
//            void Panel::loadXml() {
//                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Panel::loadXml: " + xmlFilename);
//                
//                if(xmlFilename.compare("") == 0) return;
//                
//                if(XML.loadFile(xmlFilename) == false) {
//                    ofLog(OF_LOG_ERROR, "Error loading xmlFilename: " + xmlFilename);
//                    return;
//                }
//                
//                XML.pushTag("controls");
//                for(int i=0; i < controls.size(); i++) {
//                    controls[i]->readFromXml(XML);
//                }
//                XML.popTag();
//            }
            
            
            //--------------------------------------------------------------
//            void Panel::saveXml() {
//                if(controls.size() <= 1 || xmlFilename.compare("") == 0) return;	// if it has no controls (title counts as one control)
//                
//                XML.clear();	// clear cause we are building a new xml file
//                
//                XML.addTag("controls");
//                XML.pushTag("controls");
//                for(int i=0; i < controls.size(); i++) {
//                    controls[i]->writeToXml(XML);
//                }
//                XML.popTag();
//                
//                XML.saveFile(xmlFilename);
//                //	if(doSaveBackup)
//                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Panel::saveXml: " + xmlFilename + " " + ofToString(controls.size(), 0) + " items");
//            }
            
            
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
                    
//                    if(control.parameter && !control.parameter->getName().empty()) {
                        ofNoFill();
                        ofSetColor(config->borderColor);
                        glLineWidth(1.0);
                        ofRect(curPos.x, curPos.y, control.width, control.height * getHeightScale());
//                    }
                    
                    growToInclude((ofRectangle&)control);
                }
                
//                height += config->padding.y * 2;
                
                // draw panel title again so it's on top
                if(controls[0] && getHeightScale() < 0.9) controls[0]->draw();
                
                //event stealing controls get drawn on top
                if(activeControl) {
                    activeControl->draw();  // TODO: is this drawing the whole heirarchy again? each panel has an active control, which is all sub-panels?
//                    if(activeControl->parameter && !activeControl->parameter->getName().empty()) {
                        ofNoFill();
//                        ofSetColor(config->borderColor);
//                        ofSetLineWidth(1);
//                        ofRect((ofRectangle&)*activeControl);//, stealingY, activeControl->width, activeControl->height);
//                    }
                }
                
                // panel border
//                ofNoFill();
//                ofSetColor(128, 0, 0);
//                ofSetLineWidth(1);
//                ofRect(x, y, width, height);
                ofPopStyle();
//                height = 0;
            }
            
            
            //--------------------------------------------------------------
            Control& Panel::addControl(Control *control) {
                controls.push_back(ControlPtr(control));
                return *control;
            }
            
            //--------------------------------------------------------------
            Panel& Panel::addPanel(Parameter *p) {
                return (Panel&)addControl(new Panel(this, p));
            }
            
            //--------------------------------------------------------------
            BoolButton& Panel::addButton(Parameter *p) {
                return (BoolButton&)addControl(new BoolButton(this, p));
            }
            
            //--------------------------------------------------------------
            ColorPicker& Panel::addColorPicker(Parameter *p) {
//                return (ColorPicker&)addControl(new ColorPicker(this, p));
            }
            
            //--------------------------------------------------------------
            ComboBox& Panel::addComboBox(Parameter *p) {
                return (ComboBox&)addControl(new ComboBox(this, p));
            }
            
            //--------------------------------------------------------------
            Content& Panel::addContent(Parameter *p, ofBaseDraws &content, float fixwidth) {
                if(fixwidth == -1) fixwidth = config->gridSize.x - config->padding.x;
                return (Content&)addControl(new Content(this, p, content, fixwidth));
            }
            
            //--------------------------------------------------------------
            FPSCounter& Panel::addFPSCounter() {
                return (FPSCounter&)addControl(new FPSCounter(this));
            }
            
            //--------------------------------------------------------------
            QuadWarp& Panel::addQuadWarper(Parameter *p) {
//                return (QuadWarp&)addControl(new QuadWarp(this, p));
            }
            
            //--------------------------------------------------------------
            SliderInt& Panel::addSliderInt(Parameter *p) {
                return (SliderInt&)addControl(new SliderT<int>(this, p));
            }
            
            //--------------------------------------------------------------
            SliderFloat& Panel::addSliderFloat(Parameter *p) {
                return (SliderFloat&)addControl(new SliderT<float>(this, p));
            }
            
            //--------------------------------------------------------------
            Slider2d& Panel::addSlider2d(Parameter *p) {
//                return (Slider2d&)addControl(new Slider2d(this, p));
            }
            
            //--------------------------------------------------------------
            BoolTitle& Panel::addTitle(Parameter *p, float height) {
                return (BoolTitle&)addControl(new BoolTitle(this, p, height));
            }
            
            //--------------------------------------------------------------
            BoolToggle& Panel::addToggle(Parameter *p) {
                return (BoolToggle&)addControl(new BoolToggle(this,p));
            }
            
            
            
            //--------------------------------------------------------------
            void Panel::addParameter(Parameter *p) {
                ofLogVerbose() << "msa::ControlFreak::gui::Panel::addParameter - " << parameter->getPath() << ": " << p->getPath();
                // if parameter already exists, remove it first
                
                ParameterGroup *pc = dynamic_cast<ParameterGroup*>(p);
                if(pc && pc->getNumParams() > 0) {
                    Panel &panel = addPanel(pc);
                    panel.addParameters(*pc);
                }
                
                switch(p->getType()) {
                    case Type::kFloat: addSliderFloat(p); break;
                    case Type::kInt: addSliderInt(p); break;
                    case Type::kBool: {
                        ParameterBool &pb = *(ParameterBool*)p;
                        if(pb.getBang()) addButton(p);
                        else addToggle(p);
                    }
                        break;
                        
                    case Type::kNamedIndex: addComboBox(p);

                    case Type::kGroup:
                        break;
                        
                    default:
                        ofLogWarning() << "msa::ControlFreak::Gui::addParameter - unknown type adding parameter " << p->getPath() << " " << p->getTypeName();
                        break;
                }
            }
            
            //--------------------------------------------------------------
            void Panel::addParameters(ParameterGroup& parameters) {
                ofLogVerbose() << "msa::ControlFreak::gui::Panel::addParameters - " << parameter->getPath() << ": " << parameters.getPath();
                
                if(!config) setup();
                
//                addTitle(parameters.getPath());
                //                addToggle(parameters.getPath(), *(new bool));
//                addButton(parameters.getPath(), isOpen).setToggleMode(true);
                isOpen = true;
                int np = parameters.getNumParams();
                for(int i=0; i<np; i++) {
                    addParameter(&parameters.getParameter(i));
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
                        if(controls[0]->hitTest(e.x, e.y)) setActiveControl(controls[0].get());
                    }
                    if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) {
                        controls[i]->_mousePressed(e);
                        if(controls[i]->hitTest(e.x, e.y)) setActiveControl(controls[i].get());
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
                
                Control *c = controls[0].get();
                if(c->isMouseOver()) {
                    if(keyUp)		c->onKeyUp();
                    if(keyDown)		c->onKeyDown();
                    if(keyLeft)		c->onKeyLeft();
                    if(keyRight)	c->onKeyRight();
                    if(keyEnter)	c->onKeyEnter();
                    c->_keyPressed(e);
                }
                
                if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) {
                    Control *c = controls[i].get();
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
//            vector <ControlPtr>&	Panel::getControls() {
//                return controls;
//            }
            
        }
    }
}
