
#include "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Content::Content(Panel *parent, Parameter *p, ofBaseDraws& content, float fixwidth) : ControlParameterT<Parameter>(parent, p) {
                this->content = &content;
                this->fixwidth  = fixwidth;
                setup();
            }
            
            void Content::setup() {
                fixheight = fixwidth * content->getHeight()/content->getWidth();
                width = fixwidth;
                height = fixheight + config->layout.buttonHeight;
            }
            
            void Content::draw() {
                if(content == NULL) return;
                
                if(content->getWidth() == 0 && content->getHeight() ==0) return;
                
                setup();
                
                glPushMatrix();
                glTranslatef(x, y, 0);
                ofEnableAlphaBlending();
                ofFill();
                glColor4f(0, 0, 0, 0.8f);
                ofRect(0, 0, width, fixheight);
                
                ofSetHexColor(0xffffff);
                content->draw(0, 0, width, fixheight);
                
                ofFill();
                setBGColor();
                ofRect(0, fixheight, width, config->layout.buttonHeight);
                
                setTextColor();
                config->drawString(parameter->getName(), 3, fixheight + 15);
                ofDisableAlphaBlending();
                glPopMatrix();
            }
            
        }
    }
}