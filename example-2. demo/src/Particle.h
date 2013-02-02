#pragma once

#include "ofMain.h"



class Particle {
public:
    ofVec2f pos;
    ofVec2f size;
    float rot;
    ofColor color;
    int index;
    
    void setup(int index) {
        this->index = index;
    }

    void update(float myTimer, ofVec2f maxSpread, ofVec2f maxSize) {
        // just some fancy math to make a bunch of stuff move around on screen
        float f = myTimer * 0.4 + 34.7324 + index * 258.60293;
        pos.set(ofGetWidth()/2 + ofSignedNoise(f + 7682.28476) * maxSpread.x, ofGetHeight()/2 + ofSignedNoise(f + 283.525) * maxSpread.y);
        size.set(ofSignedNoise(f*0.4+9273.442) * maxSize.x, ofSignedNoise(f*0.4+18363.5652) * maxSize.y);
        rot = ofSignedNoise(f * 0.3 + 193.56259) * 360;
        color.set(ofNoise(f+92.8274)*255, ofNoise(f+8723.34576)*255, ofNoise(f+4768.976)*255);
    }
    
    void draw(int shapeType) {
        ofPushMatrix();
        ofTranslate(pos);
        ofRotate(rot);
        ofScale(size.x, size.y);
        ofSetColor(color);
        
        // draw the shape depending on what is selected in the GUI (linked to the ParameterNamedIndex)
        switch(shapeType) {
            case 0:
                ofRect(0, 0, 1, 1);
                break;
                
            case 1:
                ofTriangle(0, -0.33, -0.33, 0.66, 0.33, 0.66);
                break;
                
            case 2:
                ofCircle(0, 0, 0.5);
                break;
        }
        ofPopMatrix();

    }
};
