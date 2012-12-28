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
                    this->width = this->config->gridSize.x - this->config->padding.x;
                    this->height = this->config->sliderHeight + this->config->sliderTextHeight;
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
                    
                    
                    this->setEmptyColor();
                    ofRect(0, 0, width, c.sliderHeight);

                    
                    this->setFullColor();
                    ofRect(0, 0, barwidth, c.sliderHeight);
                    
                    this->setTextBGColor();
                    ofRect(0, c.sliderHeight, width, c.sliderTextHeight);
                    
                    this->setTextColor();
                    string s = p.getName() + ": " + ofToString(p.getValue());
                    c.drawString(s, c.textPos.x, c.sliderHeight/2 + c.textPos.y);
                    
                    
                    if(p.getSnap()) {
                        float xinc = ofMap(p.getIncrement(), p.getMin(), p.getMax(), 0, width);
                        if(xinc >=2) {
                            ofColor &col = c.textBGColor;
                            ofSetColor(col.r, col.g, col.b, 128);
                            for(float f=0; f<=width; f+=xinc) {
                                ofLine(f, 0, f, c.sliderHeight);
                            }
                        }
                    }
                    
                    if(p.getClamp()) {
                        ofColor &col = c.textOverColor;
                        ofSetColor(col.r, col.g, col.b, 128);
                        int w = 2;
                        int h = c.sliderHeight;
                        ofRect(0, 0, w, h);
                        ofRect(width-w-1, 0, w, h);
                    }
                    
                    if(this->isMouseOver()) {
                        ofSetColor(c.textColor);
                        int ts = height * 0.5;
                        ofTriangle(width, height, width, height - ts, width - ts, height);
                    }
                    
                    // draw border
                    ofNoFill();
                    ofSetColor(c.borderColor);
                    glLineWidth(1.0);
                    ofRect(0, 0, width, height);

                    ofPopMatrix();
                    ofPopStyle();
                }
                
            };
        }
    }
}
