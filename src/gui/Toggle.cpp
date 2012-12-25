
#include  "ofxMSAControlFreak/src/gui/Toggle.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Toggle::Toggle(string name, bool &value) : Control(name) {
                this->value	= &value;
                setMomentary(false);
                controlType = "Toggle";
                setup();
            }
            
            Toggle& Toggle::setMomentary(bool m) {
                momentary = m;
                return *this;
            }
            
            
            void Toggle::setup() {
                setSize(config->gridSize.x - config->padding.x, config->toggleHeight);
            }
            
            void Toggle::readFromXml(ofxXmlSettings &XML) {
                setValue(XML.getValue(controlType + "_" + key + ":value", 0));
            }
            
            void Toggle::writeToXml(ofxXmlSettings &XML) {
                XML.addTag(controlType + "_" + key);
                XML.pushTag(controlType + "_" + key);
                XML.addValue("name", name);
                XML.addValue("value", getValue());
                XML.popTag();
            }
            
            bool Toggle::getValue() {
                return (*value);
            }
            
            void Toggle::setValue(bool b) {
                (*value) = b;
            }
            
            void Toggle::toggle() {
                (*value) = !(*value);
            }
            
            void Toggle::onPress(int x, int y, int button) {
                if(momentary) setValue(true);
                else toggle();
            }
            
            void Toggle::onRelease(int x, int y, int button) {
                if(momentary) setValue(false);
            }
            
            void Toggle::keyPressed( int key ) {
                if(key==keyboardShortcut) onPress(0, 0, 0);
            }
            
            void Toggle::keyReleased( int key ) {
                if(key==keyboardShortcut) onRelease(0, 0, 0);
            }
            
            void Toggle::onKeyEnter() {
                toggle();
            }
            
            void Toggle::update() {
                //	if(!enabled) return;
                //	enabled = false;
            }
            
            void Toggle::draw(float x, float y) {
                //	enabled = true;
                setPos(x, y);
                
                glPushMatrix();
                glTranslatef(x, y, 0);
                
                ofEnableAlphaBlending();
                ofFill();
                setFullColor(*value);
                ofRect(0, 0, height, height);
                
                if((*value)) {
                    setTextColor();
                    ofLine(0, 0, height, height);
                    ofLine(height, 0, 0, height);
                }
                
                setTextBGColor();
                ofRect(height, 0, width - height, height);
                
                setTextColor();
                config->drawString(name, height + config->textPos.x, config->textPos.y);
                ofDisableAlphaBlending();
                
                glPopMatrix();
            }
        }
    }
}
