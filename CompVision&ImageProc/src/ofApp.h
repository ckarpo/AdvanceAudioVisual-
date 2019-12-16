#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "imageProc.hpp"



class ofApp : public ofBaseApp{
    
public:
    ~ofApp();/* destructor is very useful */
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioOut     (float * input, int bufferSize, int nChannels); /* output method */
    void audioIn     (float * input, int bufferSize, int nChannels); /* input method */
    
    
    int        initialBufferSize; /* buffer size */
    int        sampleRate;
    
    ofVideoPlayer         myMovie;
    
    ofVideoGrabber        myGrabber;
    
    ofPixels pixels;
    
    ofPixels pixelout;
    
    ofPixels lastPixels;
    
    ofPixels blockpix;
    
    ofTexture myTexture,other;
    
    ofImage myImage;
    
    imageProc myImageProc;
    
    int mode;
    
    
    /* stick you maximilian stuff below */
    
    double osc, filtered,sample,outputs[2];
    maxiFilter filter1;
    ofxMaxiMix mymix;
    ofxMaxiOsc sine1;
    ofxMaxiSample beats,beat;
    int freq; 
    
    
};
