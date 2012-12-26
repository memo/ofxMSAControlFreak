
#include  "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            Content::Content(Panel *parent, string name, ofBaseDraws& content, float fixwidth) : Control(parent, name, "Content") {
                this->content = &content;
                this->fixwidth  = fixwidth;
                setup();
            }
            
            void Content::setup() {
                fixheight = fixwidth * content->getHeight()/content->getWidth();
                setSize(fixwidth, fixheight + config->sliderTextHeight);
            }
            
            void Content::draw(float x, float y) {
                if(content == NULL) return;
                
                if(content->getWidth() == 0 && content->getHeight() ==0) return;
                
                setPos(x, y);
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
                setTextBGColor();
                ofRect(0, fixheight, width, config->sliderTextHeight);
                
                setTextColor();
                config->drawString(name, 3, fixheight + 15);
                ofDisableAlphaBlending();
                glPopMatrix();
            }
            
        }
    }
}