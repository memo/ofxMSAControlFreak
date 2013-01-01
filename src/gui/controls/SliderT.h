#pragma once

#include "ofxMSAControlFreak/src/gui/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            template <typename T>
            class SliderT : public ControlParameterT<ParameterSingleValueT<T> > {
            public:

                //--------------------------------------------------------------
                SliderT(Panel *parent, Parameter *p) : ControlParameterT<ParameterSingleValueT<T> >(parent, p) {}

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
                    if(this->isMousePressed()) {
                        this->parameter->setMappedFrom(ofGetMouseX(), this->x, this->x + this->width);
                    }
                }
                
                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
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
                void onDraw() {
                    if(!this->parameter) return;
                    
                    ofFill();
                    
                    float width = this->width;
                    float height = this->height;
                    Config &c = this->getConfig();
                    
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
                            this->setColor(c.colors.bg[0]);
                            ofSetLineWidth(1);
                            for(float f=0; f<=width; f+=xinc) {
                                ofLine(f, 0, f, c.layout.sliderHeight);
                            }
                        }
                    }
                    
                    if(p.getClamp()) {
                        this->setColor(ofColor(c.colors.text[1].r, c.colors.text[1].g, c.colors.text[1].b, 128));
                        int w = 2;
                        int h = c.layout.sliderHeight;
                        ofRect(0, 0, w, h);
                        ofRect(width-w-1, 0, w, h);
                    }
                    
                    if(this->isMouseOver()) {
                        this->setColor(c.colors.text[0]);
                        int ts = height * 0.5;
                        ofTriangle(width, height, width, height - ts, width - ts, height);
                    }
                    
                    // draw border
//                    this->drawBorder();
                }
                
            };
        }
    }
}
