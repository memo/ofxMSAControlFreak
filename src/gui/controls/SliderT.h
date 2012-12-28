#pragma once

#include "ofxMSAControlFreak/src/gui/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            template <typename T>
            class SliderT : public ControlParameterT<ParameterSingleValueT<T> > {
            public:

                //--------------------------------------------------------------
                SliderT(Panel *parent, Parameter *p) : ControlParameterT<ParameterSingleValueT<T> >(parent, p) {
                }

                //--------------------------------------------------------------
                void inc(T amount) {
                    if(!this->parameter) return;
                    this->parameter->inc(amount);
                }
                
                //--------------------------------------------------------------
                void dec(T amount) {
                    if(!this->parameter) return;
                    this->parameter->dec(amount);
                }
                
                
                //--------------------------------------------------------------
                void updateSlider() {
                    if(!this->enabled) return;
                    if(!this->parameter) return;
                    if(this->active) {
                        this->parameter->setMappedFrom(this->getMouseX(), this->x, this->x + this->width);
                    }
                }
                
                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
                    this->active = button == 0;//this->getMouseY() < this->y + this->height/2;

                    updateSlider();
                }
                
                //--------------------------------------------------------------
                void onDragOver(int x, int y, int button) {
                    updateSlider();
                }
                
                //--------------------------------------------------------------
                void onDragOutside(int x, int y, int button) {
                    updateSlider();
                }
                
                //--------------------------------------------------------------
                void onKeyRight() {
                    inc(1);
                }
                
                //--------------------------------------------------------------
                void onKeyLeft() {
                    dec(1);
                }
                
                //--------------------------------------------------------------
                void onKeyUp() {
                    inc(10);
                }
                
                //--------------------------------------------------------------
                void onKeyDown() {
                    dec(10);
                }

                //--------------------------------------------------------------
                void draw() {
                    if(!this->parameter) return;
                    
                    ofPushStyle();
                    ofEnableAlphaBlending();
                    ofPushMatrix();
                    ofTranslate(this->x, this->y);
                    ofFill();
                    
                    float width = this->width;
                    float height = this->height;
                    Config &c = *this->config;
                    
                    ParameterSingleValueT<T> &p = *this->parameter;
                    
                    float barwidth = ofClamp(p.getMappedTo(0, width), 0, width);
                    
                    
                    this->setBGColor();
                    ofRect(0, 0, width, height);
                    
                    this->setSliderColor(false);
                    ofRect(0, 0, width, c.layout.sliderHeight);
                    
                    this->setSliderColor(true);
                    ofRect(0, 0, barwidth, c.layout.sliderHeight);
                    
                    string s = p.getName() + ": " + ofToString(p.getValue());
                    this->drawText(c.layout.textPos.x, c.layout.sliderHeight/2 + c.layout.textPos.y, s);
                    
                    
                    if(p.getSnap()) {
                        float xinc = ofMap(p.getIncrement(), p.getMin(), p.getMax(), 0, width);
                        if(xinc >=2) {
                            ofColor &col = c.colors.bg[0];
                            ofSetColor(col.r, col.g, col.b, 128);
                            for(float f=0; f<=width; f+=xinc) {
                                ofLine(f, 0, f, c.layout.sliderHeight);
                            }
                        }
                    }
                    
                    if(p.getClamp()) {
                        ofColor &col = c.colors.text[1];
                        ofSetColor(col.r, col.g, col.b, 128);
                        int w = 2;
                        int h = c.layout.sliderHeight;
                        ofRect(0, 0, w, h);
                        ofRect(width-w-1, 0, w, h);
                    }
                    
                    if(this->isMouseOver()) {
                        ofSetColor(c.colors.text[0]);
                        int ts = height * 0.5;
                        ofTriangle(width, height, width, height - ts, width - ts, height);
                    }
                    
                    // draw border
                    this->drawBorder();

                    ofPopMatrix();
                    ofPopStyle();
                }
                
            };
        }
    }
}
