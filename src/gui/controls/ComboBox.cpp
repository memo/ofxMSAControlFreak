///*
// *  ComboBox.cpp
// *  AlgorhythmicSorting
// *
// *  Created by Administrator on 7/2/10.
// *  Copyright 2010 __MyCompanyName__. All rights reserved.
// *
// */
//
//#include "ofxMSAControlFreak/src/gui/Includes.h"
//
//#define kMaxChoiceStringLen 150
//#define kMaxNameStringLen 100
//
//namespace msa {
//    namespace ControlFreak {
//        namespace gui {
//            
//            ComboBox::ComboBox(Panel *parent, Parameter *p) :
//            Control(parent, p)
//            {
//                selectedChoice = mouseChoice = 0;
//                if(numChoices <=1)
//                    numChoices = 1;
//                hasFocus=false;
//                title = name;
//                
//                for(int i=0; i<numChoices; i++){
//                    addChoice(choiceTitles ? choiceTitles[i] : ofToString(i));
//                }
//                setup();
//            }
//            
//            
//            ComboBox::~ComboBox() {
//            }
//            
//            
//            void ComboBox::setTitleForIndex(int index, string title) {
//                if(index < 0 || index >= choices.size()) return;
//                choices[index] = title;
//            }
//            
//            string ComboBox::getTitleForIndex(int index) {
//                if(index < 0 || index >= choices.size())return choices.size() ? choices[selectedChoice] : "No Choices Available";
//                return choices[index];
//            }
//            
//            
//            void ComboBox::addChoice(string title, int index) {
//                int insertIndex = choices.size();
//                
//                if(index >= 0 && index < choices.size()) insertIndex = index;
//                
//                choices.insert(choices.begin() + insertIndex, title);
//            }
//            
//            
//            int ComboBox::getIndexForTitle(string title) {
//                for(int i=0; i<choices.size(); i++) {
//                    if(title.compare(choices[i]) == 0) return i;
//                }
//                return -1;
//            }
//            
//            void ComboBox::removeChoice(string title) {
//                int index = getIndexForTitle(title);
//                if(index >= 0) removeChoice(index);
//            }
//            
//            void ComboBox::removeChoice(int index) {
//                int removeIndex = choices.size() - 1;
//                if(index >= 0 && index < choices.size())
//                    removeIndex = index;
//                
//                choices.erase(choices.begin() + removeIndex);
//                //also update the selected indexes.
//                if(selectedChoice >= removeIndex)
//                    selectedChoice--;
//                if(mouseChoice >= removeIndex)
//                    mouseChoice--;
//            }
//            
//            void ComboBox::setup() {
//                setSize(config->layout.gridSize.x - config->layout.padding.x, config->comboBoxHeight);
//            }
//            
////            void ComboBox::readFromXml(ofxXmlSettings &XML) {
////                setValue(XML.getValue(controlType + "_" + key + ":value", 0));
////            }
////            
////            void ComboBox::writeToXml(ofxXmlSettings &XML) {
////                XML.addTag(controlType + "_" + key);
////                XML.pushTag(controlType + "_" + key);
////                XML.addValue("name", name);
////                XML.addValue("value", getValue());
////                XML.popTag();
////            }
//            
//            void ComboBox::keyPressed( int key ) {
//            }
//            
//            int ComboBox::getValue() {
//                return selectedChoice;
//            }
//            
//            void ComboBox::setValue(int index) {
//                selectedChoice = ofClamp(index, 0, choices.size());
//            }
//            
//            void ComboBox::setValue(string title) {
//                setValue(getIndexForTitle(title));
//            }
//            
//            
//            //press was outside - handle.
//            void onPressOutside(int x, int y, int button)	{
//                
//            }
//            
//            void ComboBox::onPress(int x, int y, int button) {
//                //	beenPressed = true;
//                mouseMovedSinceClick=false;
//                //a click toggles focus state if we are off
//                if(!hasFocus) {
//                    //expand the height for all choices
//                    //      setSize(config->layout.gridSize.x - config->layout.padding.x, config->comboBoxHeight * choices.size());
//                    hasFocus = true;
//                    //notify that we want to steal all events from the parent
//                    parent->setActiveControl(this);
//                } else {
//                    //if we have focus, a click signals that we should lose it
//                    releaseEventStealingFocus();
//                }
//            }
//            
//            void ComboBox::onPressOutside(int x, int y, int button){
//                if(hasFocus)
//                    releaseEventStealingFocus();
//            }
//            
//            
//            void ComboBox::onDragOver(int x, int y, int button){
//                //same behavior as mouse move
//                onMouseMove(x,y);
//            }
//            
//            void ComboBox::onDragOutside(int x, int y, int button){
//                //same behavior as mouse move
//                onMouseMove(x,y);
//            }
//            
//            bool ComboBox::hitTest(int tx, int ty) {
//                if(!hasFocus)
//                    return ofxMSAInteractiveObject::hitTest(tx,ty);
//                
//                int fullheight = height + config->comboBoxTextHeight * choices.size();
//                
//                return ((tx > x) && (tx < x + width) && (ty > y) && (ty < y + fullheight));
//            }
//            
//            void ComboBox::onMouseMove(int x, int y) {
//                mouseMovedSinceClick=true;
//                if(hasFocus) {
//                    //see which index was selected.
//                    float fChoice = (y - (height - config->comboBoxTextHeight) - (this->y + config->comboBoxTextHeight))/config->comboBoxTextHeight;
//                    //TODO:replace with OF constrain macro.
//                    mouseChoice = fChoice < 0?-1:(fChoice>= choices.size()? -1:fChoice);
//                }
//            }
//            
//            void ComboBox::onReleaseOutside(int x, int y, int button) {
//                onRelease(x, y, button);
//            }
//            
//            void ComboBox::onRelease(int x, int y, int button) {
////                if(hasFocus && mouseMovedSinceClick) {
//                    releaseEventStealingFocus();
////                }
//            }
//            
//            void ComboBox::releaseEventStealingFocus(){
//                //see which index was selected, but only if the user actually moved around.
//                selectedChoice = mouseChoice >= 0? mouseChoice : selectedChoice;
//                
//                //a release toggles focus state if we are on - TODO: unless x and y don't change
//                hasFocus = false;
//                //      setSize(config->layout.gridSize.x - config->layout.padding.x, config->comboBoxHeight);
//                //also let the parent know we don't need to steal all the events and draw over anymore
//                parent->releaseActiveControl();
//            }
//            
//            //special overloads - this is a hack - later think about making Control's methods virtual.
//            void ComboBox::setCBTextColor() {
//                if(hasFocus) ofSetColor(config->colors.text[1]);
//                else ofSetColor(config->colors.text[0]);
//            }
//            
//            void ComboBox::setCBTextBGColor() {
//                if(hasFocus) ofSetColor(config->colors.bg[1]);
//                else ofSetColor(config->colors.bg[0]);
//            }
//            
//            
//#define kSGCBTriangleWidth   10
//#define KSGCBTrianglePadding 5
//#define kSGCBTextPaddingX    3
//#define kSGCBTextPaddingY    15
//            void ComboBox::draw(float x, float y) {
////                if(hasFocus) parent->setActiveControl(this);
//                
//                
//                //we assume a max of 256 characters.
//                char choiceBuf[256];
//                
//                setPos(x, y);
//                
//                glPushMatrix();
//                glTranslatef(x, y, 0);
//                
//                ofEnableAlphaBlending();
//                ofFill();
//                setBGColor();
//                ofRect(0, 0, width, height);
//                
//                setTextColor();
//                //	sprintf(choiceBuf, "%s: %s", title, choices.size() ? choices[selectedChoice] : "(No Choices Available)");
//                
//                config->drawString(title + ": " + (choices.size() ? choices[selectedChoice] : "N/A"), kSGCBTextPaddingX, kSGCBTextPaddingY);
//                //draw a combobox down triangle icon so the users know to click
//                ofTriangle(width - (kSGCBTriangleWidth + KSGCBTrianglePadding), kSGCBTextPaddingY/2,
//                           width - (KSGCBTrianglePadding), kSGCBTextPaddingY/2,
//                           width - (kSGCBTriangleWidth/2 + KSGCBTrianglePadding), kSGCBTextPaddingY);
//                
//                if(hasFocus) {
//                    setCBTextBGColor();
//                    ofRect(0, height, width, config->comboBoxTextHeight * (choices.size()+0.5));
//                    setTextColor();
//                    ofNoFill();
//                    ofRect(0, config->comboBoxHeight-1, width, config->comboBoxTextHeight * (choices.size()+0.5));
//                    ofFill();
////                    ofLine(0, config->comboBoxHeight-1, width, config->comboBoxHeight-1);
//                    
//                    for(int i=0; i < choices.size(); i++) {
//                        setCBTextColor();
//                        //invert for selected choice
//                        float curY = height + i*config->comboBoxTextHeight; 
//                        if(i==mouseChoice){
//                            //draw a text colored rect so we can see the inverse
//                            ofRect(0, curY+3, width, config->comboBoxTextHeight);
//                            setCBTextBGColor();
//                        }
//                        
//                        config->drawString(choices[i], kSGCBTextPaddingX, curY + kSGCBTextPaddingY);
//                    }
//                }
//                ofDisableAlphaBlending();
//                
//                glPopMatrix();
//            }
//            
//        }
//    }
//}
