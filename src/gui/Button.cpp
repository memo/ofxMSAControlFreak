
#include  "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            Button::Button(Panel* parent, string name, bool &value) : ValueControl<bool>(parent, name, value) {
                beToggle	= false;
                beenPressed = false;
                controlType = "Button";
                setup();
            }
            
            void Button::setup() {
                setSize(config->gridSize.x - config->padding.x, config->buttonHeight);
            }
            
            void Button::readFromXml(ofxXmlSettings &XML) {
                setValue(XML.getValue(controlType + "_" + key + ":value", 0));
            }
            
            void Button::writeToXml(ofxXmlSettings &XML) {
                XML.addTag(controlType + "_" + key);
                XML.pushTag(controlType + "_" + key);
                XML.addValue("name", name);
                XML.addValue("value", getValue());
                XML.popTag();
            }
            
            void Button::keyPressed( int key ) {
                if(key==keyboardShortcut) toggle();
            }
            
            
            
            bool Button::getValue() {
                return (*value);
            }
            
            void Button::setValue(bool b) {
                (*value) = b;
            }
            
            void Button::toggle() {
                (*value) = !(*value);
            }
            
            void Button::setToggleMode(bool b) {
                beToggle = b;
            }
            
            void Button::onPress(int x, int y, int button) {
                beenPressed = true;
                if(beToggle) (*value) = !(*value); 
                else (*value) = true;
            }
            
            void Button::onRelease(int x, int y, int button) {
                if(!beToggle) (*value) = false;
            }
            
            void Button::draw(float x, float y) {
                setPos(x, y);
                
                glPushMatrix();
                glTranslatef(x, y, 0);
                
                ofEnableAlphaBlending();
                ofFill();
                setTextBGColor();
                ofRect(0, 0, width, height);
                
                // if a toggle
                if((*value) && beToggle) {
                    setTextColor();
                    //ofLine(0, 0, box.width, box.height);
                    //ofLine(box.width, 0, 0, box.height);
                }
                
                setTextColor();
                config->drawString(name, 3, 15);
                
                ofDisableAlphaBlending();
                
                glPopMatrix();
            }
        }
    }
}