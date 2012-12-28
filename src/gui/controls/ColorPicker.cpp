///*
// *  ColorPicker.cpp
// *  OpenCL Particles 3. single segment trails
// *
// *  Created by Mehmet Akten on 01/11/2009.
// *  Copyright 2009 __MyCompanyName__. All rights reserved.
// *
// */
//
//#include "ofxMSAControlFreak/src/gui/Includes.h"
//
//namespace msa {
//    namespace ControlFreak {
//        namespace gui {
//            
//            ColorPicker::ColorPicker(Panel *parent, Parameter *p) : Control(parent, p) {
////                this->value = &color;
////                this->min	= 0;
////                this->max	= max;
////                setup();
//            }
//            
//            void ColorPicker::setup() {
//                setSize(config->gridSize.x - config->padding.x, config->sliderHeight * 8 + config->sliderTextHeight);
//                for(int i=0; i<4; i++) {
//                    pct[i] = ofMap(getValue(i), 0, max, 0.0, width);
//                    barwidth[i] = pct[i];
//                }
//            }
//            
////            void ColorPicker::readFromXml(ofxXmlSettings &XML) {
////                for(int i=0; i<4; i++) {
////                    setValue(XML.getValue(controlType + "_" + key + ":values_" + ofToString(i), 0.0f), i);
////                }
////            }
////            
////            void ColorPicker::writeToXml(ofxXmlSettings &XML) {
////                XML.addTag(controlType + "_" + key);
////                XML.pushTag(controlType + "_" + key);
////                XML.addValue("name", name);
////                for(int i=0; i<4; i++) {
////                    XML.addValue("values_" + ofToString(i), getValue(i));
////                }
////                XML.popTag();
////            }
//            
//            
//            float ColorPicker::getValue(int i) {
//                return value->v[i];
//            }
//            
//            
//            void ColorPicker::setValue(float f, int i) {
//                if(f < min) f = min;
//                else if(f > max) f = max;
//                value->v[i] = f;
//            }
//            
//            
//            void ColorPicker::updateSlider() {
//                if(!enabled) return;
//                
//                int i= (getMouseY() - y) / config->sliderHeight/2;
//                if(i<0 || i>=4) return;
//                
//                if(pct[i] > width) {
//                    pct[i] = width;
//                }
//                else {
//                    pct[i] = getMouseX() - x;
//                    setValue(ofMap(pct[i], 0.0, (float)width, 0, max), i);
//                }
//            }
//            
//            void ColorPicker::onPress(int x, int y, int button) {
//                updateSlider();
//            }
//            
//            void ColorPicker::onDragOver(int x, int y, int button) {
//                updateSlider();
//            }
//            
//            void ColorPicker::onDragOutside(int x, int y, int button) {
//                updateSlider();
//            }
//            
//            
//            
//            //--------------------------------------------------------------------- update
//            void ColorPicker::update() {
//                if(!enabled) return;
//                
//                if(lock) {
//                    updateSlider();
//                }
//                
//                //	enabled = false;
//            }
//            
//            //--------------------------------------------------------------------- draw
//            void ColorPicker::draw(float x, float y) {
//                
//                //	enabled = true;
//                
//                //update postion of gui object
//                setPos(x, y);
//                glPushMatrix();
//                glTranslatef(x, y, 0);
//                
//                int startY = 0;
//                for(int i=0; i<4; i++) {
//                    
//                    barwidth[i] = ofMap(getValue(i), 0, max, 0.0, (float)width);
//                    if(barwidth[i] > width)	barwidth[i] = width;
//                    else if(barwidth[i] < 0) barwidth[i] = 0;
//                    
//                    ofEnableAlphaBlending();
//                    ofFill();
//                    setEmptyColor();
//                    ofRect(0, startY, width, config->sliderHeight*1.8);
//                    
//                    
//                    switch(i) {
//                        case 0:glColor3f(getValue(i), 0, 0); break;
//                        case 1:glColor3f(0, getValue(i), 0); break;
//                        case 2:glColor3f(0, 0, getValue(i)); break;
//                        case 3:glColor3f(getValue(i), getValue(i), getValue(i)); break;
//                    }
//                    
//                    ofRect(0, startY, barwidth[i], config->sliderHeight * 1.8);
//                    
//                    int iover = (getMouseY() - y) / config->sliderHeight/2;
//                    bool isOver = iover == i;
//                    if(isOver) {
//                        glColor3f(1, 1, 1);
//                    } else {
//                        glColor3f(0.5, 0.5, 0.5);
//                    }
//                    
//                    config->drawString(ofToString(getValue(i), 4), 3, startY + 14);
//                    
//                    startY += config->sliderHeight * 2;
//                }
//                
//                ofFill();
//                
//                setBGColor();
//                ofRect(0, startY, width, config->sliderTextHeight);
//                
//                glColor3f(getValue(0), getValue(1), getValue(2));
//                //	ofRect(0, startY+config->sliderTextHeight, width, config->sliderTextHeight * 1.5);
//                ofRect(150, startY + 3, width - 150 -3, config->sliderTextHeight - 8);
//                
//                setTextColor();
//                config->drawString(parameter->getName(), 3, startY + 14);
//                ofDisableAlphaBlending();
//                glPopMatrix();
//            }
//            
//        }
//    }
//}
