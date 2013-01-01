#pragma once

#include "ofxMSAControlFreak/src/gui/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            
            //            class Panel;
            
            class DropdownList : public ControlParameterT<ParameterNamedIndex> {
            public:
                
                DropdownList(Panel *parent, Parameter *p) : ControlParameterT<ParameterNamedIndex>(parent, p) {
                    //                    hasFocus=false;
                }
                
                
                //--------------------------------------------------------------
                //                void keyPressed( int key );
                
                //--------------------------------------------------------------
                //                void onPress(int x, int y, int button) {
                ////                    mouseMovedSinceClick=false;
                //                    //a click toggles focus state if we are off
                //                    if(!hasFocus) {
                //                        //expand the height for all choices
                //                        //      setSize(config->layout.gridSize.x - config->layout.padding.x, config->dropdownListHeight * choices.size());
                //                        hasFocus = true;
                //                        //notify that we want to steal all events from the parent
                ////                        parent->setActiveControl(this);
                //                    } else {
                //                        //if we have focus, a click signals that we should lose it
                //                        releaseEventStealingFocus();
                //                    }
                //                }
                
                //--------------------------------------------------------------
                //                void onRelease(int x, int y, int button) {
                //                    //                if(hasFocus && mouseMovedSinceClick) {
                ////                    releaseEventStealingFocus();
                //                    //                }
                //                }
                
                //--------------------------------------------------------------
                //                void onReleaseOutside(int x, int y, int button) {
                //                    onRelease(x, y, button);
                //                }
                
                //--------------------------------------------------------------
                //                void onPressOutside(int x, int y, int button) {
                //                    if(hasFocus)
                //                        releaseEventStealingFocus();
                //
                //                }
                
                //--------------------------------------------------------------
                //                void onMouseMove(int x, int y) {
                ////                    mouseMovedSinceClick=true;
                //                    if(hasFocus) {
                //                        //see which index was selected.
                //                        float fChoice = (y - (height - config->dropdownListTextHeight) - (this->y + config->dropdownListTextHeight))/config->dropdownListTextHeight;
                //                        //TODO:replace with OF constrain macro.
                //                        mouseChoice = fChoice < 0?-1:(fChoice>= choices.size()? -1:fChoice);
                //                    }
                //                }
                
                //--------------------------------------------------------------
                void onDragOver(int x, int y, int button) {
                    //                    onMouseMove(x,y);
                }
                
                //--------------------------------------------------------------
                //                void onDragOutside(int x, int y, int button) {
                //                    onMouseMove(x,y);
                //                }
                
                //--------------------------------------------------------------
                //                bool hitTest(int tx, int ty) {
                //                    if(!hasFocus)
                //                        return ofxMSAInteractiveObject::hitTest(tx,ty);
                //
                //                    int fullheight = height + config->dropdownListTextHeight * choices.size();
                //                    return ofInRange(tx, x, x + width) && ofInRange(ty, y, y + fullheight);
                //                    //                ((tx > x) && (tx < x + width) && (ty > y) && (ty < y + fullheight));
                //                }
                
                
#define kSGCBTriangleWidth   10
#define KSGCBTrianglePadding 5
#define kSGCBTextPaddingX    3
#define kSGCBTextPaddingY    15
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(!this->parameter) return;
                    
                    ofFill();
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    setTextColor();
                    //	sprintf(choiceBuf, "%s: %s", title, choices.size() ? choices[selectedChoice] : "(No Choices Available)");
                    
                    config->drawString(parameter->getName() + ": " + parameter->getSelectedLabel(), kSGCBTextPaddingX, kSGCBTextPaddingY);
                    //draw a combobox down triangle icon so the users know to click
                    ofTriangle(width - (kSGCBTriangleWidth + KSGCBTrianglePadding), kSGCBTextPaddingY/2,
                               width - (KSGCBTrianglePadding), kSGCBTextPaddingY/2,
                               width - (kSGCBTriangleWidth/2 + KSGCBTrianglePadding), kSGCBTextPaddingY);
                    
                    if(getState() == 2) {
                        int numLabels = parameter->getNumLabels();
                        setBGColor();
                        ofRect(0, height, width, config->layout.dropdownListTextHeight * (numLabels + 0.5));
                        
                        ofNoFill();
                        ofSetLineWidth(1);
                        setBorderColor();
                        ofRect(0, config->layout.buttonHeight-1, width, config->layout.dropdownListTextHeight * (numLabels + 0.5));

                        ofFill();
                        //                    ofLine(0, config->dropdownListHeight-1, width, config->dropdownListHeight-1);

                        for(int i=0; i < numLabels; i++) {
                            setTextColor();
                            //invert for selected choice
                            float curY = height + i*config->layout.dropdownListTextHeight;
                            //                        if(i==mouseChoice){
                            //draw a text colored rect so we can see the inverse
//                            ofRect(0, curY+3, width, config->layout.dropdownListTextHeight);
//                            setBGColor();
                            //                        }
                            
                            config->drawString(parameter->getLabel(i), kSGCBTextPaddingX, curY + kSGCBTextPaddingY);
                        }
                    }
                }
                
                
            protected:
//                void setCBTextColor() {
//                    //                    if(hasFocus) ofSetColor(config->colors.text[1]);
//                    //                    else
//                    ofSetColor(config->colors.text[0]);
//                }
//                
//                void setCBTextBGColor() {
//                    //                    if(hasFocus) ofSetColor(config->colors.bg[1]);
//                    //                    else
//                    ofSetColor(config->colors.bg[0]);
//                }
                
                //--------------------------------------------------------------
                void releaseEventStealingFocus() {
                    //see which index was selected, but only if the user actually moved around.
                    //                    selectedChoice = mouseChoice >= 0? mouseChoice : selectedChoice;
                    
                    //a release toggles focus state if we are on - TODO: unless x and y don't change
                    //                    hasFocus = false;
                    
                    //      setSize(config->layout.gridSize.x - config->layout.padding.x, config->dropdownListHeight);
                    //also let the parent know we don't need to steal all the events and draw over anymore
                    //                    parent->releaseActiveControl();
                }
                
                //                int            mouseChoice;
                //                bool           hasFocus;
                //                bool           mouseMovedSinceClick;
            };
            
        }
    }
}