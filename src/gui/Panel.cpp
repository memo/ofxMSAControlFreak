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
                activeControl = NULL;
                isOpen = false;
//                setXMLName(p->getName() + "_settings.xml");
                
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
            float Panel::getParentHeightScale() {
                return getParent() ? getParent()->getHeightScale() : heightScale;
            }
            
            //--------------------------------------------------------------
            float Panel::getHeightScale() {
                return heightScale * getParentHeightScale();
            }

            //--------------------------------------------------------------
            void Panel::showPanel(bool bOpen, bool bRecursive) {
                isOpen = bOpen;
                titleButton->getParameter().setValue(bOpen);
                if(bRecursive) {
                    for(int i=0; i<controls.size(); i++) {
                        Panel *p = dynamic_cast<Panel*>(controls[i].get());
                        if(p) p->showPanel(bOpen, true);
                    }
                }
            }
            
            //--------------------------------------------------------------
            void Panel::setLayout(int x, int y) {
                titleButton->z = -10000;
                
                // how open is this panel
                float openSpeed = 0.1f;
                if(titleButton->getParameter().getValue() != isOpen) showPanel(titleButton->getParameter().getValue(), titleButton->bRecursive);
                if(isOpen) {
//                    if(heightScale<0.95) heightScale += (1-heightScale) * openSpeed;
                    if(heightScale < 1) heightScale += openSpeed;
                    else heightScale = 1.0f;
                } else {
//                    if(heightScale > 0.05) heightScale += (0-heightScale) * openSpeed;
                    if(heightScale > 0) heightScale -= openSpeed;
                    else heightScale = 0.0f;
                }

                // if we are drawing this Panel inside another Panel, use auto-layout parameters of that
                if(getParent()) layout = getParent()->layout;
                
                // find the maximum position we are allowed to draw at before wrapping
                ofVec2f maxPos(layout->getMaxPos());
                
                // save reference to current position for quick access
                ofVec2f &curPos = layout->curPos;
                
                // set start position for panel
                curPos = layout->clampPoint(curPos);
                setPosition(curPos);
                
                width = 0;
                height = 0;

                int panelDepth = getDepth();// * getConfig().layout.indent;
                
                int numControls = getHeightScale() ? controls.size() : 1;
                
                float heightMult = getHeightScale();//i ? getHeightScale() : getParentHeightScale();
                for(int i=0; i<numControls; i++) {
                    Control& control = *controls[i];

                    int indent = i==0 ? panelDepth * getConfig().layout.indent : (panelDepth+1) * getConfig().layout.indent;
                    
                    // if forced to be new column, or the height of the control is going to reach across the bottom of the screen, start new column
                    if(control.newColumn || curPos.y + (control.height + getConfig().layout.padding.y) * heightMult > maxPos.y) {
                        curPos.x = layout->rect.x + layout->rect.width + getConfig().layout.padding.x;
                        curPos.y = layout->maxRect.y;
                    }
                    
                    control.setWidth(getConfig().layout.columnWidth - indent);
                    control.setLayout(curPos.x + indent, curPos.y);
                    Renderer::instance().addControl(&control);  // TODO: why does this break the order?
                    layout->rect.growToInclude((ofRectangle&)control);
                    
                    curPos.y += (control.height + getConfig().layout.padding.y) * heightMult;
                }
                
                // add some padding at end of group
                curPos.y += getConfig().layout.buttonHeight;// * getParentHeightScale();
                
                ofRectangle::set(*titleButton);
            }
            
            
//            //--------------------------------------------------------------
//            void Panel::draw() {
//                ofPushStyle();
//                
//                titleButton->z = -10000;
//                sort(controlsToDraw.begin(), controlsToDraw.end(), PointerCompare());
//                
////                ofLogNotice() << "\n\ndraw PANEL : " << name;
//                
//                bool doHilit = getActive();
//
//                for(int i=0; i<controlsToDraw.size(); i++) {
//                    Control& control = *controlsToDraw[i];
//                    
////                    ofLogNotice() << "draw CONTROL : " << control.name << " " << control.getPosition() << " " << control.x << "x" << control.y;
//                    
//                    control.draw();
//                    
//                    if(doHilit) {
//                        ofNoFill();
//                        ofSetColor(getConfig().colors.text[2]);
//                        ofSetLineWidth(1);
//                        ofRect((ofRectangle&)control);
//                    }
//                    
////                    growToInclude((ofRectangle&)control);
//                }
//                
//                // border on active control
////                if(activeControl) {
////                    ofNoFill();
////                    ofSetColor(getConfig().colors.text[0]);
////                    ofSetLineWidth(1);
//////                    ofRect((ofRectangle&)*activeControl);
////                }
//                ofPopStyle();
//            }
            
            
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
            DropdownList& Panel::addDropdownList(Parameter *p) {
                return (DropdownList&)addControl(new DropdownList(this, p));
            }
            
            //--------------------------------------------------------------
            Content& Panel::addContent(Parameter *p, ofBaseDraws &content, float fixwidth) {
                if(fixwidth == -1) fixwidth = getConfig().layout.columnWidth;
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
            BoolTitle& Panel::addTitle(Parameter *p) {
                return (BoolTitle&)addControl(new BoolTitle(this, p));
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
                        if(pb.getMode() == ParameterBool::kToggle) addToggle(p);
                        else addButton(p);
                    }
                        break;
                        
                    case Type::kNamedIndex: addDropdownList(p);

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
                
//                if(!_config) setup();
                
                titleButton = new BoolTitle(this, parameter->getName());
                titleButton->getParameter().setValue(true);
                addControl(titleButton);
                int np = parameters.getNumParams();
                for(int i=0; i<np; i++) {
                    addParameter(&parameters.getParameter(i));
                }
            }
            
            //--------------------------------------------------------------
            void Panel::setActiveControl(Control* control) {
                // if old control exists, put it at the back
                if(activeControl) activeControl->z = 0;
                
                activeControl = control;
                
                // put new active control at the front
                if(activeControl) {
                    activeControl->z = -1000;
//                    ofLogNotice() << "setting active control [" << activeControl->name << "] for panel [" << name;
//                } else {
//                    ofLogNotice() << "setting active control NULL for panel [" << name;
                }
            }
            
            //--------------------------------------------------------------
            Control* Panel::getActiveControl() {
                return activeControl;
            }
            
            //--------------------------------------------------------------
            void Panel::releaseActiveControl() {
                setActiveControl(NULL);
            }
            
            //--------------------------------------------------------------
//            bool Panel::getActive() {
//                bool b = activeControl == titleButton;//activeControl != NULL;
//                return parent ? b | parent->getActive() : b;
//            }

            
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
                        if(controls[0]->hitTest(e.x, e.y)) getRoot()->setActiveControl(controls[0].get());
                    }
                    if(getHeightScale()>0.9) for(int i=1; i<controls.size(); i++) {
                        controls[i]->_mousePressed(e);
                        if(controls[i]->hitTest(e.x, e.y)) getRoot()->setActiveControl(controls[i].get());
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
                
                getRoot()->releaseActiveControl();
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
