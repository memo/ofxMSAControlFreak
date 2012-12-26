
#include  "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            Title::Title(Panel *parent, string name, float height) : Control(parent, name, "Title") {
                beToggle	= false;
                beenPressed = false;
                //		this->value	= &value;
                value		= NULL;
                controlType = "Title";
                //		newColumn	= true;
                
                if(height == 0) height = config->titleHeight;
                if(hasTitle == false) height/=2;
                setSize(config->gridSize.x - config->padding.x, height);
                setup();
            }
            
            void Title::setup() {
            }
            
//            void Title::readFromXml(ofxXmlSettings &XML) {
//                if(!value) return;
//                setValue(XML.getValue(controlType + "_" + key + ":value", 0));
//            }
//            
//            void Title::writeToXml(ofxXmlSettings &XML) {
//                if(!value) return;
//                XML.addTag(controlType + "_" + key);
//                XML.pushTag(controlType + "_" + key);
//                XML.addValue("name", name);
//                XML.addValue("value", getValue());
//                XML.popTag();
//            }
            
            bool Title::getValue() {
                if(!value) return false;
                return (*value);
            }
            void Title::setValue(bool b) {
                if(!value) return;
                (*value) = b;
            }
            void Title::toggle() {
                if(!value) return;
                (*value) = !(*value);
            }
            
            void Title::setToggleMode(bool b) {
                if(!value) return;
                beToggle = b;
            }
            
            void Title::onPress(int x, int y, int button) {
                if(!value) return;
                beenPressed = true;
                if(beToggle) (*value) = !(*value);
                else (*value) = true;
            }
            
            void Title::onRelease(int x, int y, int button) {
                if(!value) return;
                if(!beToggle) (*value) = false;
            }
            
            void Title::draw(float x, float y) {
                setPos(x, y);
                
                if(hasTitle == false) return;
                
                glPushMatrix();
                glTranslatef(x, y, 0);
                
                ofEnableAlphaBlending();
                ofFill();
                ofSetHexColor(config->fullActiveColor);
                ofRect(0, 0, width, height);
                
                // if a toggle
                if(value && (*value) && beToggle) {
                    setTextColor();
                }
                
                setTextColor(value != NULL);
                config->drawString(name, 3, 15);
                
                ofDisableAlphaBlending();
                
                glPopMatrix();
            }
            
        }
    }
}
