
#include "ofxMSAControlFreak/src/gui/Includes.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            Renderer *Renderer::renderer = NULL;
            
            //--------------------------------------------------------------
            Renderer::Renderer() {
                config = NULL;
            }
            
            //--------------------------------------------------------------
            Renderer& Renderer::instance() {
                if(renderer == NULL) renderer = new Renderer;
                return *renderer;
            }
            
            //--------------------------------------------------------------
            Renderer::~Renderer() {
                if(renderer) delete renderer;
            }

            
            //--------------------------------------------------------------
            void Renderer::addControl(Control *c) {
                controls.push_back(c);
            }
            
            //--------------------------------------------------------------
            void Renderer::clearControls() {
                controls.clear();
            }

            //--------------------------------------------------------------
            struct PointerCompare {
                bool operator()(const Control* l, const Control* r) {
                    return l->z > r->z;
                }
            };
            
            //--------------------------------------------------------------
            void Renderer::draw(Config *config) {
                this->config = config;
                sort(controls.begin(), controls.end(), PointerCompare());
                
                ofPushStyle();
                for(int i=0; i<controls.size(); i++) {
                    Control& control = *controls[i];
                    control.draw();
                }
                
                drawToolTip();
                
                ofPopStyle();
            }
            
            //--------------------------------------------------------------
            void Renderer::setToolTip(string s, int x, int y) {
                tooltip.x = x < 0 ? ofGetMouseX() : x;
                tooltip.y = y < 0 ? ofGetMouseY() : y;
                tooltip.s = s;
            }
            
            //--------------------------------------------------------------
            void Renderer::drawToolTip() {
//                printf("drawTooltip: %s\n", tooltip.s.c_str());
                if(tooltip.s.empty() || !config) return;
                
                int x = tooltip.x + config->tooltip.offset.x;
                int y = tooltip.y + config->tooltip.offset.y;
                
                ofPushStyle();
                ofRectangle r = config->font.getStringBoundingBox(tooltip.s, x, y);
                r.x -= config->tooltip.padding.x;
                r.y -= config->tooltip.padding.y;
                r.width += config->tooltip.padding.width;
                r.height += config->tooltip.padding.height;
                
                // make sure tooltip doesn't go offscreen
                ofVec2f diff;
                if(r.getLeft() < 0) { diff.x = -r.x; r.x = 0; }
                else if(r.getRight() > ofGetWidth()) { diff.x = ofGetWidth() - r.getRight(); r.x = ofGetWidth() - r.width; }
                
                if(r.getTop() < 0) { diff.y = - r.y; r.y = 0; }
                else if(r.getBottom() > ofGetHeight()) { diff.y = ofGetHeight() - r.y; r.y = ofGetHeight() - r.height; }
                
                x += diff.x;
                y += diff.y;
                
                
                ofSetLineWidth(1);
                ofSetColor(config->tooltip.bgColor);
                ofFill();
                ofRect(r);
                
                ofSetColor(config->tooltip.borderColor);
                ofNoFill();
                ofRect(r);
                
                ofSetColor(config->tooltip.textColor);
                config->drawString(tooltip.s, x, y);
                
                ofPopStyle();
                tooltip.s = "";
            }

        }
    }
}