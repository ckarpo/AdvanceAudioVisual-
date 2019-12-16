#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#include "maxiMFCC.h"

class ofApp : public ofBaseApp{

	public:
    ~ofApp();/* destructor very useful */
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;

    void keyReleased(int key) override;
    
    int threshold;
    int option;
    int offSet1, offSet2;
    
    /* audio stuff */
    void audioOut(ofSoundBuffer& output) override; //output method
    ofSoundStream soundStream;
    
    int  sampleRate;
    
    //MAXIMILIAN STUFF:
    double wave, sample, outputs[2], ifftVal;
    maxiMix mymix;
    maxiOsc osc;
    
    ofxMaxiFFTOctaveAnalyzer oct;
    int nAverages;
    float* ifftOutput;
    int ifftSize;
    
    float peakFreq = 0;
    float centroid = 0;
    float RMS = 0;
    
    ofxMaxiIFFT ifft;
    ofxMaxiFFT mfft;
    int fftSize;
    int bins, dataSize;
    
    maxiMFCC mfcc;
    double* mfccs;
    
    maxiSample samp, samp1;
    
    
    
};
